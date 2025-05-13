include <FDC_Panel_Library.scad>

q = 100;

/* [Hidden] */
$fn = $preview ? 50 : q;

Frame();

module Frame() {
	difference(){
		union(){
			FrameTop();

			FrameMain();

			FrameButtonAnchor();
		}

		FrameScrewHoles_();
		FrameLedHoles_();
	}
}

module FrameTop(){
	translate([0, screen_board_dims.y/2])
	cuber(
		frame_top_dims,
		[1, 0, 0],
		frame_top_dims.y/2
	);
}

module FrameButtonAnchor(){
	translate([0, - screen_board_dims.y/2 - screen_shroud_offset - button_anchor_dims.y/2])
	mirror([0, 0, 1])
	cuber(
		[
			button_anchor_dims.x + screen_shroud_offset*2,
			button_anchor_dims.y,
			screen_shroud_dims.z - button_anchor_dims.z,
		],
	);
}

module FrameScrewHoles_(){
	// Screwholes.
	Screwhole(frame_screw_pos[0]);
	Screwhole(frame_screw_pos[1]);

	module Screwhole(pos){
		translate(pos)
		cylr(frame_screw_hole_dia, frame_dims.z + nonzero());
	}
}

module FrameLedHoles_(){
	// Leds.
	Led(led_pos[0]);
	Led(led_pos[1]);

	module Led(pos){
		translate(pos){
			cylr(hole(led_dia, .1), frame_top_dims.z + nonzero());

			translate([0, 0, frame_top_dims.z])
			mirror([0, 0, 1])
			cylr(led_dia + 1, line[2]*5);
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
			r = frame_unnamed_dim,
		);
		translate([0, 0, -nonzero()])
		cuber([
			screen_board_dims.x - 1, 
			screen_board_dims.y - 1,
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

		// Locator pin.
		translate(holePos)
		mirror([0, 0, 1])
		cylr(
			screen_screw_hole_dia, 
			screen_board_dims.z + 1,
			[1, 1, 0],
		);

	}
}



