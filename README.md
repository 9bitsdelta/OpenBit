# OpenBit
Engine for random programs, heavily inspired by [TheCherno/Hazel](https://github.com/TheCherno/Hazel)<br>
Currently unavailable for Windows or hardware that does not support OpenGL 4.5.

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

## Compiling
Clone or download the repo. If you have Visual Studio Code, there are scripts already made for it to create the makefiles, build and debug. Else, there are bash scripts which set up the makefiles.<br>

	bash scripts/genproj-linux.sh
	make

The dependencies not included in this repo are [GLFW](https://www.glfw.org) and [GLEW](https://glew.sourceforge.net).<br>
To link with them you need to either install the packages for the development libraries or add them manually in the `premake5.lua` files.