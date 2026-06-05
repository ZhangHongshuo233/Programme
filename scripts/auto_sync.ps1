param(
    [string]$Branch = "",
    [switch]$Silent
)

if ([string]::IsNullOrEmpty($PSScriptRoot)) {
    Write-Error "ERROR: Please run this script as a file instead of pasting into terminal."
    exit 1
}

$RepoPath = (Resolve-Path "$PSScriptRoot\..").Path
Set-Location $RepoPath

$LogFile = Join-Path $RepoPath ".git\auto_sync.log"
$LockFile = Join-Path $RepoPath ".git\auto_sync.lock"
$GitIndexLockFile = Join-Path $RepoPath ".git\index.lock"

function Write-Log($Message) {
    $Timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $Line = "[$Timestamp] $Message"
    if (-not $Silent) {
        Write-Output $Line
    }
    $Line | Out-File -FilePath $LogFile -Append
}

function Exit-WithLog($Message) {
    Write-Log $Message
    exit 1
}

function Run-GitCommand {
    param(
        [string[]]$Arguments,
        [string]$ErrorMessage
    )

    try {
        $Output = & $script:GitExe @Arguments 2>&1
        if ($LASTEXITCODE -ne 0) {
            $OutputText = ($Output | Out-String).Trim()
            Exit-WithLog "$ErrorMessage Output: $OutputText"
        }
        return $Output
    }
    catch {
        Exit-WithLog "$ErrorMessage Exception: $($_.Exception.Message)"
    }
}

if (-not (Test-Path ".git")) {
    Exit-WithLog "ERROR: Not a git repository: $RepoPath"
}

$GitExe = $null
$GitCommand = Get-Command git -ErrorAction SilentlyContinue
if ($GitCommand) {
    $GitExe = $GitCommand.Source
}

if (-not $GitExe) {
    $GitCandidates = @(
        "$env:ProgramFiles\\Git\\cmd\\git.exe",
        "$env:ProgramFiles\\Git\\bin\\git.exe",
        "$env:ProgramFiles(x86)\\Git\\cmd\\git.exe",
        "$env:LocalAppData\\Programs\\Git\\cmd\\git.exe"
    )

    foreach ($Candidate in $GitCandidates) {
        if (Test-Path $Candidate) {
            $GitExe = $Candidate
            break
        }
    }
}

if (-not $GitExe) {
    Exit-WithLog "ERROR: git executable not found. Please install Git for Windows and ensure git.exe is available."
}

$script:GitExe = $GitExe
Write-Log "Using git executable: $GitExe"

# Ensure background task never opens credential prompts.
$env:GIT_TERMINAL_PROMPT = "0"

if (Test-Path $LockFile) {
    Write-Log "SKIP: Previous auto sync process is still running."
    exit 0
}

if (Test-Path $GitIndexLockFile) {
    Write-Log "SKIP: .git/index.lock exists. Another git process may still be active or a stale lock needs cleanup."
    exit 0
}

New-Item -ItemType File -Path $LockFile -Force | Out-Null

try {
    # Automatically use the current branch when no branch is provided.
    if ([string]::IsNullOrWhiteSpace($Branch)) {
        $Branch = (Run-GitCommand -Arguments @("branch", "--show-current") -ErrorMessage "ERROR: Unable to detect current branch.").Trim()
    }

    if ([string]::IsNullOrWhiteSpace($Branch)) {
        Exit-WithLog "ERROR: Unable to determine the current branch."
    }

    # 1) Commit local modifications.
    $Status = Run-GitCommand -Arguments @("status", "--porcelain") -ErrorMessage "ERROR: git status failed."
    if ($Status) {
        Run-GitCommand -Arguments @("add", "-A") -ErrorMessage "ERROR: git add failed." | Out-Null

        & $GitExe diff --cached --quiet
        if ($LASTEXITCODE -eq 0) {
            Write-Log "No staged changes after git add; skipping commit."
        }
        else {
        $CommitTime = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
        $CommitOutput = & $GitExe commit -m "chore(auto-sync): auto snapshot at $CommitTime" 2>&1
        if ($LASTEXITCODE -ne 0) {
            Exit-WithLog "ERROR: git commit failed. Output: $((($CommitOutput | Out-String).Trim()))"
        }
            Write-Log "Local changes committed."
        }
    } else {
        Write-Log "No local changes detected."
    }

    # 2) Rebase onto latest remote branch. Abort immediately on conflict.
    Run-GitCommand -Arguments @("fetch", "origin", $Branch) -ErrorMessage "ERROR: git fetch failed." | Out-Null

    & $GitExe rebase "origin/$Branch" *>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) {
        Write-Log "WARNING: Rebase conflict detected. Aborting to protect repository."
        & $GitExe rebase --abort *>&1 | Out-Null
        exit 1
    }

    # 3) Push to remote.
    & $GitExe push origin $Branch *>&1 | Out-Null
    if ($LASTEXITCODE -ne 0) {
        Exit-WithLog "ERROR: git push failed. Network issue or rejected."
    }

    Write-Log "SUCCESS: Auto sync completed."
}
finally {
    if (Test-Path $LockFile) {
        Remove-Item $LockFile -Force -ErrorAction SilentlyContinue
    }
}