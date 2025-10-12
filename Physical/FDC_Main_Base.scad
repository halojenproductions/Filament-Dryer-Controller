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
			Seal();
		}

		Electranics_();

		Heater_();

		Channel_();

		*trany(box_pos_y)
		Fan_();

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
				base_dims.radii.out.t,
			],
			[0, 1, 1],
			[0, 0, -base_dims.thick.b],
		);
		// Top interface section.
		ultracuber(
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

	module Seal(neg=false){
		difference(){
			intersection(){
				ultracuber(
					[
						interface_dims.w,
						top_dims.l,
						interface_dims.h,
						interface_dims.w - interface_dims.seal.size*2 + parting_line_relief*2,
						top_dims.l - interface_dims.seal.size*2 + parting_line_relief*2,
					],
					[
						0,
						[
							base_dims.radii.in.s + interface_outset, 
							true, 
							base_dims.radii.in.s + parting_line_relief
						],
						0,
					],
					[0, 0, 1],
					[
						0, 
						top_dims.l/2 + (base_dims.thick.s - interface_dims.seal.size), 
						base_dims.h
					],
				);

				ultracuber(
					[
						interface_dims.w,
						top_dims.l,
						interface_dims.h + nonzero(1),
					],
					[0, 0, 0],
					[0, 1, 1],
					[
						0, 
						0, 
						base_dims.h - nonzero()
					],
				);
			}

			Heater_();

			// Channel.
			ultracuber(
				[
					channel_dims.w,
					top_dims.l,
					interface_dims.h + nonzero(1),
				],
				[0, [base_dims.radii.in.s, true], 0],
				[0, 0, 1],
				[
					0, 
					top_dims.l/2 + (base_dims.thick.s), 
					base_dims.h - nonzero()
				],
			);
		}
	}

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

	module Cover_(){
		translate([0, cover_dims_inset, base_dims.h + nonzero()])
		ultracuber(
			[
				hole(cover_dims.w),
				hole(cover_dims.l),
				cover_dims.h + nonzero(),
			],
			[
				rad_neg(cover_dims.radii.b),
				[cover_dims.radii.s, true],
				-parting_line_relief,
			],
			[0, 1, -1],
			[0, 0, 0],
		);
	}
}

