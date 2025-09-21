use <..\..\3D Printing\_Shared\Library.scad>
use <..\..\3D Printing\_Shared\Hardware.scad>
use <..\..\3D Printing\_Shared\UltraCuber2.scad>

/**
 * Dimensions.
 * 
 */
base_side_rad = 2;
base_dims = object(
	w = 80,
	l = 210,
	h = 35,
	thick = object(
		b = nearest_layer(1),
		s = 2,
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
);
heater_fan_dia = 58;


 /**
 * Positions.
 * 
 */
heater_fan_pos = 35; // End to bottom of fan.
 