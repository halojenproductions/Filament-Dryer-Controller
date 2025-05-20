use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

module Mocks(){
	*translate(pcb_pos)
	Pcb();

	translate(screen_pos)
	Screen();

	translate([0, 0, pcb_screw_pos_z])
	FrameScrews();
}

module FrameScrews(){
	translate([0, screen_pos.y]){
		// Top left.
		Screw(pcb_screw_pos[0]);
		// Top right.
		Screw(pcb_screw_pos[1]);
		// Bottom left.
	}
	Screw(pcb_screw_pos[2]);
	// Bottom right.
	Screw(pcb_screw_pos[3]);

	module Screw(pos){
		screw_caphead(
			[frame_screw_dims[0], hole(5), frame_screw_dims[1], .5, 0], 
			pos,
			[0, 0],
			false
		);
	}
}

module Pcb(){
	difference(){
		cuber(
			[
				pcb_dims.x, 
				pcb_dims.y, 
				pcb_dims.z,
			],
			[1, 1, 0],
			5
		);
	}
}

module Screen(){
	// Glass.
	cuber(
		[
			screen_glass_dims.x + 1, 
			screen_glass_dims.y + 1,
			screen_glass_dims.z,
		],
	);

	// PCB.
	difference(){
		translate([0, 0, screen_glass_dims.z])
		difference(){
			cuber(
				[
					screen_board_dims.x, 
					screen_board_dims.y, 
					screen_board_dims.z,
				],
			);
		}

		/// Screw holes.
		translate([0, 0, screen_glass_dims.z]){
			// Top left.
			translate(screen_screw_pos[0])
			cylr(
				screen_screw_hole_dia, 
				screen_board_dims.z,
				[1, 1, 0]
			);
			// Top right.
			translate(screen_screw_pos[1])
			cylr(
				screen_screw_hole_dia, 
				screen_board_dims.z,
				[1, 1, 0]
			);
			// Bottom left.
			translate(screen_screw_pos[2])
			cylr(
				screen_screw_hole_dia, 
				screen_board_dims.z,
				[1, 1, 0]
			);
			// Bottom right.
			translate(screen_screw_pos[3])
			cylr(
				screen_screw_hole_dia, 
				screen_board_dims.z,
				[1, 1, 0]
			);
		}
	}

	
	/// Header pins.
	translate([
		0, 
		screen_board_dims.y/2 - header_pitch, 
		screen_glass_dims.z + screen_board_dims.z
	]){
		// Left.
		translate([-header_pitch*1.5, 0, 0])
		cylr(
			header_dia, 
			header_hei,
			[1, 1, 0]
		);
		// Mid-left.
		translate([-header_pitch*0.5, 0, 0])
		cylr(
			header_dia, 
			header_hei,
			[1, 1, 0]
		);
		// Mid-right.
		translate([header_pitch*0.5, 0, 0])
		cylr(
			header_dia, 
			header_hei,
			[1, 1, 0]
		);
		// Right.
		translate([header_pitch*1.5, 0, 0])
		cylr(
			header_dia, 
			header_hei,
			[1, 1, 0]
		);
	}
}
