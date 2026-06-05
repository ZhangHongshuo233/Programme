param(
    [string]$TaskName = "ProgrammeGitAutoSync",
    [int]$IntervalMinutes = 5,
    [switch]$RunNow
)

$ErrorActionPreference = "Stop"

if ([string]::IsNullOrEmpty($PSScriptRoot)) {
    Write-Error "ERROR: Please do not paste code into terminal directly! Run the script file instead."
    exit 1
}

$SyncScriptPath = Join-Path $PSScriptRoot "auto_sync.ps1"

if (-not (Test-Path $SyncScriptPath)) {
    Write-Error "ERROR: Cannot find auto_sync.ps1 at $SyncScriptPath"
    exit 1
}

$TaskCommand = "powershell.exe -NoLogo -NoProfile -NonInteractive -WindowStyle Hidden -ExecutionPolicy Bypass -File `"$SyncScriptPath`" -Silent"
$CreateArgs = @(
    "/Create",
    "/SC", "MINUTE",
    "/MO", "$IntervalMinutes",
    "/TN", "$TaskName",
    "/TR", "$TaskCommand",
    "/RL", "LIMITED",
    "/F"
)

schtasks.exe $CreateArgs | Out-Null

if ($RunNow) {
    schtasks.exe /Run /TN "$TaskName" | Out-Null
}

Write-Output "========================================"
Write-Output "Auto Sync Task Installed Successfully!"
Write-Output "Task Name: $TaskName"
Write-Output "Interval: Every $IntervalMinutes Minutes"
if ($RunNow) {
    Write-Output "Run Once: Triggered immediately"
}
Write-Output "Log Path: programme/.git/auto_sync.log"
Write-Output "========================================" 