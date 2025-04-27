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
    #define _WIN_WIDTH_MM 55  // floating win width (mm)
    #define _WIN_HEIGTH_MM 55 // floating win height (mm) --> playcard = 55x85
    #define _WIN_SCALE 3.2 // floating win contents size adjustment 
    #define _FULLSCR_WIDTH_MM 297  // fullscreen width (mm)
    #define _FULLSCR_HEIGHT_MM 180 // fullscreen height (mm) --> playcard = 55x85
    #define _FULLSCR_SCALE 10.8 // fullscreen size adjustment 
    #define _DPI  152   // 92 normal , 152 retina set to high density
    #define _INCH_PER_MM 0.039
    #define _PNGEXPORT 0 
    #define _PNG_WIDTH 1050  
    #define _PNG_HEIGHT 1050
  

    // ... BACKGROUND ... 
    #define _BACKGROUND GREY_122 //from geom.h

    // ... GLOBALS ...
    int WIDTH; 
    int HEIGHT;
    float ALPHA;
    float OMEGA;
    unsigned int INTERVAL;        // wait duration (microseconds) in idle loop usleep()
    unsigned long MICROSECONDS;   // total elapsed time (microseconds)
    float ELAPSED_SECONDS;
#endif
