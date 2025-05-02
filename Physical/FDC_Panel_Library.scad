use <..\..\3D Printing\Library.scad>
line = [.42, .45, .2];

screen_board_dims=[36, 33.5, 1.2];
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
screen_glass_dims = [34.5, 23, 1.8];
screen_visible_dims = [31, 16];
screen_standoff_z = line[2]*2;
screen_standoff_wid = line[0]*2;
screen_pos = [0, 10, 0];
screen_cham = 1.0;

face_dims = [50, 60, 2.0];
face_thick = 1.2;
face_in_offset = 2;
face_rad = 5;
face_cham = 1.2;

button_dims = [16, 12];
button_pos = [0, -15, 0];
button_cham = screen_cham;
button_standoff_z = line[2]*2;
button_standoff_wid = line[0]*2;

	header_pitch = 2.54;
	header_dia = 2.5;
	header_hei = 2.5;

screwpost_pitch_top = 35;
screwpost_pitch_bot = 35;
screwpost_dia = 5;

frame_unnamed_dim = 5;
frame_dims = [
	screen_board_dims.x + frame_unnamed_dim*2,
	screen_board_dims.y + frame_unnamed_dim*2,
	header_hei,
];

pcb_dims = [
	frame_dims.x, 
	60, 
	1.6
];




