// *****************************************
// * KEYBOARD DETECTION FUNCTIONS FOR GAME *
// *****************************************
// ----------------------------------------------------
void bon_keyboard_detection(SDL_Event event) {  // WHEN THE SDL WINDOW DETECTS AN EVENT
    if (event.type == SDL_KEYDOWN) {            // TEST IF THE EVENT WAS KEYBOARD INPUT
        // ----------------------------------------------------------------------------
        //std::cout<<"Keyboard detected: "<<event.key.keysym.sym<<std::endl;
        int bon_dx = bon_psin[player.bon_ua] * 5.0f;
        int bon_dy = bon_pcos[player.bon_ua] * 5.0f;;
        switch (event.key.keysym.sym) {
            case 119:                          // IF W KEY WAS PRESSED
                player.bon_ux += bon_dx;       // WE ADD THE VECTOR IF WE ARE 
                player.bon_uy += bon_dy;       // MOVING OUR PLAYER FORWARD
            break;
            case  97:                          // IF A KEY WAS PRESSED
                player.bon_ua -= 4;            // WE ROTATE AND PREVENT FROM GOING
                if(player.bon_ua < 0){         // OUTSIDE OF THE RANBE
                    player.bon_ua += 360;      //
                }
            break; 
            case 115:                          // IF S KEY WAS PRESSED
                player.bon_ux -= bon_dx;       // WE SUBTRACT OUR VECTOR IF THE USER
                player.bon_uy -= bon_dy;       // SHOULD BE MOVING BACKWARDS
            break;
            case 100:                          // IF D KEY WAS PRESSED
            player.bon_ua += 4;                // AND ALSO ROTATE AND PREVENT FROM
            if(player.bon_ua > 359){           // GOING OUTSIDE OF OUR PRECALCULATION
                player.bon_ua -= 360;          // RANGE
            }
            break;
            // --- THESE ACTIONS ARE DONE TO PERFORM STRAFE ---
            case 120:                          // IF X KEY WAS PRESSED
                player.bon_ux += bon_dy;       // WE SUBTRACT OUR VECTOR IF THE USER
                player.bon_uy -= bon_dx;       // SHOULD BE MOVING BACKWARDS
            break;
            case 122:                          // IF Z KEY WAS PRESSED
                player.bon_ux -= bon_dy;       // WE SUBTRACT OUR VECTOR IF THE USER
                player.bon_uy += bon_dx;       // SHOULD BE MOVING BACKWARDS
            break;
            case 113:                          // IF X KEY WAS PRESSED
                player.bon_ul += 2;
            break;
            case 101:                          // IF E KEY WAS PRESSED
                player.bon_ul -= 2;
            break;
            case 32:                           // IF SPACE KEY WAS PRESSED
                player.bon_uz -= 2;
            break;
            case 99:                           // IF C KEY WAS PRESSED
                player.bon_uz += 2;
            break;
        }
        // ----------------------------------------------------------------------------
    }
    // --------------------------------------------------------------------------------
}
// ..........................................