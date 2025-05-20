use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>
use <FDC_Panel_Front.scad>
use <FDC_Panel_Frame.scad>
use <FDC_Panel_Button.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

echo("Screw stack: ", 
	pcb_dims.z + frame_dims.z + pcb_inserts[1]
);


if(ex[0]){
	color("green")
	Front();
}

if(ex[1]){
	translate(frame_pos)
	color("yellow")
	Frame();
}

if(ex[2]){
	translate(button_pos)
	mirror([0, 0, 1])
	color("blue")
	Button();
}

// Ghosts.
%Mocks();


