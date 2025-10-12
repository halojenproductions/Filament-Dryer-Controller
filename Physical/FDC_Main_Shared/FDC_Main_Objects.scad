include <FDC_Main_Library.scad>

q = 100;
ex = [1,1,1,1];

/* [Hidden] */
$fn = $preview ? 50 : q;


module Heater_(){
	translate([0, heater_pos.y, heater_pos.z])
	rotate([0, 0, 180])
	ultracuber(
		[
			hole(heater_dims.bot.w),
			heater_dims.bot.l,
			hole(heater_dims.h),
			hole(heater_dims.top.w),
			heater_dims.top.l,
		],
		[
			[rad_neg(heater_dims.radii.b), true],
			[rad_neg(heater_dims.radii.s), true],
			[rad_neg(heater_dims.radii.t), true],
		],
		[0, 1, 1],
		[0, 0, 0],
		[90, 0, 0],
	);
}


module TopScrews(dep=0, neg=false){
	mover(-base_dims.w, -top_fastener_dims.shroud.dia/2)
	TopScrew_(dep, neg);
	mover(base_dims.w, -top_fastener_dims.shroud.dia/2)
	TopScrew_(dep, neg);

	module TopScrew_(dep=0, neg=false){
		trany(base_dims.l - top_dims.l - top_fastener_dims.clear_rad)
		machine_screw(
			[
				top_fastener_dims.screw.thread_dia, 
				top_fastener_dims.screw.length, 
				top_fastener_dims.screw.head_dia, 
			], 
			[0, 0, base_dims.h],
			top_fastener_dims.screw.pen,
			dep,
			[0, 0],
			neg,
			top_fastener_dims.screw.flat,
		);
	}
}


module Clips(neg=false){
	ClipPair(clip_pos.a);
	ClipPair(clip_pos.b);
	// TODO: End slot.

	module ClipPair(clip_spec){
		trany(clip_spec.y)
		tranz(base_dims.h)
			difference(){
				union(){
					// Cap.
					ultracuber(
						dims = tern(!neg, 
							[
								interface_dims.w + interface_clip_dims.overhang*2,
								interface_clip_dims.l,
								interface_dims.h - interface_clip_dims.elev
								 - nonzero(),
							],
							[
								interface_dims.w + interface_clip_dims.overhang*2,
								interface_clip_dims.l,
								interface_dims.h - interface_clip_dims.elev
								 + interface_outset - nonzero(),
							],
						),
						cham = tern(!neg, 
							[
								interface_clip_dims.overhang,
								[interface_outset, true],
								interface_clip_dims.overhang,
							],
							[
								interface_clip_dims.overhang,
								[interface_outset, true],
								interface_dims.radii.t + interface_outset,
							],
						),
						[0, 0, 1],
						[0, 0, interface_clip_dims.elev-nonzero()],
					);

					// Stalk.
					ultracuber(
						dims = [
							interface_dims.w,
							interface_clip_dims.l,
							interface_clip_dims.elev + interface_clip_dims.overhang
							+ base_dims.radii.in.t,
						],
						[
							0,
							[interface_outset - interface_clip_dims.overhang, true],
							0,
						],
						[0, 0, 1],
						[0, 0, -base_dims.radii.in.t-nonzero()],
					);

					// Slot.
					*ultracuber(
						dims = [
							interface_dims.w,
							interface_clip_dims.l,
							interface_dims.h - interface_clip_dims.elev
							 - nonzero(),
						],
						[
							0,
							[interface_outset, true],
							0,
						],
						[0, 0, 1],
						[0, interface_clip_dims.l, interface_clip_dims.elev-nonzero()],
					);
				}

				ultracuber(
					dims = [
						clip_spec.inner_w,
						interface_clip_dims.l + nonzero(1),
						interface_dims.h + base_dims.radii.in.t
						 + interface_outset + nonzero(1),
					],
					[0, 0, 0],
					[0, 0, 1],
					[0, 0, -base_dims.radii.in.t-nonzero(1)],
				);

				// ultracuber(
				// 	[
				// 		channel_dims.w,
				// 		top_dims.l - base_dims.thick.s*2,
				// 		interface_dims.h + nonzero(1),
				// 	],
				// 	[0, 0, 0],
				// 	[0, 0, 1],
				// 	[0, 0, -nonzero(1)],
				// );
			}
	}

	// module Seal(){
	// 	translate([0, top_dims.l/2, base_dims.h])
	// 	difference(){
	// 		ultracuber(
	// 			[
	// 				base_dims.w,
	// 				top_dims.l,
	// 				interface_dims.h + cover_dims.h - nonzero(),
	// 			],
	// 			[
	// 				0,
	// 				[base_dims.radii.out.s, true],
	// 				tern(neg, 0, parting_line_relief),
	// 			],
	// 			[0, 0, 1],
	// 			[0, 0, -cover_dims.h],
	// 		);

	// 		ultracuber(
	// 			[
	// 				tern(neg, interface_dims.w, hole(interface_dims.w)),
	// 				tern(neg, interface_dims.l, hole(interface_dims.l)),
	// 				interface_dims.h + cover_dims.h + nonzero(),
	// 			],
	// 			[
	// 				0,
	// 				[interface_dims.radii.s, true],
	// 				-parting_line_relief,
	// 			],
	// 			[0, 0, 1],
	// 			[0, 0, -cover_dims.h - nonzero()],
	// 		);

	// 		// Channel.
	// 		ultracuber(
	// 			[
	// 				tern(neg, channel_dims.w, hole(channel_dims.w)),
	// 				interface_inset,
	// 				interface_dims.h + cover_dims.h + nonzero(),
	// 			],
	// 			[0, 0, 0],
	// 			[0, -1, 1],
	// 			[0, top_dims.l/2 + nonzero(), -cover_dims.h - nonzero()],
	// 		);
	// 	}
	// }
}
