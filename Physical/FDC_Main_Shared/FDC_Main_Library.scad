use <..\..\..\3D Printing\_Shared\Library.scad>
use <..\..\..\3D Printing\_Shared\Hardware.scad>
use <..\..\..\3D Printing\_Shared\UltraCuber2.scad>

// Min crosssectional air flow area 2124 mm²

/*
	Dimensions.
*/
parting_line_relief = .4;

global_dims = object(
	radii = object(
		in = object(
			b = [.4, true],
			s = [1, true],
			t = .5,
		),
	),
	divs = 4,
);

base_side_rad = 2;
base_dims = object(
	w = 85,
	l = 165, // Original intake section = 210,
	h = 45,
	thick = object(
		b = nearest_layer(1),
		s = 6,
		t = nearest_layer(1),
	),
	radii = object(
		out = object(
			b = .4,
			s = base_side_rad*1.5,
			t = 1,
		),
		in = object(
			b = .4,
			s = base_side_rad*.5,
			t = .5,
		),
	),
);

heater_dims = object(
	bot = object(
		w = 74,
		l = 127,
	),
	// Fan side is considered top.
	top = object(
		w = 73,
		l = 126,
	),
	h = 36,
	radii = object(
		b = 1,
		s = 8,
		t = 1.5,
	),
	fan_pos = 35, // End to bottom of fan.
	fan_dia = 58,
);

heater_sleeve_dims = object(
	l = heater_dims.h + base_dims.thick.s + global_dims.divs,
);

electronics_dims = object(
	w = 70,
	l = 80,
	h = 18,
	ribbon_connector_l = 10,
);

box_dims = object(
	w = 70,
	l = 65,
);

top_dims = object(
	w = base_dims.w,
	l = base_dims.l,
	upper_l = base_dims.thick.s + electronics_dims.l
	 + global_dims.divs,
	h = electronics_dims.h +(heater_dims.fan_pos - base_dims.h)
	 + heater_dims.fan_dia + 2,
	thick = object(
		t = nearest_layer(1),
	),
);

sensor_dims = object(
	w = 26.5,
	l = 59,
	h = 13.5,
);

channel_dims = object(
	w = 70,
	l = base_dims.l - electronics_dims.l 
	- base_dims.thick.s*2 - global_dims.divs,
	h = base_dims.h,
	slope = base_dims.h/2,
);

echo(str(
	"\n\t channel_dims: ", channel_dims,
"\n"));

intake_dims = object(
	w = channel_dims.w,
	l = base_dims.thick.s,
	h = channel_dims.h,
	ridge = base_dims.thick.s/4,
	border = lines(4),
	louvres = object(
		thick = lines(2),
		count = 6,
		angle = 50,
	),
);


interface_inset = base_dims.thick.s/2;
interface_outset = 2.5;
interface_clip_dims = object(
	w = interface_outset,
	l = 15,
	elev = layers(4),
	overhang = lines(2),
);

interface_dims = object(
	w = channel_dims.w + interface_outset*2,
	l = top_dims.l - interface_outset*2,
	h = interface_clip_dims.elev + interface_clip_dims.overhang*2
	 + layers(2),
	radii = object(
		s = base_dims.radii.out.s,
		t = interface_outset,
	),
	seal = object(
		size = interface_outset,
	),
);

top_fastener_dims = object(
	screw = object(
		thread_dia = 2.6, // M2.6 self tapping machine screw.
		length = 10,
		head_dia = 4.1,
		pen = 6, // Penetration below the position.
		//dep = 4, // Depth from position to top surface.
		flat = true,
	),
	boss_thick = line_wid(0)*2 + line_wid(1),
	clear_rad = 7.5,
	shroud = object(
		dia = 8,
		h = 6,
		getRise = function()(
			top_fastener_dims.shroud.h 
			+ top_fastener_dims.clear_rad 
			+ top_fastener_dims.shroud.dia
		),
	),
);

//fx = function(x)x+2;
xxx=object(this="this", that=12, func=function()xxx.this);
echo(xxx, xxx.func() );

/*
	Positions.
*/
heater_pos = object(
	y = base_dims.thick.s + electronics_dims.ribbon_connector_l,
	z = electronics_dims.h,
);
fan_abs_pos_z = heater_pos.z + heater_dims.fan_pos + heater_dims.fan_dia/2;
channel_pos_y = base_dims.thick.s + electronics_dims.l + global_dims.divs;
box_pos_y = channel_pos_y;
sensor_pos = object(
	y = channel_pos_y + channel_dims.slope + sensor_dims.w/2,
);
clip_pos = object(
	a = object(
		y = heater_pos.y + heater_dims.h 
		+ global_dims.divs + interface_clip_dims.l/2,
		inner_w = electronics_dims.w,
	),
	b = object(
		y = top_dims.l - base_dims.thick.s - interface_clip_dims.l
		- interface_clip_dims.l,
		inner_w = channel_dims.w,
	),
);




