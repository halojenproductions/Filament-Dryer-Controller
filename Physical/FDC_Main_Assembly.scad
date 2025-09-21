include <FDC_Panel_Library.scad>
use <FDC_Main_Mocks.scad>
use <FDC_Main_Base.scad>



q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	Body();
}

if(ex[1]){
	
}


// Ghosts.
%Mocks();
