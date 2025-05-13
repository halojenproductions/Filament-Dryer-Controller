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

if(ex[0]){
	Front();
}

if(ex[1]){
	translate([
		0, 
		screen_pos.y, 
		face_thick + screen_standoff_z + screen_glass_dims.z + screen_board_dims.z,
	])
	Frame();
}

if(ex[2]){
	translate(button_pos)
	mirror([0, 0, 1])
	Button();
}

echo(str("screen_shroud_dims.z = ", screen_shroud_dims.z));
echo(str("screen_shroud_dims.z + frame_dims.z = ", screen_shroud_dims.z + frame_dims.z));

// Ghosts.
%translate([0, 0, face_thick + screen_standoff_z]){
	*Pcb();
	translate([0, screen_pos.y, 0])
	Screen();
}



