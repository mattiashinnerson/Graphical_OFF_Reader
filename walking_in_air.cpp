/**
 * Program for reading a OFFFile, sending the vertices to the graphics card
 * and show a visible object. The object can then be translated, scaled,
 * and rotated in z-axis. It is also possible to move the camera with a
 * regular movement with the mouse and keyboard buttons wasd, or with a
 * bezier curve smooth move controlled by wasd.
 *
 * OBSERVE: message to the teacher:
 * I'm aware of that this program has memoryleaks. Those mostly comes from
 * allocations made in the freeglut or gtk functions, and I havent been able to
 * deallocate them. But the allocations I have made in this program have been
 * deallocated.
 *
 *	made by: Mattias Hinnerson (oi11mhn)
 *	date: 2014-03-18
 */

/*the header file and the variable file*/
#include "walking_in_air.h"
#include "bezierCalc.h"
#include "keyBoardNMouse.h"
#include "convertionFuncs.h"
#include "illumination.h"
#include "openNRead.h"

vec4 vec4_(float x, float y, float z, float w)
{
	vec4 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;

	return v;
}

color4 color4_(float r, float g, float b, float a){

	color4 c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;

	return c;
}

/*--------Assigning values to the Global variables (must be global)----------*/

/*The transition matrix*/
matrix<float> *matTrans = new matrix<float> (4,4);

/*The camera movement (V) matrix*/
matrix<float> *matView = new matrix<float> (4,4);

/*The projection (P) matrix*/
matrix<float> *matProj = new matrix<float> (4,4);

float math_pi = 3.14159265359;

/*Basic variables*/
int windowHeight = 800;
int windowWidth = 800;
objectData *fileData = NULL;
char currentMode = 'm';
char chosenDirection = 'n';
char chosenMovement = 'n';
char currentProj = 'n';
vector<float> *change = new vector<float>(4);
matrix<float> *changeMat = new matrix<float>(4,4);

bool objectFilled = true;
bool fileOpen = false;
float xChanged = 0;
float yChanged = 0;
float zChanged = 0;

/*Glut variables*/
GLuint program;
GLuint idTransMat;
GLuint idViewMat;
GLuint idProjMat;
GLuint theNormal;

GLuint ambient_product_loc;
GLuint diffuse_product_loc;
GLuint diffuse_product_loc2;
GLuint specular_product_loc;
GLuint light_loc;
GLuint light_loc2;
GLuint lightShininess_loc;

/*camera vectors and points*/
vector<float> *V0 = new vector<float>(3);						//the upvector
matrix<float> *Mwc = new matrix<float>(4,4);
matrix<float> *MwcTranspose = new matrix<float>(4,4);
myVector *P0 = new myVector;
myVector *Pref = new myVector;

/*The size of the view field*/
float top = 1;
float bottom = -1;
float left = -1;
float right = 1;
float near = 1;
float far = 100;
float scaleForm = 1;

/*Camera variables */
float camStartX = 4;
float camStartY = 0;
float camStartZ = 0;

/*mouse*/
float verticalMouseSens = 4.0;		/*X sense. Higher value = slower rotation*/
float HorizontalMouseSens = 4.0;	/*Y sense. Higher value = slower rotation*/
float camHorizChange = 0.0;
float camVertChange = 0.0;
float camHorizRot = 0.0;
float camVertRot = 0.0;

bool firstTimeClick = true;
int currentMouseX;
int currentMouseY;

/*Illumination*/
float ambientLight;
vector<float> *light_ambient = new vector<float>(4);
vector<float> *light_diffuseNspecular = new vector<float>(4);

vector<float> *material_ambient = new vector<float>(4);
vector<float> *material_diffuse = new vector<float>(4);
vector<float> *material_specular = new vector<float>(4);
vector<float> *ambient_prod = new vector<float>(4);
vector<float> *diffuse_prod = new vector<float>(4);
vector<float> *diffuse_prod2 = new vector<float>(4);
vector<float> *specular_prod = new vector<float>(4);;
float material_shininess;
bool lightPos2MoveR = true;
bool lightPos2MoveU;

//lightscources.
vector<float> *lightPosition = new vector<float>(4);
vector<float> *lightPosition2 = new vector<float>(4);

vec4 *verticeNormals;
float lightScourceR = 255;
float lightScourceG = 222;
float lightScourceB = 0;

/*time variables*/
bool continueCounting = true;
int timerCountMillis = 50;
int nrOfBezPoints = 101;					//the number of points on the curve.
int bezierPCounter;

/*Bezier curves variables*/
bool useSmooth = false;
char direction = 'r';
float bezSpeed = 0.5;
float d = 0.5;		/*the distance konstant between our bezier points*/
matrix<float> *uM = new matrix<float>(nrOfBezPoints,3);
matrix<float> *uMPrim = new matrix<float>(nrOfBezPoints,3);
matrix<float> *bezierP = new matrix<float>(nrOfBezPoints,3);
matrix<float> *PrefChange = new matrix<float>(nrOfBezPoints,3);


/*
 * main function that initializes variables, gui, and start the glutMainLoop.
 */
int main(int argc, char **argv) {

    /* Initialize GUI */
    guiInit(&argc, argv);
    guiInitWindow("ass3gui.glade");

    /* Initialization */
    initGlut(argc, argv);
    initGL();

    /* Glut Call-backs */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(onMouseClick);
    glutMotionFunc(mouseMovement);
    //initialize timer with one alert every 100 millisecond.
    glutTimerFunc(timerCountMillis,timerFunc,0);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);

    /*prepare bezier variables*/
    initBezierVariables(nrOfBezPoints,uM,uMPrim);


    /* Set up exit function */
    atexit(&atclose);

    /*initialize idle func for gui*/
    glutIdleFunc(idle);

    /* Loop forever */
    glutMainLoop();

    glutLeaveMainLoop();

    return 0;
}

/**
 * initializes glut functions.
 */
void initGlut(int argc, char **argv) {

    /* Initialize glut */
    glutInit(&argc, argv);

	/* Display Mode
      GLUT_DOUBLE together with glutSwapBuffers(); for double buffering */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    /* Window Size */
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(512,512);
	glutInitContextProfile( GLUT_CORE_PROFILE );
    /* GL Version
       Check with glxinfo | grep Open for supported version */
    glutInitContextVersion(3, 1);

    /* Window label */
    glutCreateWindow("walking in air.");
}

/**
 * initialize gl functions, binding arraybuffers and setting initial values for
 * the light positions, colours, transform matrix, projection matrix,
 * view matrix, and sending them to the GPU.
 */
void initGL(void) {
    GLuint indexBufferId;
    GLuint buffer;
    GLuint loc;
    GLuint vao;
    GdkColor color;
    gdouble k[3];

	/* Setting up GL Extensions */
	glewExperimental = GL_TRUE;
    glewInit();

    /* Create and initialize a program object with shaders */
    program = initProgram("vshader.glsl", "fshader.glsl");

    /* installs the program object as part of current rendering state */
    glUseProgram(program);

    /* Creat a vertex array object */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* Create buffer in the shared display list space and
       bind it as GL_ARRAY_BUFFER */
    glGenBuffers( 1, &buffer);
    glBindBuffer( GL_ARRAY_BUFFER, buffer);

    /* Create index buffer for locating triangle indexes.*/
    glGenBuffers( 1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

    /* Initialize attribute vPosition in program */
    loc = glGetAttribLocation( program, "vPosition");
    glEnableVertexAttribArray(loc);

    glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0,
    							(GLvoid*)BUFFER_OFFSET(0));

    /*Initialize attribute vNormal in program*/
    theNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(theNormal);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    /*initialize matrixes for the vshader.*/
	idTransMat = glGetUniformLocation(program,"T");
	idViewMat = glGetUniformLocation(program,"V");
	idProjMat = glGetUniformLocation(program,"P");

	/*the colors*/
	ambient_product_loc = glGetUniformLocation(program,"ambientProduct");
	diffuse_product_loc = glGetUniformLocation(program,"diffuseProduct");
	diffuse_product_loc2 = glGetUniformLocation(program,"diffuseProduct2");
	specular_product_loc = glGetUniformLocation(program,"specularProduct");
	light_loc = glGetUniformLocation(program,"lightningPos");
	light_loc2 = glGetUniformLocation(program,"lightningPos2");
	lightShininess_loc = glGetUniformLocation(program,"shininess");

    /*initiating camera vector and points*/
    V0->insert_element(0,0);
    V0->insert_element(1,1);
    V0->insert_element(2,0);

    P0->x = camStartX;
    P0->y = camStartY;
    P0->z = camStartZ;

    Pref->x = 0;
    Pref->y = 0;
    Pref->z = 0;

    view(P0,Pref,V0,Mwc, MwcTranspose, matView);

    /*make orthografic the initial projection*/
    orthographic();

    /*filling main matrices with initial values. */
    for(int i=0; i < 4; i++){
    	for(int j=0; j < 4; j++){
    		if(i==j){
    			(*matTrans)(i,j) = 1;
    			(*matView)(i,j) = 1;
    			(*matProj)(i,j) = 1;
    		}else{
    			(*matTrans)(i,j) = 0;
    			(*matView)(i,j) = 0;
    			(*matProj)(i,j) = 0;
    		}
    	}
    }

    /*------------initialize shader lightning parameters----------*/

    /*lightsource 1 position*/
    setLightScourcePosX(-2);
    setLightScourcePosY(4);
    setLightScourcePosZ(2);
	(*lightPosition)(3) = 1;

	/*lightsource 2 position*/
	(*lightPosition2)(0) = -10;
	(*lightPosition2)(1) = 3;
	(*lightPosition2)(2) = 0;
	(*lightPosition2)(3) = 1;

    /*diffuse and specular light*/
    setLightScourceIntens(1.0,0.87,0.0);
    (*light_diffuseNspecular)(3) = 1.0;

    color.red = 1.0*65535;
    color.green = 0.87*65535;
    color.blue = 0.0*65535;
    gui_set_I_light(color);

    /*ambient light*/
    setAmbientLightIntens(0.66,0.0,0.0);

    color.red = 0.66*65535;
    color.green = 0.0*65535;
    color.blue = 0.0*65535;
    gui_set_I_ambient(color);

    /*material ambient coeff*/
    setMaterialAmbientCoeffR(0.57);
    setMaterialAmbientCoeffG(0.0);
    setMaterialAmbientCoeffB(0.0);
    (*material_ambient)(3) = 1.0;

    k[0] = 0.57;
    k[1] = 0.0;
    k[2] = 0.0;
    gui_set_k_ambient(k);

    /*material diffuse coeff*/
    setMaterialDiffuseCoeffR(0.75);
    setMaterialDiffuseCoeffG(0.55);
    setMaterialDiffuseCoeffB(0.0);
    (*material_diffuse)(3) = 1.0;

    k[0] = 0.75;
    k[1] = 0.55;
    k[2] = 0.0;
    gui_set_k_diffuse(k);

    /*material specular coeff*/
    setMaterialSpecularCoeffR(1.0);
    setMaterialSpecularCoeffG(0.81);
    setMaterialSpecularCoeffB(1.0);
    (*material_specular)(3) = 1.0;

    k[0] = 1.0;
    k[1] = 0.81;
    k[2] = 1.0;
    gui_set_k_specular(k);

	/*----the light 2 color will be static----*/
    vector<float> *light_diffuseNspecular2 = new vector<float>(4);
    (*light_diffuseNspecular2)(0) = 0.91;
    (*light_diffuseNspecular2)(1) = 0.77;
    (*light_diffuseNspecular2)(2) = 0.0;
    (*light_diffuseNspecular2)(3) = 1.0;

    vector<float> *material_diffuse2 = new vector<float>(4);
    (*material_diffuse2)(0) = 0.30;
    (*material_diffuse2)(1) = 0.10;
    (*material_diffuse2)(2) = 0.0;
    (*material_diffuse2)(3) = 1.0;

	multiply3(light_diffuseNspecular2,material_diffuse2,diffuse_prod2);

	free(light_diffuseNspecular2);
	free(material_diffuse2);

    /*setting phong sininess*/
    setPhongShininess(6);
    gui_set_phong((guint16) 6);

    /* sending the matrix to the grafic card */
    sendColorToGPU();
    sendTMatrixToGPU();
    sendViewMatrixToGPU();
    sendProjMatrixToGPU();

    /* Set graphics attributes */
    glLineWidth(1.0);
    glPointSize(1.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);				//the background color.
    glEnable(GL_DEPTH_TEST);

}

/*-------------------functions for sending matrices to GPU-------------------*/

/**
 * function for sending the matTrans matrix to the GPU.
 */
void sendTMatrixToGPU(){
	glUniformMatrix4fv(idTransMat, 1, GL_TRUE, &matTrans->data()[0]);
}

/**
 * function for sending the view matrix to the GPU.
 */
void sendViewMatrixToGPU(){
	glUniformMatrix4fv(idViewMat, 1, GL_TRUE, &matView->data()[0]);
}

/**
 * function for sending the proj matrix to the GPU.
 */
void sendProjMatrixToGPU(){
	glUniformMatrix4fv(idProjMat, 1, GL_TRUE, &matProj->data()[0]);
}

/**
 * send the color vectors to the GPU.
 */
void sendColorToGPU(){

	/*calculating products where combining light and material light*/
	multiply3(light_ambient,material_ambient,ambient_prod);
	multiply3(light_diffuseNspecular,material_diffuse,diffuse_prod);
	multiply3(light_diffuseNspecular,material_specular,specular_prod);

	glUniform4fv(ambient_product_loc,1, &ambient_prod->data()[0]);
	glUniform4fv(diffuse_product_loc, 1,&diffuse_prod->data()[0]);
	glUniform4fv(diffuse_product_loc2, 1,&diffuse_prod2->data()[0]);
	glUniform4fv(specular_product_loc, 1, &specular_prod->data()[0]);
	glUniform4fv(light_loc, 1, &lightPosition->data()[0]);
	glUniform4fv(light_loc2, 1, &lightPosition2->data()[0]);
	glUniform1f(lightShininess_loc, material_shininess);
}

/*
 * enables the bezier function.
 */
void enableSmoothBezierMove(bool enable){

		useSmooth = enable;
		bezierPCounter = 0;
		/*calculate bezier curve, with right direction as default.*/
		calculateNewBezierCurve(direction,P0,Pref,V0,bezierP,PrefChange,uM,
								 uMPrim,bezSpeed);
}

/*---------------------------------P matrix methods--------------------------*/

/**
 * changing the Projection matrix to orthographic.
 */
void orthographic(){

	orthographic(scaleForm*left,scaleForm*right,scaleForm*top,scaleForm*bottom,
					scaleForm*near,scaleForm*far, matProj);

	sendProjMatrixToGPU();
	glutPostRedisplay();
	currentProj = 'r';
}

/**
 * changing the Projection matrix to oblique.
 */
void oblique(){

	oblique(26.565,26.565,scaleForm*left,scaleForm*right, scaleForm*top,
				scaleForm*bottom,scaleForm*near,scaleForm*far, matProj);

	sendProjMatrixToGPU();
	glutPostRedisplay();
	currentProj = 'o';
}

/**
 * changing the Projection matrix to perspective.
 */
void perspective(){

	perspective(scaleForm*left,scaleForm*right,scaleForm*top,scaleForm*bottom,
					scaleForm*near,scaleForm*far, matProj);

	sendProjMatrixToGPU();
	glutPostRedisplay();
	currentProj = 'p';
}

/*----------------------------camera movement methods------------------------*/

/**
 * moving the camera forward (in world coordinates, not camera coordinates).
 */
void cameraForward(float stepSize){

	convertMovToWorldCord('+','z',stepSize);

	view(P0,Pref,V0, Mwc, MwcTranspose, matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/**
 *  moving the camera backwards (in world coordinates, not camera coordinates).
 */
void cameraBackward(){

	convertMovToWorldCord('-','z',0);

	view(P0,Pref,V0,Mwc,MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/**
 *  moving the camera left.
 */
void cameraLeft(){

	convertMovToWorldCord('l','x',0);

	view(P0,Pref,V0,Mwc,MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/**
 * moving the camera right.
 */
void cameraRight(){

	convertMovToWorldCord('r','x',0);

	view(P0,Pref,V0,Mwc,MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/**
 * moving the camera up.
 */
void cameraUp(){

	convertMovToWorldCord('u','y',0);

	view(P0,Pref,V0,Mwc,MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/**
 * moving the camera down.
 */
void cameraDown(){

	convertMovToWorldCord('d','y',0);

	view(P0,Pref,V0,Mwc, MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}


/* Rotates the camera around the y-axis. Observe that the Y-value remains the
 * same!.
 * @param direction char, p if right movement, else left movement.
 * @param angle float, the angle to rotate in degrees!
 */
void cameraRotateY(char direction,float angle){

	vector<float> PrefWorld = convertRotToWorldCord(direction,angle,'y');

	Pref->x = PrefWorld(0);
	Pref->y = PrefWorld(1);
	Pref->z = PrefWorld(2);

	view(P0,Pref,V0,Mwc, MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/* Rotates the camera around the x-axis. Observe that the X-value remains the
 * same!.
 * @param direction char, p if down movement, else up movement.
 * @param angle float, the angle to rotate in degrees!
 */
void cameraRotateX(char direction,float angle){

	vector<float> PrefWorld = convertRotToWorldCord(direction,angle,'x');

	Pref->x = PrefWorld(0);
	Pref->y = PrefWorld(1);
	Pref->z = PrefWorld(2);

	view(P0,Pref,V0,Mwc, MwcTranspose,matView);
	sendViewMatrixToGPU();
	glutPostRedisplay();
}

/*----------------------------object movement methods------------------------*/

/**
 * function for translating the matTrans matrix depending on keyboard input.
 * the axis coordinates possible is x and y and the translations possible are
 * plus (+) or minus (-). Example pressing y-button, then +, makes the visible
 * object move upwards in y-direction.
 */
void translateStage(){

	if(chosenDirection == 'x'){
		if(chosenMovement == '+'){

			translate(0.1,0,0,matTrans);
			xChanged += 0.1;
			sendTMatrixToGPU();
			glutPostRedisplay();

		}else if(chosenMovement == '-'){

			translate((-0.1),0,0,matTrans);
			xChanged -= 0.1;
			sendTMatrixToGPU();
			glutPostRedisplay();
		}
	}
	if(chosenDirection == 'y'){
		if(chosenMovement == '+'){

			translate(0,0.1,0,matTrans);
			yChanged += 0.1;
			sendTMatrixToGPU();
			glutPostRedisplay();

		}else if(chosenMovement == '-'){

			translate(0,(-0.1),0,matTrans);
			yChanged -= 0.1;
			sendTMatrixToGPU();
			glutPostRedisplay();
		}
	}
	if(chosenDirection == 'z'){
		if(chosenMovement == '+'){

			translate(0,0,0.1,matTrans);
			zChanged += 0.1;
			sendTMatrixToGPU();
			glutPostRedisplay();

		}else if(chosenMovement == '-'){

			translate(0,0,(-0.1),matTrans);
			zChanged -= 0.1;
			sendTMatrixToGPU();
			glutPostRedisplay();
		}
	}
}

/**
 * function for scaling the matTrans matrix.
 * The scaling possible are plus (+) or minus (-).
 * Pressing + makes the object increase in size,
 * Pressing - makes the object decrease in size.
 */
void scaleStage(){

	/*we use the same scale factor for every dimension, e.g., 1.1 or 1/1.1*/

	if(chosenMovement == '+'){

		scale(1.1,1.1,1.1,matTrans);
		sendTMatrixToGPU();
		glutPostRedisplay();

	}else if(chosenMovement == '-'){

		scale(0.9,0.9,0.9,matTrans);
		sendTMatrixToGPU();
		glutPostRedisplay();
	}
}

/**
 * function for rotating the matTrans matrix around the x,y, or z-axis.
 * by pressing plus (+) or minus (-) the object can rotate around the selected
 * axis clockwise or counterclockwise.
 */
void rotateStage(){

	/*To rotate correctly:first translate object, rotate, then translate back.*/

	translate(-xChanged,-yChanged,-zChanged,matTrans);

	if(chosenMovement == '+'){

		if(chosenDirection == 'x'){
			rotatex(10,matTrans);
			translate(xChanged,yChanged,zChanged,matTrans);

			sendTMatrixToGPU();
			glutPostRedisplay();
		}else if(chosenDirection == 'y'){
			rotatey(10,matTrans);
			translate(xChanged,yChanged,zChanged,matTrans);

			sendTMatrixToGPU();
			glutPostRedisplay();
		}else if(chosenDirection == 'z'){
			rotatez(10,matTrans);
			translate(xChanged,yChanged,zChanged,matTrans);

			sendTMatrixToGPU();
			glutPostRedisplay();
		}
	}else if(chosenMovement == '-'){

		if(chosenDirection == 'x'){
			rotatex(-10,matTrans);
			translate(xChanged,yChanged,zChanged,matTrans);

			sendTMatrixToGPU();
			glutPostRedisplay();
		}else if(chosenDirection == 'y'){
			rotatey(-10,matTrans);
			translate(xChanged,yChanged,zChanged,matTrans);

			sendTMatrixToGPU();
			glutPostRedisplay();
		}else if(chosenDirection == 'z'){
			rotatez(-10,matTrans);
			translate(xChanged,yChanged,zChanged,matTrans);

			sendTMatrixToGPU();
			glutPostRedisplay();
		}
	}
}


/*A timer for keeping track of the time in milliseconds.*/
void timerFunc(int value){

	if(useSmooth == true){

		/*take one step on the beziercurve,if reached end,continue forward*/
		if(bezierPCounter < (int)(*bezierP).size1()){

			/*take one step on the bezier curve*/
			P0->x = (*bezierP)(bezierPCounter,0);
			P0->y = (*bezierP)(bezierPCounter,1);
			P0->z = (*bezierP)(bezierPCounter,2);

			/*configure Pref so it follows our vision*/
			Pref->x = (*PrefChange)(bezierPCounter,0);
			Pref->y = (*PrefChange)(bezierPCounter,1);
			Pref->z = (*PrefChange)(bezierPCounter,2);

			/*update the view matrix*/
			view(P0,Pref,V0,Mwc, MwcTranspose,matView);
			sendViewMatrixToGPU();
			glutPostRedisplay();
		}else{
			cameraForward(0.05);
		}
		bezierPCounter++;
	}


	/*move the position of the lightscource2 in a circle around the object.
	 *(will move between x:-10,10, and y: 3,20, lowest y value in the x end
	 * points.)*/

	/*if lightPos2MoveR is true, then move point in positive x direction.*/
	if(lightPos2MoveR == true){
		(*lightPosition2)(0) = (*lightPosition2)(0) + 0.1;
		if((*lightPosition2)(0)>= 10){
			lightPos2MoveR = false;
		}
	}else if(lightPos2MoveR == false){
		(*lightPosition2)(0) = (*lightPosition2)(0) - 0.1;
		if((*lightPosition2)(0)<= -10){
					lightPos2MoveR = true;
		}
	}

	if(lightPos2MoveU == true){
		(*lightPosition2)(1) = (*lightPosition2)(1) + 0.2;
		if((*lightPosition2)(0)<= 0){
			lightPos2MoveU = false;
		}
	}else if(lightPos2MoveU == false){
		(*lightPosition2)(1) = (*lightPosition2)(1) - 0.2;
		if((*lightPosition2)(0)>= 0){
					lightPos2MoveU = true;
		}
	}
	sendColorToGPU();
	glutPostRedisplay();

	if(continueCounting == true){
			glutTimerFunc(timerCountMillis, timerFunc, value);
	}
}

/*
 * idle function that will run when glut is idle.
 */
void idle(){

    guiMainIteration();
}

/*-------------------------------Display functions----------------------------*/

/**
* function for reshaping the visible window.
*/
void reshape(int x, int y){
	glViewport(0,0,x,y);
	scaleForm = (float) y/x;

	if(currentProj == 'o'){						/*oblique*/
		oblique();
	}else if(currentProj == 'p'){				/*perspective*/
		perspective();
	}else if(currentProj == 'r'){				/*orthographic*/
		orthographic();
	}
}

/**
 * function that makes sends graphical information to the GPU.
 */
void display(void){
	int size;
	char locString[512] = "", modeString[128] = "", PrefString[128] = "";
	char buffer[33];

	/*clear color and depth buffers*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(fileOpen == false){
		size = 0;
	}else{
		size = fileData->totTriangles*3;
	}
	/*draw 3d scene*/
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT,
    				(GLvoid*)0);

    /*unloading shaders to be able to generate 2d text font.*/
    glUseProgram(0);

	setOrthographicProjection();
    glPushMatrix();
    /*reset transformations.*/
    glLoadIdentity();
	glColor3f(0.0,1.0,0.0);				/*sets the color of the font*/

	/*creating the visible string: current mode*/
	strcat(modeString,"current mode: ");
	if(currentMode == 'm'){
		sprintf(buffer, "%s", "move");
	}else if(currentMode == 't'){
		sprintf(buffer, "%s", "transform");
	}else if(currentMode == 's'){
		sprintf(buffer, "%s", "scale");
	}else if(currentMode == 'r'){
		sprintf(buffer, "%s", "rotate");
	}else{
		sprintf(buffer, "%s", "-");
	}
	strcat(modeString,buffer);
	renderBitMapString(5,471,(char*)modeString);

	/*creating the visible string: Camera lookat point.*/
	strcat(PrefString,"camera look-at-point: x: ");
	sprintf(buffer, "%f", Pref->x);
	strcat(PrefString,buffer);
	strcat(PrefString," y: ");
	sprintf(buffer, "%f", Pref->y);
	strcat(PrefString,buffer);
	strcat(PrefString," z: ");
	sprintf(buffer, "%f", Pref->z);
	strcat(PrefString,buffer);

	renderBitMapString(5,483,(char*)PrefString);

	/*creating the visible string: current mode*/
	strcat(locString,"camera position: x: ");
	sprintf(buffer, "%f", P0->x);
	strcat(locString,buffer);
	strcat(locString," y: ");
	sprintf(buffer, "%f", P0->y);
	strcat(locString,buffer);
	strcat(locString," z: ");
	sprintf(buffer, "%f", P0->z);
	strcat(locString,buffer);

    renderBitMapString(5,495,(char*)locString);
    glPopMatrix();
    resetPerspectiveProjection();
    glEnable(GL_TEXTURE_2D);

    glFlush();

    //loading in shaders again.
    glUseProgram(program);
    glutSwapBuffers();

}
/*
 * sets a orthographic projection temporary to be able to show 2d text.
 */
void setOrthographicProjection(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glScalef(1,-1,-1);
	glTranslatef(0,-500,0);
	glMatrixMode(GL_MODELVIEW);
}
/*
 * Resets the original projection.
 */
void resetPerspectiveProjection(){
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


/**
 * renders a sting into the visual display.
 * @param x float, the position in x-axis, measured from left to right.
 * @param y float, the position in y-axis, measured from up to down.
 * *theString const char, the string that should be printed out.
 */
void renderBitMapString(float x, float y,const char *theString){

	glRasterPos2i(x,y);					/*set the text appearance location.*/
	int stringLen = strlen(theString),i;
	void * font = GLUT_BITMAP_9_BY_15;

	for(i=0;i<stringLen;i++){
		glutBitmapCharacter(font,theString[i]);
	}
}

/*----------------------------------closing methods--------------------------*/

/**
 * gui exit method.
 */
void
atclose(void) {
    /*deallocate Buffers, programs and shaders.*/
	glutExit();

	if(fileOpen == true){
		freeOFFReaderMemory(fileData);
		free(verticeNormals);

	}
	continueCounting = false;
	Mwc->resize(0,0);
	MwcTranspose->resize(0,0);
	free(Mwc);
	free(MwcTranspose);
	delete[] P0;
	delete[] Pref;

	/*light functions.*/
	free(light_ambient);
	free(light_diffuseNspecular);
	free(material_ambient);
	free(material_diffuse);
	free(material_specular);
	free(ambient_prod);
	free(diffuse_prod);
	free(diffuse_prod2);
	free(specular_prod);

	free(lightPosition);
	free(lightPosition2);

	/*bezier variables*/
	free(uM);
	free(uMPrim);
	free(bezierP);
	free(PrefChange);

	/*random*/
	free(change);
	free(changeMat);
	free(V0);
	free(matTrans);
	free(matView);
	free(matProj);

    exit(0);
}
