// -----------------------------------------------------------------------------
// cross.h 
// project : Kapla VERSION_014 
// -----------------------------------------------------------------------------

#ifndef CROSS
    #define CROSS

    #include "geom.h"
    #include "globals.h"

    // cross globals
    static int len;      // sides of the kapla blocks
    static int wth;
    static int thk;
    float PIX_MULT;   // object size multipier relative to screen size for good anti-aliasing
    
    static bool VFLAG;
    static bool HFLAG;

    static struct Point center;  // position of the cross on screen 


    // CROSS -------------------------------------------------------------------
    float alpha;            // angle of wheel
    float omega;            // angular velocity in radian
    struct Point orb;       // all movement originate from this point
    struct Point previous_orb; 
    struct Vec orb_dir;     // sliding direction
    struct Vec previous_orb_dir; // previous sliding direction
    struct Point p1;            // centers of 4 static + 1 sliding horizontal rects
    struct Point p2;
    struct Point p3;
    struct Point p4;
    struct Point h_slider;
    int extents_x;          // radii extents of the wheel mechanism
    struct Point p5;         // centers of four static vertical rects + 1 sliding
    struct Point p6;
    struct Point p7;
    struct Point p8;
    struct Point v_slider;
    int extents_y;


    // FUNCTIONS ---------------------------------------------------------------
    void init(int w, int h, float s); // width height and content scaling factor
    void orbit(float ELAPSED_SECONDS);
    void update();
    void export_frame(int frn);
    void draw(cairo_t * cr);



#endif  
