use <..\..\3D Printing\Library.scad>
line = [.42, .45, .2];

screen_board_dims=[36, 33.5, 1.0];
screen_screw_pitch = [30.5, 28.5];
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
screen_screw_hole_dia = 3;
screen_glass_dims = [34.5, 23, 1.6];
screen_visible_dims = [31, 16];
screen_standoff_z = line[2]*2;
screen_standoff_wid = line[0]*2;
screen_pos = [0, 10, 0];
screen_cham = 1.0;

screen_shroud_offset = line[0]*2;
screen_shroud_dims = [
	screen_board_dims.x + screen_shroud_offset*2, 
	screen_board_dims.y + screen_shroud_offset*2, 
	screen_standoff_z + screen_glass_dims.z + screen_board_dims.z,
];


face_dims = [50, 65, 2.0];
face_thick = 1.4;
face_in_offset = 2;
face_rad = 5;
face_cham = 1.2;

led_dia = 3.0;
led_shroud_dia = hole(led_dia) + line[0]*4;
led_pitch = 18;

	header_pitch = 2.54;
	header_dia = 2.5;
	header_hei = 2.5;

frame_unnamed_dim = 4;
frame_dims = [
	screen_board_dims.x + frame_unnamed_dim*2,
	screen_board_dims.y + frame_unnamed_dim*2,
	header_hei,
];
frame_locator_dia = hole(screen_screw_hole_dia) + line[0]*4;
frame_screw_hole_dia = 2; // M2
frame_insert_dims = [hole(2.8), 3];
frame_screw_post_dia = frame_insert_dims[0] + line[0]*6;
frame_top_dims = [
	screen_shroud_dims.x, 
	max(led_dia + screen_shroud_offset*2, frame_screw_post_dia), 
	frame_dims.z,
];
frame_screw_pitch_x = screen_screw_pitch.x;
frame_screw_pos = [
	[
		-frame_screw_pitch_x/2, 
		screen_board_dims.y/2 + frame_top_dims.y/2,
	],
	[
		frame_screw_pitch_x/2, 
		screen_board_dims.y/2 + frame_top_dims.y/2
	],
	// TODO bottom screws
];

led_pos = [
	[
		-led_pitch/2, 
		frame_screw_pos[0].y,
	],
	[
		led_pitch/2, 
		frame_screw_pos[1].y,
	],
];

button_dims = [16, 12, screen_shroud_dims.z + frame_dims.z - 3];
button_cham = screen_cham;
button_flange_offset = line[0]*2;
button_hinge_len = 2;
button_hinge_thick = line[2]*2;

button_anchor_dims = [
	button_dims.x + 5, 
	2,
	button_dims.z,
];

button_pos = [
	0, 
	screen_pos.y - 2 - screen_shroud_dims.y/2 
	- button_anchor_dims.y - button_hinge_len 
	- button_flange_offset - button_dims.y/2, 
	face_thick + button_dims.z
];

 // Relative to button position.
button_anchor_pos_y = button_dims.y/2 + button_flange_offset 
+ button_hinge_len + button_anchor_dims.y/2;


pcb_dims = [
	frame_dims.x, 
	60, 
	1.6
];



