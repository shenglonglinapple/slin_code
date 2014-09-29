@echo off

REM user set param
set CURRENT_DIR=%~dp0
set SUB_LOG_DIR=%~dp0\ALL_LOG_PATH\

echo "CURRENT_DIR=%CURRENT_DIR%"
echo "SUB_LOG_DIR=%SUB_LOG_DIR%"


REM del DLL File
del %CURRENT_DIR%\*.log
del %SUB_LOG_DIR%\*.log



REM pause   /* pause */
REM pause



