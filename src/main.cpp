#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "SDL2/SDL_mixer.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char *argv[]) {

    // setup sdl2 with opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL ERROR: " << SDL_GetError() << endl;
        exit(1);
	}
	//                       (title, xpos, ypos, width, height, flags);
	SDL_Window* window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (!window) {
        printf("failed to init window: %s!\n", SDL_GetError());
        exit(1);
	}

    // Load OpenGL
    SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("failed to load Gl: %s\n", SDL_GetError());
        exit(1);
    }

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
        printf("failed to init renderer: %s!\n", SDL_GetError());
	}
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // enable alpha blending

	//Initialize SDL_mixer
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(1);
    }
    //loadSound(); // load sound files


    puts("OpenGL Loaded");
    printf("Vendor:     %s\n", glGetString(GL_VENDOR));
    printf("Renderer:   %s\n", glGetString(GL_RENDERER));
    printf("Version:    %s\n", glGetString(GL_VERSION));
    

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
                    break;
                } default: {
                    break;
                }
            } // switch
	    } // poll event
    } // main loop    
    puts("exited game engine");

    return 0;
} // main

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina displays
    glViewport(0, 0, width, height);
}

/*
    // open GL sample code

    GLFWwindow* window;

    // Initialize the library
    if(!glfwInit())
        return -1;

    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Mathe the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize the OpenGL API with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        // Render here!
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
*/

