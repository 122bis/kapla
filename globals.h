// -----------------------------------------------------------------------------
// globals.h 
// project : Kapla VERSION_013 
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
    #define _WIN_WIDTH_MM 55 // win width (mm)
    #define _WIN_HEIGTH_MM 55 // win height (mm) --> playcard = 55x85
    #define _PNGEXPORT 0 
    #define _PNG_WIDTH 2560  
    #define _PNG_HEIGHT 1600
    #define _DPI  152   // 92 normal , 152 retina set to high density
    #define _INCH_PER_MM 0.039
  

    // ... BACKGROUND ... 
    #define _BACKGROUND GREY_122

    // ... GLOBALS ...

    int WIN_WIDTH; 
    int WIN_HEIGHT;
    float ALPHA;
    float OMEGA;
#endif
