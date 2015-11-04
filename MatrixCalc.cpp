/*
 * matrixCalc.cpp
 * program with functions for translating, rotating, and scaling matrixes.
 *  Created on: Jan 29, 2014
 *      Author: oi11mhn
 */

#include "MatrixCalc.h"

/**
 * function that translates a matrix
 * @param dx float, difference for x value.
 * @param dy float, difference for y value.
 * @param dz float, difference for z value.
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * that is 4x4 large where the result will be stored.
 */
void translate(float dx, float dy, float dz, matrix<float> *m){

	int i,j;

	/*creating translation matrix.*/
	boost::numeric::ublas::matrix<float> mat (4,4);
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			if(i==j){
				mat(i,j) = 1;
			}else{
				mat(i,j) = 0;
			}
		}
	}
	mat(0,3) = dx;
	mat(1,3) = dy;
	mat(2,3) = dz;

	//matrix<float> resultMatrix = prod(mat,*m);
	matrix<float> resultMatrix = prod(*m,mat);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*m)(i,j)) = ((resultMatrix)(i,j));
		}
	}
}

/**
 * function that scales a matrix.
 * @param sx float, scale increase/decrease in x-axis.
 * @param sy float, scale increase/decrease in y-axis.
 * @param sz float, scale increase/decrease in z-axis.
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void scale(float sx,float sy,float sz,
						boost::numeric::ublas::matrix<float> *m){
	int i,j;
	boost::numeric::ublas::matrix<float> resultM (4,4);

	/*creating translation matrix.*/
	boost::numeric::ublas::matrix<float> mat (4,4);
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
				mat(i,j) = 0;
		}
	}
	mat(0,0) = sx;
	mat(1,1) = sy;
	mat(2,2) = sz;
	mat(3,3) = 1;

	matrix<float> resultMatrix = prod(mat,*m);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*m)(i,j)) = ((resultMatrix)(i,j));
		}
	}
}

/**
 * rotates a matrix around the z axis.
 * @param dx float, rotation in degrees
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void rotatez(float a, boost::numeric::ublas::matrix<float> *m){

	int i,j;

	/*converting to radians*/
	float rotation = (a*3.14159265359/180);

	/*creating translation matrix.*/
	boost::numeric::ublas::matrix<float> mat (4,4);
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
				mat(i,j) = 0;
		}
	}
	mat(0,0) = cos(rotation);
	mat(0,1) = -sin(rotation);
	mat(1,0) = sin(rotation);
	mat(1,1) = cos(rotation);
	mat(2,2) = 1;
	mat(3,3) = 1;

	matrix<float> resultMatrix = prod(mat,*m);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*m)(i,j)) = ((resultMatrix)(i,j));
		}
	}
}

/**
 * rotates a matrix around the y axis.
 * @param dx float, rotation in degrees
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void rotatey(float a, boost::numeric::ublas::matrix<float> *m){

	int i,j;

	/*converting to radians*/
	float rotation = (a*3.14159265359/180);

	/*creating translation matrix.*/
	boost::numeric::ublas::matrix<float> mat (4,4);
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
				mat(i,j) = 0;
		}
	}
	mat(0,0) = cos(rotation);
	mat(0,2) = -sin(rotation);
	mat(1,1) = 1;
	mat(2,0) = sin(rotation);
	mat(2,2) = cos(rotation);
	mat(3,3) = 1;


	matrix<float> resultMatrix = prod(mat,*m);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*m)(i,j)) = ((resultMatrix)(i,j));
		}
	}
}

/**
 * rotates a matrix around the x axis.
 * @param dx float, rotation in degrees
 * @param *M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void rotatex(float a, boost::numeric::ublas::matrix<float> *m){

	int i,j;

	/*converting to radians*/
	float rotation = (a*3.14159265359/180);

	/*creating translation matrix.*/
	boost::numeric::ublas::matrix<float> mat (4,4);
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
				mat(i,j) = 0;
		}
	}
	mat(0,0) = 1;
	mat(1,1) = cos(rotation);
	mat(1,2) = -sin(rotation);
	mat(2,1) = sin(rotation);
	mat(2,2) = cos(rotation);
	mat(3,3) = 1;

	matrix<float> resultMatrix = prod(mat,*m);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*m)(i,j)) = ((resultMatrix)(i,j));
		}
	}
}

/**
 * function that calculates the division between two vectors (v1/v2).
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *v2 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return *result<float> (3), pointer to a vector of size 3.
 */
vector<float> *vectorDivision(boost::numeric::ublas::vector<float> *v1,
								boost::numeric::ublas::vector<float> *v2){

	vector<float> *resultVector = new vector<float> (3);
	for(int i=0;i<3;i++){
		resultVector->insert_element(i,( ((*v1)(i)) / ((*v2)(i)) ));
	}
	return resultVector;
}


/**
 * calculates the crossProduct between the vertices for getting an orthogonal
 * vector to v1,v2.
 * observer that this function only works for vectors with length 3!
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *v2 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return *result<float> (3), pointer to a vector of size 3.
 * observe, this method may suffer from catastrophic cancellation in a small
 * form!
 */
vector<float> *cross_product(boost::numeric::ublas::vector<float> *v1,
								boost::numeric::ublas::vector<float> *v2){

	if(v1->size() != 3 || v2->size() != 3){
		printf("ERROR! one vertice doesn't have the length 3!\n");
		return NULL;
	}

	vector<float> *resultVector = new vector<float> (3);

	/*calculating the new x-value for the new vector.*/
	/*(y1*z2 - z1*y2)*/
	resultVector->insert_element(0,( (*v1)(1)*(*v2)(2) - (*v1)(2)*(*v2)(1)));
	/*(x1*z2 - z1*x2)*/
	resultVector->insert_element(1,( (*v1)(2)*(*v2)(0) - (*v1)(0)*(*v2)(2)));
	/*(x1*y2 - y1*x2)*/
	resultVector->insert_element(2,( (*v1)(0)*(*v2)(1) - (*v1)(1)*(*v2)(0)));

	return resultVector;
}

/**
 * get a normalized vector for the vector v1.
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 */
void normalization(boost::numeric::ublas::vector<float> *v1){

	/*taking the norm of the vector values, then dividing all elements with*/
	float norm = sqrt(((*v1)(0))*(((*v1)(0))) +
						((*v1)(1))*(((*v1)(1))) +((*v1)(2))*(((*v1)(2))) );

	/*calculating normalized vector*/
	(*v1)(0) = ((*v1)(0)/norm);
	(*v1)(1) = ((*v1)(1)/norm);
	(*v1)(2) = ((*v1)(2)/norm);
}

/**
 * takes the difference between two vector points (P2 - P1)
 * @param *p1, a vertice point of type myVector;
 * @param *p2, a vertice point of type myVector;
 * @return resultVector vector<float>, a boost vector of size 3.
 */
vector<float> *difference(myVector *p1, myVector *p2){

	vector<float> *resultVector = new vector<float> (3);

	/*calculating the new x-value for the new vector.*/
	/*(y1*z2 - z1*y2)*/
	resultVector->insert_element(0,(p2->x - p1->x) );
	/*(x1*z2 - z1*x2)*/
	resultVector->insert_element(1,(p2->y - p1->y) );
	/*(x1*y2 - y1*x2)*/
	resultVector->insert_element(2,(p2->z - p1->z) );

	return resultVector;
}

/**
 * creates the negative for a vector.
 * @param *v1 vector<float>, pointer to a ublas vector of size 3.
 */
vector<float> *negative(boost::numeric::ublas::vector<float> *v1){

	vector<float> *resultVector = new vector<float> (3);

	/*calculating the new x-value for the new vector.*/
	/* -x */
	resultVector->insert_element(0, -(*v1)(0));
	/* -y */
	resultVector->insert_element(1,-(*v1)(1));
	/* -z */
	resultVector->insert_element(2,-(*v1)(2));

	return resultVector;
}

/**
 * multiply a matrix M1 with a matrix M2.
 * @param M1 , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @param M2 , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @return a matrix<float> (4,4), OBSERVE NOT A POINTER!
 */
matrix<float> multiply(boost::numeric::ublas::matrix<float> *M1,
						boost::numeric::ublas::matrix<float> *M2){

	matrix<float> resultMatrix = prod((*M1),(*M2));
	return resultMatrix;
}

/**
 * multiply a matrix M with a vector V.
 * @param m , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @param v , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return a vector<float> (3), OBSERVE NOT A POINTER!
 */
vector<float> multiply2(boost::numeric::ublas::matrix<float> *m,
						boost::numeric::ublas::vector<float> *v){

	vector<float> resultMatrix = prod((*m),(*v));
	return resultMatrix;
}

/**
 * calculates the product of a vector v1 and a vector V2.
 * @param *v1 , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @param *v2 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *resultVv , boost::numeric::ublas::vector<float> pointer to a ublas
 * vector where the result will be stored.
 */
void multiply3(vector<float> *v1,vector<float> *v2,vector<float> *resultV){

	(*resultV)(0) = (*v1)(0)*(*v2)(0);
	(*resultV)(1) = (*v1)(1)*(*v2)(1);
	(*resultV)(2) = (*v1)(2)*(*v2)(2);
	(*resultV)(3) = (*v1)(3)*(*v2)(3);
}

/**
 * translates a vector into a matrix
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return a  a ublas matrix<float> (4,4).
 */
matrix<float> translate(boost::numeric::ublas::vector<float> *v1){

	/*creating one identity matrix*/
	matrix<float> resultM(4,4);

	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			if(i==j){
				resultM(i,j) = 1;
			}else{
				resultM(i,j) = 0;
			}
		}
	}

	/*translating identity matrix with our vector values through translate f.*/
	translate((*v1)(0),(*v1)(1),(*v1)(2),&resultM);
	return resultM;
}

/**
 * creates a view matrix from 2 vertice points and a vector.
 * this matrix. The vectors should be in world coordinates.
 * @param *p1 myVector, a vector point of struct type myVector.
 * @param *p2 myVector, a vector point of struct type myVector.
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *Mwc matrix<float>, a matrix of size 4x4 where values will be stored
 * 		   for easy convertion between world and acmera cordinates.
 * @param *MwcInverse matrix<float>, a matrix of size 4x4, the inverse of Mwc.
 * @param *matView matrix<float>, the view matrix of size 4x4 where the result
 * will be stored.
 */
void view(myVector *P0,myVector *Pref, vector<float> *v1,
					matrix<float> *Mwc, matrix<float> *MwcInverse,
					matrix<float> *matView){
	int i,j;

	/*find out the difference*/
	vector<float> *n = difference(Pref,P0);

	/*first we want to find out the camera's Z-axis in world coordinates.*/
	/*n = (P0-Pref)/(norm(P0-Pref))*/

	normalization(n);

	/*then we find the vector perpendicular to P0-Pref*/
	/*u = ( (v1 x n) / (norm(v1 x n)) )*/

	vector<float> *u = (cross_product(v1,n));
	normalization(u);

	/*find the vector (v) perpendicular to n and u*/
	vector<float> *v = cross_product(n,u);

	/*combine vertice y,v, and n to get the matrix [u v n], then invert to
	 * get the Mwc matrix, which will be:*/
	/*	|u1	u2	u3	0|
		|v1	v2	v3	0|
		|n1	n2	n3	0|
		|0	0	0	1|
	*/

	Mwc-> insert_element(0,0,( (*u)(0) ));
	Mwc-> insert_element(0,1,( (*u)(1) ));
	Mwc-> insert_element(0,2,( (*u)(2) ));
	Mwc-> insert_element(0,3, 0);

	Mwc-> insert_element(1,0,( (*v)(0) ));
	Mwc-> insert_element(1,1,( (*v)(1) ));
	Mwc-> insert_element(1,2,( (*v)(2) ));
	Mwc-> insert_element(1,3, 0);

	Mwc-> insert_element(2,0,( (*n)(0) ));
	Mwc-> insert_element(2,1,( (*n)(1) ));
	Mwc-> insert_element(2,2,( (*n)(2) ));
	Mwc-> insert_element(2,3, 0);

	Mwc-> insert_element(3,0, 0);
	Mwc-> insert_element(3,1, 0);
	Mwc-> insert_element(3,2, 0);
	Mwc-> insert_element(3,3, 1);

	/*also saving the inverse matrix of Mwc*/
	MwcInverse-> insert_element(0,0,( (*u)(0) ));
	MwcInverse-> insert_element(1,0,( (*u)(1) ));
	MwcInverse-> insert_element(2,0,( (*u)(2) ));
	MwcInverse-> insert_element(3,0, 0);

	MwcInverse-> insert_element(0,1,( (*v)(0) ));
	MwcInverse-> insert_element(1,1,( (*v)(1) ));
	MwcInverse-> insert_element(2,1,( (*v)(2) ));
	MwcInverse-> insert_element(3,1, 0);

	MwcInverse-> insert_element(0,2,( (*n)(0) ));
	MwcInverse-> insert_element(1,2,( (*n)(1) ));
	MwcInverse-> insert_element(2,2,( (*n)(2) ));
	MwcInverse-> insert_element(3,2, 0);

	MwcInverse-> insert_element(0,3, 0);
	MwcInverse-> insert_element(1,3, 0);
	MwcInverse-> insert_element(2,3, 0);
	MwcInverse-> insert_element(3,3, 1);

	/*Find the translation matrix of -P0*/
	vector<float> *ublasVP0 = new vector<float> (3);
	ublasVP0->insert_element(0,(-(P0->x)));
	ublasVP0->insert_element(1,(-(P0->y)));
	ublasVP0->insert_element(2,(-(P0->z)));
	matrix<float> TminusP0 = translate(ublasVP0);

	matrix<float> *tp = &TminusP0;

	/*now we calculate the final view matrix via the calculation:
	  Mwc * TminusP0*/

	matrix<float> resultMatrix = multiply(Mwc,tp);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*matView)(i,j)) = ((resultMatrix)(i,j));
		}
	}

	//deallocating memory for middle stage matrices.
	n->resize(0);
	u->resize(0);
	v->resize(0);
	ublasVP0->resize(0);

	free(n);
	free(u);
	free(v);
	free(ublasVP0);
}

/**
 * creates a perspective matrix from 6 float values.
 * @param right float,
 * @param left float,
 * @param top float,
 * @param bottom float,
 * @param far float,
 * @param near float,
 * @param *matProj matrix<float> (4,4), one ublas matrix of size 4x4.
 * where our result will be stored.
 */
void perspective(float left,float right,float top,float bottom,
							float near,float far, matrix<float> *matProj){
	int i,j;

	matrix<float> *Ppersp = new matrix<float> (4,4);
	/*filling Ppersp with zeros*/
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			Ppersp->insert_element(i,j,0);
		}
	}
	Ppersp->insert_element(0,0,( (2*near)/(right-left) ));
	Ppersp->insert_element(0,2,( (right+left)/(right-left) ));
	Ppersp->insert_element(1,1,( (2*near)/(top-bottom) ));
	Ppersp->insert_element(1,2,( (top+bottom)/(top-bottom) ));
	Ppersp->insert_element(2,2,-( (far+near)/(far-near) ));
	Ppersp->insert_element(2,3,( (-2*far*near)/(far-near) ));
	Ppersp->insert_element(3,2,-1);

	matrix<float> resultMatrix = *Ppersp;

	/*deallocating memory for middlestage storages.*/
	Ppersp->resize(0,0);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*matProj)(i,j)) = ((resultMatrix)(i,j));
		}
	}

	free(Ppersp);
}

/**
 * creates a orthographic projection matrix from 6 float values.
 * @param right float,
 * @param left float,
 * @param top float,
 * @param bottom float,
 * @param far float,
 * @param near float,
 * @param *matProj matrix<float> (4,4), one ublas matrix of size 4x4.
 * where our result will be stored.
 */
void orthographic(float left,float right,float top,float bottom,
								float near,float far, matrix<float> *matProj){
	int i,j;

	/* General equation: S * T*/
	matrix<float> *ST = new matrix<float> (4,4);

	/*filling ST with zeros*/
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			ST->insert_element(i,j,0);
		}
	}
	ST->insert_element(0,0,(2/(right-left)));
	ST->insert_element(1,1,(2/(top-bottom)));
	ST->insert_element(2,2,-(2/(far-near)));
	ST->insert_element(0,3,-((left+right)/(right-left)));
	ST->insert_element(1,3,-((top+bottom)/(top-bottom)));
	ST->insert_element(2,3,-((far+near)/(far-near)));
	ST->insert_element(3,3,1);

	matrix<float> resultM = *ST;

	/*deallocating memory for middlestage storages.*/
	ST->resize(0,0);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*matProj)(i,j)) = ((resultM)(i,j));
		}
	}

	free(ST);
}

/**
 * creates one oblique matrix from 2 floats.
 * @param theta float, the angle in degrees compared to the x-axis.
 * @param phi float, the angle in degrees compared to the y-axis.
 * @param right float,
 * @param left float,
 * @param top float,
 * @param bottom float,
 * @param near float,
 * @param far float,
 * @param *matProj matrix<float> (4,4), one ublas matrix of size 4x4.
 * where our result will be stored.
 */
void oblique(float theta,float phi,float left,float right,float top,
				float bottom,float near,float far, matrix<float> *matProj){
	int i,j;

	/*converting to radians*/
	float thetaRadians = (theta*180/3.14159265359);			//************
	float phiRadians = (phi*180/3.14159265359);				//************


	/*Morth * S * T *H(theta,..) = Morth * Poblique*/

	matrix<float> *H = new matrix<float> (4,4);
	/*filling H*/
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			if(i==j){
				H->insert_element(i,j,1);
			}else{
				H->insert_element(i,j,0);
			}
		}
	}

	H->insert_element(0,2,( cos(thetaRadians) / sin(thetaRadians) ));
	H->insert_element(1,2,( cos(phiRadians) / sin(phiRadians) ));

	orthographic(left,right,top,bottom,near,far,matProj);
	matrix<float> resultMatrix = multiply(matProj,H);

	/*deallocating memory for middlestage storages.*/
	H->resize(0,0);
	free(H);

	/*transfering the result to matTrans matrix.*/
	for(i=0; i < 4; i++){
		for(j=0; j < 4; j++){
			((*matProj)(i,j)) = ((resultMatrix)(i,j));
		}
	}
}
