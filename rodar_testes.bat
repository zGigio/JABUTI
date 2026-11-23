@echo off
rem ============================================================
rem  rodar_testes.bat - Bateria de testes automaticos do JABUTI
rem  (equivalente ao "make teste" do Linux). Use depois de
rem  compilar.bat. Parametro opcional: sempausa
rem ============================================================
setlocal
chcp 65001 >nul
cd /d "%~dp0"
if exist C:\MinGW\bin set PATH=%PATH%;C:\MinGW\bin
if not exist jabuti.exe (
    echo [ERRO] jabuti.exe nao encontrado. Rode compilar.bat primeiro.
    pause
    exit /b 1
)
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0testes\rodar_testes.ps1"
set RC=%errorlevel%
if /i not "%~1"=="sempausa" pause
exit /b %RC%
