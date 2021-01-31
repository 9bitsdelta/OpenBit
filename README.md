# OpenBit
Engine for random programs, heavily inspired by [TheCherno/Hazel](http://github.com/TheCherno/Hazel)<br>
Currently unavailable for hardware that does not support OpenGL 4.5.

## Primary Goal:
Create an engine capable of (semi-accurate) scientific simulations.

### Primary-Goal Features:
2D Renderers<br>
Scripting<br>
Entity-Component-System<br>

## Secondary Goal:
Make a game engine.<br>

### Features:
_Let's not go down that road **yet**_

## Compiling on Linux
Unzip the archive. If you have Visual Studio Code, there are scripts already made for it to create the makefiles, build and debug. Else, there are bash scripts which set up the makefiles.<br>

	bash scripts/genproj-linux.sh
	make

## Compiing on Windows
Unzip the archive. Run the script `scripts/genproj-windows.bat` which will create visual studio 2019 project files.