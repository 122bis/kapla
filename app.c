// -----------------------------------------------------------------------------
// app.c  
// project : kapla VERSION_009 
// -----------------------------------------------------------------------------


#include <gtk/gtk.h>
#include <unistd.h> // usleep() in idle loop
#include "scene.h" // init() update() draw()
#include "config.h"
#include "globals.h"

#define MICROSEC 1000000

// ... GLOBALS ...
int FPS;          
int PNG_EXPORT;   
int PNG_DURATION;
int PNG_WIDTH;    
int PNG_HEIGHT;   
int SCREEN_WIDTH; 
int SCREEN_HEIGHT;

// ... LOCALS ...
static void on_draw (GtkDrawingArea * area, cairo_t * cr, int width, int height, gpointer user_data);
static void png_export(cairo_t * cr, int width, int height);

static int WAIT = 0;  // wait duration (microseconds) in idle loop usleep()
static int FR = 0;                             // frame number
static unsigned long MICROSECONDS=0;                     // total elapsed time (microseconds)
static GtkWidget * C;                          // the drawing widget
static GtkWidget * W;                          // the window

// ... INTERACTION ...
static gboolean on_key_pressed(GtkWidget * drawing_area, guint keyval, guint keycode, GdkModifierType state, GtkEventControllerKey * event_controller)
{
    if (keyval == 'q') gtk_window_destroy (GTK_WINDOW (W));
    return TRUE;
}


// ... DRAW  ...
static void on_draw (GtkDrawingArea * area, cairo_t * cr, int width, int height, gpointer user_data)
{

    FR ++;
    scene_draw(cr,FR); // ................................. SCENE DRAW FUNCTION ...
    if (PNG_EXPORT) png_export(cr, width, height);  
}

// ... PNG export ...
static void png_export(cairo_t * cr, int width, int height)
{
    char fr_filename[20];
    sprintf(fr_filename, "./png/fr_%04d.png", FR);

    cairo_surface_t * T;
    cairo_t * crxp;

    T = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    crxp = cairo_create(T);
    scene_draw(cr,FR);    // ...............................SCENE DRAW FUNCTION ...
    cairo_surface_write_to_png(T, fr_filename);

    cairo_destroy(crxp);
    cairo_surface_destroy(T);
}

// ... UPDATE ...
gboolean on_idle_loop(GtkWidget * widget)
{
    usleep(WAIT); //wait (time in microseconds)
    MICROSECONDS += WAIT;
    ELAPSED_SECONDS = (float)MICROSECONDS / (float)MICROSEC;  // time converted to seconds
    scene_update();             // ................... SCENE UPDATE FUNCTION ... 
    gtk_widget_queue_draw(C);   // request gtk to redraw
    return TRUE;
}


static void on_activate (GApplication * app)
{
    gtk_window_present (GTK_WINDOW (W));
}


static void on_shutdown (GApplication * application)
{
    g_application_quit(G_APPLICATION(application));
}


static void on_startup (GApplication * app, gpointer user_data)
{
    W = gtk_application_window_new (GTK_APPLICATION (app));
    gtk_window_set_default_size(GTK_WINDOW(W), SCREEN_WIDTH, SCREEN_HEIGHT);
    gtk_window_fullscreen (GTK_WINDOW(W));
    gtk_window_set_resizable (GTK_WINDOW(W), FALSE);
    gtk_window_set_title (GTK_WINDOW (W), "mi");
    
    C = gtk_drawing_area_new ();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA (C), on_draw, NULL, NULL);
    gtk_window_set_child (GTK_WINDOW (W), C);
    
    GtkEventController * event_controller = gtk_event_controller_key_new ();
    gtk_widget_add_controller (GTK_WIDGET (W), event_controller);
    g_signal_connect_object (event_controller, "key-pressed", G_CALLBACK (on_key_pressed), C, G_CONNECT_SWAPPED);
    g_idle_add((GSourceFunc) on_idle_loop, (gpointer) C);
}


#define APPLICATION_ID "cairo.app"

int main (int argc, char ** argv) {

    // parse config file :
    FPS             = get_value("FPS");
    PNG_EXPORT      = get_value("PNG_EXPORT");
    SCREEN_WIDTH    = get_value("SCREEN_WIDTH");
    SCREEN_HEIGHT   = get_value("SCREEN_HEIGHT");
    ELAPSED_SECONDS  = 0;             // total elapsed time (seconds) global set to 0
    WAIT = (int)(MICROSEC / FPS);  // animation wait duration
    printf("WAIT = %d microseconds\n", WAIT);
    
    if (PNG_EXPORT) {
        PNG_DURATION  = get_value("PNG_DURATION");
        PNG_WIDTH     = get_value("PNG_WIDTH");
        PNG_HEIGHT    = get_value("PNG_HEIGHT");
        system("rm ./png/*.png");
        system("mkdir ./png");
        SCREEN_WIDTH = PNG_WIDTH;
        SCREEN_HEIGHT = PNG_HEIGHT;
    }

    printf("SCREEN_WIDTH  = %d\n",SCREEN_WIDTH );
    printf("SCREEN_HEIGHT = %d\n",SCREEN_HEIGHT);

    scene_init(); // ................................... SCENE INIT FUNCTION ...

    // ... GTK INIT ...
    GtkApplication * app;
    app = gtk_application_new (APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "startup", G_CALLBACK (on_startup), NULL);
    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
    g_signal_connect (app, "shutdown", G_CALLBACK (on_shutdown), NULL);

    int stat;
    stat = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}
