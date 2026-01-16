include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [
	1, // Box.
	0, // Lid.
	1, // Lid mod.
	1, // Support.
];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	DessiccantBox();
}

if(ex[1]){
	DessiccantBoxLid();
}

if(ex[3]){
	DessiccantBoxSupport();
}

module DessiccantBox(){
	difference(){
		union(){
			Main();
			LidInterface();
		}

		Main_();
		Duct_();
		BottomMesh_();
		BottomSideMesh_();
		TopSideMesh_();
		BottomDoveRelief_();
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
					-parting_line_relief,
				],
				[0, 0, -1],
				[0, box_dims.l/2, nonzero()],
			);
		}
	}

	module Duct_(){
		// Duct.
		*trany(box_pos_y - nonzero())
		tranz(fan_low_side_pos_z)
		rotate([-90, 0, 0])
		ultracuber(
			[
				box_dims.inner().w,
				duct_dims.h,
				box_dims.inner().l + box_dims.thi().s,
			],
			[
				-parting_line_relief,
				0,
				0,
			],
			[0, 0, 1],
			[0, -nonzero(), -nonzero()],
		);
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

	module TopSideMesh_(){
		trany(box_pos_y + nonzero())
		tranz(fan_low_side_pos_z)
		{
			ultracuber(
				[
					box_dims.inner().w,
					duct_dims.h,
					box_dims.thi().mesh + nonzero()*2,
				],
				[
					0,
					[0, true],
					box_dims.thi().b,
				],
				[0, 0, -1],
				[0, 0, -nonzero()],
				[90, 0, 0],
			);

			// Dove relief.
			ultracuber(
				[
					box_dims.inner().w - box_dims.thi().b*2 + parting_line_relief*2,
					box_dims.thi().s + nonzero()*2,
					duct_dims.h - box_dims.thi().b*2 + parting_line_relief*2,
				],
				[
					0,
					[0, true],
					0,
				],
				[0, 1, 0],
				[0, -nonzero()*2, -nonzero()],
			);
		}
	}

	module BottomDoveRelief_(){
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

module DessiccantBoxSupport(){
	height = duct_dims.h - box_dims.lid().h + parting_line_relief - layers(2);

	trany(box_pos_y + nonzero())
	tranz(box_dims.pos().z - box_dims.lid().h)
	{
		ultracuber(
			[
				box_dims.inner().w - box_dims.thi().b*2 + parting_line_relief*2 - 1,
				box_dims.thi().s,
				// duct_dims.h - box_dims.thi().b*2 + parting_line_relief*2,
				height,
			],
			[
				0,
				[0, true],
				0,
			],
			[0, 1, -1],
			[0, -nonzero()*2, 0],
		);

		ultracuber(
			[
				box_dims.inner().w - box_dims.thi().b*2 + parting_line_relief*2 - 1,
				box_dims.thi().s - 1,
				// duct_dims.h - box_dims.thi().b*2 + parting_line_relief*2,
				height/2,
			],
			[
				-.5,
				[0, true],
				-.5,
			],
			[0, 1, -1],
			[0, .5-nonzero()*2, 0],
		);
	}
}

module DessiccantBoxLid(){
	difference(){
		Main();

		Main_();
		FrontChampher_();
		LidInterface_();

	}

	module Main(){
		tranz(box_dims.pos().z)
		trany(box_pos_y){
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
		}
	}

	module Main_(){
		tranz(box_dims.pos().z)
		trany(box_pos_y){
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

		// Duct.
		trany(box_pos_y - nonzero())
		tranz(fan_low_side_pos_z)
		rotate([-90, 0, 0])
		ultracuber(
			[
				box_dims.inner().w,
				duct_dims.h,
				box_dims.inner().l + box_dims.thi().s,
			],
			[
				-parting_line_relief,
				0,
				0,
			],
			[0, 0, 1],
			[0, -nonzero(), -nonzero()],
		);
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

		trany(box_pos_y - nonzero())
		rotx(-90)
		hull(){
			extrude(parting_line_relief, 1)
			projection()
			rotx(90)
			LidInterface_();

			extrude(0, 1)
			offset(parting_line_relief)
			projection()
			rotx(90)
			LidInterface_();
		}
	}

	module LidInterface_(){
		tranz(box_dims.pos().z - box_dims.lid().h)
		trany(box_pos_y)
		intersection(){
			ultracuber(
				[
					hole(box_dims.w, box_dims.lid().clear),
					box_dims.l,
					box_dims.interface().h,
				],
				[
					0,
					[0, true],
					-box_dims.interface().h,
				],
				[0, 1, -1],
				[0, 0, 0],
			);
		}
	}
}

