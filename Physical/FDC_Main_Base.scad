include <FDC_Main_Library.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	*BodyTop();
}

if(ex[1]){
	BodyBase();
}

module BodyTop(){
	difference(){
		union(){
			Top();
		}

		trany(base_dims.l)
		Heater_();

		trany(box_pos_y)
		DessiccantBox_();

		trany(box_pos_y)
		Fan_();
	}

	module Top(){
		translate([0, base_dims.l, base_dims.h])
		difference(){
			ultracuber(
				[
					base_dims.w,
					top_dims.l,
					top_dims.h,
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

	module Fan_(){
		teardrop(
			object(d=heater_dims.fan_dia, l=base_dims.thick.s),
			object(b=.4, f=.4),
			[0, 1, -1],
			[0, 0, heater_dims.fan_pos],
			[0, 180, 0]
		);
	}
}

module BodyBase(){
	difference(){
		union(){
			Base();
			Interface();
		}

		trany(base_dims.l)
		Heater_();

		*trany(box_pos_y)
		DessiccantBox_();

		Channel_();
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
				[base_dims.radii.in.s, true],
				0,
			],
			[0, -1, 1],
			[0, 0, 0],
		);
	}
}

module DessiccantBox_(){
	// Front.
	*#trany(-box_dims.l)
	Taper();
	// Back.
	*#mirror([0, 1, 0])
	Taper();

	ultracuber(
		[
			hole(box_dims.w),
			hole(box_dims.l),
			top_dims.h + nonzero()*2,
		],
		[
			0,
			base_dims.thick.s,
			0,
		],
		[0, -1, 1],
		[0, 0, base_dims.h - nonzero()],
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
				[0, -1, 1],
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
				[0, -1, 1],
				[0, 0, base_dims.h],
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



