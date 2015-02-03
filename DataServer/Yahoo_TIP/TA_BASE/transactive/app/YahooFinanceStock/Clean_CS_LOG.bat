@echo off

REM user set param
set CURRENT_DIR=%~dp0
set YahooFinanceStockClient_DIR=%~dp0\YahooFinanceStockClient
set YahooFinanceAutoClient_DIR=%~dp0\YahooFinanceAutoClient
set YahooFinanceStockServer_DIR=%~dp0\YahooFinanceStockServer

echo "CURRENT_DIR=%CURRENT_DIR%"
echo "YahooFinanceStockClient_DIR=%YahooFinanceStockClient_DIR%"
echo "YahooFinanceAutoClient_DIR=%YahooFinanceAutoClient_DIR%"
echo "YahooFinanceStockServer_DIR=%YahooFinanceStockServer_DIR%"


REM del DLL File
del %YahooFinanceStockClient_DIR%\*.log*
del %YahooFinanceAutoClient_DIR%\*.log*
del %YahooFinanceStockServer_DIR%\*.log*



REM pause   /* pause */
REM pause



