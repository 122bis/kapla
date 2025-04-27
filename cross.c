// -----------------------------------------------------------------------------
// cross.c
// project : Kapla VERSION_014
// -----------------------------------------------------------------------------

#include "cross.h"

void init(int w, int h, float scale)
{

    // ... init GLOBALS ...
    WIDTH  = w * _DPI * _INCH_PER_MM;
    HEIGHT = h * _DPI * _INCH_PER_MM;
    //printf("WIN_WIDTH  = %d\n", WIN_WIDTH );
    //printf("WIN_HEIGHT = %d\n", WIN_HEIGHT);

    INTERVAL = (int)(1000000 / _FPS);   // wait duration (microseconds) in idle loop usleep()
    MICROSECONDS = 0;     // total elapsed time (microseconds)
    ELAPSED_SECONDS = 0;

    ALPHA = 0;  // orb engine angle (radians)
    OMEGA = TWO_PI * (float)_ORB_RPM / 60.0; // angular velocity (radians per sec) : 1 rev.p.mn = 1/60 rev.p.s

    len = 33 * scale;
    wth = 11 * scale;
    thk =  6 * scale;
    extents_x = 0.55 * (len + thk + wth + len + thk - len);
    extents_y = 0.55 * (len + thk + wth + len + thk - len );

    center.x = WIDTH * 0.5;
    center.y = HEIGHT * 0.5;  // position of the cross on screen

    // positions of four + 1 sliding horizontal rects
    p1 = (struct Point) { len/2 + wth/2 + thk,    wth/2+thk/2 };
    p2 = (struct Point) { len/2 + wth/2 + thk,   -wth/2-thk+thk/2 };
    p3 = (struct Point) { -len/2-thk-wth/2,        wth/2+thk/2 };
    p4 = (struct Point) { -len/2-thk-wth/2,       -wth/2-thk+thk/2 };
    h_slider = (struct Point) { extents_x * cos(ALPHA), 0 };

    // positions of four vertical cts + 1 sliding
    p5 = (struct Point) {  wth/2+thk/2,  len/2+wth/2+thk };
    p6 = (struct Point) { -wth/2-thk/2,  len/2+wth/2+thk };
    p7 = (struct Point) {  wth/2+thk/2, -len/2-thk-wth/2 };
    p8 = (struct Point) { -wth/2-thk/2, -len/2-thk-wth/2 };
    v_slider = (struct Point) { 0, extents_y * sin(ALPHA) };

    orb = (struct Point) { 0, 0 };//  all movement originate from this point
    previous_orb = (struct Point) { 0, 0 };
}

void orbit(float t)
{
    // wheel is rotating, angle stays within [0,360°]
    // % operator returns an int from the remaining of a division
    // fmod is real modulo for floats
    ALPHA = fmod( (float)t * OMEGA, TWO_PI );
    // save previous orb position
    previous_orb.x = orb.x;
    previous_orb.y = orb.y;
    // new pos
    orb.x = extents_x * cos(ALPHA);
    orb.y = extents_y * sin(ALPHA);
    //printf("t: %f, ALPHA : %f, orb.x : %f, orb.y : %f\n", t, ALPHA * RAD2DEG , orb.x, orb.y);

    // if HORIZONTAL direction changes...
    orb_dir.x = cmp(previous_orb.x, orb.x);
    if (orb_dir.x + previous_orb_dir.x == 0) {
        HFLAG = true;
    }
    // if VERTICAL direction changes...
    orb_dir.y = cmp( previous_orb.y, orb.y);
    if (orb_dir.y + previous_orb_dir.y == 0) {
        VFLAG = true;
    }
    previous_orb_dir.x = orb_dir.x;
    previous_orb_dir.y = orb_dir.y;}


void update()
{
    // apply orb new position to h and v sliders
    h_slider.x = orb.x;
    v_slider.y = orb.y;

    // if direction changes, target_v colors cycle, sound played
    if (HFLAG) {
        system("timeout 0.5 afplay ./snd/bow1.wav &");  //BOW1.play();
        HFLAG = !HFLAG;
    }
    if (VFLAG) {
        system("timeout 0.5 afplay -r 4 ./snd/bow.wav &");  //BOW1.play();
        VFLAG = !VFLAG;
    }
}


void draw(cairo_t * cr)
{
    cairo_set_source_rgba (cr, _BACKGROUND.r, _BACKGROUND.g, _BACKGROUND.b, _BACKGROUND.a);
    cairo_paint (cr);

    //printf("draw...\n");
    
    cairo_save(cr);
    cairo_translate(cr, center.x, center.y);
    
    //box_draw(cr, & KRED,    & h_slider, len, HEIGHT + 5); // h_slider box
    rec_draw(cr, & KLRED,    & h_slider, len, HEIGHT + 5); // h_slider box
    //box_draw(cr, & KGREEN,  & v_slider, WIDTH + 5, len); // v_slider
    rec_draw(cr, & KLGREEN,  & v_slider, WIDTH + 5, len); // v_slider
    disk_draw(cr, & _BACKGROUND,  & orb, len * 0.5); // orb disc

    // four + 1 sliding horizontal rects
    rec_draw(cr, & KRED,    & p1, len, thk); // r1 bottom right
    rec_draw(cr, & KGREEN,  & p2, len, thk); // r2
    rec_draw(cr, & KYELLOW, & p3, len, thk); // r3
    rec_draw(cr, & KBLUE,   & p4, len, thk); // r4
    rec_draw(cr, & KRED,    & h_slider, len, wth); // h_slider
                                      //
    // four vertical rects + 1 sliding
    rec_draw(cr, & KGREEN,  & p5, thk, len); // r5 bottom right
    rec_draw(cr, & KYELLOW, & p6, thk, len); // r6 bottom left
    rec_draw(cr, & KBLUE,   & p7, thk, len); // r7 top right
    rec_draw(cr, & KRED,    & p8, thk, len); // r8 top left
    rec_draw(cr, & KGREEN,  & v_slider, wth, len); // v_slider
    // large outline recs, transparency toggled when key 'I' pressed
    //hr = rec1(w=len, h=WIN_HEIGHT-2, color=grey, pos=(0,0,0), plane=hslide)
    dot_draw(cr, & KBLUE, & orb);
    dot_draw(cr, & KRED, & ORIGIN);

    cairo_restore(cr);
}



