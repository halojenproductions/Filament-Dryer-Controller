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
			difference(){
				hull(){
					// Middle cylinder.
					translate([0, 0, face_thick/2])
					rotate([0, 90, 0])
					cylr(
						face_thick,
						button_dims.x,
						[1, 0, 1],
						button_cham,
						1
					);

					// Bottom cylinder.
					translate([0, -button_dims.y/2 + .2, face_thick/2])
					rotate([0, 90, 0])
					cylr(
						face_thick,
						button_dims.x,
						[1, 0, 1],
						button_cham,
						1
					);

					// Base bit.
					translate([0, 0, 0])
					cuber(
						[button_dims.x, button_dims.y, face_thick - button_hole_cham],
						[1, 1, 0],
					);
				}
				
				// Curvey cutout.
				translate([0, button_dims.y/2, face_thick - button_hole_cham])
				rotate([-angle, 0, 0])
				rotate([-90, 0, 0])
				rotate([0, 90, 0])
				segment(
					[
						hype,
						.2,
						button_dims.x, 
					],
					[0, 0, 1],
					360
				);
			}
			
			// Bottom.
			cuber(
				[button_dims.x, button_dims.y, face_thick - button_hole_cham],
				[1, 1, 0],
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



