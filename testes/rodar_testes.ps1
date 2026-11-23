# ============================================================
# Bateria de testes do compilador JABUTI no Windows (equivalente
# ao testes/rodar_testes.sh do Linux).
#  - exemplos\*.jab  : devem compilar, gerar C valido e produzir a
#                      saida registrada em <nome>.saida
#  - testes\erro_*   : devem FALHAR (codigo 1) e emitir as mensagens
#                      listadas em <nome>.esperado
#  - testes\avisos   : compila com sucesso, mas com 3 avisos
#  - divisao por zero: erro em tempo de execucao (codigo 1)
# Uso: rodar_testes.bat   (a partir da pasta do projeto)
# ============================================================
$raiz = Split-Path -Parent $PSScriptRoot
Set-Location $raiz
$tmp = Join-Path $env:TEMP 'jabuti_testes'
New-Item -ItemType Directory -Force -Path $tmp | Out-Null
$ok = 0; $falhas = 0
$utf8 = New-Object System.Text.UTF8Encoding($false)

function Passou($m) { Write-Host "  [OK]    $m"; $script:ok++ }
function Falhou($m) { Write-Host "  [FALHA] $m"; $script:falhas++ }

# executa uma linha de comando do cmd, grava a saida em $log e devolve o codigo de saida
function Exec([string]$linha, [string]$log) {
    $c = Join-Path $tmp 'exec.cmd'
    [System.IO.File]::WriteAllText($c, "@echo off`r`n$linha > `"$log`" 2>&1`r`nexit /b %errorlevel%`r`n")
    & cmd.exe /c $c
    return $LASTEXITCODE
}
function Texto([string]$arq) {
    if (-not (Test-Path $arq)) { return '' }
    return ([System.IO.File]::ReadAllText($arq, $utf8)) -replace "`r`n", "`n"
}

$log = Join-Path $tmp 'log.txt'
$gcc = Join-Path $tmp 'gcc.txt'
$sai = Join-Path $tmp 'saida.txt'

Write-Host "== Programas validos (exemplos/) =="
foreach ($f in Get-ChildItem 'exemplos\*.jab' | Sort-Object Name) {
    $b = $f.FullName -replace '\.jab$', ''
    $nome = "exemplos/" + $f.Name
    if ((Exec ".\jabuti.exe `"$($f.FullName)`"" $log) -ne 0) { Falhou "$nome (erro ao compilar)"; continue }
    if ((Exec "gcc -Wall -Werror -o `"$b.exe`" `"$b.c`"" $gcc) -ne 0) { Falhou "$nome (C gerado nao compila)"; continue }
    if (Test-Path "$b.entrada") { [void](Exec "`"$b.exe`" < `"$b.entrada`"" $sai) }
    else { [void](Exec "`"$b.exe`"" $sai) }
    if ((Texto $sai) -ceq (Texto "$b.saida")) { Passou $nome } else { Falhou "$nome (saida diferente da esperada)" }
}

Write-Host "== Programas com erros (testes/erro_*) =="
foreach ($f in Get-ChildItem 'testes\erro_*.jab' | Sort-Object Name) {
    $b = $f.FullName -replace '\.jab$', ''
    $nome = "testes/" + $f.Name
    $rc = Exec ".\jabuti.exe `"$($f.FullName)`"" $log
    if ($rc -ne 1) { Falhou "$nome (esperava codigo 1, veio $rc)"; continue }
    if (Test-Path "$b.c") { Falhou "$nome (gerou C apesar dos erros)"; continue }
    $saida = Texto $log
    $faltou = $false
    foreach ($linha in (Texto "$b.esperado").Split("`n")) {
        if ($linha.Trim() -eq '') { continue }
        if (-not $saida.Contains($linha)) { $faltou = $true; Write-Host "         faltou: $linha" }
    }
    if ($faltou) { Falhou "$nome (mensagens esperadas ausentes)" } else { Passou $nome }
}

Write-Host "== Avisos =="
$rc = Exec ".\jabuti.exe testes\avisos.jab" $log
$n = @((Texto $log).Split("`n") | Where-Object { $_.StartsWith('[AVISO]') }).Count
if ($rc -eq 0 -and $n -eq 3) { Passou "testes/avisos.jab (3 avisos, compilou)" }
else { Falhou "testes/avisos.jab (rc=$rc, avisos=$n)" }

Write-Host "== Erro de execucao (divisao por zero) =="
[void](Exec ".\jabuti.exe testes\execucao_divisao_zero.jab" $log)
[void](Exec "gcc -o testes\execucao_divisao_zero.exe testes\execucao_divisao_zero.c" $gcc)
$rc = Exec "testes\execucao_divisao_zero.exe < testes\execucao_divisao_zero.entrada" $sai
if ($rc -eq 1 -and (Texto $sai).Contains('divisao por zero')) { Passou "execucao_divisao_zero (codigo 1 + mensagem)" }
else { Falhou "execucao_divisao_zero (rc=$rc)" }

Write-Host ""
Write-Host "Resultado: $ok teste(s) OK, $falhas falha(s)."
if ($falhas -eq 0) { exit 0 } else { exit 1 }
