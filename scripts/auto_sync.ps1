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

$status = git status --porcelain
if (-not $status) {
    Write-Output "No changes. Skip sync."
    exit 0
}

$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"

git add -A
git commit -m "chore(auto-sync): snapshot $timestamp"

git push origin $Branch
Write-Output "Auto sync completed at $timestamp"
