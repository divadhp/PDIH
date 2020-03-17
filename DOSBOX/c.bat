@echo off
REM Espera el nombre de un fichero con código ensamblador
REM Solo necesita un nombre, sin extensión

if "%1" == "" goto :error_parametros
if NOT EXIST "%1.asm" goto :error_parametros

TASM /zi %1.asm
TLINK /v %1.obj

goto :fin

:error_parametros
    echo ERROR: Parámetro incorrecto

:fin
