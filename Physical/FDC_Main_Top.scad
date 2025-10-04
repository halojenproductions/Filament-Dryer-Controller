include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	BodyTop();
}

if(ex[1]){

}

module BodyTop(){
	difference(){
		union(){
			Top();
		}

		Heater_();

		DessiccantBox_();

		trany(box_pos_y)
		Fan_();
	}

	module Top(){
		translate([0, base_dims.l, base_dims.h])
		ultracuber(
			[
				base_dims.w,
				top_dims.l,
				top_dims.h - interface_dims.h,
			],
			[
				parting_line_relief,
				[base_dims.radii.out.s, true],
				base_dims.radii.out.t,
			],
			[0, -1, 1],
			[0, 0, interface_dims.h],
		);

		Interface();
	}

	module Fan_(){
		teardrop(
			object(d=heater_dims.fan_dia, l=global_dims.divs),
			object(b=.4, f=.4),
			[0, 1, -1],
			[0, 0, heater_dims.fan_pos],
			[0, 180, 0]
		);
	}

	module DessiccantBox_(){
		trany(box_pos_y){
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
					top_dims.h + interface_dims.h + nonzero()*2,
				],
				[
					0,
					global_dims.divs,
					0,
				],
				[0, -1, -1],
				[0, 0, base_dims.h + top_dims.h + nonzero()],
			);
		}
		
		module Taper(){
			hull(){
				ultracuber(
					[
						hole(box_dims.w - global_dims.divs*2),
						global_dims.divs,
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

	module Interface(){
		translate([0, base_dims.l - top_dims.l/2, base_dims.h])
		difference(){
			ultracuber(
				[
					interface_dims.w,
					interface_dims.l,
					interface_dims.h,
				],
				[
					parting_line_relief,
					[interface_dims.radii.s*1.5, true],
					0,
				],
				[0, 0, 1],
				[0, 0, 0],
			);

			*ultracuber(
				[
					interface_dims.w,
					interface_dims.l,
					interface_dims.h + nonzero(),
				],
				[
					-parting_line_relief,
					[interface_dims.radii.s, true],
					0,
				],
				[0, 0, 1],
				[0, 0, -nonzero()],
			);

			// Channel.
			*ultracuber(
				[
					hole(channel_dims.w),
					interface_inset,
					interface_dims.h + cover_dims.h,
				],
				[0, 0, 0],
				[0, 1, 1],
				[0, -top_dims.l/2 - nonzero(), -cover_dims.h - nonzero()],
			);
		}
	}
}



