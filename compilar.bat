@echo off
rem ============================================================
rem  compilar.bat - Gera o compilador JABUTI no Windows
rem  Requisitos no PATH: win_flex, win_bison (WinFlexBison) e gcc (MinGW)
rem  (funciona tambem com "flex" e "bison" se estes estiverem instalados)
rem ============================================================
setlocal
rem  Parametro opcional: "sempausa" (nao espera uma tecla no final)
set SEMPAUSA=%~1
rem  Instalacao comum do MinGW (gcc, win_flex, win_bison): usada se nao estiver no PATH
if exist C:\MinGW\bin set PATH=%PATH%;C:\MinGW\bin
echo ============================================
echo  Compilando o JABUTI (Flex + Bison + GCC)
echo ============================================
echo.

set FLEX=win_flex
set BISON=win_bison

where %FLEX% >nul 2>nul
if errorlevel 1 set FLEX=flex
where %FLEX% >nul 2>nul
if errorlevel 1 goto sem_flex

where %BISON% >nul 2>nul
if errorlevel 1 set BISON=bison
where %BISON% >nul 2>nul
if errorlevel 1 goto sem_bison

where gcc >nul 2>nul
if errorlevel 1 goto sem_gcc

echo [1/3] %BISON% -d -v -o parser.tab.c src\parser.y
%BISON% -d -v -o parser.tab.c src\parser.y
if errorlevel 1 goto erro

echo [2/3] %FLEX% -o lex.yy.c src\lexer.l
%FLEX% -o lex.yy.c src\lexer.l
if errorlevel 1 goto erro

echo [3/3] gcc -Wall -Wextra -O2 -Isrc -I. -o jabuti.exe parser.tab.c lex.yy.c src\main.c src\simbolos.c src\gerador.c src\diagnostico.c
gcc -Wall -Wextra -O2 -Isrc -I. -o jabuti.exe parser.tab.c lex.yy.c src\main.c src\simbolos.c src\gerador.c src\diagnostico.c
if errorlevel 1 goto erro

echo.
echo ============================================
echo  Compilacao concluida com sucesso!
echo ============================================
echo.
dir /b parser.tab.c parser.tab.h parser.output lex.yy.c jabuti.exe
echo.
echo Para testar:  jabuti.exe -r exemplos\01_ola_mundo.jab
echo.
if /i not "%SEMPAUSA%"=="sempausa" pause
exit /b 0

:sem_flex
echo [ERRO] nem "win_flex" nem "flex" foram encontrados no PATH.
goto fim_erro
:sem_bison
echo [ERRO] nem "win_bison" nem "bison" foram encontrados no PATH.
goto fim_erro
:sem_gcc
echo [ERRO] "gcc" nao foi encontrado no PATH.
goto fim_erro
:erro
echo.
echo [ERRO] Falha em uma das etapas acima. Veja a mensagem de erro.
:fim_erro
if /i not "%SEMPAUSA%"=="sempausa" pause
exit /b 1
