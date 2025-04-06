// -----------------------------------------------------------------------------
// cross.c 
// project : Kapla VERSION_009 
// -----------------------------------------------------------------------------

#include "cross.h"
#include "geom.h"
#include "config.h"
#include "globals.h"


void cross_init(int i)
{
    
    len = 33 * PIX_MULT;
    wth = 11 * PIX_MULT;
    thk =  6 * PIX_MULT;
    printf("\ninit cross %d\n",i);
    crosses[i].alpha = 0;
    
    // angular velocity in radians per sec: 1 ORB_RPM = 1/60 RPS
    // desync will increase at each extra iteration of cross
    crosses[i].omega = (1.0 + (i * ORB_DESYNC)) * TWO_PI * (float)ORB_RPM / 60.0;  
    printf("omega %d = %f\n", i, crosses[i].omega); 
    crosses[i].extents_x = 33 * PIX_MULT;
    crosses[i].extents_y = 50 * PIX_MULT;

    // positions of four + 1 sliding horizontal rects
    crosses[i].p1 = (struct Point) { len/2 + wth/2 + thk,    wth/2+thk/2 };
    crosses[i].p2 = (struct Point) { len/2 + wth/2 + thk,   -wth/2-thk+thk/2 };
    crosses[i].p3 = (struct Point) {-len/2-thk-wth/2,        wth/2+thk/2 };
    crosses[i].p4 = (struct Point) {-len/2-thk-wth/2,       -wth/2-thk+thk/2};
    crosses[i].sl_h = (struct Point) { crosses[i].extents_x * cos(crosses[i].alpha), 0 };
     
    printf("sl_h[%d] .x = %f, .y = %f \n", i, crosses[i].sl_h.x, crosses[i].sl_h.y);
    // positions of four vertical cts + 1 sliding
    crosses[i].p5 = (struct Point) { wth/2+thk/2,      len/2+wth/2+thk };
    crosses[i].p6 = (struct Point) {-wth/2-thk/2,      len/2+wth/2+thk };
    crosses[i].p7 = (struct Point) { wth/2+thk/2,     -len/2-thk-wth/2 };
    crosses[i].p8 = (struct Point) {-wth/2-thk/2,     -len/2-thk-wth/2 };
    crosses[i].sl_v = (struct Point) { 0, crosses[i].extents_y * sin(crosses[i].alpha) };
    printf("sl_v[%d] .x = %f, .y = %f \n", i, crosses[i].sl_v.x, crosses[i].sl_v.y);

    crosses[i].peg          = (struct Point) { 0, 0 };
    crosses[i].previous_peg = (struct Point) { 0, 0 };

}


void cross_update(int i)
{
    // wheel is rotating, angle stays within [0,360°]
    // % operator returns an int from the remaining of a division
    // fmod is real modulo for floats
    crosses[i].alpha = fmod(ELAPSED_SECONDS * crosses[i].omega, TWO_PI);
    // save previous peg position
    crosses[i].previous_peg.x = crosses[i].peg.x;
    crosses[i].previous_peg.y = crosses[i].peg.y;
    // new pos
    crosses[i].peg.x = cos(crosses[i].alpha);
    crosses[i].peg.y = sin(crosses[i].alpha);
    // apply to h and v sliders
    crosses[i].sl_h.x = crosses[i].extents_x * crosses[i].peg.x;
    crosses[i].sl_v.y = crosses[i].extents_y * crosses[i].peg.y;

    printf("\nupdate cross %d\n",i);
    printf("alpha : %f, peg.x : %f, peg.y : %f\n", crosses[i].alpha, crosses[i].peg.x, crosses[i].peg.y);
   
    // ... SOUND ...
    // hslide is oscillating
    // if direction changes, target_h colors cycle, sound played
    crosses[i].peg_dir.x = cmp(crosses[i].previous_peg.x, crosses[i].peg.x);
    if (crosses[i].peg_dir.x + crosses[i].previous_peg_dir.x == 0) {
        system("afplay -r 2 ./snd/bow1.wav &");  //BOW1.play();
    }
    // vslide is oscillating
    // if direction changes, target_v colors cycle, sound played
    crosses[i].peg_dir.y = cmp( crosses[i].previous_peg.y, crosses[i].peg.y);
    if (crosses[i].peg_dir.y + crosses[i].previous_peg_dir.y == 0) {
        system("afplay -r 2 ./snd/bow.wav &");  //BOW1.play();
    }

    crosses[i].previous_peg_dir.x = crosses[i].peg_dir.x;
    crosses[i].previous_peg_dir.y = crosses[i].peg_dir.y;
}


void cross_draw(cairo_t * cr, int i)
{

    printf("\ndraw cross %d\n",i);

    // four + 1 sliding horizontal rects
    rec_draw(cr, & KRED,    & crosses[i].p1, len, thk); // r1 bottom right
    rec_draw(cr, & KGREEN,  & crosses[i].p2, len, thk); // r2
    rec_draw(cr, & KYELLOW, & crosses[i].p3, len, thk); // r3
    rec_draw(cr, & KBLUE,   & crosses[i].p4, len, thk); // r4
    rec_draw(cr, & KRED,    & crosses[i].sl_h, len, wth); // sl_h
                                      //
    printf("sl_h[%d] .x = %f, .y = %f \n", i, crosses[i].sl_h.x, crosses[i].sl_h.y);
    // four vertical rects + 1 sliding
    rec_draw(cr, & KGREEN,  & crosses[i].p5, thk, len); // r5 bottom right
    rec_draw(cr, & KYELLOW, & crosses[i].p6, thk, len); // r6 bottom left
    rec_draw(cr, & KBLUE,   & crosses[i].p7, thk, len); // r7 top right
    rec_draw(cr, & KRED,    & crosses[i].p8, thk, len); // r8 top left
    rec_draw(cr, & KGREEN,  & crosses[i].sl_v, wth, len); // sl_v
    printf("sl_v[%d] .x = %f, .y = %f \n", i, crosses[i].sl_v.x, crosses[i].sl_v.y);
    // large outline recs, transparency toggled when key 'I' pressed
    //vr = rec1(w=SCREEN_WIDTH-2, h=len, color=grey, pos=(0,0,0), plane=vslide)
    //hr = rec1(w=len, h=SCREEN_HEIGHT-2, color=grey, pos=(0,0,0), plane=hslide)
    dot_draw(cr, & KBLUE, & crosses[i].peg);
    dot_draw(cr, & KRED, & ORIGIN);
}



