#ifndef bezierCalc_H
#define bezierCalc_H

#include <stdio.h>
#include <stdlib.h>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include "OFFReader.h"
#include "MatrixCalc.h"


using namespace boost::numeric::ublas;

/*
 * Initialize the bezier variables that only need to be calculated once.
 * @param nrOfBezPoints int, the wanted number of points on the bezier curve.
 * @param *uM matrix<float>, one 3*nrOfBezPoints matrix for storing result.
 * @param *uMPrim matrix<float>, one 3*nrOfBezPoints matrix for storing result.
 */
void initBezierVariables(int nrOfBezPoints,matrix<float> *uM,
							matrix<float> *uMPrim);

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
									matrix<float> *uMPrim, float speed);

#endif
