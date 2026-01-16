include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [1,0,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	DessiccantBox();
}

if(ex[1]){
	DessiccantBoxLid();
}

module DessiccantBox(){
	difference(){
		union(){
			Main();
			LidInterface();
		}

		Main_();
		BottomMesh_();
		BottomSideMesh_();
		DoveRelief_();
	}

	module Main(){
		tranz(box_dims.pos().z - box_dims.lid().h)
		trany(box_pos_y){
			ultracuber(
				[
					box_dims.w,
					box_dims.l,
					box_dims.h - box_dims.lid().h,
				],
				[
					box_dims.thi().b,
					[box_dims.thi().s, true],
					0,
				],
				[0, 1, -1],
				[0, 0, 0],
			);
		}
	}

	module LidInterface(){
		tranz(box_dims.pos().z - box_dims.lid().h)
		trany(box_pos_y)
		intersection(){
			ultracuber(
				[
					box_dims.w,
					box_dims.l,
					box_dims.interface().h,
				],
				[
					0,
					[box_dims.thi().s, true],
					-box_dims.interface().h,
				],
				[0, 1, -1],
				[0, 0, 0],
			);

			// Intersector.
			ultracuber(
				[
					box_dims.w + box_dims.interface().h*2 - parting_line_relief*2,
					box_dims.l + box_dims.interface().h - parting_line_relief,
					box_dims.interface().h,
				],
				[0, [box_dims.thi().s + box_dims.interface().h, true], 0],
				[0, 1, -1],
				[0, 0, 0],
			);
		}
	}

	module Main_(){
		tranz(box_dims.pos().z - box_dims.lid().h)
		trany(box_pos_y){
			ultracuber(
				[
					box_dims.inner().w,
					box_dims.inner().l,
					box_dims.inner().h - box_dims.lid().h - box_dims.thi().mesh + nonzero()*2,
				],
				[
					box_dims.thi().b,
					[0, true],
					0,
				],
				[0, 0, -1],
				[0, box_dims.l/2, nonzero()],
			);
		}
	}

	module BottomMesh_(){
		// Main.
		trany(box_pos_y)
		tranz(box_dims.pos().z - box_dims.h + box_dims.thi().b){
			ultracuber(
				[
					box_dims.inner().w,
					box_dims.inner().l + box_dims.thi().s,
					box_dims.thi().mesh + nonzero()*2,
				],
				[
					box_dims.thi().b,
					[0, true],
					0,
				],
				[0, 1, -1],
				[0, box_dims.thi().s, nonzero()],
			);
		}
	}

	module BottomSideMesh_(){
		trany(box_pos_y + box_dims.l + nonzero())
		tranz(box_dims.pos().z - box_dims.h)
		{
			ultracuber(
				[
					box_dims.inner().w,
					channel_dims.h - channel_dims.slope + box_dims.thi().b + nonzero()*2,
					box_dims.thi().mesh + nonzero()*2,
				],
				[
					box_dims.thi().b,
					[0, true],
					0,
				],
				[0, 1, 1],
				[0, 0, -nonzero()],
				[90, 0, 0],
			);

			// Corners.
			ultracuber(
				[
					box_dims.inner().w,
					box_dims.thi().b + nonzero()*2,
					box_dims.thi().b + nonzero()*2,
				],
				[
					0,
					[0, true],
					0,
				],
				[0, 1, 1],
				[0, 0, -nonzero()],
				[90, 0, 0],
			);
		}
	}

	module DoveRelief_(){
		trany(box_pos_y + box_dims.thi().b + box_dims.thi().s - parting_line_relief)
		tranz(box_dims.pos().z - box_dims.h)
		ultracuber(
			[
				box_dims.inner().w - box_dims.thi().b*2 + parting_line_relief*2,
				box_dims.inner().l - box_dims.thi().b + box_dims.thi().s + parting_line_relief + nonzero(),
				channel_dims.h - channel_dims.slope + parting_line_relief,
			],
			[
				0,
				[0, true],
				0,
			],
			[0, 1, 1],
			[0, 0, -nonzero()],
		);
	}
}

module DessiccantBoxLid(){
	difference(){
		Main();

		FrontChampher_();

	}

	module Main(){
		tranz(box_dims.pos().z)
		trany(box_pos_y){
			difference(){
				ultracuber(
					[
						base_dims.w,
						top_dims.l - top_dims.upper_l,
						top_dims.h - top_dims.lower().h,
					],
					[
						parting_line_relief,
						[base_dims.radii.out.s, true],
						base_dims.radii.out.t,
					],
					[0, 1, -1],
					[0, 0, 0],
				);

				ultracuber(
					[
						hole(box_dims.w, box_dims.lid().clear),
						hole(box_dims.l, box_dims.lid().clear),
						top_dims.h - top_dims.lower().h - box_dims.lid().h,
					],
					[
						-parting_line_relief,
						0,
						0,
					],
					[0, 0, -1],
					[0, box_dims.l/2 - nonzero(), -box_dims.lid().h - nonzero()],
				);
			}
		}
	}

	module FrontChampher_(){
		trany(box_pos_y)
		tranz(box_dims.pos().z - box_dims.lid().h)
		ultracuber(
			[
				hole(box_dims.w, box_dims.lid().clear),
				top_dims.h - top_dims.lower().h - box_dims.lid().h,
				parting_line_relief*2,
			],
			[
				0,
				[0, true],
				-parting_line_relief,
			],
			[0, -1, -1],
			[0, 0, -nonzero()],
			[90, 0, 0],
		);
	}
}

