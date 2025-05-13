include <FDC_Panel_Library.scad>


/* [Hidden] */


module Button() {
	ButtonBack();

	ButtonAnchor();

	Hinge();
	

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
		translate([0, button_anchor_pos_y - button_hinge_len])
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



