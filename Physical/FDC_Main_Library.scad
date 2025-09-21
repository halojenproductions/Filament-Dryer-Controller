use <..\..\3D Printing\_Shared\Library.scad>
use <..\..\3D Printing\_Shared\Hardware.scad>
use <..\..\3D Printing\_Shared\UltraCuber2.scad>

/**
 * Dimensions.
 * 
 */
base_side_rad = 2;
base_dims = object(
	w = 85,
	l = 210,
	h = 35,
	thick = object(
		b = nearest_layer(1),
		s = 4,
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
	l = heater_dims.h + base_dims.thick.s,
);

box_dims = object(
	w = 75,
	l = 35,
);

sensor_dims = object(
	w = 26.5,
	l = 13.5,
	h = 53.5,
);

chamber_dims = object(
	l = 25,
);

top_dims = object(
	w = base_dims.w,
	l = heater_sleeve_dims.l + box_dims.l + chamber_dims.l,
	h = (heater_dims.fan_pos - base_dims.h) + heater_dims.fan_dia,
);



 /**
 * Positions.
 * 
 */
 box_pos_y = base_dims.l - heater_sleeve_dims.l;