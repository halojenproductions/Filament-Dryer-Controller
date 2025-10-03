include <FDC_Main_Library.scad>
use <FDC_Main_Mocks.scad>
use <FDC_Main_Base.scad>



q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	#color("SeaGreen")
	BodyTop();
}

if(ex[1]){
	color("LightCyan")
	BodyBase();
}


// Ghosts.
%Mocks();


crosssections = object(
	heater_fan = PI * pow(heater_dims.fan_dia/2, 2),
	box_bottom = box_dims.w * box_dims.l,
	channel = channel_dims.w * channel_dims.h,
	intake = intake_dims.w * intake_dims.l,
);

echo(str(
	"\n\t Cross sections ",
	"\n\t Heater fan: ", crosssections.heater_fan,
	"\n\t Box bottom: ", crosssections.box_bottom,
	"\n\t Channel: ", crosssections.channel,
	"\n\t Intake: ", crosssections.intake,
"\n"));

assert(
	crosssections.heater_fan < crosssections.box_bottom, 
	"Box bottom area is too small"
);
assert(
	crosssections.heater_fan < crosssections.channel, 
	"Channel area is too small"
);
assert(
	crosssections.heater_fan < crosssections.intake, 
	"Intake area is too small"
);
