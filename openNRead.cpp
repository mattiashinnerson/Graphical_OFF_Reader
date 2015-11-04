/*
 * A file that handles the opening function, and makes sure that the read
 * information gets stored in the right way. The values that
 * get loaded is for example vertices and element indexes which will be sent
 * to the GPU. It also calculates the vertice normals.
 *
 * author: Mattias Hinnerson
 * date: 2014-03-18
 */

#include "openNRead.h"
#include "walking_in_air.h"
#include "variables.h"

/**
 * loads all the vertices from one specified OFF file, stores all the read
 * data in the objectData struct fileData. the Data is later stored in the
 * vertice and element buffer, and sent to the GPU.
 * @param char *fileName, filename to load from. Set NULL if want to read from
 * keyboard input.
 */
void loadVertices(char *fName){
	int i, count = 0;
	fileOpen = false;

	/*open OFF file to get vertice points*/
	int returnV = openStage(fName);

	/*if failed, close program*/
	if(returnV == -1){
		exit(-1);
	}

    glBufferData( GL_ARRAY_BUFFER, fileData->totNrOfVertices*sizeof(vec4)+
    			  fileData->totNrOfVertices*sizeof(vec4),NULL, GL_STATIC_DRAW);

	/*put one attribute pointer in the normal databuffer*/
    glVertexAttribPointer(theNormal, 4, GL_FLOAT, GL_FALSE, 0,
        				BUFFER_OFFSET(fileData->totNrOfVertices*sizeof(vec4)));


    /*creating data arrays for vertices, elements, and color*/
    vec4 points[fileData->totNrOfVertices];
    //vec4 normals[fileData->totNrOfVertices];
    vec4 *normals = (vec4*) calloc(fileData->totNrOfVertices,sizeof (vec4));

    for(i=0;i<fileData->totNrOfVertices;i++){
    	normals[i] = vec4_(0,0,0,0);
    }
    verticeNormals = &normals[0];
	GLuint indices[fileData->totTriangles*3];

    /* inserting vertices in array buffer,one vertice only appear once in
       the array.*/
	for(i=0;i<fileData->totNrOfVertices;i++){

		points[i] = vec4_(fileData->allVertices[i].x,fileData->
							allVertices[i].y,fileData->allVertices[i].z,1);
	}

	/* Define indexes to element array.*/
	for(i=0;i<fileData->totTriangles;i++){

		/* Define indexes to element array and normals to normalArray.*/
		indices[count] = fileData->allTriangles[i].vertexIndices[0];
		count++;
		indices[count] = fileData->allTriangles[i].vertexIndices[1];
		count++;
		indices[count] = fileData->allTriangles[i].vertexIndices[2];
		count++;


		/*calculating the Face normal for this triangle face*/
		/*u = b-a, v = c-b, normal = u crossp. v*/
		int PIndex0 = fileData->allTriangles[i].vertexIndices[0];
		int PIndex1 = fileData->allTriangles[i].vertexIndices[1];
		int PIndex2 = fileData->allTriangles[i].vertexIndices[2];

		vec4 p1 = points[PIndex0];
		vec4 p2 = points[PIndex1];
		vec4 p3 = points[PIndex2];

		vec4 u = vec4_(p2.x -p1.x,p2.y -p1.y,p2.z -p1.z,1.0);
		vec4 v = vec4_(p2.x -p3.x,p2.y -p3.y,p2.z -p3.z,1.0);

		/*crossproduct, v x u*/
		vec4 oneN = vec4_((v.y*u.z - v.z*u.y),(v.z*u.x - v.x*u.z),
									(v.x*u.y - v.y*u.x),1.0);

		/*normalizating the face normal*/
		float norm = sqrt((oneN.x*oneN.x) + (oneN.y*oneN.y) + (oneN.z*oneN.z));
		oneN.x = (oneN.x/norm);
		oneN.y = (oneN.y/norm);
		oneN.z = (oneN.z/norm);
		oneN.w = 0;


		/* calculating normal for each vertex (midvalue of all nearby faces).
		 * the equation is: go through each face normal, add it to the normal
		 * array at the index specified, for each time it occurs in the
		 * vertexIndices (faces indexes for which vertice that belongs to
		 * each vertex)*/
		normals[PIndex0].x = normals[PIndex0].x + oneN.x;
		normals[PIndex0].y = normals[PIndex0].y + oneN.y;
		normals[PIndex0].z = normals[PIndex0].z + oneN.z;

		normals[PIndex1].x = normals[PIndex1].x + oneN.x;
		normals[PIndex1].y = normals[PIndex1].y + oneN.y;
		normals[PIndex1].z = normals[PIndex1].z + oneN.z;

		normals[PIndex2].x = normals[PIndex2].x + oneN.x;
		normals[PIndex2].y = normals[PIndex2].y + oneN.y;
		normals[PIndex2].z = normals[PIndex2].z + oneN.z;

	}

	/*now normalize the normal array*/
	for(i=0;i < fileData->totNrOfVertices;i++){

		vec4 oneNorm = normals[i];

		if((oneNorm.x != 0) || (oneNorm.y != 0 || oneNorm.z != 0)){
			float norm = sqrt((oneNorm.x*oneNorm.x) + (oneNorm.y*oneNorm.y) +
								(oneNorm.z*oneNorm.z));
			normals[i].x = (oneNorm.x/norm);
			normals[i].y = (oneNorm.y/norm);
			normals[i].z = (oneNorm.z/norm);
		}
	}

	/* Load it to the buffer data/element array */
	glBufferSubData( GL_ARRAY_BUFFER, 0,
						fileData->totNrOfVertices*sizeof(vec4),points);
	glBufferSubData( GL_ARRAY_BUFFER, fileData->totNrOfVertices*sizeof(vec4),
						fileData->totNrOfVertices*sizeof(vec4),normals);

	glBufferData( GL_ELEMENT_ARRAY_BUFFER, fileData->
				totTriangles*3*sizeof(GLuint), indices ,GL_STATIC_DRAW );

	fileOpen = true;

	/*make sure the objects fits in a unit cube (z-axis not included)*/
	while((fileData->biggestX > right) || (fileData->biggestY > top) ||
	  		(fileData->smallestX < left) || (fileData->smallestY < bottom)){

	   	scale(0.9,0.9,0.9,matTrans);
	   	fileData->biggestX *= 0.9;
		fileData->biggestY *= 0.9;
		fileData->smallestX *= 0.9;
		fileData->smallestY *= 0.9;
	    sendTMatrixToGPU();
	}

	/*making the camera move little bit forward for updating view matrix*/
	cameraForward(0);
}

/**
 * function that opens one OFF file, reads all the data (happends if
 * OFFReader.cpp) and stores it in the objectData struct fileData.
 * @param fName char*, a pointer to a char array.
 * @return int, 0 if success, -1 if failed.
 */
int openStage(char* fName){

	char *pickedFileName = 	new char[512];
	char temp[512], buf[512];

	if(fileData != NULL){
		/*calling function from OFFReader.c*/
		freeOFFReaderMemory(fileData);
	}

	/*if not sent in name parameter, get path and name from stdin */
	if(fName == NULL){
		printf("Enter the filePath to where the file is located: \n");
		printf("(Example: \"home/myDocuments/edu/ou3/offFiles/\")\n");
		printf("Type \"Default\" to choose the directiory OffFiles\n");
		fgets(temp,512,stdin);

		int strLength = strlen(temp);
		temp[strLength-1] = '\0';

		if(strcmp(temp,"Default") == 0){
			printf("Default directiory \"OffFiles\" chosen.");
			getcwd(buf,512);
			strcpy(pickedFileName,buf);
			strcat(pickedFileName,"/OffFiles/");
		}
		else if(strcmp(temp,"Default") != 0){
			strcpy(pickedFileName,temp);
		}
		printf("Now enter the fileName: \n");
		scanf("%s",temp);
		strcat(pickedFileName,temp);
	}else{
		pickedFileName = fName;
	}

	/*reading from desired file:*/
	fileData = (objectData*) OFFRead(pickedFileName);

	if(fileData == NULL){
		return -1;
	}


	return 0;
}
