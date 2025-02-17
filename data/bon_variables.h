// ***************************************
// * GLOBAL LIBRARIES OF THE GAME ENGINE *
// ***************************************
// .......................................
#define BON_RES 4                           // DEFINE THE ENTIRE SCREEN RESOLUTION
#define BON_SCREENW 160*BON_RES             // DEFINE THE SCREEN WIDTH
#define BON_SCREENH 120*BON_RES             // DEFINE THE SCREEN HEIGHT
#define BON_HALF_SW (BON_SCREENW/2)         // DEFINE CENTER OF SCREEN
#define BON_HALF_SH (BON_SCREENH/2)         // AND HORIZONTAL CENTER OF SCREEN
#define BON_PIXEL_S 4/BON_RES               // CALCULATE PIXEL RESOLUTION SIZE
#define BON_W_SDL_W BON_SCREENW*BON_PIXEL_S // BASED OFF THAT DEFINE THE SIZE
#define BON_W_SDL_H BON_SCREENH*BON_PIXEL_S // OF THE SDL SCREEN TO BE CREATED
#define BON_MATH_PI 3.14159                 // DEFINE THE VALUE OF PI
#define BON_MAX_SEG 1000                     // MAXIMUM SEGMENTS IN WORLD 
// ---------------------------------------
SDL_Window *window = nullptr;       // DISPLAY WINDOW 
SDL_Renderer *renderer = nullptr;   // AND RENDERER VARIABLES
// ---------------------------------------
int bon_max_creg = 0;   // MAX COLOR REGISTER SUPPORTED
int bon_colors[3][255]; // TABLE FOR PREDEFINED COLORS (MUST BE INITIALIZED)
// ---------------------------------------
struct Bon_player {
    // -----------------------
    bool bon_upkey = false; // ****************************************************
    bool bon_dwkey = false; // THESE FOUR VARIABLES HANDLE THE MULTIKEY DETECTION
    bool bon_lfkey = false; // HANDLING SYSTEM PERFORMING FALSE AND TRUE OPERATIONS
    bool bon_rhkey = false; // ****************************************************
    // -----------------------************************
    bool bon_lstrafe = false; // left strafe
    bool bon_rstrafe = false; // right strafe
    // -----------------------************************
    bool bon_actionb = false; // action button handle
    // -----------------------************************
    int bon_ux =  70; // USER X
    int bon_uy =-110; // USER Y
    int bon_uz =  20; // USER Z
    int bon_ua =   0; // USER Angle
    int bon_ul =   0; // USER Lookup
    // ************************************************
}player;
// ------------------------------------------
float bon_pcos[360]; // TO MAKE THE ENGINE FASTER ON CALCULATIONS
float bon_psin[360]; // WE STORE THE 360 VALUES ON THESE ARRAYS
// -------------------- HAVING PRECALCULATED VALUES ON SCREEN
// ..........................................
struct Wall {          // THIS IS A TEMPORAL STRUCT I'LL USE TO TEST
    int x1 = 0;        // THE ENGINE ALONG THE DEVELOPMENT
    int x2 = 0;        // 
    int y1 = 0;        // IN HERE WE WILL DEFINE X AND Y POINTS
    int y2 = 0;        // FOR THE WALL SEGMENTS, AS WELL AS COLORS
    int c  = 0;        // 
};                     // ----------------------------------------
int bon_wall_num = 0;  // STORE WALL POINTER TRACKER
// ..........................................
struct sectors {        // 
    int ws = 0;         // IN THIS PART IM GOING TO IMPLEMENT THE SECTORS
    int we = 0;         // THE WS AND WE DEFINE THE SECTOR START AND END
    int z1 = 0;         // THESE Z VALUES ARE TO INDICATE THE LIMIT Z BOTTOM
    int z2 = 0;         // AND LIMIT Z TOP FOR THE SECTORS
    int  x = 0;         // THIS IS THE X POSITION FOR THE SECTOR
    int  y = 0;         // AND THE Y SECTOR POSITION FOR THE SECTOR
    int  d = 0;         // AND THIS IS THE DISTANCE (DRAW VALUE)
    Wall  w[4];         // THE WALL SEGMENTS ARE STORED IN SECTORS THIS MAKES MORE SENSE
    int c1 = 0;         // CEIL 1 COLOR
    int c2 = 0;         // CEIL 2 COLOR
    //int sf = 0;         // SURFACE STORAGE
    //int sf[BON_SCREENW];// STORE SURFACE PERIMTER
}Sectors[BON_MAX_SEG];// FINALLY DEFINE OUR SECTOR ARRAY
int bon_sec_num = 0;  // NUMBER OF SECTORS IN GAME
// ---------------------------------------------