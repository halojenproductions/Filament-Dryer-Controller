@SET kicadcli="C:\Program Files\KiCad\8.0\bin\kicad-cli.exe"
@SET python="C:\Program Files\KiCad\8.0\bin\python.exe"
@SET bom="C:\Users\Alastair\Documents\KiCad\8.0\3rdparty\plugins\org_openscopeproject_InteractiveHtmlBom\generate_interactive_bom.py"
@SET outdir=Media

@echo Schematic Preview.
@SET kicadfile="Circuit\FilamentDryerController2\FilamentDryerController1.kicad_sch"

@SET args=-o "%outdir%\Schematic.pdf"
@%kicadcli% sch export pdf %args% %kicadfile%

@echo.
@echo Bill of materials.
@SET kicadfile="Circuit\FilamentDryerController2\FilamentDryerController1.kicad_pcb"
@SET args=--dark-mode --checkboxes Sourced,Fetched,Placed --no-browser --dest-dir "../../%outdir%" --name-format "BOM"
%python% %bom% %args% %kicadfile%

@echo.
@echo PCB Preview.
@SET kicadfile="Circuit\FilamentDryerController2\FilamentDryerController1.kicad_pcb"

@SET args=-l Edge.Cuts,F.Cu -o "%outdir%\Pcb_Front_Copper.pdf"  -t Export
@%kicadcli% pcb export pdf %args% %kicadfile%

@SET args=-l Edge.Cuts,B.Cu -o "%outdir%\Pcb_Back_Copper.pdf"  -t Export -m
@%kicadcli% pcb export pdf %args% %kicadfile%

@SET args=-l Edge.Cuts,F.Silkscreen,F.Fab -o "%outdir%\Pcb_Front_Components.pdf" -t Export
@%kicadcli% pcb export pdf %args% %kicadfile%

@SET args=-l Edge.Cuts,B.Silkscreen,B.Fab -o "%outdir%\Pcb_Back_Components.pdf" -t Export -m
@%kicadcli% pcb export pdf %args% %kicadfile%





@echo.
::@pause