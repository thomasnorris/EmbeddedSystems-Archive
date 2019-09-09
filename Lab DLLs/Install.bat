::----------------------------
:: This installs the project DLLs
::----------------------------

@echo off

echo Installing... TexaS Dlls

xcopy "..\Lab dlls\ARM" "..\..\ARM" /s /e /i

echo Install Complete!

pause