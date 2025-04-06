// -----------------------------------------------------------------------------
// scene.c 
// project : Kapla VERSION_009 
// -----------------------------------------------------------------------------

#include "scene.h"
#include "geom.h"
#include "config.h"
#include "globals.h"


void scene_init(){

    int r = get_value("BACKGROUND_R");
    int g = get_value("BACKGROUND_G");
    int b = get_value("BACKGROUND_B");
    int a = get_value("BACKGROUND_A");
    BACKGROUND.r = r/255.0;
    BACKGROUND.g = g/255.0;
    BACKGROUND.b = b/255.0;
    BACKGROUND.a = a/1.0;

    // get scene engine speed and individual cross variability
    ORB_RPM = get_value("ORB_RPM");
    ORB_DESYNC = get_value("ORB_DESYNC");

    // object size multipier relative to screen size for good anti-aliasing
    PIX_MULT = (int)(0.5 * SCREEN_WIDTH / 85); 
    printf("PIX_MULT = %d\n", PIX_MULT);
    FIG_NUM_X = (int)get_value("FIG_NUM_X");
    FIG_NUM_Y = (int)get_value("FIG_NUM_Y");
    FIG_NUM = FIG_NUM_X * FIG_NUM_Y;
    printf("FIG_NUM = %d\n", FIG_NUM);
    
    anchors  = (struct Anchor *)malloc(FIG_NUM * sizeof(struct Anchor));
    crosses  = (struct Cross *)malloc(FIG_NUM * sizeof(struct Cross)); 

    anchors[0].origin = (struct Point) {-(85 * 0.5 * PIX_MULT) - 50, 0};
    anchors[0].scale = 0.95;
    anchors[0].angle = 0;
    
    anchors[1].origin = (struct Point) {(85 * 0.5 * PIX_MULT) + 50, 0};
    anchors[1].scale = 0.95;
    anchors[1].angle = 0;
    // overall drawing V size is 85 PIX_MULT so it just fits into screen
    // set rec sizes relative to screen with proportions of the telepantin figure
    // for cross in crosses   
    for (int i=0; i<FIG_NUM; i++)
    {
    cross_init(i);
    }
}

void scene_update()
{
    // for cross in crosses   
    for (int i=0; i<FIG_NUM; i++)
    {
    cross_update(i);
    }
}


void scene_draw(cairo_t * cr, int FR) {
    printf("\n .............................repaint %d at %f s\n", FR, ELAPSED_SECONDS);
    cairo_translate(cr, SCREEN_WIDTH/2, SCREEN_HEIGHT/2); // move origin to origin of the window
    cairo_set_source_rgba (cr, BACKGROUND.r, BACKGROUND.g, BACKGROUND.b, BACKGROUND.a); /*  */
    cairo_paint (cr);
    // for cross in crosses  
    for (int i=0; i<FIG_NUM; i++)
    {
        cairo_save(cr);
        cairo_translate(cr, anchors[i].origin.x, anchors[i].origin.y); 
        cairo_scale(cr, anchors[i].scale, anchors[i].scale);
        cross_draw(cr, i);
        cairo_restore(cr);
    }
}


