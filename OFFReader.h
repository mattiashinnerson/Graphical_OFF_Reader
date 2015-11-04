/*
 * OFFReader.h
 *
 *  Created on: Jan 28, 2014
 *      Author: oi11mhn
 */

#ifndef OFFREADER_H_
#define OFFREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <unistd.h>

typedef struct{
	float x;
	float y;
	float z;
}myVector;

/*struct for polygons*/
typedef struct{
	int nrOfvertices;
	/*size of vertices[] may cause a constraint when reading off files if
	  columns > 128.*/
	myVector* vertices[128];
	int vertexIndeces[128];
	float colours[4];
}faces;

/*struct for triangled polygons*/
typedef struct{
	int nrOfvertices;
	myVector* vertices[3];
	int vertexIndices[3];
	float colours[4];
}triangledFaces;

/*struct that will contain all the final information.*/
typedef struct{
	int totTriangles;
	int totNrOfVertices;
	float biggestY;
	float biggestX;
	float biggestZ;
	float smallestX;
	float smallestY;
	float smallestZ;
	myVector* origoForObject;
	myVector *allVertices;
	triangledFaces *allTriangles;

}objectData;

/**
 * method for start reading one OFFFile. This method starts the whole program!
 * @param nrOfargs int, the total number of arguments.
 * @returns a pointer to a objectData struct. NULL if failed.
 */
 objectData *OFFRead(char args[]);

/**
 * Function for reading the input from a OFF file.
 * @param *infile FILE, the file to be read.
 * @param NVertices int, the number of vertices.
 * @param NFaces int, the total amount of faces.
 * @param NEdges int, the total amount of edges.
 * @param *allVectors, one pointer to one array of struct type myVector.
 * @return a pointer to a triangledFaces struct.
 */
triangledFaces* readFromFile(FILE *inFile, int NVertices, int NFaces,
						int NEdges, myVector *allVectors, objectData *allData);

/**
 * function that triangulates data.
 * @param allFaces[] faces, one array of the type struct faces.
 * @param nrOfFaces int.
 * @param triangledFaces[] triangledFaces, one array of the struct type
 * triangledFaces.
 * @return newIndex int, the size of the total amount of triangle polygons.
 */
int triangulation(faces *(allFaces[]), int nrOfFaces,
					triangledFaces triangledFaces[]);

/**
 * function for realeasing allocated memory.Observe that the main function must
 * have been called before using this.
 * @param *allTriangles objectData, a pointer to a struct of type objectData.
 */
void freeOFFReaderMemory(objectData *allTriangles);


#endif /* OFFREADER_H_ */
