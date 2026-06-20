@echo off
setlocal

rem Clean Keil build output files for MSPM0G3507_Template.
rem This script only removes compiler/linker outputs and keeps source files,
rem SysConfig files, documents, and project settings.

set "PROJECT_DIR=%~dp0"
set "KEIL_DIR=%PROJECT_DIR%keil"

echo Cleaning build outputs...
echo Project: %PROJECT_DIR%
echo.

if exist "%KEIL_DIR%\Objects" (
    echo Removing: %KEIL_DIR%\Objects
    rmdir /s /q "%KEIL_DIR%\Objects"
)

if exist "%KEIL_DIR%\Listings" (
    echo Removing: %KEIL_DIR%\Listings
    rmdir /s /q "%KEIL_DIR%\Listings"
)

for %%F in (
    "%KEIL_DIR%\*.map"
    "%KEIL_DIR%\*.lst"
    "%KEIL_DIR%\*.lnp"
    "%KEIL_DIR%\*.htm"
    "%KEIL_DIR%\*.build_log.htm"
    "%KEIL_DIR%\*.crf"
    "%KEIL_DIR%\*.dep"
    "%KEIL_DIR%\*.axf"
    "%KEIL_DIR%\*.hex"
    "%KEIL_DIR%\*.bin"
) do (
    if exist %%F (
        echo Removing: %%F
        del /f /q %%F
    )
)

echo.
echo Clean complete.
pause
