@echo off
setlocal

set "BIN_DIR=bin"

if "%~1"=="" (
    echo Usage: run ^<program^> [arguments...]
    exit /b 1
)

set "PROGRAM=%~1"

if /I not "%PROGRAM:~-4%"==".exe" (
    set "PROGRAM=%PROGRAM%.exe"
)

echo Searching for "%PROGRAM%" in "%BIN_DIR%"...

for /R "%BIN_DIR%" %%F in (*) do (
    if /I "%%~nxF"=="%PROGRAM%" (
        echo Found: %%F
        echo Running...

        shift
        "%%F" %*

        exit /b %errorlevel%
    )
)

echo ERROR: "%PROGRAM%" not found in "%BIN_DIR%".
exit /b 1
