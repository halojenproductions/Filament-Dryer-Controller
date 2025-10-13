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

module Intake(ispos=true){
	translate([
		0, 
		base_dims.l - intake_dims.l/2, 
		intake_dims.h/2 + nonzero()
	]){
		difference(){
			union(){
				Main();

				Ridge();

				Top();
			}
			if(ispos){
				LouvreSection_();
			}
		}

		if(ispos){
			Louvres();
		}
	}

	module Main(){
		ultracuber(
			[
				tern(ispos,
					intake_dims.w - intake_dims.ridge*2,
					hole(intake_dims.w - intake_dims.ridge*2),
				),
				tern(ispos,
					intake_dims.h - intake_dims.ridge*2,
					hole(intake_dims.h - intake_dims.ridge*2),
				),
				intake_dims.l + tern(ispos, 0, nonzero()),
			],
			[
				tern(ispos, parting_line_relief, -parting_line_relief),
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
						tern(ispos,
							intake_dims.w - intake_dims.ridge*2,
							hole(intake_dims.w - intake_dims.ridge*2),
						),
						tern(ispos,
							intake_dims.h + parting_line_relief - intake_dims.ridge,
							hole(intake_dims.h + parting_line_relief - intake_dims.ridge),
						),
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
						hole(intake_dims.w, when=!ispos),
						hole(intake_dims.h + parting_line_relief + intake_dims.ridge, when=!ispos),
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
					tern(ispos,
						intake_dims.w,
						hole(intake_dims.w),
					),
					tern(ispos,
						intake_dims.h,
						hole(intake_dims.h),
					),
					intake_dims.ridge*2,
				],
				[0, 0, 0],
				[0, 0, 0],
				[0, 0, 0],
				[90, 0, 0],
			);
		}
	}

	module Top(){
		ultracuber(
			[
				tern(ispos,
					intake_dims.w - intake_dims.ridge*2,
					hole(intake_dims.w - intake_dims.ridge*2),
				),
				tern(ispos,
					intake_dims.ridge + parting_line_relief*2,
					hole(intake_dims.ridge + parting_line_relief*2),
				),
				intake_dims.l + tern(ispos, 0, nonzero()),
			],
			[
				tern(ispos, parting_line_relief, -parting_line_relief),
				0,
				0,
			],
			[0, -1, 0],
			[0, 0, intake_dims.h/2 + tern(ispos, 0, nonzero())],
			[90, 0, 0],
		);
	}	

	module LouvreSection_(){
			ultracuber(
				[
					intake_dims.w - intake_dims.border*2,
					intake_dims.h - intake_dims.border*2,
					intake_dims.l + nonzero(),
				],
				[
					0,
					[base_dims.radii.in.s, true],
					0,
				],
				[0, 0, 0],
				[0, 0, 0],
				[90, 0, 0],
			);
	}

	module Louvres(){
		hypotenuse = hyp(intake_dims.w/2, intake_dims.h);
		pitch = (intake_dims.h - intake_dims.border*2 - intake_dims.louvres.thick) / intake_dims.louvres.count;

		intersection(){
			rotate([90, 0, 0])
			union(){
				render(5)
				for(i = [1 : intake_dims.louvres.count*2 - 1]){
					trany(i * pitch)
					Louvre(i);

					mirror([1,0,0])
					trany(i * pitch)
					Louvre(i);
				}

				ultracuber(
					[
						intake_dims.louvres.thick,
						intake_dims.h - intake_dims.border*2,
						intake_dims.l + nonzero(),
					],
					[0, 0, 0],
					[0, 0, 0],
					[0, 0, 0],
				);

				AngledSupport();
				mirror([1,0,0])
				AngledSupport();

			}


			LouvreSection_();
		}
		
		module Louvre(i){
			trany(-intake_dims.h/2 - intake_dims.w/2)
			tranz(-intake_dims.l/2)
			hull(){
				// Bottom
				ultracuber(
					[
						hypotenuse,
						intake_dims.louvres.thick,

					],
					[0, 0, 0],
					[1, 1, 0],
					[0, 0, 0],
					[0, 0, 45],
				);

				// Top
				ultracuber(
					[
						hypotenuse,
						intake_dims.louvres.thick,

					],
					[0, 0, 0],
					[1, 1, 0],
					[
						0, 
						intake_dims.l / tan(intake_dims.louvres.angle), 
						intake_dims.l, 
					],
					[0, 0, 45],
				);
			}
		}

		module AngledSupport(){
			ultracuber(
				[
					intake_dims.louvres.thick,
					hypotenuse,
					intake_dims.l + nonzero(),
				],
				[0, 0, 0],
				[0, -1, 0],
				[0, intake_dims.h/2 - intake_dims.border, 0],
				[0, 0, 45],
			);
		}
	}
}
