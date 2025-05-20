include <FDC_Panel_Library.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;


Button();

module Button() {
	ButtonBack();

	ButtonFront();

	ButtonAnchor();

	Hinge();

	module ButtonFront(){
		rise = face_thick - (face_thick - button_hole_cham) + .05;
		run = button_dims.y/2 - face_thick/2;
		angle = atan(rise/run);
		hype = sqrt(pow(rise, 2) + pow(run, 2));

		translate([0, 0, button_dims.z]){
			// Top.
			translate([0, -button_dims.y/2 * 1/3, 0])
			hull(){
				cuber(
					[
						button_dims.x - button_hole_cham*2,
						button_dims.y * 2/3 - button_hole_cham*2, 
						face_thick
					],
					[1, 1, 0],
					.2,
				);

				cuber(
					[
						button_dims.x, 
						button_dims.y * 2/3, 
						face_thick - button_hole_cham
					],
					[1, 1, 0],
					.2
				);
			}
			
			// Bottom.
			cuber(
				[button_dims.x, button_dims.y, face_thick - button_hole_cham],
				[1, 1, 0],
				.2
			);
		}
	}
	

	module ButtonBack(){
		cuber(
			[
				button_dims.x + button_flange_offset*2,
				button_dims.y + button_flange_offset*2,
				button_dims.z,
			], 
			[1, 1, 0],
		);
	}

	module ButtonAnchor(){
		translate([0, button_anchor_pos_y])
		cuber(
			button_anchor_dims,
			[1, 1, 0],
		);
	}

	module Hinge(){
		translate([
			0, 
			button_anchor_pos_y - button_hinge_len, 
			button_anchor_dims.z - button_hinge_thick - line[2]
		])
		cuber(
			[
				button_dims.x,
				button_hinge_len,
				button_hinge_thick,
			], 
			[1, 1, 0],
		);
	}

}



