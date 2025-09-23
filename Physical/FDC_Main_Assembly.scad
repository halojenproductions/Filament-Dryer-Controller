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

echo(str(
	"\n\t Cross sections ",
	"\n\t Heater fan: ", PI * pow(heater_dims.fan_dia/2, 2),
	"\n\t Box bottom: ", box_dims.w * box_dims.l,
	"\n\t Channel: ", channel_dims.w * channel_dims.h,
	"\n\t Intake: ", intake_dims.w * intake_dims.l,
"\n"));
