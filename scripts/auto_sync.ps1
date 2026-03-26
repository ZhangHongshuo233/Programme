param(
    [string]$RepoPath = "C:\Users\Lenovo\Desktop\programme",
    [string]$Branch = "main"
)

$ErrorActionPreference = "Stop"

if (-not (Test-Path $RepoPath)) {
    Write-Error "Repo path not found: $RepoPath"
    exit 1
}

Set-Location $RepoPath

if (-not (Test-Path ".git")) {
    Write-Error "Not a git repository: $RepoPath"
    exit 1
}

git fetch origin $Branch
if ($LASTEXITCODE -ne 0) {
    Write-Error "git fetch failed"
    exit 1
}

$status = git status --porcelain
if ($status) {
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"

    git add -A
    if ($LASTEXITCODE -ne 0) {
        Write-Error "git add failed"
        exit 1
    }

    git commit -m "chore(auto-sync): snapshot $timestamp"
    if ($LASTEXITCODE -ne 0) {
        Write-Error "git commit failed"
        exit 1
    }
} else {
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    Write-Output "No local changes at $timestamp."
}

git rebase "origin/$Branch"
if ($LASTEXITCODE -ne 0) {
    Write-Error "git rebase failed, manual conflict resolution required"
    exit 1
}

git push origin $Branch
if ($LASTEXITCODE -ne 0) {
    Write-Error "git push failed"
    exit 1
}

Write-Output "Auto sync completed at $timestamp"
