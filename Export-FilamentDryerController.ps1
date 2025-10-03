# Export 3D Parts for Filament Dryer Controller project
# Calls the shared OpenSCAD export script with project-specific model definitions

# Project-specific paths (relative to this script)
$scadDir = "Physical"
$outDir = "Physical\FDC_Panel_Models"

# PANEL model definitions
$models = @(
	@{ ScadFile = "FDC_Panel_Front"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Front"; Suffix = "Lenses"; Ex = 2; Q = 100 },
	@{ ScadFile = "FDC_Panel_Front"; Suffix = "Castle1"; Ex = 3; Q = 100 },
	@{ ScadFile = "FDC_Panel_Front"; Suffix = "Castle2"; Ex = 4; Q = 100 },
	@{ ScadFile = "FDC_Panel_Frame"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Button"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Back"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Back"; Suffix = "Solid"; Ex = 2; Q = 100 }
)

# Call the shared export script
Export3dModels.ps1 -Models $models -ScadDir $scadDir -OutDir $outDir


$outDir = "Physical\FDC_Main_Models"

# MAIN model definitions
$models = @(
	@{ ScadFile = "FDC_Main_Base"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Main_Top"; Suffix = ""; Ex = 2; Q = 100 },
	@{ ScadFile = "FDC_Panel_Front"; Suffix = "Castle1"; Ex = 3; Q = 100 },
	@{ ScadFile = "FDC_Panel_Front"; Suffix = "Castle2"; Ex = 4; Q = 100 },
	@{ ScadFile = "FDC_Panel_Frame"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Button"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Back"; Suffix = ""; Ex = 1; Q = 100 },
	@{ ScadFile = "FDC_Panel_Back"; Suffix = "Solid"; Ex = 2; Q = 100 }
)

# Call the shared export script
Export3dModels.ps1 -Models $models -ScadDir $scadDir -OutDir $outDir

