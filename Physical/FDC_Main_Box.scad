include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	DessiccantBox();
}

if(ex[1]){
	
}

module DessiccantBox(){
	difference(){
		Main();

		BottomMesh_();
		BottomSideMesh_();
	}

	module Main(){
		tranz(box_dims.pos().z)
		trany(box_pos_y){
			difference(){
				ultracuber(
					[
						box_dims.w,
						box_dims.l,
						box_dims.h,
					],
					[
						box_dims.thi().b,
						[box_dims.thi().s, true],
						0,
					],
					[0, 1, -1],
					[0, 0, 0],
				);

				ultracuber(
					[
						box_dims.inner().w,
						box_dims.inner().l,
						box_dims.inner().h - box_dims.thi().mesh + nonzero()*2,
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
	}

	module BottomMesh_(){
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


		trany(box_pos_y - parting_line_relief)
		tranz(box_dims.pos().z - box_dims.h)
		ultracuber(
			[
				box_dims.inner().w - box_dims.thi().b*2 + parting_line_relief*2,
				box_dims.inner().l - box_dims.thi().b + box_dims.thi().s + parting_line_relief,
				box_dims.thi().mesh + box_dims.thi().b + parting_line_relief,
			],
			[
				0,
				[0, true],
				0,
			],
			[0, 1, 1],
			[0, box_dims.thi().s + box_dims.thi().b, -nonzero()],
		);

	}

	module BottomSideMesh_(){
		#trany(box_pos_y + box_dims.l + nonzero())
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
		}

	}
}