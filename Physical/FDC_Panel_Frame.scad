include <FDC_Panel_Library.scad>


/* [Hidden] */
$fn = $preview ? 50 : q;


module Frame() {
	translate([0, -2, 0]){
		difference(){
			FrameMain();

			FrameLocatorHoles_();
		}
	}
}

module FrameMain(){
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
		cuber([
			screen_board_dims.x, 
			screen_board_dims.y,
			frame_dims.z + nonzero()*2,
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

	module Locator(holePos = [0, 0], corner = [-1, 1]) {
		x1 = corner.x < 0 ? -frame_dims.x/2 : frame_dims.x/2;
		y1 = corner.y < 0 ? -frame_dims.y/2 : frame_dims.y/2;

		hull(){
			translate([x1, holePos.y])
			cuber([
				nonzero(),
				frame_locator_dia,
				frame_dims.z,
			]);
			translate([holePos.x, y1])
			cuber([
				frame_locator_dia,
				nonzero(),
				frame_dims.z,
			]);
			translate(holePos)
			cylr(
				frame_locator_dia, 
				frame_dims.z,
				[1, 1, 0],
			);
		}
	}
}

module FrameLocatorHoles_(){
	/// Holes.
	// Top left.
	FrameLocatorHole(screen_screw_pos[0]);
	// Top right.
	FrameLocatorHole(screen_screw_pos[1]);
	// Bottom left.
	FrameLocatorHole(screen_screw_pos[2]);
	// Bottom right.
	FrameLocatorHole(screen_screw_pos[3]);

	module FrameLocatorHole(pos){
		translate([pos.x, pos.y, -nonzero()])
		cylr(
			screen_screw_hole_dia, 
			frame_dims.z/2 + nonzero(1),
			[1, 1, 0],
		);
	}
}


