@echo off
setlocal EnableDelayedExpansion

REM ######################################
REM
REM         TEST LAUNCHER
REM
REM run_test              -> Run all tests
REM run_test test1 test2  -> Run selected tests
REM run_test -X           -> Show test stdout
REM
REM ######################################

set "SCRIPT_DIR=%~dp0"
set "BIN_DIR=%SCRIPT_DIR%..\bin"

set "ASSETS_DIR=%SCRIPT_DIR%assets"
set "OUT_DIR=%SCRIPT_DIR%out"

set "STDOUT_ON=0"
set "FILE_AMOUNT=0"
set "TEST_AMOUNT=0"
set "KO_AMOUNT=0"

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

set "RED=%ESC%[31m"
set "GREEN=%ESC%[32m"
set "YELLOW=%ESC%[33m"
set "CYAN=%ESC%[36m"
set "BOLD=%ESC%[1m"
set "NC=%ESC%[0m"

if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

:parse_args
if "%~1"=="" goto run_tests

if "%~1"=="-X" (
    set "STDOUT_ON=1"
    set "FEUR_Tests_Enable_Minimal_Output=1"
    shift
    goto parse_args
)

if "%~1"=="-h" goto help
if "%~1"=="--help" goto help

echo %RED%Unknown option: %~1%NC%
exit /b 1


:help
echo Usage: %~nx0 [-X] [tests...]
echo.
echo   run_test              Run all tests
echo   run_test test1 test2  Run specified tests
echo   run_test -X           Show test stdout
exit /b 0


:run_tests

echo.
echo __________________________ _____________  ___________              __   
echo \_   _____/\_   _____/    ^|   \______   \ \__    ___/___   _______/  ^|_ 
echo  ^|    __)   ^|    __)_^|    ^|   /^|       _/   ^|    ^|_/ __ \ /  ___/\   __\
echo  ^|     \    ^|        \    ^|  / ^|    ^|   \   ^|    ^|\  ___/ \___ \  ^|  ^|  
echo  \___  /   /_______  /______/  ^|____^|_  /   ^|____^| \___  ^>____  ^> ^|__^|  
echo      \/            \/                 \/               \/     \/        

echo.
echo %BOLD%%CYAN%========== Running tests ==========%NC%
echo.


REM No arguments: run all .tst files
if "%FILE_AMOUNT%"=="0" (

    for %%F in ("%BIN_DIR%\*.tst.exe") do (
        call :run_test "%%F"
    )

    for %%F in ("%BIN_DIR%\Debug\*.tst.exe") do (
        call :run_test "%%F"
    )

    for %%F in ("%BIN_DIR%\Release\*.tst.exe") do (
        call :run_test "%%F"
    )


    goto summary
)

goto summary


:run_test
set "TEST_FILE=%~1"
for %%A in ("%TEST_FILE%") do set "TEST_NAME=%%~nxA"

if not exist "%TEST_FILE%" (
    echo "%YELLOW%[SKIP]%NC% !TEST_NAME! (not found)"
    exit /b
)

if "%STDOUT_ON%"=="1" (
    "%TEST_FILE%"
) else (
    "%TEST_FILE%" >nul 2>&1
)

set "STATUS=!ERRORLEVEL!"

set /a TEST_AMOUNT+=1

if "!STATUS!"=="0" (
    echo %BLUE%[ !TEST_NAME! ]%NC% : %GREEN%OK%NC%
) else (
    echo %BLUE%[ !TEST_NAME! ]%NC% : %RED%FAILED%NC% (code !STATUS!)
    set /a KO_AMOUNT+=1
)

exit /b

:summary

echo "TEST_AMOUNT = %TEST_AMOUNT%"
echo "KO_AMOUNT = %KO_AMOUNT%"

set /a PASSED=TEST_AMOUNT-KO_AMOUNT

echo.
echo            SUMMARY CAN BE BUGGED
echo %BOLD%============== Summary ==============%NC%
echo %GREEN%Passed%NC% : %PASSED%
echo %RED%Failed%NC% : %KO_AMOUNT%
echo Total : %TEST_AMOUNT%
echo.

if "%TEST_AMOUNT%"=="0" (
    echo %BOLD%Aucun test trouve :(%NC%
    echo Aucun binaire .tst dans %BIN_DIR%
    echo Essaye de compiler d'abord.
    exit /b 0
)

if "%KO_AMOUNT%"=="0" (
    echo %GREEN%OK - Juste le GOAT en fait B^)%NC%
) else if "%KO_AMOUNT%"=="%TEST_AMOUNT%" (
    echo %RED%FAILED - Tous les tests ont echoue :( %NC%
) else (
    echo %YELLOW%Quelques tests ont echoue.%NC%
)

exit /b 0