@SET openscad="C:\Program Files\OpenSCAD (Nightly)\openscad.exe"
@SET common=--render --imgsize=3840,2160 --export-format png ^
--colorscheme "Nocturnal Gem" --backend=manifold

@SET scadfile="Physical\DropTrigger_ControllerShell.scad"
@SET outDir="Media"


@REM %openscad% ^
@REM -D ex=[1,0,0,0,0] -D q=50 ^
@REM %common% ^
@REM --camera=0,10,0,22.5,0,45,350 ^
@REM -o %outDir%\Preview_Shell_inside.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[1,0,0,0,0] -D q=50 ^
@REM %common% ^
@REM --camera=-10,0,0,202.5,0,135,320 ^
@REM -o %outDir%\Preview_Shell_outside.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[0,1,0,0,0] -D q=50 ^
@REM %common% ^
@REM --camera=-18,0,0,202.5,0,135,300 ^
@REM -o %outDir%\Preview_Base_inside.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[0,1,0,0,0] -D q=50 ^
@REM %common% ^
@REM --camera=0,13,0,22.5,0,45,350 ^
@REM -o %outDir%\Preview_Base_outside.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[0,0,1,0,0] -D q=50 ^
@REM %common% ^
@REM --camera=-20,10,0,67.5,0,157.5,180 ^
@REM -o %outDir%\Preview_Xlr.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[0,0,0,1,0] -D q=50 ^
@REM %common% ^
@REM --camera=-2,2,0,45,0,45,60 ^
@REM -o %outDir%\Preview_Light.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[0,0,0,0,1] -D q=50 ^
@REM %common% ^
@REM --camera=-4,-31,0,22.5,0,45,165 ^
@REM -o %outDir%\Preview_Frame_inside.png ^
@REM %scadfile%

@REM %openscad% ^
@REM -D ex=[0,0,0,0,1] -D q=50 ^
@REM %common% ^
@REM --camera=0,-35,0,202.5,0,135,150 ^
@REM -o %outDir%\Preview_Frame_outside.png ^
@REM %scadfile%



::pause