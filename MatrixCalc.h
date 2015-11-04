/*
 * matrixCalc.h
 *
 *  Created on: Jan 29, 2014
 *      Author: oi11mhn
 */

#ifndef MATRIXCALC_H_
#define MATRIXCALC_H_

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "OFFReader.h"

using namespace boost::numeric::ublas;

/**
 * function that translates a matrix
 * @param dx float, difference for x value.
 * @param dy float, difference for y value.
 * @param dz float, difference for z value.
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * that is 4x4 large where the result will be stored.
 */
void translate(float dx, float dy, float dz, matrix<float> *m);


/**
 * function that scales a matrix.
 * @param sx float, scale increase/decrease in x-axis.
 * @param sy float, scale increase/decrease in y-axis.
 * @param sz float, scale increase/decrease in z-axis.
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void scale(float sx, float sy, float sz,
				boost::numeric::ublas::matrix<float> *m);


/**
 * rotates a matrix around the z axis.
 * @param dx float, rotation in degrees
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void rotatez(float a, boost::numeric::ublas::matrix<float> *M);


/**
 * rotates a matrix around the z axis.
 * @param dx float, rotation in degrees
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 */
void rotatey(float a, boost::numeric::ublas::matrix<float> *M);


/**
 * rotates a matrix around the z axis.
 * @param dx float, rotation in degrees
 * @param M , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * this method also suffer for a little catastrophic calculation!
 */
void rotatex(float a, boost::numeric::ublas::matrix<float> *M);

/**
 * function that calculates the division between two vectors (v1/v2).
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *v2 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return *result<float> (3), pointer to a vector of size 3.
 */
vector<float> *vectorDivision(boost::numeric::ublas::vector<float> *v1,
								boost::numeric::ublas::vector<float> *v2);

/**
 * calculates the crossProduct between the vertices.
 * this function only works for 3x3 vectors.
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *v2 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return *result<float> (3), pointer to a vector of size 3.
 * observe, this method may suffer from catastrophic cancellation in a small
 * form!
 */
vector<float> *cross_product(boost::numeric::ublas::vector<float> *v1,
								boost::numeric::ublas::vector<float> *v2);


/**
 * normalizes the vector.
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 */
void normalization(boost::numeric::ublas::vector<float> *v1);

/**
 * takes the difference between two vector points.
 * @param *p1, a vertice point of type myVector;
 * @param *p2, a vertice point of type myVector;
 * @return resultVector vector<float>, a boost vector of size 3.
 */
vector<float> *difference(myVector *p1, myVector *p2);

/**
 * creates the negative for a vector.
 * @param *v1 vector<float>, pointer to a ublas vector of size 3.
 */
vector<float> *negative(boost::numeric::ublas::vector<float> *v1);

/**
 * multiply a matrix M1 with a matrix M2.
 * @param M1 , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @param M2 , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @return a matrix<float> (4,4), OBSERVE NOT A POINTER!
 */
matrix<float> multiply(boost::numeric::ublas::matrix<float> *M1,
						boost::numeric::ublas::matrix<float> *M2);

/**
 * multiply a matrix M with a vector V.
 * @param m , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @param v , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return a vector<float> (3), OBSERVE NOT A POINTER!
 */
vector<float> multiply2(boost::numeric::ublas::matrix<float> *m,
						boost::numeric::ublas::vector<float> *v);

/**
 * calculates the product of a vector v1 and a vector V2.
 * @param *v1 , boost::numeric::ublas::matrix<float> pointer to a ublas matrix
 * @param *v2 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @param *resultVv , boost::numeric::ublas::vector<float> pointer to a ublas
 * vector where the result will be stored.
 */
void multiply3(vector<float> *v1,vector<float> *v2,vector<float> *resultV);

/**
 * translates a vector into a matrix
 * @param *v1 , boost::numeric::ublas::vector<float> pointer to a ublas vector
 * @return a  a ublas matrix<float> (4,4).
 */
matrix<float> translate(boost::numeric::ublas::vector<float> *v1);
/**
 * creates a view matrix from 2 vertice points and a vector.
 * The vectors should be in world coordinates.
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
					matrix<float> *matView);

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
							float near,float far, matrix<float> *matProj);

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
					float near,float far, matrix<float> *matProj);

/**
 * creates one oblique matrix from 2 floats.
 * @param theta float, the angle in degrees compared to the x-axis.
 * @param phi float, the angle in degrees compared to the y-axis.
 * @param right float,
 * @param left float,
 * @param top float,
 * @param bottom float,
 * @param far float,
 * @param near float,
 * @param *matProj matrix<float> (4,4), one ublas matrix of size 4x4.
 * where our result will be stored.
 */
void oblique(float theta,float phi,float left,float right,float top,
				float bottom,float near,float far, matrix<float> *matProj);



#endif /* MATRIXCALC_H_ */
