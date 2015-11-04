#ifndef openNRead_H
#define openNRead_H

/*loads all the vertices from one specified OFF file, stores all the read
 * data in the objectData struct fileData. the Data is later stored in the
 * vertice and element buffer, and sent to the GPU.
 * @param char *fileName, filename to load from. Set NULL if want to read from
 * keyboard input.
 */
void loadVertices(char *fName);

/**
 * function that opens one OFF file, reads all the data (happends if
 * OFFReader.cpp) and stores it in the objectData struct fileData.
 * @param fName char*, a pointer to a char array.
 * @return int, 0 if success, -1 if failed.
 */
int openStage(char* fName);


#endif
