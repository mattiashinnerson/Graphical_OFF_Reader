/**
 * File that contains all the convertionfunctions from world to
 * camera coordinates.
 *
 * Author: Mattias Hinnerson(oi11mhn)
 * date: 2013-03-18
 */

#include "convertionFuncs.h"
#include "variables.h"
#include "walking_in_air.h"

/**
 * converts the camera coordinates to world coordinates for a specific move
 * @param direction char, l = left, r = right, u = up, d = down,
 * 						  + = zoom in, - = zoom out.
 * @param axis char, the axis to perform the movement.
 * @param stepSize float, the stepzie to make.
 */
void convertMovToWorldCord(char direction, char axis, float stepSize){

	/*The regular equation: T(P0) * MwcTranspose * [0,0,-d,1]*/

	/*calculating T(p0)*/
	vector<float> *pZero = new vector<float>(3);
	pZero->insert_element(0,P0->x);
	pZero->insert_element(1,P0->y);
	pZero->insert_element(2,P0->z);
	matrix<float> TP0 = translate(pZero);

	/*converting to get world coordinates for P0.*/
	matrix<float> temp = multiply(&TP0,MwcTranspose);

	if((direction == 'l') && (axis == 'x')){

		/*Converting to get world coordinates for P0, where Pc = [-d,0,0,1]*/
		change->insert_element(0,-0.1);
		change->insert_element(1,0);
		change->insert_element(2,0);
		change->insert_element(3,1);

		vector<float> P0w = multiply2(&temp,change);
		P0->x = P0w(0);
		P0->y = P0w(1);
		P0->z = P0w(2);

		/* Converting to get world coordinates for Pref,
		 * where Prefc = [-d,0,-1,1]*/
		change->insert_element(0,-0.1);
		change->insert_element(1,0);
		change->insert_element(2,-1);
		change->insert_element(3,1);

	}else if((direction == 'r') && (axis == 'x')){

		/*Converting to get world coordinates for P0, where Pc = [d,0,0,1]*/
		change->insert_element(0,0.1);
		change->insert_element(1,0);
		change->insert_element(2,0);
		change->insert_element(3,1);

		vector<float> P0w = multiply2(&temp,change);
		P0->x = P0w(0);
		P0->y = P0w(1);
		P0->z = P0w(2);

		/* Converting to get world coordinates for Pref,
		 * where Prefc = [d,0,-1,1]*/
		change->insert_element(0,0.1);
		change->insert_element(1,0);
		change->insert_element(2,-1);
		change->insert_element(3,1);

	}else if((direction == 'u') && (axis == 'y')){

		/*Converting to get world coordinates for P0, where Pc = [0,d,0,1]*/
		change->insert_element(0,0);
		change->insert_element(1,0.1);
		change->insert_element(2,0);
		change->insert_element(3,1);

		vector<float> P0w = multiply2(&temp,change);
		P0->x = P0w(0);
		P0->y = P0w(1);
		P0->z = P0w(2);

		/* Converting to get world coordinates for Pref,
		 * where Prefc =[0,d,-1,1]*/
		change->insert_element(0,0);
		change->insert_element(1,0.1);
		change->insert_element(2,-1);
		change->insert_element(3,1);

	}else if((direction == 'd') && (axis == 'y')){

		/*Converting to get world coordinates for P0, where Pc = [0,-d,0,1]*/
		change->insert_element(0,0);
		change->insert_element(1,-0.1);
		change->insert_element(2,0);
		change->insert_element(3,1);

		vector<float> P0w = multiply2(&temp,change);
		P0->x = P0w(0);
		P0->y = P0w(1);
		P0->z = P0w(2);

		/* Converting to get world coordinates for Pref,
		 * where Prefc =[0,-d,-1,1]*/
		change->insert_element(0,0);
		change->insert_element(1,-0.1);
		change->insert_element(2,-1);
		change->insert_element(3,1);
	}
	else if((direction == '+') && (axis == 'z')){

		/*Converting to get world coordinates for P0, where Pc = [0,0,-d,1]*/
		change->insert_element(0,0);
		change->insert_element(1,0);
		/*if using smooth moving with variable move speed, else move p0 -0.1*/
		if(stepSize != 0){
			change->insert_element(2,-stepSize);
		}else{
			change->insert_element(2,-0.1);
		}
		change->insert_element(3,1);

		vector<float> P0w = multiply2(&temp,change);
		P0->x = P0w(0);
		P0->y = P0w(1);
		P0->z = P0w(2);

		/* Converting to get world coordinates for Pref,
		 * where Prefc =[0,-1-d,0,1]*/
		change->insert_element(0,0);
		change->insert_element(1,0);
		/*if using smooth moving with variable move speed, else move pref -1.1*/
		if(useSmooth){
			change->insert_element(2,(-1-d));
		}else{
			change->insert_element(2,(-1.1));
		}
		change->insert_element(3,1);

	}else if((direction == '-') && (axis == 'z')){

		/*Converting to get world coordinates for P0, where Pc = [0,0,d,1]*/
		change->insert_element(0,0);
		change->insert_element(1,0);
		change->insert_element(2,0.1);
		change->insert_element(3,1);

		vector<float> P0w = multiply2(&temp,change);
		P0->x = P0w(0);
		P0->y = P0w(1);
		P0->z = P0w(2);

		/* Converting to get world coordinates for Pref,
		 * where Prefc =[0,-1+d,0,1]*/
		change->insert_element(0,0);
		change->insert_element(1,0);
		change->insert_element(2,(-0.9));
		change->insert_element(3,1);
	}
	vector<float> Prefw = multiply2(&temp,change);
	Pref->x = Prefw(0);
	Pref->y = Prefw(1);
	Pref->z = Prefw(2);

	free(pZero);
}

/**
 * converts the camera coordinates to world coordinates for a rotation
 * @param direction char, if x-axis then p = right, else left,
 * 						  if y-axis then p = down, else up.
 * @param angle float, the rotation angle.
 * @param axis char, the axis to perform the movement, can be x or y.
 */
vector<float> convertRotToWorldCord(char direction,float angle, char axis){

	/*convert angle to radians.*/
	float angleRadian = (angle*math_pi / 180);

	/*P0 and upvector V remains unchanged, changing Pref.*/

	/*first we calculate Pref in camera coordinates.*/
	change->insert_element(0,0);
	change->insert_element(1,0);
	change->insert_element(2,-1);
	change->insert_element(3,1);

	/*resetting changeMat*/
	for(int i=0; i < 4; i++){
		for(int j=0; j < 4; j++){
			(*changeMat)(i,j) = 0;
		}
	}
	/*rotation around the X-axis.*/
	if(axis == 'x'){
		if(direction == 'p'){
			changeMat->insert_element(1,1,cos(angleRadian));
			changeMat->insert_element(1,2,sin(angleRadian));
			changeMat->insert_element(2,1,-sin(angleRadian));
			changeMat->insert_element(2,2,cos(angleRadian));
		}
		if(direction == 'n'){
			changeMat->insert_element(1,1,cos(angleRadian));
			changeMat->insert_element(1,2,sin(angleRadian));
			changeMat->insert_element(2,1,-sin(angleRadian));
			changeMat->insert_element(2,2,cos(angleRadian));
		}
		changeMat->insert_element(0,0,1);
		changeMat->insert_element(3,3,1);
	}
	/*rotation around the Y-axis.*/
	if(axis == 'y'){
		if(direction == 'p'){
			changeMat->insert_element(0,0,cos(angleRadian));
			changeMat->insert_element(0,2,-sin(angleRadian));
			changeMat->insert_element(2,0,sin(angleRadian));
			changeMat->insert_element(2,2,cos(angleRadian));
		}

		if(direction == 'n'){
			changeMat->insert_element(0,0,cos(angleRadian));
			changeMat->insert_element(0,2,-sin(angleRadian));
			changeMat->insert_element(2,0,sin(angleRadian));
			changeMat->insert_element(2,2,cos(angleRadian));
		}
		changeMat->insert_element(1,1,1);
		changeMat->insert_element(3,3,1);
	}

	vector<float> PrefCamera= multiply2(changeMat,change);

	/*Then we convert the camera coordinates to worldcoordinates.*/

	/*calculating T(p0)*/
	vector<float> *pZero = new vector<float>(3);
	pZero->insert_element(0,P0->x);
	pZero->insert_element(1,P0->y);
	pZero->insert_element(2,P0->z);
	matrix<float> TP0 = translate(pZero);

	/*converting to get world coordinates for P0.*/
	matrix<float>  temp = multiply(&TP0,MwcTranspose);

	vector<float> PrefWorld = multiply2(&temp,&PrefCamera);

	return PrefWorld;
}

