use <..\..\3D Printing\Library.scad>
use <..\..\3D Printing\Hardware.scad>
include <FDC_Panel_Library.scad>
use <FDC_Panel_Mocks.scad>
use <FDC_Panel_Frame.scad>
use <FDC_Panel_Button.scad>

q = 100;
ex = [1,0,1,0];

/* [Hidden] */
$fn = $preview ? 50 : q;

screw_post_end = back_dims.z - back_screw_post_len + (face_dims.z - face_thick);
post_shroud_len = back_dims.z - screw_post_end + back_screw_post_disc_thick;


maxscrewlen = back_inserts[2][0] + back_screw_post_disc_thick;
echo("Overpenetration: ", 
	back_inserts[2][0] - back_inserts[1]
);
echo("Max back screw len: ", 
	maxscrewlen
);
echo("Max container thick: ", 
	maxscrewlen - (back_inserts[1]/2 + back_screw_post_disc_thick)
);


if(ex[0]){
	Back();
}

if(ex[1]){
	Solid();
}


module Back() {
	difference(){
		union(){
			Shell();
			
			intersection(){
				Shrouds();

				ShellOutside();
			}
		}

		PostShrouds_();
		ScrewShrouds_();
	}

	Discs();

}


module Shell(){
	difference(){
		ShellOutside();

		#ShellInside_();
	}
}

module Solid(){
	Shrouds();
}


module ShellOutside(){
	Bottom();

	translate([0, 0, back_screw_post_dia])
	Sides();

	translate([0, 0, back_dims.z - back_perim_thick])
	Perimeter();

	module Perimeter(){
		supercuber(
			[
				[face_dims.x, face_dims.y], 
				[face_dims.x, face_dims.y], 
				back_perim_thick,
			], 
			[1, 1, 0], 
			[0, 0, face_rad],
			[1, 0, 0],
		);
	}

	module Sides(){
		supercuber(
			[
				[face_dims.x, face_dims.y], 
				[face_dims.x, face_dims.y], 
				back_dims.z - back_screw_post_dia - back_perim_thick,
			], 
			[1, 1, 0], 
			[0, 0, face_rad],
			[1, 0, 0],
		);
	}

	module Bottom(){
		inset = face_rad - hole(back_screw_dims[1], .2)/2 - line[0]*2;
		hull(){
			translate([0, 0, back_screw_post_dia])
			cuber(
				[
					face_dims.x,
					face_dims.y,
					nonzero()
				],
				[1, 1, 0], 
				face_rad
			);

			cuber(
				[
					face_dims.x - inset*2, 
					face_dims.y - inset*2,
					nonzero()
				],
				[1, 1, 0], 
				face_rad - inset
			);
		}
	}
}

module ShellInside_(){
	
	Bottom_();

	translate([0, 0, back_screw_post_dia])
	Sides_();

	translate([0, 0, back_dims.z - back_perim_thick])
	Perimeter_();

	module Perimeter_(){
		translate([0, 0, -nonzero()])
		supercuber(
			[
				[
					face_dims.x - face_in_offset*2, 
					face_dims.y - face_in_offset*2
				], 
				[
					face_dims.x - face_in_offset*2, 
					face_dims.y - face_in_offset*2
				], 
				back_perim_thick + nonzero(1),
			], 
			[1, 1, 0], 
			[0, 0, face_rad],
			[1, 0, 0],
		);
	}

	module Sides_(){
		translate([0, 0, -nonzero()])
		cuber(
			[
				face_dims.x - face_in_offset*2 - back_screw_post_dia, 
				face_dims.y - face_in_offset*2 - back_screw_post_dia*2,
				back_dims.z - back_screw_post_dia - back_perim_thick + nonzero(),
			], 
			[1, 1, 0], 
			2,
		);
	}

	module Bottom_(){
		hull(){
			translate([0, 0, back_screw_post_dia])
			cuber(
				[
					face_dims.x - face_in_offset*2 - back_screw_post_dia, 
					face_dims.y - face_in_offset*2 - back_screw_post_dia*2,
					nonzero()
				],
				[1, 1, 0], 
				2
			);

			translate([0, 0, back_shell_thick])
			cuber(
				[
					face_dims.x - face_in_offset*2 - back_screw_post_dia*4, 
					face_dims.y - face_in_offset*2 - back_screw_post_dia*2,
					nonzero()
				],
				[1, 1, 0], 
				face_rad/2
			);
		}
	}
}


module Shrouds(){
	for(pos = back_screw_pos){
		Shroud(pos);
	}

	module Shroud(pos){
		translate(pos)
		coner(
			back_screw_post_dia + back_screw_post_shroud_thick*2, 
			back_screw_post_dia + back_screw_post_shroud_thick*2, 
			back_dims.z,
			[1, 1, 0], 
			back_screw_post_shroud_thick, 
			0,
			true,
		);
	}
}

module Discs(){
	translate([0, 0, screw_post_end - back_screw_post_disc_thick])
	for(pos = back_screw_pos){
		Disc(pos);
	}

	module Disc(pos){
		translate(pos)
		difference(){
			cylr(
				hole(back_screw_post_dia), 
				back_screw_post_disc_thick,
				[1, 1, 0], 
			);

			cylr(
				hole(back_screw_dims[0], .1), 
				back_screw_post_disc_thick + nonzero(),
				[1, 1, 0], 
			);

			translate([0, 0, -nonzero()*2])
			cuber(
				[
					hole(back_screw_thread_dia), 
					hole(back_screw_post_dia), 
					line[2],
				],
				[1, 1, 0], 
				0
			);

		}
	}
}


module PostShrouds_(){
	translate([0, 0, back_dims.z - post_shroud_len])
	for(pos = back_screw_pos){
		Shroud_(pos);
	}

	module Shroud_(pos){
		translate(pos)
		coner(
			hole(back_screw_post_dia), 
			hole(back_screw_post_dia), 
			post_shroud_len + nonzero(),
			[1, 1, 0], 
			0, 
			0,
			true,
		);
	}
}

module ScrewShrouds_(){
	translate([0, 0, -nonzero()])
	for(pos = back_screw_pos){
		Shroud_(pos);
	}

	module Shroud_(pos){
		translate(pos)
		coner(
			hole(back_screw_dims[1], .2), 
			hole(back_screw_dims[1], .2), 
			post_shroud_len + nonzero(),
			[1, 1, 0], 
			0, 
			0,
			true,
		);
	}
}

