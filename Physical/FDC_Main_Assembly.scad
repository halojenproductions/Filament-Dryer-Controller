include <FDC_Main_Shared/FDC_Main_Library.scad>
use <FDC_Main_Shared/FDC_Main_Mocks.scad>
use <FDC_Main_Base.scad>
use <FDC_Main_Top.scad>
use <FDC_Main_Intake.scad>
use <FDC_Main_Box.scad>


q = 100;
ex = [
	1, // Body top upper.
	1, // Body top lower.
	1, // Body base.
	1, // Intake.
	1, // Dessiccant box.
];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	// color("Tan")
	%render(10)
	BodyTop();
}

if(ex[1]){
	// color("MediumSeaGreen")
	%render(10)
	BodyTop(false);
}

if(ex[2]){
	// color("Turquoise")
	%render(10)
	BodyBase();
}

if(ex[3]){
	// color("PaleVioletRed")
	%render(10)
	Intake();
}

if(ex[4]){
	// color("PaleVioletRed")
	render(10)
	DessiccantBox();
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
	duct = duct_dims.w * duct_dims.h,
	box_bottom = box_dims.w * box_dims.l,
	channel = channel_dims.w * channel_dims.h,
	intake = intake_vent_dims.w * intake_vent_dims.h,
);

echo(str(
	"\n\t Cross sections ",
	"\n\t Heater fan: ", crosssections.heater_fan,
	"\n\t Box bottom: ", crosssections.box_bottom,
	"\n\t Duct: ", crosssections.duct,
	"\n\t Channel: ", crosssections.channel,
	"\n\t Intake: ", crosssections.intake,
"\n"));

assert(
	crosssections.heater_fan < crosssections.box_bottom, 
	"Box bottom area is too small."
);
assert(
	crosssections.heater_fan < crosssections.channel, 
	"Channel area is too small."
);
assert(
	crosssections.heater_fan < crosssections.duct, 
	"Duct area is too small."
);
assert(
	crosssections.heater_fan < crosssections.intake, 
	"Intake area is too small."
);
