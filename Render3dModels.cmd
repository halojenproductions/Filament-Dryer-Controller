@SET openscad="C:\Program Files\OpenSCAD (Nightly)\openscad.exe"
@SET scadfile="Physical\FDC_Panel.scad"
@SET outDir="Physical\Models"

%openscad% ^
--backend=manifold ^
-D ex=[1,0,0,0] -D q=100 ^
-o %outDir%\FDC_Panel_Front.stl ^
%scadfile%

%openscad% ^
--backend=manifold ^
-D ex=[0,1,0,0] -D q=100 ^
-o %outDir%\FDC_Panel_Frame.stl ^
%scadfile%

%openscad% ^
--backend=manifold ^
-D ex=[0,0,1,0] -D q=100 ^
-o %outDir%\FDC_Panel_Button.stl ^
%scadfile%




pause