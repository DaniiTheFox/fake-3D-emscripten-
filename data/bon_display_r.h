// ***********************************************
// * THIS IS THE MAIN RENDERING LOOP ON THE GAME *
// ***********************************************
// ...............................................................
void main_loop() {                          // 
    SDL_Event event;                        // 
    while (SDL_PollEvent(&event)) {         // THIS FUNCTION WILL BE EXECUTED PER EACH FRAME
        if (event.type == SDL_QUIT) {       // OF THE GAME WHILE IT IS WORKING, AND THIS SEGMENT OF THE CODE
            emscripten_cancel_main_loop();  // WILL SPECIFICALLY LOOK FOR ANY EVENT THAT COULD HAPPEN
        }                                   // ON THE SDL WINDOW SCREEN INPUT
         bon_keyboard_detection(event);     //
    }                                       // 
    // ..................................................................
    // ********************************
    // * Flush the buffers on screen  *
    // ********************************
    // ------------------------------------------------------
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // CLEAN SCREEN
    SDL_RenderClear(renderer);                      // CLEAR BUFFER
    // ------------------------------------------------------
    bon_draw_3d();
    // ********************************
    // * Present the updated renderer *
    // ********************************
    // ------------------------------------------------------
    SDL_RenderPresent(renderer); // SWAP THE BUFFERS TO DISPLAY THE NEW IMAGE
}
// ...................................................................