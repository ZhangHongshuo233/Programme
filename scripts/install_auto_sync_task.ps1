param(
    [string]$TaskName = "ProgrammeGitAutoSync",
    [string]$RepoPath = "C:\Users\Lenovo\Desktop\programme",
    [int]$IntervalMinutes = 5
)

$ErrorActionPreference = "Stop"

$scriptPath = Join-Path $RepoPath "scripts\auto_sync.ps1"
if (-not (Test-Path $scriptPath)) {
    Write-Error "Sync script not found: $scriptPath"
    exit 1
}

$taskCommand = "powershell.exe -NoProfile -ExecutionPolicy Bypass -File `"$scriptPath`""
$createArgs = @(
    "/Create",
    "/SC", "MINUTE",
    "/MO", "$IntervalMinutes",
    "/TN", "$TaskName",
    "/TR", "$taskCommand",
    "/F"
)

schtasks.exe $createArgs | Out-Null

Write-Output "Task installed: $TaskName (every $IntervalMinutes minutes)"
