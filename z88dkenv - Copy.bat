@echo off
rem *********************************
rem ** z88dk environment variables **
rem *********************************
rem
rem **************************************************
rem ** You can call this file from the command line **
rem ** before running the compiler executables; or  **
rem ** from inside another .bat file using the CALL **
rem ** statement.                                   **
rem **************************************************

IF NOT "%Z88DK_ENV_id074741%"=="" GOTO exit_without_settings
REM SET Z80_OZFILES=A:\ZZ\Z88DK\lib\
SET Z80_OZFILES=C:\z88dk new\lib

REM SET ZCCCFG=A:\ZZ\Z88DK\lib\config\
SET ZCCCFG=C:\z88dk new\lib\config

REM SET PATH=A:\ZZ\Z88DK\bin;%PATH%
SET PATH=C:\z88dk new\bin;%PATH%

REM SET Z88DK_ENV_id074741=true
SET Z88DK_ENV_id074741=true

GOTO the_end

:exit_without_settings
rem echo Nothing to set :-)
:the_end
