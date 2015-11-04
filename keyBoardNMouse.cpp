/**
 * File that controls all the keyboard and mouse input from the user and
 * makes the appropriate action in the walking_in_air program.
 *
 * author: Mattias Hinnerson(oi11mhn)
 * date: 2013-03-18
 */


#include "walking_in_air.h"
#include "variables.h"
#include "keyBoardNMouse.h"
#include "bezierCalc.h"
#include "openNRead.h"

/*
 * function that controls actions while any mouse button is being clicked.
 */
void onMouseClick(int button, int state, int x, int y){

	/*Storing the values for x and y where the click happend if left-click*/
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		currentMouseX = x;
		currentMouseY = y;
	}

	/*If scroll up (button 3), then move camera forward*/
	if(button == 3){
		cameraForward(0);
	}
	/*If scroll down (button 4), then move camera backwards*/
	if(button == 4){
		cameraBackward();
	}
}

/*
 * Handle the actions when the mous is being moved. A mouse button must be
 * clicked for registering any movement.
 */
void mouseMovement(int x, int y){

	if(firstTimeClick == false){

		/*calculate thee angle movement difference*/
		camHorizChange = ((x-currentMouseX)/ HorizontalMouseSens);
		camVertChange = ((y-currentMouseY) / verticalMouseSens);

		/*keep track of the total rotation.*/
		camHorizRot = camHorizRot + camHorizChange;
		camVertRot = camVertRot + camVertChange;

		/*if movement right in x-axis*/
		if( currentMouseX < (camHorizChange)){
			cameraRotateY('p',  camHorizChange);
		}
		/*if movement left in x-axis*/
		if(currentMouseX > (camHorizChange)){
			cameraRotateY('n', camHorizChange);
		}

		/*if movement up in y-axis and total rotation less than 85 degrees*/
		if((currentMouseY > (camVertChange)) && (camVertRot) > -85){
			cameraRotateX('n', camVertChange);
		}
		/*if movement down in y-axis*/
		if((currentMouseY < (camVertChange)) && (camVertRot) < 85){
			cameraRotateX('p', camVertChange);
		}
	}
	currentMouseX = x;
	currentMouseY = y;
	firstTimeClick = false;
}

/**
 * Function that listens for event input from keyboard.
 */
void Keyboard(unsigned char key, int x, int y) {

	switch (key){

	/*projection commands*/
	case '1':
		printf("changing projection to orthographic.\n");
		orthographic();
		break;
	case '2':
		printf("changing projection to oblique.\n");
		oblique();
		break;
	case '3':
		printf("changing projection to perspective.\n");
		perspective();
		break;

	/*camera movement*/

	case 'm':
		printf("Camera movement. You can no use w,a,s,d,z,x to move ");
		printf("around.\n");
		currentMode = 'm';
		glutPostRedisplay();
		break;

	case 'w':
		if(useSmooth == true){
			useSmooth = false;
			bezSpeed += 0.25;
			calculateNewBezierCurve(direction,P0,Pref,V0,bezierP,PrefChange,uM,
									uMPrim,bezSpeed);
			bezierPCounter = 0;
			useSmooth = true;
		}else{
			cameraForward(0);
		}
		break;
	case 'a':
		if(useSmooth == true){
			direction = 'l';
			calculateNewBezierCurve(direction,P0,Pref,V0,bezierP,PrefChange,uM,
									uMPrim,bezSpeed);
			bezierPCounter = 0;
		}else{
			cameraLeft();
		}
		break;
	case 's':
		if(useSmooth == true){
			if(bezSpeed > 0.5){
				useSmooth = false;
				bezSpeed -= 0.25;
				calculateNewBezierCurve(direction,P0,Pref,V0,bezierP,PrefChange,
										uM,uMPrim,bezSpeed);
				bezierPCounter = 0;
				useSmooth = true;
			}

		}else{
			cameraBackward();
		}
		break;
	case 'd':
		if(useSmooth == true){
			direction = 'r';
			calculateNewBezierCurve(direction,P0,Pref,V0,bezierP,PrefChange,uM,
									uMPrim,bezSpeed);
			bezierPCounter = 0;
		}else{
			cameraRight();
		}
		break;

	/*object movement*/
	case 'q':
		printf("Closing program.....\n");
		exit(0);
		break;

	case 'v':
		glutFullScreenToggle();
		break;

	case 'o':
		printf("\ncurrent mode: open OFF file.\n");
		currentMode = 'o';
		glutPostRedisplay();
		loadVertices(NULL);
		glutPostRedisplay();
		break;

	case 't':
		printf("current mode: translation.\n");
		currentMode = 't';
		chosenMovement = 'n';
		chosenMovement = 'n';
		glutPostRedisplay();
		printf("In which direction (x,y or z) do you want to move the object?");
		printf("\npress x,y or z button to choose.\n");

		break;

	case 'e':
		printf("current mode: Scaling.\n");
		currentMode = 's';
		glutPostRedisplay();
		chosenMovement = 'n';
		chosenMovement = 'n';
		printf("press + or - button to scale the object.\n");
		break;

	case 'r':
		printf("current mode: Rotating.\n");
		currentMode = 'r';
		glutPostRedisplay();
		chosenMovement = 'n';
		chosenMovement = 'n';
		printf("Press x,y,or z to choose which axis the object should ");
		printf("rotate around.\n");
		break;

	case 'x':

		if(currentMode == 't'){
			printf("X direction chosen. press + or - button ");
			printf("to move the object.\n");
			chosenDirection = 'x';
		}else if(currentMode == 'r'){
			printf("X direction chosen. press + or - button ");
			printf("to rotate the object around the X-axis.\n");
			chosenDirection = 'x';
		}else{
			cameraUp();
		}
		break;

	case 'y':
		if(currentMode == 't'){
			printf("Y direction chosen. press + or - button ");
			printf("to move the object.\n");
			chosenDirection = 'y';
		}else if(currentMode == 'r'){
			printf("Y direction chosen. press + or - button ");
			printf("to rotate the object around the Y-axis.\n");
			chosenDirection = 'y';
		}
		break;

	case 'z':
		if(currentMode == 't'){
			printf("Z direction chosen. press + or - button ");
			printf("to move the object.\n");
			chosenDirection = 'z';
		} else if(currentMode == 'r'){
			printf("Z direction chosen. press + or - button ");
			printf("to rotate the object around the Z-axis.\n");
			chosenDirection = 'z';
		}else{
			cameraDown();
		}
	break;

	case '+':

		if(currentMode == 't'){
			if(chosenDirection == 'x' || chosenDirection == 'y'
					|| chosenDirection == 'z'){
				chosenMovement = '+';
				translateStage();
			}
		}else if(currentMode == 's'){
			chosenMovement = '+';
			scaleStage();
		}else if(currentMode == 'r'){
			chosenMovement = '+';
			rotateStage();
		}

		break;

	case '-':
		if(currentMode == 't'){
			if(chosenDirection == 'x' || chosenDirection == 'y'
					|| chosenDirection == 'z'){
				chosenMovement = '-';
				translateStage();
			}
		}else if(currentMode == 's'){
			chosenMovement = '-';
			scaleStage();
		}else if(currentMode == 'r'){
			chosenMovement = '-';
			rotateStage();
		}

		break;

	case 'f':
		/*changes between line mode and filled mode for the object.*/
		if(objectFilled == false){
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			sendTMatrixToGPU();
			glutPostRedisplay();
			objectFilled = true;
		}else if(objectFilled == true){
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			sendTMatrixToGPU();
			glutPostRedisplay();
			objectFilled = false;
		}
		break;

	case 'h':

		printf("Help:\n----------------------------------------------------\n");
		printf("The allowed keyboard commands are: \n");
		printf("o: open file,		q: quit program,	t: transform object\n");
		printf("e: scale object,	r: rotate object,	m: camera movement.\n");
		printf("f: object fill: on/off	");
		printf("x: choose x-axis. If camera mode: go up.\ny: choose y-axis	");
		printf("z: choose z-axis. If camera mode: go down.\n\n");
		printf("w: move camera forward.		a: move camera left.\n");
		printf("s: move camera backwards.	d: move camera right.\n");
		printf("v: toggle between fullscreenmode..\n");
		printf("1: orthographic projection.	2: oblique projection.\n");
		printf("3: perspective projection.\n");
		printf("You may also use the mouse to move the camera. To enable, ");
		printf("press and hold left\nmouse button and move the mouse.\n");
		printf("Use the mouseScroll to zoom in or out.\n");
		printf("-----------------------------------------------------------\n");
		break;

	default:
		printf("Unknown keyboard command. Press \"h\" for help. \n");
		break;
	}
}

