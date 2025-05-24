use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>
use <FDC_Panel_Front.scad>
use <FDC_Panel_Frame.scad>
use <FDC_Panel_Button.scad>
use <FDC_Panel_Back.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;

echo("Screw stack: ", 
	pcb_dims.z + frame_dims.z + pcb_inserts[1]
);


if(ex[0]){
	color("SeaGreen")
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
	color("SteelBlue")
	Button();
}

if(ex[3]){
	*translate([0, 0, face_dims.z + back_dims.z])
	mirror([0, 0, 1])
	color("SaddleBrown")
	Back();
}

// Ghosts.
%Mocks();


