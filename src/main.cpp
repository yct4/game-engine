#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "constants.hpp"
#include "util.hpp"
#include "types.hpp"

using namespace std;

// global variables
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gStretchedSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
//SDL_Surface* gCurrentSurface = NULL;

bool init();
bool loadGlobalMedia();
void deallocMedia(SDL_Surface* _surface);
void close();
SDL_Surface* loadSurfaceFromBmp(string path);


int main(int argc, char* args[]) {

    if (!init()) {
        printf("init failed!");
        exit(1);
    }

    if (!loadGlobalMedia()) {
        PRINT("load global surfaces failed!");
        exit(1);
    }

    //Fill the surface white
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
    
    //The image we will load and show on the screen
    SDL_Surface* helloWorld = loadSurfaceFromBmp("assets/helloWorld.bmp");

    //Apply the image
    //SDL_BlitSurface(helloWorld, NULL, gScreenSurface, NULL);

    //Set default current surface
    SDL_Surface* currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    SDL_BlitSurface(currentSurface, NULL, gScreenSurface, NULL);

    //Update the surface, only call when render back buffer is done (ie frame is finished)
    SDL_UpdateWindowSurface(gWindow);

    // main game loop
    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    isRunning = false;
                    break;
                } case SDL_MOUSEMOTION: {
                    break;
                } case SDL_MOUSEBUTTONDOWN: {
                    if (event.button.button == SDL_BUTTON_LEFT) {}
                    break;
                } case SDL_MOUSEBUTTONUP: {
                    if (event.button.button == SDL_BUTTON_LEFT) {}
                    break;
                } case SDL_KEYDOWN: {
                    //Select surfaces based on key press
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE: {
                            isRunning = false;
                            break;
                        } case SDLK_UP: {
                            currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                        } case SDLK_DOWN: {
                            currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;
                        } case SDLK_LEFT: {
                            currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;
                        } case SDLK_RIGHT: {
                            currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;
                        } default: {
                            currentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                    break;
                } default: {
                    break;
                }
            } // switch
        } // poll event

        // Apply image stretched
        SDL_Rect stretchRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        //SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect); TODO use me instead of BlitSurface

        // update screen surface with current surface
        SDL_BlitSurface(currentSurface, NULL, gScreenSurface, NULL);
        //Update the surface, only call when render back buffer is done (ie frame is finished)
        SDL_UpdateWindowSurface(gWindow);

    } // main loop

    deallocMedia(helloWorld); // TODO add me to close()
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        deallocMedia(gKeyPressSurfaces[i]);
    }
    close();

    puts("exited game engine");
    return 0;
} // main


// modifies global state gWindow, gScreenSurface
// inits SDL, creates window, assigns window to surface
bool init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true; 
}

bool loadGlobalMedia() {
    // load gKeyPressSurfaces from bmp
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        gKeyPressSurfaces[i] = loadSurfaceFromBmp(gKeyPressBmpPaths[i]);
        if (gKeyPressSurfaces[i] == NULL) {
            return false;
        }
    
    }

    //Load stretching surface
    gStretchedSurface = loadSurfaceFromBmp("assets/stretch.bmp");
    if (gStretchedSurface == NULL) {
    	printf("Failed to load stretching image!\n");
    	return false;
    }    
    return true;
}

SDL_Surface* loadSurfaceFromBmp(string path) { // TODO pass gScreenSurface as input?
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return NULL;
    }
    //Convert surface to screen format
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
    	printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return NULL;
    }
    
    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);    
    return optimizedSurface;
}


void deallocMedia(SDL_Surface* _surface) {
    //Deallocate surface
    if (_surface == NULL) {
        PRINT("surface is already null!");
        return;
    }
    SDL_FreeSurface(_surface);
    _surface = NULL;
}

void close() {
	//Free loaded image
	SDL_FreeSurface( gStretchedSurface );
	gStretchedSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

