@echo off

REM user set param
set CURRENT_DIR=%~dp0
set ClientDB_DIR=%~dp0\ClientDB
set ServerDB_DIR=%~dp0\ServerDB

echo "CURRENT_DIR=%CURRENT_DIR%"
echo "ClientDB_DIR=%ClientDB_DIR%"
echo "ServerDB_DIR=%ServerDB_DIR%"


REM del DLL File
del %ClientDB_DIR%\*.db*
del %ServerDB_DIR%\*.db*



REM pause   /* pause */
REM pause



