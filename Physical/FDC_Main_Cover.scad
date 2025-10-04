include <FDC_Main_Shared/FDC_Main_Library.scad>
// use <FDC_Main_Shared/FDC_Main_Objects.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


if(ex[0]){
	Cover();
}

if(ex[1]){
	
}

module Cover(){
	translate([0, 0, base_dims.h])
	ultracuber(
		[
			cover_dims.w,
			cover_dims.l,
			cover_dims.h,
		],
		[
			cover_dims.radii.b,
			[cover_dims.radii.s, true],
			cover_dims.radii.t,
		],
		[0, 1, -1],
		[0, base_dims.thick.s/2, 0],
	);
}