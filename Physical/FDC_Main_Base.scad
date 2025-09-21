include <FDC_Main_Library.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	Body();
}

if(ex[1]){
}

module Body(){
	difference(){
		union(){
			trany(base_dims.l)
			Top();

			Base();
		}

		trany(base_dims.l)
		Heater_();

		trany(box_pos_y)
		DessiccantBox_();
	}

	module Top(){
		difference(){
			ultracuber(
				[
					base_dims.w,
					top_dims.l,
					base_dims.h + top_dims.h,
				],
				[
					0,
					[base_dims.radii.out.s, true],
					base_dims.radii.out.t,
				],
				[0, -1, 1],
				[0, 0, 0],
			);
		}
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

	module DessiccantBox_(){
		// Front.
		trany(-box_dims.l)
		Taper();
		// Back.
		mirror([0, 1, 0])
		Taper();

		ultracuber(
			[
				hole(box_dims.w),
				box_dims.l - base_dims.thick.s*2,
				top_dims.h + nonzero(),
			],
			[
				0,
				0,
				0,
			],
			[0, -1, 1],
			[0, -base_dims.thick.s, base_dims.h],
		);
		
		module Taper(){
			hull(){
				ultracuber(
					[
						hole(box_dims.w - base_dims.thick.s*2),
						base_dims.thick.s,
						top_dims.h + nonzero(),
					],
					[
						0,
						0,
						0,
					],
					[0, 1, 1],
					[0, 0, base_dims.h],
				);

				ultracuber(
					[
						hole(box_dims.w),
						0,
						top_dims.h + nonzero(),
					],
					[
						0,
						0,
						0,
					],
					[0, 1, 1],
					[0, base_dims.thick.s, base_dims.h],
				);
			}
		}


	}

	module Heater_(){
		ultracuber(
			[
				hole(heater_dims.bot.w),
				heater_dims.bot.l,
				hole(heater_dims.h),
				hole(heater_dims.top.w),
				heater_dims.top.l,
			],
			[
				[rad_neg(heater_dims.radii.b), true],
				[rad_neg(heater_dims.radii.s), true],
				[rad_neg(heater_dims.radii.t), true],
			],
			[0, 1, 1],
			[0, - base_dims.thick.s, 0],
			[90, 0, 0],
		);
	}
}


