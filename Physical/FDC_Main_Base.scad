include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	BodyBase();
}

if(ex[1]){
}

module BodyBase(){
	difference(){
		union(){
			Base();
			Interface();
		}

		trany(base_dims.l)
		Heater_();

		Channel_();

		trany(box_pos_y)
		Fan_();

		Electranics_();
	}

	module Base(){
		ultracuber(
			[
				base_dims.w,
				base_dims.l,
				base_dims.h + base_dims.thick.b,
			],
			[
				base_dims.radii.out.b,
				[base_dims.radii.out.s, true],
				base_dims.radii.out.t,
			],
			[0, 1, 1],
			[0, 0, -base_dims.thick.b],
		);
	}

	module Interface(){
		trany(base_dims.l - top_dims.l/2)
		difference(){
			ultracuber(
				[
					base_dims.w,
					top_dims.l,
					base_dims.h + 2,
				],
				[
					0,
					[base_dims.radii.out.s, true],
					parting_line_relief,
				],
				[0, 0, 1],
				[0, 0, 0],
			);

			ultracuber(
				[
					hole(base_dims.w - base_dims.thick.s),
					hole(top_dims.l - base_dims.thick.s),
					base_dims.h + 2 + nonzero(),
				],
				[
					0,
					[base_dims.radii.out.s, true],
					-parting_line_relief,
				],
				[0, 0, 1],
				[0, 0, 0],
			);
		}
	}

	module Channel_(){
		trany(channel_pos_y)
		ultracuber(
			[
				channel_dims.w,
				channel_dims.l,
				channel_dims.h + nonzero(),
			],
			[
				0,
				global_dims.radii.in.s,
				0,
			],
			[0, -1, 1],
			[0, 0, 0],
		);
	}

	module Fan_(){
		tranz(heater_dims.fan_pos)
		align([
			heater_dims.fan_dia, 
			global_dims.divs, 
			heater_dims.fan_dia
		], [0, 1, 1])
		rotate([90, 0, 0])
		cylr(
			heater_dims.fan_dia, 
			global_dims.divs,
			[1, 1, 1],
			-.4,
			true,
		);
	}
	module Electranics_(){
		ultracuber(
			[
				electronics_dims.w,
				electronics_dims.l,
				base_dims.h + nonzero(),
			],
			[0, global_dims.radii.in.s, 0],
			[0, 1, 1],
			[0, base_dims.thick.s, 0],
		);
	}
}


