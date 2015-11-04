# README #

### What is this repository for? ###

This is a simple program graphically paint up OFF models. In the program you can.
1: load in a model of OFF format (must not be bigger than 12 MB as it is right now).
2: A gtk panel will be visible, where you can set the position of a light source. There is one light that goes around the object (like a sun) that you can not affect, however, there is a second light that you may change position and colour for. You can also set the ambient, diffuse, and specular light for the reflection on the object.

useful keyboard commands:
-------------------------------------
1: Set camera to use orthographic projection.
2: Set camera to use oblique projection.
3: Set camera to use graphical projection (3D feeling). Best feeling when moving the camera around.
M: Put program into move mode, so you can move your camera with the mouse and W,A,S,D buttons.
T: put program into transform mode. The model will be moved but camera remains still. use x,y,z to choose axis, +/- to move it.
R: put the program into rotation mode. The camera remains still but the object can be rotated. select the axis to rotate around (x,y,z) and use -/+ to rotate clock/counter clockwise.
E: Put program into Scale mode, to scale the model. use +/- for making the model larger/smaller.
F: Toggle filled/non filled polygons.
Close the program using the window x-button.

Version: 1.0 

### How do I get set up? ###

* Summary of set up

This program uses OpenGL, so you will have to run it in a UNIX system (Linux, Mac). Otherwise the packages gtk+-2.0 will be needed, as well as jpeg, and make packages.

*how to compile the program:
cd into the folder for the program. It exist a make file in there, so just type "make" to compile. The runnable file will have the name "walking_in_air"

*how to run:

use the command: 
./walking_In_air

* the creator:

Mattas Hinnerson, Student at Umeå univeristy.
