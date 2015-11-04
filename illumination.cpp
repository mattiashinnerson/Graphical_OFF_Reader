/**
 * File containing all the functions for setting the light positions and color
 * attributes.
 *
 * author: Mattias Hinnerson(oi11mhn)
 * date: 2013-03-18
 */

#include "illumination.h"
#include "variables.h"
#include "walking_in_air.h"

void setLightScourcePosX(float x){

	(*lightPosition)(0) = x;
}

void setLightScourcePosY(float y){

	(*lightPosition)(1) = y;
}

void setLightScourcePosZ(float z){

	(*lightPosition)(2) = z;
}

void setLightScourceIntens(float r, float g, float b){

	(*light_diffuseNspecular)(0) = r;
	(*light_diffuseNspecular)(1) = g;
	(*light_diffuseNspecular)(2) = b;
}

void setAmbientLightIntens(float r, float g, float b){

    (*light_ambient)(0) = r;
    (*light_ambient)(1) = g;
    (*light_ambient)(2) = b;
    (*light_ambient)(3) = 1.0;
}

void setMaterialAmbientCoeffR(float r){

    (*material_ambient)(0) = r;
}

void setMaterialAmbientCoeffG(float g){

    (*material_ambient)(1) = g;
}

void setMaterialAmbientCoeffB(float b){

    (*material_ambient)(2) = b;
}

void setMaterialDiffuseCoeffR(float r){

    (*material_diffuse)(0) = r;
}

void setMaterialDiffuseCoeffG(float g){

    (*material_diffuse)(1) = g;
}

void setMaterialDiffuseCoeffB(float b){

    (*material_diffuse)(2) = b;
}

void setMaterialSpecularCoeffR(float r){

    (*material_specular)(0) = r;
}

void setMaterialSpecularCoeffG(float g){

    (*material_specular)(1) = g;
}

void setMaterialSpecularCoeffB(float b){

    (*material_specular)(2) = b;
}

void setPhongShininess(int shininess){
	material_shininess = shininess;
}

void flipNormals(){
	int i;

	for(i=0;i < fileData->totNrOfVertices;i++){
		verticeNormals[i].x = (-verticeNormals[i].x);
		verticeNormals[i].y = (-verticeNormals[i].y);
		verticeNormals[i].z = (-verticeNormals[i].z);
	}
	glBufferSubData( GL_ARRAY_BUFFER, fileData->totNrOfVertices*sizeof(vec4),
					 fileData->totNrOfVertices*sizeof(vec4),verticeNormals);

	glutPostRedisplay();
}
