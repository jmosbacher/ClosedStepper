@echo off
set LIB_NAME=ClosedStepper
:: Make Arduino library directory (and parent directories, if necessary).
setlocal enableextensions
md "%PREFIX%"\Library\include\Arduino\%LIB_NAME%
endlocal

:: Copy library source files into Arduino library directory.
xcopy /S /Y /I /Q "%SRC_DIR%" "%PREFIX%"\Library\include\Arduino\%LIB_NAME%
del "%PREFIX%"\Library\include\Arduino\%LIB_NAME%\bld.bat
if errorlevel 1 exit 1
