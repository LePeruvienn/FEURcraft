@echo off
setlocal
set "OBJ_DIR=obj"
set "BIN_DIR=bin"
set "BUILD_DIR=build"

if /I "%~1"=="" goto compile

if /I "%~1"=="compile" goto compile
if /I "%~1"=="configure" goto configure
if /I "%~1"=="clean" goto clean

echo Unknown command: %~1
echo Usage: %~nx0 compile^|configure^|clean
exit /b 1

:compile
if not exist "%OBJ_DIR%\" mkdir "%OBJ_DIR%"
if not exist "%BIN_DIR%\" mkdir "%BIN_DIR%"

if not exist "%BUILD_DIR%\" (
    call :configure
    if errorlevel 1 exit /b 1
)

cmake --build "%BUILD_DIR%"
exit /b %errorlevel%


:configure
cmake -B "%BUILD_DIR%"
exit /b %errorlevel%


:clean
if exist "%OBJ_DIR%\" (
    rmdir /S /Q "%OBJ_DIR%"
    echo %OBJ_DIR% deleted.
)
if exist "%BIN_DIR%\" (
    rmdir /S /Q "%BIN_DIR%"
    echo %BIN_DIR% deleted.
)
if exist "%BUILD_DIR%\" (
    rmdir /S /Q "%BUILD_DIR%"
    echo %BUILD_DIR% deleted.
)
exit /b 0
