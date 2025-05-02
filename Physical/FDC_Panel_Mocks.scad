include <FDC_Panel_Library.scad>

Pcb();
Screen();

module Pcb(){
	translate([0, 0, screen_glass_dims.z + screen_board_dims.z + header_hei])
	difference(){
		cuber(
			[
				pcb_dims.x, 
				pcb_dims.y, 
				pcb_dims.z,
			],
		);
	}
}

module Screen(){
	translate([0, -2, 0]){
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
}
