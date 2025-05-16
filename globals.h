// -----------------------------------------------------------------------------
// globals.h 
// project : Kapla VERSION_014 
//
//                 GLOBAL PROGRAM SETTINGS 
//
// -----------------------------------------------------------------------------

#ifndef GLOBALS
    #define GLOBALS

    #include "geom.h"

    // ... TIME ...
    #define _FPS 12  // frames per sec for both png export and screen play    
    #define _ORB_RPM 30  // orbital engine revolutions per minute
   
    // ... DIMENSIONS ...
    // size pix = size mm * 152 (DPI apple retina) * 0.039 (inch per mm)
    #define _WIN_WIDTH 326          // floating win width (55 mm on screen)
    #define _WIN_HEIGTH 326         // floating win height (mm) --> playcard = 55x85
    #define _WIN_SCALE 3.2          // floating win contents size adjustment 
    #define _FULLSCR_WIDTH 1760     // fullscreen width (297 mm)
    #define _FULLSCR_HEIGHT 1067    // fullscreen height (180 mm)
    #define _FULLSCR_SCALE 10.8     // fullscreen size adjustment 
    #define _PNG_WIDTH 1050  
    #define _PNG_HEIGHT 1050
    #define _PNG_SCALE 10.5        // png contents size adjustment 

    // ... BACKGROUND ... 
    #define _BACKGROUND GREY_122 //from geom.h

    // ... GLOBALS ...
    int WIDTH; 
    int HEIGHT;
    int EXPORT;
    int NUMFRAMES;  // number of frames for png export. If 0 : no export
    int FRN;        // current frame number
    float ALPHA;
    float OMEGA;
    unsigned int INTERVAL;        // pause duration (microseconds) in idle loop usleep()
    unsigned long MICROSECONDS;   // elapsed time (microseconds)
    float ELAPSED_SECONDS;
#endif
