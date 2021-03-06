# OpenBit
Engine for random programs, heavily inspired by [TheCherno/Hazel](http://github.com/TheCherno/Hazel).

Currently unavailable for Mac or for hardware that does not support OpenGL 4.5.

### Primary Goal:
Create an engine capable of creating scientific simulation software.

### Secondary Goal:
Make a game engine.

## Compiling on Linux
Unzip the `dependencies.zip` archive. There are bash scripts which set up the makefiles.

	bash scripts/genproj-linux.sh
	make

Possible configurations for `make` are `debug` (default) and `release`.

The built binaries will be found at `bin/linux-x86_64-{configuration}/{projectname}/`.
Some of the example projects included might load external files at runtime, these can be found in their respective
project directory, under `assets/`. You can either copy this folder to the same directory as the binary or set the
working directory to the project directory.

## Compiling on Windows
Unzip the `dependencies.zip` archive. Run the script `scripts/genproj-windows.bat` which will create
visual studio 2019 project files. You can then open `OpenBit.sln` and run the build from there,
either in `debug` or `release` configurations.
