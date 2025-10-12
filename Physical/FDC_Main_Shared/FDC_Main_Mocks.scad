include <FDC_Main_Library.scad>
use <FDC_Main_Objects.scad>

q = 100;
ex = [1,1,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

Mocks();

module Mocks(){
	translate([0, heater_pos.y, heater_pos.z])
	rotate([0, 0, 180])
	Heater();

	Sensor();

	*Screws();

	module Sensor(){
		trany(sensor_pos.y)
		ultracuber(
			[
				sensor_dims.w,
				sensor_dims.l,
				sensor_dims.h,
			],
			[0, 0, 0],
			[0, 0, 1],
			[0, 0, 0],
			[0, 0, -90],
		);
	}

	module Heater(){
		rotate([90, 0, 0])
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

	module Screws(){
		TopScrews();
	}
}
