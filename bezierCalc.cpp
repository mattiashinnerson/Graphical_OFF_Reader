/**
 * File that calculates a bezier curve with N number of points for the camera
 * movement (P0) and Pref.
 */

#include "bezierCalc.h"

/*
 * Initialize the bezier variables that only need to be calculated once.
 * @param nrOfBezPoints int, the wanted number of points on the bezier curve.
 * @param *uM matrix<float>, one 3*nrOfBezPoints matrix for storing result.
 * @param *uMPrim matrix<float>, one 3*nrOfBezPoints matrix for storing result.
 */
void initBezierVariables(int nrOfBezPoints,matrix<float> *uM,
							matrix<float> *uMPrim){

	matrix<float> *uPrim = new matrix<float>(nrOfBezPoints,3);
	matrix<float> *M = new matrix<float>(3,3);
	matrix<float> temp, temp2;
	int i;

	/*General form for finding the bezier curve is the sum of:
	 *    bi(u)*pi(u)	, where i = our points. 	*/

	/*creating 11 u for later calculating 11 bezier points. */
	matrix<float> *u = new matrix<float>(nrOfBezPoints,3);

	/*each vector will have the values: [1	u	u^2], where u = [1/11,1]*/
	for(int i=1;i<nrOfBezPoints+1;i++){

		(*u)(i-1,0) = 1;
		(*u)(i-1,1) = (((float)i)/nrOfBezPoints);
		(*u)(i-1,2) = (((float)i)/nrOfBezPoints)*(((float)i)/nrOfBezPoints);
	}

	/*now we find our M matrix and multiply with u[] to get our b konstants
	 * (M can be found by making a )*/
	(*M)(0,0) = 1;
	(*M)(1,0) = -2;
	(*M)(2,0) = 1;
	(*M)(0,1) = 0;
	(*M)(1,1) = 2;
	(*M)(2,1) = -2;
	(*M)(0,2) = 0;
	(*M)(1,2) = 0;
	(*M)(2,2) = 1;

	temp = prod(*u,*M);

	/*derivate of u will be needed to calculate Pref.*/

	for(int i=1;i<nrOfBezPoints+1;i++){

		(*uPrim)(i-1,0) = 0;
		(*uPrim)(i-1,1) = 1;
		(*uPrim)(i-1,2) = 2*(((float)i)/nrOfBezPoints);
	}

	temp2 = prod(*uPrim,*M);

	/*transfering results to allocated matrixes.*/
	for(i=0;i<nrOfBezPoints;i++){
		(*uM)(i,0) = temp(i,0);
		(*uM)(i,1) = temp(i,1);
		(*uM)(i,2) = temp(i,2);

		(*uMPrim)(i,0) = temp2(i,0);
		(*uMPrim)(i,1) = temp2(i,1);
		(*uMPrim)(i,2) = temp2(i,2);
	}

	/*deallocating temporary variables.*/
	free(u);
	free(M);
	free(uPrim);
}

/*
 * calculate our new bezier curve.
 * @param lOrR char, l if left, r if right.
 * @param *P0 myVector, the coordinates of the point P0.
 * @param *Pref myVector, the coordinates of the point Pref.
 * @param *V0 vector<float>, the upvector.
 * @param *bezierP matrix<float>, where our bezier points will be stored.
 * @param *PrefChange matrix<float>, where our normal for each bezier point
 * 		   will be stored.
 * @param *uM matrix<float>, one 3*nrOfBezPoints matrix.
 * @param *uMPrim matrix<float>, one 3*nrOfBezPoints matrix.
 * @param speed float, the speed of the bezier animation. default = 0.5
 */
void calculateNewBezierCurve(char lOrR, myVector *P0, myVector *Pref,
							  vector<float> *V0, matrix<float> *bezierP,
							     matrix<float> *PrefChange, matrix<float> *uM,
									matrix<float> *uMPrim, float speed){
	float degreeAngle = 55; //55 degrees.

	vector<float> *V;
	vector<float> *P1 = new vector<float>(3);
	vector<float> *P2 = new vector<float>(3);
	vector<float> *delta = new vector<float>(3);
	matrix<float> *P = new matrix<float>(3,3);
	matrix<float> temp, temp2;
	int i;
	float turnAngleX = cos(degreeAngle*3.14159265359/180);
	float turnAngleY = sin(degreeAngle*3.14159265359/180);

	/*For finding our end point P2 we need to now the orthogonal vector,
	  equation = (cross((Pref-P0),V0)*/

	(*delta)(0) = (Pref->x - P0->x);
	(*delta)(1) = (Pref->y - P0->y);
	(*delta)(2) = (Pref->z - P0->z);

	normalization(delta);
	(*delta)(0) = speed*(*delta)(0);
	(*delta)(1) = speed*(*delta)(1);
	(*delta)(2) = speed*(*delta)(2);

	if(lOrR == 'l'){
		V = (cross_product(V0,delta));
	}else{
		V = cross_product(delta,V0);
	}
	normalization(V);

	(*V)(0) = speed * (*V)(0);
	(*V)(1) = speed * (*V)(1);
	(*V)(2) = speed * (*V)(2);

	/*Calculating our P1 (control point)*/
	(*P1)(0) = P0->x + (*delta)(0);
	(*P1)(1) = P0->y + (*delta)(1);
	(*P1)(2) = P0->z + (*delta)(2);

	/*We sum the vector with the point p1 depending on the angle we want
	 *to turn compared to P0. Equation: p2 = p1 + cos(a)*delta + sin(a)*v */

	(*P2)(0)= Pref->x + turnAngleX*((*delta)(0)) + turnAngleY*((*V)(0));
	(*P2)(1)= Pref->y + turnAngleX*((*delta)(1)) + turnAngleY*((*V)(1));
	(*P2)(2) = Pref->z + turnAngleX*((*delta)(2)) + turnAngleY*((*V)(2));

	/*assigning our 3 bezier points. Note that they are in camera coordinates.*/

	(*P)(0,0) = P0->x;
	(*P)(0,1) = P0->y;
	(*P)(0,2) = P0->z;
	(*P)(1,0) = (*P1)(0);
	(*P)(1,1) = (*P1)(1);
	(*P)(1,2) = (*P1)(2);
	(*P)(2,0) = (*P2)(0);
	(*P)(2,1) = (*P2)(1);
	(*P)(2,2) = (*P2)(2);

	/*we now calculate our bezier points.*/
	temp = prod(*uM,*P);

	/* We want to find the points how Pref will change.
	 * For this we first need the tangent:*/
	temp2 = prod(*uMPrim, *P);

	for(i=0;i< ((int)temp.size1()) ;i++){

		/*then to get the Pref point, we take P(u) + P'(u)*/
		temp2(i,0) = P0->x + temp2(i,0);
		temp2(i,1) = P0->y + temp2(i,1);
		temp2(i,2) = P0->z + temp2(i,2);

		/*transfering results to allocated matrixes.*/
		(*bezierP)(i,0) = temp(i,0);
		(*bezierP)(i,1) = temp(i,1);
		(*bezierP)(i,2) = temp(i,2);

		(*PrefChange)(i,0) = temp2(i,0);
		(*PrefChange)(i,1) = temp2(i,1);
		(*PrefChange)(i,2) = temp2(i,2);
	}

	/*free temporary variables.*/
	free(P1);
	free(P2);
	free(delta);
	free(V);
	free(P);
}

