
#ifndef variables_H
#define variables_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "OFFReader.h"

using namespace boost::numeric::ublas;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef struct{
	float r;
	float g;
	float b;
	float a;
} color4;

/*--------Global variables (must be global)--------------*/

/*The transition matrix*/
extern matrix<float> *matTrans;

/*The camera movement (V) matrix*/
extern matrix<float> *matView;

/*The projection (P) matrix*/
extern matrix<float> *matProj;

extern float math_pi;

/*Basic variables*/
extern int windowHeight;
extern int windowWidth;
extern objectData *fileData;
extern char currentMode;
extern char chosenDirection;
extern char chosenMovement;
extern char currentProj;
extern vector<float> *change;
extern matrix<float> *changeMat;

extern bool objectFilled;
extern bool fileOpen;
extern float xChanged;
extern float yChanged;
extern float zChanged;

/*Glut variables*/
extern GLuint program;
extern GLuint idTransMat;
extern GLuint idViewMat;
extern GLuint idProjMat;
extern GLuint theNormal;

extern GLuint ambient_product_loc;
extern GLuint diffuse_product_loc;
extern GLuint diffuse_product_loc2;
extern GLuint specular_product_loc;
extern GLuint light_loc;
extern GLuint light_loc2;
extern GLuint lightShininess_loc;

/*camera vectors and points*/
extern vector<float> *V0;						//the upvector
extern matrix<float> *Mwc;
extern matrix<float> *MwcTranspose;
extern myVector *P0;
extern myVector *Pref;

/*The size of the view field*/
extern float top;
extern float bottom;
extern float left;
extern float right;
extern float near;
extern float far;
extern float scaleForm;

/*Camera variables */
extern float camStartX;
extern float camStartY;
extern float camStartZ;

/*mouse*/
extern float verticalMouseSens;		/*X sense. Higher value = slower rotation*/
extern float HorizontalMouseSens;	/*Y sense. Higher value = slower rotation*/
extern float camHorizChange;
extern float camVertChange;
extern float camHorizRot;
extern float camVertRot;

extern bool firstTimeClick;
extern int currentMouseX;
extern int currentMouseY;

/*Illumination*/
extern float ambientLight;
extern vector<float> *light_ambient;
extern vector<float> *light_diffuseNspecular;

extern vector<float> *material_ambient;
extern vector<float> *material_diffuse;
extern vector<float> *material_specular;
extern vector<float> *ambient_prod;
extern vector<float> *diffuse_prod;
extern vector<float> *diffuse_prod2;
extern vector<float> *specular_prod;
extern float material_shininess;
extern bool lightPos2MoveR;
extern bool lightPos2MoveU;

//lightscources.
extern vector<float> *lightPosition;
extern vector<float> *lightPosition2;

extern vec4 *verticeNormals;
extern float lightScourceR;
extern float lightScourceG;
extern float lightScourceB;

/*time variables*/
extern bool continueCounting;
extern int timerCountMillis;
extern int nrOfBezPoints;					//the number of points on the curve.
extern int bezierPCounter;

/*Bezier curves variables*/
extern bool useSmooth;
extern char direction;
extern float bezSpeed;
extern float d;		/*the distance konstant between our bezier points*/
extern matrix<float> *uM;
extern matrix<float> *uMPrim;
extern matrix<float> *bezierP;
extern matrix<float> *PrefChange;

#endif
