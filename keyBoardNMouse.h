#ifndef keyBoardNMouse_H
#define keyBoardNMouse_H


/*function that controls actions while any mouse button is being clicked.*/
void onMouseClick(int button, int state, int x, int y);

/* Handle the actions when the mous is being moved. A mouse button must be
 * clicked for registering any movement.
 */
void mouseMovement(int x, int y);

/**
 * Function that listens for event input from keyboard.
 */
void Keyboard(unsigned char key, int x, int y);

#endif
