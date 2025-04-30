use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>

q = 100;
ex = [1,1,0,0];


/* [Hidden] */
$fn = $preview ? 50 : q;

translate([
	0, 
	screen_pos.y, 
	face_thick + screen_standoff_z +screen_glass_dims.z + screen_board_dims.z
])
Frame();
Front();

// Ghosts.
%translate([0, 0, face_thick + screen_standoff_z]){
	Pcb();
	translate([0, screen_pos.y, 0])
	Screen();
}

module Frame(){
	translate([0, -2, 0]){
		difference(){
			cuber(
				[
					frame_dims.x, 
					frame_dims.y,
					frame_dims.z,
				],
				r = 1,
			);
			translate([0, 0, -nonzero()])
			cuber(
				[
					screen_board_dims.x, 
					screen_board_dims.y,
					frame_dims.z + nonzero()*2,
				],
			);
		}

		/// Locators.
		// Top left.
		translate([
			-screen_screw_pitch.x/2 - screen_screw_hole_dia/2, 
			screen_screw_pitch.y/2 + screen_screw_hole_dia/2,
			0,
		])
		Locator();
		// Top right.
		translate([
			screen_screw_pitch.x/2 + screen_screw_hole_dia/2, 
			screen_screw_pitch.y/2 + screen_screw_hole_dia/2,
			0,
		])
		Locator();
		// Bottom left.
		translate([
			-screen_screw_pitch.x/2 - screen_screw_hole_dia/2, 
			-screen_screw_pitch.y/2 - screen_screw_hole_dia/2,
			0,
		])
		Locator();
		// Bottom right.
		translate([
			screen_screw_pitch.x/2 + screen_screw_hole_dia/2, 
			-screen_screw_pitch.y/2 - screen_screw_hole_dia/2,
			0,
		])
		Locator();
	}

	module Locator(){
		cuber(
			[
				screen_screw_hole_dia*2,
				screen_screw_hole_dia*2,
				frame_dims.z,
			],
			r = screen_screw_hole_dia/2,
		);
	}
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

