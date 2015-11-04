/*
 * OFFReader.cpp
 *
 *  Created on: Jan 28, 2014
 *      Author: oi11mhn
 */

#include "OFFReader.h"

int nrOfTrianglePolygons = 0;

/**
 * method for start reading one OFFFile. This method starts the whole program!
 * @param nrOfargs int, the total number of arguments.
 * @returns a pointer to a objectData struct. NULL if failed.
 */
objectData *OFFRead(char args[]){

	DIR *pdir = NULL;
	FILE *inFile = NULL;
	char offString[] = "OFF";
	char readLine[256];
	char *part, *fileName, filePath[512], temp[512];
	int NVertices, NFaces, NEdges, nrOfDir = 0;
	myVector *allVectors;
	objectData *allData = (objectData*) malloc(sizeof(objectData));
	allData->biggestX = 0;
	allData->biggestY = 0;
	allData->biggestZ = 0;
	allData->smallestX = 0;
	allData->smallestY = 0;
	allData->smallestZ = 0;

	/*making sure that the working directory is correct*/
	strcpy(temp,args);
	part = strtok(temp,"/");

	/*first count how many directories the filepath have, also get filename.*/
	while((part = strtok(NULL,"/")) != NULL){
	    fileName = part;
	    nrOfDir++;
	}
	nrOfDir--;

	/*get the searchpath.*/
	part = strtok(args,"/");
	strcpy(filePath,"/");
	strcat(filePath,part);
	strcat(filePath,"/");
	for(int i=0;i<nrOfDir;i++){
		part = strtok(NULL,"/");
		strcat(filePath,part);
		strcat(filePath,"/");
	}

	/*changing directory to the specified FilePath*/
	chdir(filePath);

	/*opening file*/
	inFile = fopen(fileName,"r");

	if(inFile == NULL){

		printf("ERROR: couldn't open the selected OFF file. "
			   "Restart the program and try again.\nRemember that the file must"
			   " be a OFF file.\n");
		closedir(pdir);
		return NULL;
	}
	//read the first line, check if OFF file.
	fgets(readLine, 256, inFile);
	if(strncmp(readLine, offString,3) == 0){

		//reading nr of vertices, faces, edges.
		fgets(readLine, 256, inFile);

		char *part = strtok (readLine," ");
		NVertices = atoi(part);

		part = strtok (NULL," ");
		NFaces = atoi(part);

		part = strtok (NULL," ");
		NEdges = atoi(part);

		//allocating place to store all vectors.
		allVectors = (myVector*) calloc(NVertices,sizeof(myVector));

		//read body from the file
		allData->allTriangles = readFromFile(inFile, NVertices, NFaces, NEdges,
												allVectors, allData);

		//after this point, all values are read and stored!
	}else{
		printf("ERROR! wrong OFF file format.\n");
		return NULL;

	}

	chdir("..");

	//clear all allocated memory
	closedir(pdir);
	fclose(inFile);

	allData->totTriangles = nrOfTrianglePolygons;
	allData->totNrOfVertices = NVertices;

	allData->allVertices = allVectors;

	return allData;
}

/**
 * Function for reading the input from a OFF file.
 * @param *infile FILE, the file to be read.
 * @param NVertices int, the number of vertices.
 * @param NFaces int, the total amount of faces.
 * @param NEdges int, the total amount of edges.
 * @param *allVectors, one pointer to one array of struct type myVector.
 * @return a pointer to a triangledFaces struct.
 */
triangledFaces *readFromFile(FILE *inFile, int NVertices, int NFaces,
						int NEdges, myVector *allVectors, objectData *allData){

	setlocale(LC_ALL,"C");

	char readLine[256], *temp;
	int  i,j, colorCounter, totNrOfTriangles = 0;
	faces *(allFaces[NFaces]);

	/*reading and storing all the vertices.*/
	for(i=0;i<NVertices;i++){
		fgets(readLine,256,inFile);

		/*dont read lines that doesn't contain anything.*/
		if(strlen(readLine)>2){
			//putting in the vector values in a struct.
			sscanf(readLine,"%f%f%f",&allVectors[i].x,&allVectors[i].y,
										&allVectors[i].z);

			/*saving the smallest/biggest values for calculating the origo.*/
			if(allVectors[i].x > allData->biggestX){
				allData->biggestX = allVectors[i].x;
			}
			if(allVectors[i].x < allData->smallestX){
				allData->smallestX = allVectors[i].x;
			}
			if(allVectors[i].y > allData->biggestY){
				allData->biggestY = allVectors[i].y;
			}
			if(allVectors[i].y < allData->smallestY){
				allData->smallestY = allVectors[i].y;
			}
			if(allVectors[i].z > allData->biggestZ){
				allData->biggestZ = allVectors[i].z;
			}
			if(allVectors[i].z < allData->smallestZ){
				allData->smallestZ = allVectors[i].z;
			}
		}else{
			i--;
		}
	}

	/*allocating and calculating the origo for the object (a + ((b-a)/2) ).*/
	allData->origoForObject = (myVector*) malloc(sizeof(myVector));

	allData->origoForObject->x = (allData->smallestX +
									((allData->biggestX-allData->smallestX)/2));
	allData->origoForObject->y = (allData->smallestY +
									((allData->biggestY-allData->smallestY)/2));
	allData->origoForObject->z = (allData->smallestZ +
									((allData->biggestZ-allData->smallestZ)/2));

	/*getting all the edges*/
	for (i=0;i<NFaces;i++){
		fgets(readLine,256,inFile);
		faces *oneFace = (faces*) malloc(sizeof(faces));

		//putting all the edge values in a struct. observe token=space and tab.
		temp = strtok(readLine," \t");
		oneFace-> nrOfvertices = atoi(temp);
		totNrOfTriangles = totNrOfTriangles + (atoi(temp) -2);

		//make sure that the polygon values fits in array vertices[].
		if(oneFace->nrOfvertices < 128){

			for(j=0;j<(oneFace->nrOfvertices);j++){
				temp = strtok(NULL," \t");
				oneFace->vertices[j] = &allVectors[atoi(temp)];
				oneFace->vertexIndeces[j] = atoi(temp);
			}
			colorCounter = 0;

			//reading in color (if any).
			while((temp = strtok(NULL," ")) != NULL){
				oneFace->colours[colorCounter] =  atof(temp);
				colorCounter++;
			}
			allFaces[i] = oneFace;
		}else{

			printf("ERROR! one polygon has too many vertices ");
			printf("to fit in the program.\n");
			printf("closing program.\n");
			return NULL;
		}
	}

	triangledFaces *triangles = (triangledFaces*) calloc(totNrOfTriangles,
									sizeof (triangledFaces));

	//call function for triangulation.
	triangulation(allFaces, NFaces, triangles);
	nrOfTrianglePolygons = totNrOfTriangles;
	return triangles;
}

/**
 * function that triangulates data.
 * @param allFaces[] faces, one array of the type struct faces.
 * @param nrOfFaces int.
 * @param triangledFaces[] triangledFaces, one array of the struct type
 * triangledFaces.
 * @return newIndex int, the size of the total amount of triangle polygons.
 */
int triangulation(faces *(allFaces[]), int nrOfFaces,
						triangledFaces *triangledFaces){

	int j,i,oldIndex = 0, newIndex = 0;

	//go through every row, divide all polygons until they are triangles.
	for(j=0;j<nrOfFaces;j++){
		for(i=2;i <= (allFaces[j]->nrOfvertices-1);i++){
				triangledFaces[newIndex].nrOfvertices = 3;
				triangledFaces[newIndex].vertices[0] =
										allFaces[oldIndex]->vertices[0];
				triangledFaces[newIndex].vertexIndices[0] =
										allFaces[oldIndex]->vertexIndeces[0];
				triangledFaces[newIndex].vertices[1] =
										allFaces[oldIndex]->vertices[i-1];
				triangledFaces[newIndex].vertexIndices[1] =
										allFaces[oldIndex]->vertexIndeces[i-1];
				triangledFaces[newIndex].vertices[2] =
										allFaces[oldIndex]->vertices[i];
				triangledFaces[newIndex].vertexIndices[2] =
										allFaces[oldIndex]->vertexIndeces[i];

				triangledFaces[newIndex].colours[0] =
										allFaces[oldIndex]->colours[0];
				triangledFaces[newIndex].colours[1] =
										allFaces[oldIndex]->colours[1];
				triangledFaces[newIndex].colours[2] =
										allFaces[oldIndex]->colours[2];
				triangledFaces[newIndex].colours[3] =
										allFaces[oldIndex]->colours[3];

				newIndex++;
		}
		free(allFaces[oldIndex]);
		oldIndex++;
	}
	return newIndex;
}

/**
 * function for realeasing allocated memory.Observe that the main function must
 * have been called before using this.
 * @param *allTriangles objectData, a pointer to a struct of type objectData.
 */
void freeOFFReaderMemory(objectData *allData){

	free(allData->allVertices);
	free(allData->allTriangles);
	free(allData->origoForObject);
	free(allData);
}
