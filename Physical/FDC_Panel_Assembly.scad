use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>
use <FDC_Panel_Front.scad>
use <FDC_Panel_Frame.scad>
use <FDC_Panel_Button.scad>
use <FDC_Panel_Back.scad>

q = 100;
ex = [1,1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


PCB_Info();

if(ex[0]){
	color("SeaGreen")
	Front();
}

if(ex[1]){
	color("LightCyan")
	LedLenses();
}

if(ex[2]){
	translate(frame_pos)
	color("yellow")
	Frame();
}

if(ex[3]){
	translate(button_pos)
	mirror([0, 0, 1])
	color("SteelBlue")
	Button();
}

if(ex[4]){
	*translate([0, 0, face_dims.z + back_dims.z])
	mirror([0, 0, 1])
	// color("SaddleBrown")
	Back();
}

// Ghosts.
%Mocks();

module PCB_Info(){
	echo("Grid origin top left corner. All positions relative to that.");
	echo(str("pcb_dims ", pcb_dims));

	echo(str("pcb_centre_x ", pcb_dims.x/2));
	echo(str("pcb_centre_y ", pcb_dims.y/2));
	echo(str("pcb_screw_pos (from corner) ", [
		[
			pcb_dims.x/2 + pcb_screw_pos[0].x, 
			pcb_dims.y/2 - pcb_screw_pos[0].y, 
		],
		[
			pcb_dims.x/2 + pcb_screw_pos[1].x, 
			pcb_dims.y/2 - pcb_screw_pos[1].y, 
		],
		[
			pcb_dims.x/2 + pcb_screw_pos[2].x, 
			pcb_dims.y/2 - pcb_screw_pos[2].y, 
		],
		[
			pcb_dims.x/2 + pcb_screw_pos[3].x, 
			pcb_dims.y/2 - pcb_screw_pos[3].y, 
		],
	]));
	echo(str("pcb_header_pos_y ", pcb_dims.y/2 -pcb_header_pos_y));
	echo(str("led_pos ", [
		[pcb_dims.x/2 + led_pos[0].x, pcb_dims.y/2 - (led_pos[0].y + screen_pos.y)],
		[pcb_dims.x/2 + led_pos[1].x, pcb_dims.y/2 - (led_pos[1].y + screen_pos.y)],
	]));
}