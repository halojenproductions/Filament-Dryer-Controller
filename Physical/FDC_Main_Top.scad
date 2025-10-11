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
			TopScrewShrouds();
		}

		Heater_();

		DessiccantBox_();

		FanDuct_();

		TopScrews(top_fastener_dims.shroud.getRise(), true);
	}

	module Top(){
		translate([0, 0, base_dims.h])
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
			[0, 1, 1],
			[0, 0, interface_dims.h],
		);

		TopInterface();
	}

	module FanDuct_(){
		trany(heater_pos.y + heater_dims.h)
		teardrop(
			object(
				d=heater_dims.fan_dia, 
				l=channel_pos_y - (heater_pos.y + heater_dims.h),
			),
			object(b=.4, f=.4),
			[0, 1, -1],
			[0, 0, heater_pos.z + heater_dims.fan_pos],
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
				[0, 1, -1],
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
					[0, 0, base_dims.h],
				);
			}
		}
	}

	module TopInterface(){
		translate([0, top_dims.l/2, base_dims.h]){
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

			// Channel.
			ultracuber(
				[
					channel_dims.w,
					interface_inset,
					interface_dims.h + cover_dims.h + parting_line_relief,
				],
				[0, 0, 0],
				[0, 1, 1],
				[0, top_dims.l/2 + nonzero(), -cover_dims.h - nonzero()],
			);
		}
	}

	module TopScrewShrouds(){
		difference(){
			union(){
				mover(-base_dims.w, -top_fastener_dims.shroud.dia/2)
				TopScrewShroud();
				mover(base_dims.w, -top_fastener_dims.shroud.dia/2)
				TopScrewShroud();
			}

			// tranz(-(interface_dims.h + parting_line_relief))
			// Top();

			Interface(true);
		}


		module TopScrewShroud(){
			translate([0, base_dims.l - top_dims.l, base_dims.h])
			hull(){
				trany(top_fastener_dims.shroud.dia/2)
				coner(
					top_fastener_dims.shroud.dia,
					top_fastener_dims.shroud.dia,
					top_fastener_dims.shroud.getRise(),
					[1, 1, 0],
					0, .5,
					true, false,
				);

				trany(-top_fastener_dims.clear_rad)
				coner(
					top_fastener_dims.shroud.dia,
					top_fastener_dims.shroud.dia,
					top_fastener_dims.shroud.h,
					[1, 1, 0],
					0, .5,
					true, false,
				);
			}
		}
	}
}



