@echo off
setlocal
setlocal EnableDelayedExpansion

set "BIN_DIR=bin"

if "%~1"=="" (
    echo Usage: run ^<program^> [arguments...]
    
    set "PROGRAM_COUNT=0"

    set "FOUND=0"
    for /R "%BIN_DIR%" %%F in (*.tst.exe) do (

        if "!FOUND!"=="0" (
            echo.
            echo [TESTS]
            set "FOUND=1"
        )

        echo   %%~nF
        set /A PROGRAM_COUNT+=1
    )
    set "FOUND=0"
    for /R "%BIN_DIR%" %%F in (*.ex.exe) do (

        if "!FOUND!"=="0" (
            echo.
            echo [EXAMPLES]
            set "FOUND=1"
        )

        echo   %%~nF
        set /A PROGRAM_COUNT+=1
    )
    set "FOUND=0"
    for /R "%BIN_DIR%" %%F in (*.exe) do (

        if "!FOUND!"=="0" (
            echo.
            echo [OTHER]
            set "FOUND=1"
        )

        set "FILE=%%~nxF"

        set "NAME=!FILE:~0,-4!"
        set "TST=!NAME:~-4!"
        set "EX=!NAME:~-3!"

        if /I not "!TST!"==".tst" (
            if /I not "!EX!"==".ex" (
                echo   !NAME!
                set /A PROGRAM_COUNT+=1
            )
        )
    )
    echo.

    if !PROGRAM_COUNT! EQU 0 (
        echo No programs found in "%BIN_DIR%" try compiling first.
    ) else (
        echo !PROGRAM_COUNT! program^(s^) found.
    )

    exit /b 1
)


set "PROGRAM=%~1"

echo Searching for "%PROGRAM%" in "%BIN_DIR%"...

for /R "%BIN_DIR%" %%F in (*) do (

    if /I "%%~nxF"=="%PROGRAM%.exe" (
        echo Found: %%F
        echo Running...

        shift
        "%%F" %*

        exit /b %errorlevel%
    )
    if /I "%%~nxF"=="%PROGRAM%.ex.exe" (
        echo Found: %%F
        echo Running...

        shift
        "%%F" %*

        exit /b %errorlevel%
    )
    if /I "%%~nxF"=="%PROGRAM%.tst.exe" (
        echo Found: %%F
        echo Running...

        shift
        "%%F" %*

        exit /b %errorlevel%
    )
)

echo ERROR: "%PROGRAM%" not found in "%BIN_DIR%".
exit /b 1
