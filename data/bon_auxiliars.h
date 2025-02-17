// *********************************************************
// * BON AUXILIAR LIBRARY WHICH HAS MOST FUNCTIONS IN GAME *
// *********************************************************
// ........................................................
void bon_put_pixel (int _x, int _y, int _color, SDL_Renderer *canva) {
    int tmp_c = _color % 255; // WE LIMIT THE VALUE TO 255 AS IN RUST
    // ---------------------------------------------------------
    SDL_SetRenderDrawColor(canva,    bon_colors[0][tmp_c],      //
                                     bon_colors[1][tmp_c],      // IN THIS PART WE DEFINE THE COLOR
                                     bon_colors[2][tmp_c], 255);//
    // ---------------------------------------------------------
    SDL_Rect rect = {      _x * BON_PIXEL_S,                    // DEFINE PIXEL POSITION X
                           _y * BON_PIXEL_S,                    // DEFINE PIXEL POSITION Y
                           BON_PIXEL_S,                         // *******************************
                           BON_PIXEL_S};                        // THEN SETUP THE SCALE OF PIXEL 
    SDL_RenderFillRect(canva, &rect);                           // FINALLY DRAW THE PIXEL IN CANVA
}
// .............................................................
void bon_precal_sincos () {
    // .........................................................
    for (int i = 0; i < 360; i++) {                 // 
        bon_pcos[i] = cos(i / 180.0f * BON_MATH_PI);// IN THIS LOOP WE PRECALCULATE ALL POSITIONS
        bon_psin[i] = sin(i / 180.0f * BON_MATH_PI);// FOR THE SINE AND COSINE FUNCTIONS THAT COULD BE USED
    }                                               // 
    // ..........................................................
}
// ***********************************************************
// * THIS IS A FUNCTION THAT WILL PUSH SECTORS TO DRAW STACK *
// ***********************************************************
// --------------------------------------------------------------
void bon_push_segment (int _sx, int _sy, int _ws, int _we, int _z1, int _z2, int _sc) {
    // ------------------ SX,SY WORK AS AN ORIGIN, AND WS AND WE AS X AND Y TARGET
    Sectors[bon_sec_num].ws = _ws;      // ------------------------------------------------
    Sectors[bon_sec_num].we = _we;      // IN THIS PART WE PUSH TO THE ARRAY OUR SECTOR
    Sectors[bon_sec_num].z1 = _z1;      // TO DEFINE IT'S VALUES AND BOUNDARIES
    Sectors[bon_sec_num].z2 = _z2;      // ------------------------------------------------
    // ------------------------------------------------------------------------------------
    // WALL INSERTION LOGIC WILL GO HERE I'LL JUST MAKE VOXELS LOL
    Sectors[bon_sec_num].w[0].x1 = _sx;
    Sectors[bon_sec_num].w[0].y1 = _sy;
    Sectors[bon_sec_num].w[0].x2 = _ws;
    Sectors[bon_sec_num].w[0].y2 = _sy;
    Sectors[bon_sec_num].w[0].c  = _sc;

    Sectors[bon_sec_num].w[1].x1 = _ws;
    Sectors[bon_sec_num].w[1].y1 = _sy;
    Sectors[bon_sec_num].w[1].x2 = _ws;
    Sectors[bon_sec_num].w[1].y2 = _we;
    Sectors[bon_sec_num].w[1].c  = _sc;

    Sectors[bon_sec_num].w[2].x1 = _sx;
    Sectors[bon_sec_num].w[2].y1 = _we;
    Sectors[bon_sec_num].w[2].x2 = _sx;
    Sectors[bon_sec_num].w[2].y2 = _sy;
    Sectors[bon_sec_num].w[2].c  = _sc;

    Sectors[bon_sec_num].w[3].x1 = _ws;
    Sectors[bon_sec_num].w[3].y1 = _we;
    Sectors[bon_sec_num].w[3].x2 = _sx;
    Sectors[bon_sec_num].w[3].y2 = _we;
    Sectors[bon_sec_num].w[3].c  = _sc;
    // ------------------------------------------------------------------------------------
    bon_sec_num += 1 % BON_MAX_SEG;     // INCREASE NUMBER OF SEGMENT AND LIMIT TO BOUNDARY
}
// ..............................................................
// **********************************
// * INITIALIZE ALL THE GAME ENGINE *
// **********************************
// ..............................................................
void bon_init () {
    // ............................................
    bon_precal_sincos();                    // CALL THE PRECALCULATION ROUTINES
    bon_create_colormatic();                // CALL THE COLOR CREATION FUNCTION
    // ............................................
    player.bon_ux =  70; // |
    player.bon_uy =-110; // +- THIS IS THE PLAYER POSITION
    player.bon_uz =  20; // |

    player.bon_ua =   0; // THIS IS THE PLAYER DIRECTION
    player.bon_ul =   0; // IN GAME
    // .............................................
    bon_push_segment( (0*10), (0*10), (0*10)+10,(0*10)+10, (0*10),10,0);
    bon_push_segment( (4*10), (4*10), (4*10)+10,(4*10)+10, (0*10),10,1);

    bon_push_segment( (0*10), (4*10), (0*10)+10,(4*10)+10, (0*10),10,2);
    bon_push_segment( (4*10), (0*10), (4*10)+10,(0*10)+10, (0*10),10,3);

    for (int i = 0; i < 100; i++) {
        bon_push_segment( (8*10), (8*10), (8*10)+10,(8*10)+10, (-i*10),10,(i+0)%6);
        bon_push_segment( (7*10), (7*10), (7*10)+10,(7*10)+10, (-i*10),10,(i+1)%6);
        bon_push_segment( (8*10), (7*10), (8*10)+10,(7*10)+10, (-i*10),10,(i+2)%6);
        bon_push_segment( (7*10), (8*10), (7*10)+10,(8*10)+10, (-i*10),10,(i+3)%6);
    }
}
// *****************************
// * RENDER A CLIPPING ON GAME *
// *****************************
// --------------------------------------------------
void bon_clip_behind (int *x1, int *y1, int *z1, int x2, int y2, int z2) {
    // ----------------------------------------------
    float da = *y1;  // 
    float db =  y2;  // FIRST WE CALCULATE THE DIFFERENCES
    float d  = da-db;//     ON THE DISTANCES IN Y
    if (d == 0) {d = 1;}
    // ----------------------------------------------
    float s = da / (da-db); // INTERSECTION ON THE VALUES
    // ----------------------------------------------
    *x1 = *x1 + s * (x2 - (*x1)); // 
    *y1 = *y1 + s * (y2 - (*y1)); // IN THIS PART WE CALCULATE INTERSECT
    if(*y1==0) { *y1 = 1; }       // AS WELL AS PREVENT BY ZERO DIVISION
    *z1 = *z1 + s * (z2 - (*z1)); // 
}
// ************************************
// * IN THIS PART WE GET THE DISTANCE *
// ************************************
// -------------------------------------------------------------------
float fsqrt(float number) {         // FAST SQUARE ROOT FROM QUAKE III
    // ----------------------------------------------------------------
    long i;                         //
    float x2, y;                    // SO BASICALLY THE QUAKE BIT TRICK
    const float threehalfs = 1.5F;  // AND THEN JUST RETURN THE INVERSE RESULT
    // ....................................
    x2 = number * 0.5F;                  // IT WILL ALLOW TO CALCULATE FASTER DISTANCES
    y  = number;                         // 
    i  = *(long *)&y;                    // Evil bit-level hack
    i  = 0x5f3759df - (i >> 1);          // Magic number
    y  = *(float *)&i;
    y  = y * (threehalfs - (x2 * y * y)); // 1st iteratio
    return 1/y;                           // square root
    // --------------------------------------------------------------
}
// -------------------------------------------------------------------
int bon_dist (int x1, int y1, int x2, int y2) {                       // ***************************************
    int diff_x = (x2-x1);                                             // THIS MAY LOOK DUMB BUT 
    int diff_y = (y2-y1);                                             // WE DO IT TO AVOID RECALCULATIONS
    int distancef = fsqrt ( diff_x +  diff_y );                       // FAST SQUARE ROOT TRICK!!!
    return distancef;                                                 // FAST SQUARE ROOT ALGORITHMS)
}  // ---------------------------------------------------------------- ***************************************
// ******************************
// * DRAW WALL FUNCTION IS HERE *
// ******************************
void bon_draw_wall (int x1, int x2,int b1, int b2, int t1, int t2, int fc) {
    int x = 0;  // DEFINE X
    int y = 0;  // DEFINE Y
    // ............................
    int dyb = b2 - b1;      // IN THIS PART WE CALCULATE 
    int dyt = t2 - t1;      // ALL OF THE DIFFERENT 
    int dx  = x2 - x1;      // THE DIFFERENCES AMONG DISTANCE AND
    if(dx == 0) { dx = 1; } // BOTTOM OF THE LINE
    int xs = x1;            // AS WELL AS HOLD INITIAL POSITION
    // *****************************
    // * CLIPPING FOR OPTIMIZATION *
    // *****************************--------------------------
    if (x1 < 1) { x1 = 1; }                         // 
    if (x2 < 1) { x2 = 1; }                         // IF THE SEGMENT TO DRAW IS OFFSCREEN
    if (x1 > BON_SCREENW-1) { x1 = BON_SCREENW-1; } // THEN AVOID DRAWING IT, IT IS SIMPLE
    if (x2 > BON_SCREENW-1) { x2 = BON_SCREENW-1; } // AS THAT
    // -------------------------------------------------------
    // ............................
    for (x = x1; x < x2; x++) {
        // ..........................................
        int y1 = dyb * (x -xs + 0.5) / dx+b1; // CALCULATE Y BOTTOM POINT
        int y2 = dyt * (x -xs + 0.5) / dx+t1; // CALCULATE Y TOP POINT
        // ..........................................
        // *****************************
        // * CLIPPING FOR OPTIMIZATION *
        // *****************************--------------------------
        if (y1 < 1) { y1 = 1; }                         // 
        if (y2 < 1) { y2 = 1; }                         // IF THE SEGMENT TO DRAW IS OFFSCREEN
        if (y1 > BON_SCREENH-1) { y1 = BON_SCREENH-1; } // THEN AVOID DRAWING IT, IT IS SIMPLE
        if (y2 > BON_SCREENH-1) { y2 = BON_SCREENH-1; } // AS THAT
        // -------------------------------------------------------
        for (y = y1; y < y2; y++) {
            bon_put_pixel(x,y,fc, renderer); // pixel on wall
        }
    }
}
// *****************************
// * DRAWING 3D CALC BASE CODE *
// *****************************
void bon_draw_3d () {
    // -= VARIABLE DEFINITION FOR OUR WALLS =-
    int bon_wx[4];  // 
    int bon_wy[4];  // DEFINE OUR WALL COORDINATES
    int bon_wz[4];  // 
    // ........................................
    for (int s = 0; s < bon_sec_num-1; s++) {
        for (int w = 0; w < bon_sec_num-s-1; w++) {     // ------------------------------------------------
            if (Sectors[w].d < Sectors[w+1].d ) {   // THIS IS A SMALL BUBBLE SORT ALGORITHM
                sectors Aux = Sectors[w];           // IT IS USED FOR RENDERING PRIORITY AND DEPTH
                Sectors[w] = Sectors[w+1];          // WE DRAW FIRST WHAT'S BEHIND AND THEN WHAT'S NEAR
                Sectors[w+1] = Aux;                 // IN THAT WAY WE GET TO DRAW OUR WORLD
            }                                       // ------------------------------------------------
        }
    }
    // ........................................
    for (int s = 0; s <= bon_sec_num; s++) {                 // 
        Sectors[s].d = 0;                                   // WE ARE GONNA LOOP ALONG THE SECTORS AND THEIR WALLS
        for(int w = 0; w < 4; w++) {
         for (int l = 0; l < 2; l++) {
           // ........................................
           float bon_cs = bon_pcos[player.bon_ua]; // DEFINE FOR OUR WALL THE TRANSFORMATION
           float bon_sn = bon_psin[player.bon_ua]; // AROUND THE AXIS
           // ........................................
           int x1 =Sectors[s].w[w].x1 - player.bon_ux;    // THIS IS A SMALL OFFSET FOR OUR PLAYER POSITION
           int y1 =Sectors[s].w[w].y1 - player.bon_uy;    // ON ONE POINT OF THE WALL
           int x2 =Sectors[s].w[w].x2 - player.bon_ux;    // THIS IS A SMALL OFFSET FOR OUR PLAYER POSITION
           int y2 =Sectors[s].w[w].y2 - player.bon_uy;    // ON ONE POINT OF THE WALL
           // .........................................
           if (l==0) { int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp; } // FLIP FACE
           // .........................................
           bon_wx[0] = x1 * bon_cs - y1 * bon_sn; // CALCULATE THE ROTATION OF THESE POINTS
           bon_wx[1] = x2 * bon_cs - y2 * bon_sn; // AROUND THE PLAYER
           bon_wx[2] = bon_wx[0];
           bon_wx[3] = bon_wx[1];
           // ... DEPTH ...............................
           bon_wy[0] = y1 * bon_cs + x1 * bon_sn; // CALCULATE THE ROTATION OF THESE POINTS
           bon_wy[1] = y2 * bon_cs + x2 * bon_sn; // AROUND THE PLAYER
           bon_wy[2] = bon_wy[0];
           bon_wy[3] = bon_wy[1];
           Sectors[s].d += bon_dist(0, 0, (bon_wx[0]+bon_wx[1])/2, (bon_wy[0]+bon_wy[1])/2); // GET THE SECTOR DISTANCE
           // .........................................
           bon_wz[0] = Sectors[s].z1 - player.bon_uz + ((player.bon_ul * bon_wy[0])/32.0f); // CALCULATE A HEIGHT FOR THE WALLS
           bon_wz[1] = Sectors[s].z1 - player.bon_uz + ((player.bon_ul * bon_wy[1])/32.0f); // BASED ON THE PLAYER
           bon_wz[2] = bon_wz[0]+Sectors[s].z2;
           bon_wz[3] = bon_wz[1]+Sectors[s].z2;
           // .........................................
           if (bon_wy[0] < 1 && bon_wy[1]<1) { return;}  // IF THE WALL IS OUT OF OUR RANGE IGNORE THE FUNCTION
                                                           // IS NOT EVEN WORTH TO DRAW THE WALL
           if (bon_wy[0] < 1) {                            // IF ONE OF OUR POINTS IS IN FRONT, WE SHOULD CALCULATE CLIP
               bon_clip_behind(&bon_wx[0],&bon_wy[0],&bon_wz[0], bon_wx[1], bon_wy[1], bon_wz[1]); // SO WE CALL A TEST IF CAN BE CLIPPED
               bon_clip_behind(&bon_wx[2],&bon_wy[2],&bon_wz[2], bon_wx[3], bon_wy[3], bon_wz[3]); // AND CLIP THE WALL
           }
           // ----------------------------------------------------------------------------------------------------------
           if (bon_wy[1] < 1) {                                                                    // 
               bon_clip_behind(&bon_wx[1],&bon_wy[1],&bon_wz[1], bon_wx[0], bon_wy[0], bon_wz[0]); // DO THE SAME FOR THE OTHER SIDE OF THE WALL
               bon_clip_behind(&bon_wx[3],&bon_wy[3],&bon_wz[3], bon_wx[2], bon_wy[2], bon_wz[2]); // 
           }
           // .........................................
           bon_wx[0] = bon_wx[0] * 200 / bon_wy[0] + BON_HALF_SW; // 
           bon_wy[0] = bon_wz[0] * 200 / bon_wy[0] + BON_HALF_SH; // CALCULATE THE ROTATION
                                                                  // OF THE OBJECTS IN ORDER TO
           bon_wx[1] = bon_wx[1] * 200 / bon_wy[1] + BON_HALF_SW; // MAKE THE ROTATE EFFECT AROUND THE PLAYER
           bon_wy[1] = bon_wz[1] * 200 / bon_wy[1] + BON_HALF_SH; //
       
           bon_wx[2] = bon_wx[2] * 200 / bon_wy[2] + BON_HALF_SW; // 
           bon_wy[2] = bon_wz[2] * 200 / bon_wy[2] + BON_HALF_SH; // CALCULATE THE ROTATION
                                                                  // OF THE OBJECTS IN ORDER TO
           bon_wx[3] = bon_wx[3] * 200 / bon_wy[3] + BON_HALF_SW; // MAKE THE ROTATE EFFECT AROUND THE PLAYER
           bon_wy[3] = bon_wz[3] * 200 / bon_wy[3] + BON_HALF_SH; // 
           // .........................................
           bon_draw_wall(bon_wx[0], bon_wx[1], bon_wy[0], bon_wy[1], bon_wy[2], bon_wy[3] , Sectors[s].w[w].c);
          }
        }
    }
}