rem compiling options



@echo off


rem if not exist z88dkenv.bat (
rem   echo.
rem  echo Error: z88dkenv.bat doesn't exist. Please copy it into this folder.
rem   exit /b 1
rem )



echo #########################
echo #### remove old TAP  ####
echo #########################
del game.tap



echo #########################
echo ## compile with        ##
echo ##    FASE GFX         ##
echo #########################


echo #########################
echo #### setting paths   ####
echo #########################
rem /////////////////////////////////////////////////
SET PATH=%PATH%;c:\z88dk10
SET Z80_OZFILES=C:\z88dk10\lib
SET ZCCCFG=C:\z88dk10\lib\config
SET PATH=C:\z88dk10\bin;%PATH%
SET Z88DK_ENV_id074741=true
rem /////////////////////////////////////////////////



rem pause

if "%1"=="gfx" (
  lib\bin\Png2Rcs gfx\loading.png build\loading.rcs build\loading.atr
  lib\bin\zx7b build\loading.rcs build\loading.rcs.zx7b
  lib\bin\zx7b build\loading.atr build\loading.atr.zx7b
rem  lib\bin\GenTmx 3 3 10 10 gfx\map.tmx
  lib\bin\TmxCompress gfx\map.tmx build\map_compressed.bin > build\defmap.asm
  lib\bin\sjasmplus asm\player.asm > nul
  lib\bin\zx7b build\player.bin build\player.zx7b
  lib\bin\xm2tritone mus\music.xm build\music.asm
  lib\bin\step1
  lib\bin\sjasmplus asm\music.asm > nul
  lib\bin\zx7b build\music.bin build\music.zx7b
  goto cont
)

echo ######################
echo ##graphics and sound##
echo ######################

if "%1"=="config" (
:cont
  lib\bin\sjasmplus asm\engine0.asm > nul
  lib\bin\sjasmplus asm\engine1.asm > nul
  lib\bin\sjasmplus asm\engine2.asm > nul
  lib\bin\step2
  lib\bin\zx7b build\block1.bin build\block1.zx7b
  lib\bin\zx7b build\block2.bin build\block2.zx7b
)
echo.

echo ##################
echo ##    engine    ##
echo ##################

rem pause

rem cls

rem call z88dkenv.bat

echo #######################
echo ## ready to compiled ##
echo #######################

zcc +zx -zorg=32772 -O3 -vn main.c -o build\main.bin -lndos

echo ######################################
echo ##File main.bin compiled from main.c##
echo ######################################
echo ################
echo ##compiled....##
echo ################
rem pause


lib\bin\zx7b build\main.bin build\main.zx7b
lib\bin\step3
lib\bin\sjasmplus asm\loader.asm

if exist build\player.zx7b (
  lib\bin\gentape game.tap                    ^
            basic 'game' 0  build\loader.bin  ^
             data           build\engine.zx7b ^
             data           build\player.zx7b
) else (
  lib\bin\gentape game.tap                    ^
            basic 'game' 0  build\loader.bin  ^
             data           build\engine.zx7b
)

REM to build a TZX instead
rem
rem if exist build\player.zx7b (
rem  lib\bin\gentape game.tzx                    ^
rem            basic 'game' 0  build\loader.bin  ^
rem             data           build\engine.zx7b ^
rem           stop48                             ^
rem             data           build\player.zx7b
rem ) else (
rem   lib\bin\gentape game.tzx                    ^
rem             basic 'game' 0  build\loader.bin  ^
rem              data           build\engine.zx7b
rem )
rem

echo #################
echo ## making tape ##
echo #################