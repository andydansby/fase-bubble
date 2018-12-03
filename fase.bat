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
SET PATH=%PATH%;C:\z88dk10
SET Z80_OZFILES=C:\z88dk10\lib
SET ZCCCFG=C:\z88dk10\lib\config
SET PATH=C:\z88dk10\bin;%PATH%
SET Z88DK_ENV_id074741=true
rem /////////////////////////////////////////////////

echo #########################
echo ## done setting paths  ##
echo #########################
rem pause


if "%1"=="gfx" (

  lib\bin\Png2Rcs gfx\loading.png build\loading.rcs build\loading.atr
  lib\bin\zx7b build\loading.rcs build\loading.rcs.zx7b
  lib\bin\zx7b build\loading.atr build\loading.atr.zx7b
  
rem copy mus\music.asm build\music.asm 

  lib\bin\png2rcs gfx\menu.png build\menu.rcs build\menu.atr  
  lib\bin\zx7b build\menu.rcs build\menu.rcs.zx7b
  lib\bin\zx7b build\menu.atr build\menu.atr.zx7b
  
  
  lib\bin\Png2Rcs gfx\control.png build\control.rcs build\control.atr
  lib\bin\zx7b build\control.rcs build\control.rcs.zx7b
  lib\bin\zx7b build\control.atr build\control.atr.zx7b

rem  lib\bin\GenTmx 3 3 10 10 gfx\map.tmx

  lib\bin\TmxCompress gfx\map.tmx build\map_compressed.bin > build\defmap.asm

  echo #########################
  echo ##        MUSIC        ##
  echo #########################

  rem 128k only music
rem  lib\bin\sjasmplus asm\player.asm > nul
rem  lib\bin\zx7b build\player.bin build\player.zx7b
  
  rem push music data (notes) to the build directory
rem  lib\bin\xm2tritone mus\music.xm build\music.asm
  copy mus\music.asm build\music.asm




  lib\bin\step1

 

rem compiling the player file
  lib\bin\sjasmplus asm\music.asm > nul
rem compressing and moving the compiled player
  lib\bin\zx7b build\music.bin build\music.zx7b

  echo #########################
  echo ##        MUSIC        ##
  echo #########################
  
 
  goto cont
)

rem pause


echo ######################
echo ##graphics and sound##
echo ######################

if "%1"=="config" (
:cont

rem pause
  lib\bin\sjasmplus asm\engine0.asm > nul
  lib\bin\sjasmplus asm\engine1.asm > nul
  lib\bin\sjasmplus asm\engine2.asm > nul
rem  lib\bin\step2
 lib\bin\step2
rem	lib\bin\step2_original
  lib\bin\zx7b build\block1.bin build\block1.zx7b
  lib\bin\zx7b build\block2.bin build\block2.zx7b
)
echo.

rem pause	step2.original

echo ##################
echo ##    engine    ##
echo ##################

rem pause

rem cls

rem call z88dkenv.bat

echo #######################
echo ## ready to compiled ##
echo ## CHECK FOR ERRORS  ##
echo ##      HERE         ##
echo #######################
rem zcc +zx -zorg=32772 -O3 -z80-verb main.c -o build\main.bin -lndos
rem zcc +zx -zorg=32772 -O3 -vn main.c -o build\main.bin -lndos
rem zcc +zx -zorg=32772 -O3  -vn -m main.c -o build\main.bin -lndos
rem zcc +zx -zorg=32772 -O3 -vn -m main.c -o build\main.bin -lndos

rem zcc +zx_dev -vn tritone.c tritone_tricerops.asm tritone_demo.asm graphic_window.asm -o tritone -create-app

rem normal compile here
rem zcc +zx -zorg=32772 -O3 -vn -m main.c -o build\main.bin -lndos

rem zcc +zx -zorg=32772 -O3 -vn -m main.c  mus\gamesong.asm -o build\main.bin -lndos
zcc +zx -zorg=32772 -O3 -vn -m main.c  mus\anteat.asm -o build\main.bin -lndos



rem zcc +zx -zorg=32772 -O3 -vn -m main.c hubybin.bin -o build\main.bin -lndos

rem zx is target (sinclair spectrum)
rem zorg is starting address for program
rem O3 is optimization
rem vm is less verbose
rem m is an output map
rem -o is binary file to be used
rem lndos sends to tape

rem shows help file
rem zcc +zx -zorg=32772 -O3 -vn -m  -h main.c -o build\main.bin -lndos

rem -clib=sdcc_iy
echo #######################
echo ## ready to compiled ##
echo ## CHECK FOR ERRORS  ##
echo ##      HERE         ##
echo #######################


echo ######################################
echo ##File main.bin compiled from main.c##
echo ######################################
echo ################
echo ##compiled....##
echo ################




lib\bin\zx7b build\main.bin build\main.zx7b

rem pause

lib\bin\step3
rem pause
lib\bin\sjasmplus asm\loader.asm

if exist build\player.zx7b (
  lib\bin\gentape game.tap                    ^
            basic 'game' 10  build\loader.bin  ^
             data           build\engine.zx7b ^
             data           build\player.zx7b
) else (
  lib\bin\gentape game.tap                    ^
            basic 'game' 10  build\loader.bin  ^
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