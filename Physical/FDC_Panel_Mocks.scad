include <FDC_Panel_Library.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

Mocks();

module Mocks(){
	translate(pcb_pos)
	PcbRender();

	*translate(pcb_pos)
	render(convexity = 50)
	color("#999999", .5)
	Pcb();

	translate(screen_pos)
	render(convexity = 5)
	color("#999999", .5)
	Screen();

	translate([0, 0, pcb_screw_pos_z])
	render(convexity = 5)
	color("#999999", .5)
	FrameScrews();

	translate([0, 0, face_thick + back_screw_post_len + back_screw_post_disc_thick])
	render(convexity = 5)
	color("#999999", .5)
	BackScrews();
}

module BackScrews(){
	for(pos = back_screw_pos){
		Screw(pos);
	}

	module Screw(pos){
		screw_caphead(
			back_screw_dims, 
			pos,
			[0, 0],
			false
		);
	}
}

module FrameScrews(){
	for(pos = pcb_screw_pos){
		Screw(pos);
	}

	module Screw(pos){
		screw_caphead(
			[pcb_screw_dims[0], hole(3.2), pcb_screw_dims[1], 1.3, 0], 
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
			1
		);
	}

	translate([
		0, 
		pcb_header_pos_y, 
		pcb_dims.z
	])
	cuber(pcb_header_dims, [1, 1, 0]);
}

module PcbRender(){
	translate([-pcb_dims.x/2, pcb_dims.y/2])
	import(
		"FDC_Panel_PCB.stl", 
		center = false,
		convexity = 50, 
		scale = 1
	);
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
