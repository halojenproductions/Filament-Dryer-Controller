include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Objects.scad>
use <FDC_Main_Intake.scad>

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
			*Seal();
		}

		Electranics_();

		Heater_();

		Channel2_();

		*trany(box_pos_y)
		Fan_();

		Intake();
		*Cover_();

		*TopScrews();
	}

	Clips();
	

	module Base(){
		// Main.
		ultracuber(
			[
				base_dims.w,
				base_dims.l,
				base_dims.h + base_dims.thick.b,
			],
			[
				base_dims.radii.out.b,
				[base_dims.radii.out.s, true],
				// base_dims.radii.out.t,
				parting_line_relief,
			],
			[0, 1, 1],
			[0, 0, -base_dims.thick.b],
		);
		// Top interface section.
		*ultracuber(
			[
				base_dims.w,
				top_dims.l,
				base_dims.radii.out.t,
			],
			[
				0,
				[base_dims.radii.out.s, true],
				parting_line_relief,
			],
			[0, 1, -1],
			[0, 0, base_dims.h],
		);
	}

	// Not needed when eliminating the intake section.
	module Channel2_(){
		trany(channel_pos_y){
			// Fillet.
			ultracuber(
				[
					channel_dims.w,
					channel_dims.l,
					global_dims.radii.in.t,
				],
				[
					0,
					global_dims.radii.in.s,
					0,//-global_dims.radii.in.t,
				],
				[0, 1, 1],
				[0, 0, channel_dims.h - global_dims.radii.in.t + nonzero()],
			);

			hull(){
				// 
				ultracuber(
					[
						channel_dims.w,
						channel_dims.l,
						channel_dims.h - channel_dims.slope + nonzero(),
					],
					[
						global_dims.radii.in.b,
						global_dims.radii.in.s,
						0,
					],
					[0, 1, 1],
					[0, 0, channel_dims.slope + nonzero()],
					[0, 0, 0]
				);

				// 
				ultracuber(
					[
						channel_dims.w,
						channel_dims.l - channel_dims.slope,
						channel_dims.slope,
					],
					[
						global_dims.radii.in.b,
						global_dims.radii.in.s,
						0,
					],
					[0, -1, 1],
					[0, channel_dims.l, nonzero()],
					[0, 0, 0]
				);


			}
		}
	}

	// Not needed when eliminating the intake section.
	module Channel_(){
		trany(channel_pos_y){
			// Fillet.
			ultracuber(
				[
					channel_dims.w,
					channel_dims.l,
					global_dims.radii.in.t,
				],
				[
					0,
					global_dims.radii.in.s,
					0,//-global_dims.radii.in.t,
				],
				[0, 1, 1],
				[0, 0, channel_dims.h - global_dims.radii.in.t + nonzero()],
			);

			hull(){
				// Full height, upside down.
				ultracuber(
					[
						channel_dims.w,
						channel_dims.l,
						channel_dims.h + nonzero(),
						channel_dims.w,
						channel_dims.l - channel_dims.h*2,
					],
					[
						0,
						global_dims.radii.in.s,
						global_dims.radii.in.b,
					],
					[0, -1, -1],
					[0, 0, nonzero()],
					[180, 0, 0]
				);

				// Half height, also upside down.
				ultracuber(
					[
						channel_dims.w,
						channel_dims.l/2,
						channel_dims.slope,
						channel_dims.w,
						channel_dims.l/2 - channel_dims.slope*2,
					],
					[
						0,
						global_dims.radii.in.s,
						global_dims.radii.in.b,
					],
					[0, -1, -1],
					[0, 0, nonzero()],
					[180, 0, 0]
				);


				// Big rounding at the end.
				intersection(){
					trany(channel_dims.l)
					align(
						[channel_dims.w, channel_dims.h*2, channel_dims.h*2],
						[0, -1, 1],
					)
					rotate([0, 90, 0])
					cylr(
						channel_dims.h*2, 
						channel_dims.w,
						[1, 1, 1],
						global_dims.radii.in.s[0],
						false,
					);

					ultracuber(
						[
							channel_dims.w,
							channel_dims.l,
							channel_dims.h + nonzero(),
						],
						[0, 0, 0],
						[0, 1, 1],
						[0, 0, nonzero()],
					);
				}
			}
		}
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
			[
				global_dims.radii.in.b, 
				global_dims.radii.in.s, 
				0,//-global_dims.radii.in.t
			],
			[0, 1, 1],
			[0, base_dims.thick.s, 0],
		);
	}
}

