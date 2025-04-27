// -----------------------------------------------------------------------------
// geom.h 
// project : Kapla VERSION_014 
// -----------------------------------------------------------------------------

#ifndef GEOM
    #define GEOM
    
    #define PI 3.1415927
    #define TWO_PI 6.2831854
    #define RAD2DEG 360 / TWO_PI 
    #define DEG2RAD TWO_PI / 360


    // ... POINT ...............................................................

    struct Point {
        float x;
        float y;
    };
    
    #define Vec Point
    #define Rec Point

    struct Point ORIGIN;
    
    // ... FUNCTIONS ...

    struct Point point_rotate(struct Point * p, struct Point * center, float alpha);
  
    // ... QUAD ................................................................

    struct Quad {
        struct Point pt[4];
    };

    // .... FUNCTIONS ...
    
    struct Quad quad_deep_copy(struct Quad * q);
    struct Quad quad_rotate(struct Quad * q, struct Point * center, float alpha );
    

    // ... COLORS  .............................................................

    struct Color {
        float r; //   0 <=  red    <= 1 
        float g; //   0 <=  green  <= 1 
        float b; //   0 <=  blue   <= 1 
        float a; //   0 <=  alpha  <= 1     
    };
 
    struct Color WHITE;
    struct Color GREY;
    struct Color GREY_122;  // dark 122bis site background
    struct Color PAPER;
    struct Color DARK;

    struct Color KRED;      // red telepantin
    struct Color KBLUE;     // blue telepantin
    struct Color KGREEN;    // green telepantin
    struct Color KYELLOW;   // yellow telepantin

    struct Color KLRED;      // light red telepantin
    struct Color KLBLUE;     // light blue telepantin
    struct Color KLGREEN;    // light green telepantin
    struct Color KLYELLOW;   // light yellow telepantin

    // ... FUNCTIONS ...
    struct Color color_deep_copy(struct Color * q);


    // ... CAIRO ...............................................................
    
    // ... DRAWING FUNCTIONS ...

    #include <gtk/gtk.h>
    void  dot_draw(cairo_t * cr, struct Color * k, struct Point * p);
    void spot_draw(cairo_t * cr, struct Color * k, struct Point * p);
    void  rec_draw(cairo_t * cr, struct Color * k, struct Point * c, int w, int h);
    void  box_draw(cairo_t * cr, struct Color * k, struct Point * c, int w, int h);
    void rrec_draw(cairo_t * cr, struct Color * k, struct Point * c, int w, int h, double a);
    void quad_draw(cairo_t * cr, struct Color * k, struct  Quad * q);
    void circle_draw(cairo_t * cr, struct Color * k, struct Point * p, int d);
    void disk_draw(cairo_t * cr, struct Color * k, struct Point * p, int d);


    // ... HELPERS .............................................................
    int cmp(float a, float b); 
    float sind(float x);
    float cosd(float x);
    float tand(float x);
    float arclength(float r, float a, float b);
    float dist(struct Point a, struct Point b);
    float magn(struct Vec v);
    float cosv(struct Vec v);
    float sinv(struct Vec v);
    struct Vec vec(struct Point a, struct Point b);

#endif  

// NOTES:
// - all functions now use pointers
