#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// global variables
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* helloWorld = NULL;

bool init();
SDL_Surface* loadMedia();
void deallocMedia(SDL_Surface* _surface);
void close();


int main(int argc, char* args[]) {

    if (!init()) {
        printf("init failed!");
        exit(1);
    }

    //Fill the surface white
    SDL_FillRect(gScreenSurface, NULL, SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
    
    //The image we will load and show on the screen
    SDL_Surface* helloWorld = loadMedia();

    //Apply the image
    SDL_BlitSurface(helloWorld, NULL, gScreenSurface, NULL);

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
                    break;
                } case SDL_SCANCODE_ESCAPE: {
                    isRunning = false;
                    break;
                } default: {
                    break;
                }
            } // switch
        } // poll event
    } // main loop


    deallocMedia(helloWorld); // TODO add me to close()
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

SDL_Surface* loadMedia() {
    //Load splash image
    SDL_Surface* ret = SDL_LoadBMP("assets/helloWorld.bmp");
    if(ret == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "assets/helloWorld.bmp", SDL_GetError());
        return NULL;
    }
    return ret;
}

void deallocMedia(SDL_Surface* _surface) {
    //Deallocate surface
    SDL_FreeSurface(_surface);
    _surface = NULL;
}

void close() {
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

