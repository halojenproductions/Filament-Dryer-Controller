use <..\..\3D Printing\_Shared\Library.scad>
use <..\..\3D Printing\_Shared\Hardware.scad>

/**
 * Dimensions.
 * 
 * Something i've learnt: 
 * Never make dimensions dependent on positions and always 
 * define positions after all dimensions are defined.
 */

line = [.42, .45, .2];

screen_board_dims=[36, 33.5, 1.0];
screen_screw_pitch = [30.5, 28.5];
screen_screw_hole_dia = 3;
screen_glass_dims = [34.5, 23, 1.6];
screen_window_shift_y = 2;
screen_visible_dims = [31, 16];
screen_standoff_z = line[2]*2;
screen_standoff_wid = line[0]*2;
screen_cham = 1.0;

screen_shroud_offset = line[0]*2;
screen_shroud_dims = [
	screen_board_dims.x + screen_shroud_offset*2, 
	screen_board_dims.y + screen_shroud_offset*2, 
	screen_standoff_z + screen_glass_dims.z + screen_board_dims.z,
];

back_screw_dims = [3, 5.5, 10, 3, 0]; // M3.
back_screw_thread_dia = 3; // M3.
back_screw_post_len = 9;
back_inserts = [back_screw_dims[0], 4, [back_screw_post_len-1, true]];
back_screw_post_dia = heatset_insert_hole(back_inserts[0]) + line[0]*6;
back_screw_post_shroud_thick = 2;
back_screw_post_disc_thick = 3;


face_thick = 1.4;
face_in_offset = 2;
face_rad = back_screw_post_dia/2 + face_in_offset;
face_cham = 1.2;

led_dia = 3.0;
led_shroud_dia = led_dia + line[0]*4;
led_pitch = 20.5;

	header_pitch = 2.54;
	header_dia = 2.5;
	header_hei = 2.5;

switch_hei = 3.1;

frame_dims = [
	screen_shroud_dims.x,
	screen_shroud_dims.y,
	header_hei,
];
frame_locator_dia = hole(screen_screw_hole_dia) + line[0]*4;
pcb_screw_dims = [2, 6]; // M2
pcb_inserts = [pcb_screw_dims[0], 2, .6];
pcb_screw_post_dia = heatset_insert_hole(pcb_inserts[0]) + line[0]*6;
frame_top_dims = [
	screen_shroud_dims.x, 
	max(led_shroud_dia, pcb_screw_post_dia), 
	frame_dims.z,
];
frame_screw_pitch_x = screen_screw_pitch.x;

button_dims = [16, 12, screen_shroud_dims.z + frame_dims.z - 3];
button_hole_cham = screen_cham;
button_flange_offset = line[0]*2;
button_hinge_len = 2;
button_hinge_thick = line[2]*3;
button_cham = .5;
button_anchor_dims = [
	button_dims.x + 5, 
	2,
	button_dims.z,
];

pcb_dims = [
	38, 
	58, 
	1.6
];
pcb_header_dims = [10.5, 5, 3.66];
conn_hei = 6;
pcb_screw_post_len = screen_shroud_dims.z + frame_dims.z;

back_shell_thick = 3;
back_perim_thick = 1.6;

/**
 * Positions.
 * 
 * Something i've learnt: 
 * Never make dimensions dependent on positions and always 
 * define positions after all dimensions are defined.
 */

screen_pos = [0, 6.5, face_thick + screen_standoff_z];

screen_screw_pos = [
	[
		-screen_screw_pitch.x/2, 
		screen_screw_pitch.y/2 ,
	],
	[
		screen_screw_pitch.x/2, 
		screen_screw_pitch.y/2
	],
	[
		-screen_screw_pitch.x/2, 
		-screen_screw_pitch.y/2
	],
	[
		screen_screw_pitch.x/2, 
		-screen_screw_pitch.y/2
	],
];

button_pos = [
	0, 
	screen_pos.y - screen_shroud_dims.y/2 
		- button_anchor_dims.y - button_hinge_len 
		- button_flange_offset - button_dims.y/2, 
	face_thick + button_dims.z
];

 // Relative to button position.
button_anchor_pos_y = button_dims.y/2 + button_flange_offset 
+ button_hinge_len + button_anchor_dims.y/2;

frame_pos = [
	0, 
	screen_pos.y,
	face_thick + screen_shroud_dims.z
];

pcb_pos = [
	0,
	0,
	frame_pos.z + frame_dims.z
];

frame_screw_pos = [
	[ // Relative to frame position.
		-frame_screw_pitch_x/2, 
		screen_board_dims.y/2 + pcb_screw_post_dia/2,
	],
	[ // Relative to frame position.
		frame_screw_pitch_x/2, 
		screen_board_dims.y/2 + frame_top_dims.y/2,
	],
	[
		-frame_screw_pitch_x/2, 
		button_pos.y - button_dims.y/2 
		- button_flange_offset + pcb_screw_post_dia/2
	],
	[ 
		frame_screw_pitch_x/2, 
		button_pos.y - button_dims.y/2 
		- button_flange_offset + pcb_screw_post_dia/2
	],
];

pcb_screw_pos = [
	[
		-frame_screw_pitch_x/2, 
		screen_board_dims.y/2 + pcb_screw_post_dia/2  + screen_pos.y,
	],
	[
		frame_screw_pitch_x/2, 
		screen_board_dims.y/2 + frame_top_dims.y/2 + screen_pos.y,
	],
	[
		-frame_screw_pitch_x/2, 
		button_pos.y - button_dims.y/2 
		- button_flange_offset + pcb_screw_post_dia/2
	],
	[ 
		frame_screw_pitch_x/2, 
		button_pos.y - button_dims.y/2 
		- button_flange_offset + pcb_screw_post_dia/2
	],
];
pcb_screw_pos_z = pcb_pos.z + pcb_dims.z;

pcb_insert_pos = [
	[
		pcb_screw_pos[0].x,
		pcb_screw_pos[0].y + screen_pos.y, 
		frame_pos.z,
	],
	[
		pcb_screw_pos[1].x,
		pcb_screw_pos[1].y + screen_pos.y, 
		frame_pos.z,
	],
	[
		pcb_screw_pos[2].x,
		pcb_screw_pos[2].y, 
		pcb_pos.z,
	],
	[
		pcb_screw_pos[3].x,
		pcb_screw_pos[3].y, 
		pcb_pos.z,
	],
];

pcb_header_pos_y = screen_board_dims.y/2 + screen_pos.y 
	- pcb_header_dims.y/2 - header_pitch/2;

assert(
	(screen_shroud_dims.z - pcb_inserts[1])
	>= 0,
	"Insert would be in the face."
);

led_pos = [ // Relative to screen position.
	[
		-led_pitch/2, 
		frame_screw_pos[0].y,
	],
	[
		led_pitch/2, 
		frame_screw_pos[1].y,
	],
];


back_screw_pos = [
	[
		-frame_dims.x/2 - 1, 
		1 + pcb_screw_pos[0].y + 
			(frame_top_dims.y + screen_shroud_offset)/2 + 
			back_screw_post_dia/2 + back_screw_post_shroud_thick,
	],
	[
		frame_dims.x/2 + 1, 
		1 + pcb_screw_pos[0].y + 
			(frame_top_dims.y + screen_shroud_offset)/2 + 
			back_screw_post_dia/2 + back_screw_post_shroud_thick,
	],
	[
		-frame_dims.x/2 - 1, 
		-1 - pcb_screw_pos[0].y - 
			(frame_top_dims.y + screen_shroud_offset)/2 - 
			back_screw_post_dia/2 - back_screw_post_shroud_thick,
	],
	[
		frame_dims.x/2 + 1, 
		-1 - pcb_screw_pos[0].y - 
			(frame_top_dims.y + screen_shroud_offset)/2 - 
			back_screw_post_dia/2 - back_screw_post_shroud_thick,
	],
];


/**
 * Outside dims.
 * 
 * Ok so i decided there's an exception to the rule. The outermost 
 * thing/things can have their dimensions depend on positions.
 */

face_dims = [
	abs(back_screw_pos[0].x) + back_screw_pos[1].x +
		back_screw_post_dia + face_in_offset*2,
	back_screw_pos[0].y + abs(back_screw_pos[2].y) + 
		back_screw_post_dia + face_in_offset*2,
	2.0
];

back_dims = [
	face_dims.x, 
	face_dims.y, 
	pcb_pos.z + pcb_dims.z + max(pcb_header_dims.z, conn_hei) + 
		back_shell_thick - face_thick,
];



