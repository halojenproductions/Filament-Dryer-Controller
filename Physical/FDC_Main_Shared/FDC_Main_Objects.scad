include <FDC_Main_Library.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


module Heater_(){
	trany(base_dims.l)
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

