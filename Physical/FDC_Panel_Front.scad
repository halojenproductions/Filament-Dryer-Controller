use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>
use <FDC_Panel_Frame.scad>
use <FDC_Panel_Button.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

if(ex[0]){
	Front();
}


module Front() {
	difference(){
		Face();

		translate([0, screen_pos.y]){
			ScreenHole_();

			LedHoles_();

		}
		
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
		translate([0, screen_pos.y + screen_window_shift_y, face_thick])
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

	// Screen shroud.
	translate([0, screen_pos.y, face_thick])
	ScreenShroud();

	// Led shrouds.
	translate([0, screen_pos.y, face_thick])
	LedShrouds();

	// Button anchor shroud.
	translate([0, button_pos.y, face_thick])
	ButtonAnchorShroud();

	// Frame screw posts (position relative to frame).
	translate([0, screen_pos.y, face_thick])
	FrameScrewPosts();

	// Pcb screw posts (position not relative to frame).
	translate([0, 0, face_thick])
	PcbScrewPosts();
}

module ScreenHole_(){
	translate([0, screen_window_shift_y]){
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
}

module ButtonHole_(){
	button_hole_dims = [hole(button_dims.x, .2), hole(button_dims.y, .2)];
	cuber(
		[button_hole_dims.x , button_hole_dims.y, face_dims.z + nonzero()],
		[1, 1, 0],
	);
	// Champher.
	hull(){
		cuber(
			[button_hole_dims.x, button_hole_dims.y, button_hole_cham],
			[1, 1, 0],
		);
		translate([0, 0, -nonzero()])
		cuber(
			[
				button_hole_dims.x + button_hole_cham*2, 
				button_hole_dims.y + button_hole_cham*2, 
				nonzero(),
			],
			[1, 1, 0],
			button_hole_cham,
		);
	}
}

module LedHoles_(){
	Led(led_pos[0]);
	Led(led_pos[1]);

	module Led(pos){
		translate(pos)
		cylr(hole(led_dia, .1), frame_pos.z);
	}
}

module LedShrouds(){
	LedShroud(led_pos[0]);
	LedShroud(led_pos[1]);
	
	module LedShroud(pos){
		translate(pos)
		difference(){
			cylr(
				led_shroud_dia, 
				screen_standoff_z + screen_glass_dims.z + screen_board_dims.z,
				[1, 1, 0],
			);
			cylr(
				hole(led_dia, .1), 
				screen_standoff_z + screen_glass_dims.z + screen_board_dims.z + nonzero(),
				[1, 1, 0],
			);
		}
	}
}

module ScreenShroud(){
	translate([0, 0, -nonzero()]){
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

		difference(){
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

			LocatorHole([holePos.x, holePos.y, hei + nonzero()]);
		}


		module LocatorHole(pos){
			translate(pos)
			mirror([0, 0, 1])
			cylr(hole(screen_screw_hole_dia, -.1), 1.2);
		}

		// Pin.
		// translate(holePos)
		// cylr(
		// 	screen_screw_hole_dia - .1, 
		// 	hei + screen_board_dims.z + frame_dims.z/2 - line[2],
		// 	[1, 1, 0],
		// );
	}
}


module FrameScrewPosts(){
	// Top left.
	PcbScrewPost(pcb_screw_pos[0]);
	// Top right.
	PcbScrewPost(pcb_screw_pos[1]);
}


module PcbScrewPosts(){
	// Bottom left.
	PcbScrewPost(pcb_screw_pos[2]);
	// Bottom right.
	PcbScrewPost(pcb_screw_pos[3]);
}

module PcbScrewPost(pos){
	difference(){
		translate(pos)
		coner(
			pcb_screw_post_dia, 
			pcb_screw_post_dia, 
			screen_shroud_dims.z,
			[1, 1, 0], 
			-1, 
			0,
			true,
		);

		heatset_insert(pcb_inserts, pos=[pos.x, pos.y, screen_shroud_dims.z]);
	}
}


module ButtonAnchorShroud(){
	translate([0, button_anchor_pos_y]){
		difference(){
			cuber(
				[
					button_anchor_dims.x + screen_shroud_offset*2,
					button_anchor_dims.y + screen_shroud_offset*2,
					button_anchor_dims.z,
				],
				r = screen_shroud_offset,
			);
			translate([0, 0, -nonzero()])
			cuber([
				hole(button_anchor_dims.x),
				hole(button_anchor_dims.y),
				button_anchor_dims.z + nonzero()*2,
			]);

			// Hinge cutout.
			translate([0, - screen_shroud_offset/2 - button_anchor_dims.y/2])
			cuber(
				[
					hole(button_dims.x, -.1),
					screen_shroud_offset + nonzero(),
					button_anchor_dims.z + nonzero(),
				],
				[1, 1, 0],
			);
			
		}
	}
}
