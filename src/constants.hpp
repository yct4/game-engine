#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <iostream>

using namespace std;

#define ERROR_EXIT(...) fprint(stderr, __VA_ARGS__)
#define ERROR_RETURN(R, ...) fprintf(stderr, __VA_ARGS__); return R
#define PRINT(...) cout << __VA_ARGS__ << endl

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



//Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const string gKeyPressBmpPaths[KEY_PRESS_SURFACE_TOTAL] = {
    "assets/press.bmp",
    "assets/up.bmp",
    "assets/down.bmp",
    "assets/left.bmp",
    "assets/right.bmp"
};

#endif // CONSTANTS_H
