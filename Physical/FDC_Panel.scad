use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>
use <FDC_Panel_Frame.scad>

q = 100;
ex = [1,1,0,0];


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

echo(str("Variable = ", screen_standoff_z + screen_glass_dims.z + screen_board_dims.z));

// Ghosts.
%translate([0, 0, face_thick + screen_standoff_z]){
	*Pcb();
	translate([0, screen_pos.y, 0])
	Screen();
}


module Front() {
	difference(){
		Face();

		translate([0, screen_pos.y])
		ScreenHole_();
		
		translate([0, button_pos.y])
		ButtonHole_();
	}
}

module Face(){
	difference(){
		supercuber(
			[
				[face_dims.x, face_dims.y], 
				[face_dims.x, face_dims.y], 
				face_dims.z,
			], 
			[1, 1, 0], 
			[face_cham, 0, face_rad],
			[1, 0, 0],
		);

		translate([0, 0, face_thick])
		supercuber(
			[
				[
					face_dims.x - face_in_offset*2, 
					face_dims.y - face_in_offset*2
				], 
				[
					face_dims.x - face_in_offset*2, 
					face_dims.y - face_in_offset*2
				], 
				face_dims.z - face_thick + nonzero(),
			], 
			[1, 1, 0], 
			[face_cham, 0, face_rad - face_in_offset],
			[1, 0, 0],
		);
	}

	// Screen standoff.
	difference() {
		translate([0, screen_pos.y, face_thick])
		cuber(
			[
				screen_visible_dims.x + screen_standoff_wid*2, 
				screen_visible_dims.y + screen_standoff_wid*2,
				screen_standoff_z,
			],
			r = screen_standoff_wid,
		);
	}

	// Button standoff.
	*difference() {
		translate([0, button_pos.y, face_thick])
		cuber(
			[
				button_dims.x + screen_standoff_wid*2, 
				button_dims.y + screen_standoff_wid*2,
				screen_standoff_z,
			],
			r = screen_standoff_wid,
		);
	}

	translate([0, screen_pos.y, face_thick])
	ScreenShroud();
}


module ScreenHole_(){
	cuber(
		[screen_visible_dims.x , screen_visible_dims.y, face_dims.z]
	);
	hull(){
		cuber(
			[screen_visible_dims.x, screen_visible_dims.y, screen_cham]
		);
		translate([0, 0, -nonzero()])
		cuber(
			[
				screen_visible_dims.x + screen_cham*2, 
				screen_visible_dims.y + screen_cham*2, 
				nonzero(),
			],
			r = screen_cham,
		);
	}
}

module ButtonHole_(){
	cuber(
		[button_dims.x , button_dims.y, face_dims.z + nonzero()]
	);
	hull(){
		cuber(
			[button_dims.x, button_dims.y, button_cham]
		);
		translate([0, 0, -nonzero()])
		cuber(
			[
				button_dims.x + button_cham*2, 
				button_dims.y + button_cham*2, 
				nonzero(),
			],
			r = button_cham,
		);
	}
}

module ScreenShroud(){
	translate([0, -2, -nonzero()]){
		difference(){
			cuber(
				[
					screen_shroud_dims.x,
					screen_shroud_dims.y,
					screen_shroud_dims.z,
				],
				r = screen_shroud_offset,
			);
			translate([0, 0, -nonzero()])
			cuber([
				screen_board_dims.x,
				screen_board_dims.y,
				screen_shroud_dims.z + nonzero()*2,
			]);
		}

		/// Locators.
		// Top left.
		Locator(screen_screw_pos[0], [-1, 1]);
		// Top right.
		Locator(screen_screw_pos[1], [1, 1]);
		// Bottom left.
		Locator(screen_screw_pos[2], [-1, -1]);
		// Bottom right.
		Locator(screen_screw_pos[3], [1, -1]);
	}

	module Locator(holePos = [0, 0], corner = [-1, 1]) {
		x1 = corner.x < 0 ? -screen_shroud_dims.x/2 : screen_shroud_dims.x/2;
		y1 = corner.y < 0 ? -screen_shroud_dims.y/2 : screen_shroud_dims.y/2;
		hei = screen_standoff_z + screen_glass_dims.z;

		hull(){
			translate([x1, holePos.y])
			cuber([
				nonzero(),
				frame_locator_dia,
				hei,
			]);
			translate([holePos.x, y1])
			cuber([
				frame_locator_dia,
				nonzero(),
				hei,
			]);
			translate(holePos)
			cylr(
				frame_locator_dia, 
				hei,
				[1, 1, 0],
			);
		}

		// Pin.
		translate(holePos)
		cylr(
			screen_screw_hole_dia - .1, 
			hei + screen_board_dims.z + frame_dims.z/2 - line[2],
			[1, 1, 0],
		);
	}
}

module ScreenPosts(){
	translate([0, 0, face_thick]){
		// Top left.
		ScreenPost(screen_screw_pos[0]);
		// Top right.
		ScreenPost(screen_screw_pos[1]);
		// Bottom left.
		ScreenPost(screen_screw_pos[2]);
		// Bottom right.
		ScreenPost(screen_screw_pos[3]);
	}
}

module ScreenPost(pos){
	translate(pos)
	coner(
		screen_screw_hole_dia, 
		screen_screw_hole_dia, 
		screen_standoff_z + screen_glass_dims.z ,
		[1, 1, 0], 
		screen_cham, 
		0,
		ex
	);
}