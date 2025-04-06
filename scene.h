// -----------------------------------------------------------------------------
// scene.h 
// project : Kapla VERSION_009 
// -----------------------------------------------------------------------------

#ifndef SCENE
    #define SCENE

    #include "geom.h"
    #include "cross.h"
    // scene globals

    // FIGS LIST -----------------------------------------------------------
       // Declare a pointer to the structure
       // size will be set later
    struct Anchor{    
        struct Point origin;     // origin of the figure (and center of circle)
        float scale;
        float angle;
    };
    
    struct Anchor * anchors;

    // APP FUNCTIONS ------------------------------------------------------
    void scene_init();
    void scene_update();
    void scene_draw(cairo_t * cr, int FR);  

#endif  
