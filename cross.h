// -----------------------------------------------------------------------------
// cross.h 
// project : Kapla VERSION_009 
// -----------------------------------------------------------------------------

#ifndef CROSS
    #define CROSS

    #include "geom.h"

    // cross globals
    static int len;      // sides of the kapla blocks
    static int wth;
    static int thk; 

    // CROSS --------------------------------------------------------------
    struct Cross
    {
        float alpha;            // angle of wheel
        float omega;            // angular velocity in radian
        int extents_x;          // radii extents of the wheel mechanism
        int extents_y;
        struct Point peg;        // all movement originate from this point on the rotating disc.
        struct Vec peg_dir;          // sliding direction of horizontal K
        struct Point previous_peg;
        struct Vec previous_peg_dir; // sliding direction of vertical K
        struct Point p1;         // centers of four static + 1 sliding horizontal rects
        struct Point p2;
        struct Point p3;
        struct Point p4;
        struct Point sl_h;
        struct Point p5;         // centers of four static vertical rects + 1 sliding
        struct Point p6;
        struct Point p7;
        struct Point p8;
        struct Point sl_v;
    };

    struct Cross * crosses;

    // STATIC FIGURE LIST FUNCTIONS ------------------------------------------------
    void cross_init(int i);
    void cross_update(int i);
    void cross_draw(cairo_t * cr, int i);



#endif  
