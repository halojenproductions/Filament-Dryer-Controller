@SET openscad="C:\Program Files\OpenSCAD (Nightly)\openscad.exe"
@SET scadDir=Physical
@SET outDir=Physical\Models

@SET file=FDC_Panel_Front
%openscad% --backend=manifold ^
-D ex=[1,0,0,0] -D q=100 ^
-o "%outDir%\%file%.stl" ^
"%scadDir%\%file%.scad"

@SET file=FDC_Panel_Frame
%openscad% --backend=manifold ^
-D ex=[0,1,0,0] -D q=100 ^
-o "%outDir%\%file%.stl" ^
"%scadDir%\%file%.scad"

@SET file=FDC_Panel_Button
%openscad% --backend=manifold ^
-D ex=[0,0,1,0] -D q=100 ^
-o "%outDir%\%file%.stl" ^
"%scadDir%\%file%.scad"




pause