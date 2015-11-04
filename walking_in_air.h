
#ifndef walking_in_air_H
#define walking_in_air_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

#include "shadertools.h"
#include "MatrixCalc.h"
#include "guicontrol.h"
#include "guicallback.h"
#include "variables.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define MINDEX(r,c) ((r-1)+(c-1)*4)

/*function headers*/

vec4 vec4_(float x, float y, float z, float w);

//initializes glut functions.
void initGlut(int argc, char **argv);

/**
 * initialize gl functions, binding arraybuffers and setting initial values for
 * the light positions, colours, transform matrix, projection matrix,
 * view matrix, and sending them to the GPU.
 */
void initGL(void);

//function for sending the matTrans matrix to the GPU.
void sendTMatrixToGPU();
//function for sending the view matrix to the GPU.
void sendViewMatrixToGPU();
//function for sending the projection matrix to the GPU.
void sendProjMatrixToGPU();
//send the color vectors to the GPU.
void sendColorToGPU();

//enables the bezier function.
void enableSmoothBezierMove(bool enable);

/*--------------------------projection functions------------------*/
//changing the Projection matrix to orthographic.
void orthographic();
//changing the Projection matrix to oblique.
void oblique();
//changing the Projection matrix to perspective.
void perspective();

/*--------------------------View functions------------------------*/
void cameraForward(float stepSize);

void cameraBackward();

void cameraLeft();

void cameraRight();

void cameraUp();

void cameraDown();

/* Rotates the camera around the y-axis. Observe that the Y-value remains the
 * same!.
 * @param direction char, p if right movement, else left movement.
 * @param angle float, the angle to rotate in degrees!
 */
void cameraRotateY(char direction, float angle);

/* Rotates the camera around the x-axis. Observe that the X-value remains the
 * same!.
 * @param direction char, p if down movement, else up movement.
 * @param angle float, the angle to rotate in degrees!
 */
void cameraRotateX(char direction, float angle);

/*----------------------- Object transformation functions --------------*/

/* function for translating the matTrans matrix depending on keyboard input.
* the axis coordinates possible is x and y and the translations possible are
* plus (+) or minus (-). Example pressing y-button, then +, makes the visible
* object move upwards in y-direction.
*/
void translateStage();

/* function for scaling the matTrans matrix.
* The scaling possible are plus (+) or minus (-).
* Pressing + makes the object increase in size,
* Pressing - makes the object decrease in size.
*/
void scaleStage();

/* function for rotating the matTrans matrix around the x,y, or z-axis.
 * by pressing plus (+) or minus (-) the object can rotate around the selected
 * axis clockwise or counterclockwise.
 */
void rotateStage();

/*------------------------time functions---------------------------------*/
// A timer for keeping track of the time in milliseconds.*/
void timerFunc(int value);

//idle function that will run when glut is idle.
void idle();

/*------------------------Display functions------------------------------*/

//function for reshaping the visible window.
void reshape(int x, int y);

//function that makes sends graphical information to the GPU.
void display(void);

//sets a orthographic projection temporary to be able to show 2d text.
void setOrthographicProjection();

//Resets the original projection.
void resetPerspectiveProjection();

/* renders a sting into the visual display.
* @param x float, the position in x-axis, measured from left to right.
* @param y float, the position in y-axis, measured from up to down.
* *theString const char, the string that should be printed out.
*/
void renderBitMapString(float x, float y, const char *theString);

/*-------------------------------closing methods--------------------------*/

void atclose(void);

#endif
