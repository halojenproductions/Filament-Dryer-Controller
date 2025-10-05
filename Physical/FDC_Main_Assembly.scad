include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Mocks.scad>
use <FDC_Main_Base.scad>
use <FDC_Main_Top.scad>
use <FDC_Main_Cover.scad>


q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	color("MediumSeaGreen")
	BodyTop();
}

if(ex[1]){
	color("Turquoise")
	BodyBase();
}

if(ex[2]){
	*color("PaleVioletRed")
	Cover();
}


// Ghosts.
%Mocks();


echo(str(
	"\n\t Dimensions ",
	"\n\t Width: ", base_dims.w,
	"\n\t Height: ", base_dims.h + top_dims.h,
	"\n\t Length: ", base_dims.l,
	"\n\t Base height: ", base_dims.h,
	"\n\t Top length: ", top_dims.l,
	"\n\t Top height: ", top_dims.h,
"\n"));

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
