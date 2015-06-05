#Cubicuous Developers Guide

This guide is intended to give the developer an overview of the coding style/standard to be used throughout the Cubicuous engine.

###File Structure

  - All source code should be under the src directory
  - All sub folders of the src directory should be uppercase to match the namespace
  - All documentation should go under the doc directory
  - All test should be catagorised by folder and located in the test directory

###Namespaces
  - Namespaces should be similar to Cubicuous::Window::Window()
  - Window/Input/Buttons etc. should go under the Window namespace
  - Sprites/Rendering/Cubes/Shaders etc should go under the Graphics namespace
  - Timers/Menus/FileHandling etc should go under the Helpers namespace

###Naming Standards
  - Class names should be PascalCase
  - Methods and variables should be camelCase