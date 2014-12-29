@echo off
set OUTPUT_PATH=C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\TA_APP\transactive\app\SmartTrader\SmartTraderQT\bat\
set ROOT_BASE=C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\TA_APP\transactive\app\SmartTrader\SmartTraderQT\src
cd %ROOT_BASE%
for %%i in (*.h *.java) do echo "%%i">>%ROOT_BASE%\fileclass.txt
@echo "done"
pause
