// ----------------------------------
#include <iostream>         // IOSTREAM DEFAULT INPUT LIBRARY
#include <SDL.h>            // SDL SCREEN RENDERING LIBRARY
#include <emscripten.h>     // EMSCRIPTEN LIBRARY FOR RESOURCES
#include <math.h>           // MATH LIBRARY
#include <stdio.h>          // C LIBRARY REQUIRED
// ----------------------------------
#include "data/bon_variables.h" // GLOBAL VARIABLES OF THE GAME ENGINE
#include "data/bon_color_lst.h" // MAIN COLOR PALETTE IS DEFINED HERE (RGB ACCEPTED)
#include "data/bon_auxiliars.h" // GLOBAL AUXILIAR FUNCTIONS FOR GAME
#include "data/bon_keyboardf.h" // KEYBOARD DETECTION FUNCTION
#include "data/bon_display_r.h" // GLOBAL VARIABLES OF THE DISPLAY ENGINE
// ----------------------------------
int main() {
    bon_init();                             // INITIALIZE FUNCTION ON GAME ENGINE
    // ..........................................
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {    //
        return -1;                          // IF ANY ERROR HAPPENS WHILE CREATING WINDOW
    }                                       // RETURN -1 IN A CRASH
    // ...............................................
    // . CREATE A WINDOW AND A RENDERER FOR OUR GAME .
    // ...............................................
    window = SDL_CreateWindow("DUNGEON GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, BON_W_SDL_W, BON_W_SDL_H, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // ...........................................
    if (!window || !renderer) {     // 
        SDL_Quit();                 // IF THE RENDERER FAILS OR THE WINDOW FAILS TO BE CREATED
        return -1;                  // WE SHOULD AVOID A FURTHER PROBLEM SO WE SHUT DOWN THE APPLICATION
    }                               // 
    // ...........................................
    emscripten_set_main_loop(main_loop, 0, 1); // CALL EMSCRIPTEN TO ENTER THE MAIN LOOP
    // ...........................................
    SDL_DestroyRenderer(renderer);  //
    SDL_DestroyWindow(window);      // AT THE END OF THE APPLICATION WE DESTROY THE RENDERER
    SDL_Quit();                     //
    // ...........................................
    return 0;                       // RETURN 0 VALUE TO KNOW EXECUTION WAS CORRECT 
}
// ------------------------------------