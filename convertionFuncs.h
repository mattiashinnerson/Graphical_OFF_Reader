#ifndef convertionFuncs_H
#define convertionFuncs_H

#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric::ublas;

/**
 * converts the camera coordinates to world coordinates for a specific move
 * @param direction char, l = left, r = right, u = up, d = down,
 * 						  + = zoom in, - = zoom out.
 * @param axis char, the axis to perform the movement.
 * @param stepSize float, the stepzie to make.
 */
void convertMovToWorldCord(char direction, char axis, float stepSize);

/**
 * converts the camera coordinates to world coordinates for a rotation
 * @param direction char, if x-axis then p = right, else left,
 * 						  if y-axis then p = down, else up.
 * @param angle float, the rotation angle.
 * @param axis char, the axis to perform the movement, can be x or y.
 */
vector<float> convertRotToWorldCord(char direction,float angle, char axis);

#endif
