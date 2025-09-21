include <FDC_Main_Library.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

Mocks();

module Mocks(){
	translate([0, base_dims.l - base_dims.thick.s, 0])
	rotate([90, 0, 0])
	Heater();


	module Sensor(){

	}

	module Heater(){
		difference(){
			ultracuber(
				[
					heater_dims.bot.w,
					heater_dims.bot.l,
					heater_dims.h,
					heater_dims.top.w,
					heater_dims.top.l,
				],
				[
					[heater_dims.radii.b, true],
					[heater_dims.radii.s, true],
					[heater_dims.radii.t, true],
				],
				[0, 1, 1],
				[0, 0, 0],
			);

			translate([0, heater_dims.fan_pos, heater_dims.h])
			cylr(
				heater_dims.fan_dia,
				1,
				[1, 0, 1],
			);
		}
	}
}
