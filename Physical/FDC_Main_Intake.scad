include <FDC_Main_Shared/FDC_Main_Library.scad>
// use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	Intake();
}

if(ex[1]){
	
}

module Intake(){
	translate([0, base_dims.l - intake_dims.l/2, intake_dims.h/2 + nonzero()]){
		Main();

		Ridge();

		Top();
	}

	module Top(){
		ultracuber(
			[
				intake_dims.w - intake_dims.ridge*2,
				intake_dims.ridge + parting_line_relief*2,
				intake_dims.l,
			],
			[
				parting_line_relief,
				0,
				0,
			],
			[0, -1, 0],
			[0, 0, intake_dims.h/2],
			[90, 0, 0],
		);
	}	

	module Main(){
		// Smaller.
		ultracuber(
			[
				intake_dims.w - intake_dims.ridge*2,
				intake_dims.h - intake_dims.ridge*2,
				intake_dims.l,
			],
			[
				parting_line_relief,
				[parting_line_relief],
				0,
			],
			[0, 0, 0],
			[0, 0, 0],
			[90, 0, 0],
		);
	}

	module Ridge(){
		intersection(){
			hull(){
				ultracuber(
					[
						intake_dims.w - intake_dims.ridge*2,
						intake_dims.h + parting_line_relief - intake_dims.ridge,
						intake_dims.ridge*2,
					],
					[
						0,
						parting_line_relief,
						0,
					],
					[0, 0, 0],
					[0, 0, parting_line_relief/2 + intake_dims.ridge/2],
					[90, 0, 0],
				);

				ultracuber(
					[
						intake_dims.w,
						intake_dims.h + parting_line_relief + intake_dims.ridge,
						layers(2),
					],
					[
						0,
						parting_line_relief + intake_dims.ridge/2,
						0,
					],
					[0, 0, 0],
					[
						0, 
						0, 
						parting_line_relief/2 + intake_dims.ridge/2
					],
					[90, 0, 0],
				);
			}

			ultracuber(
				[
					intake_dims.w,
					intake_dims.h,
					intake_dims.ridge*2,
				],
				[0, 0, 0],
				[0, 0, 0],
				[0, 0, 0],
				[90, 0, 0],
			);
		}
	}
}



module Intake_(){
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
