// -----------------------------------------------------------------------------
// app.c  
// project : kapla VERSION_014
// -----------------------------------------------------------------------------


#include <gtk/gtk.h>
#include <unistd.h> // usleep() getopt()
#include "cross.h" // init() update() draw()
#include "globals.h"

#define APPLICATION_ID "cairo.app"

// ... FUNCTIONS ...

static gboolean on_key_pressed(GtkWidget * drawing_area, guint keyval, guint keycode, GdkModifierType state, GtkEventControllerKey * event_controller);

// ... GTK ...
static GtkWidget * C;                 // the drawing widget
static GtkWidget * W;                 // the window

// ... INTERACTION ...
static gboolean on_key_pressed(GtkWidget * drawing_area, guint keyval, guint keycode, GdkModifierType state, GtkEventControllerKey * event_controller){
    if (keyval == 'q') gtk_window_destroy (GTK_WINDOW (W));
    if (keyval == 'f'){ 
        int width  = gtk_widget_get_width (drawing_area);
        int height = gtk_widget_get_height(drawing_area);
        // Print the screen size
        printf("display : %d x %d\n", width, height);

        if (gtk_window_is_fullscreen ( GTK_WINDOW (W))){
            gtk_window_unfullscreen ( GTK_WINDOW (W));
            gtk_window_set_resizable (GTK_WINDOW(W), FALSE); // block again resize
            init(_WIN_WIDTH, _WIN_HEIGTH, _WIN_SCALE); //... SCENE INIT (WINDOWED)
        }
        else{
            gtk_window_fullscreen ( GTK_WINDOW (W)); 
            gtk_window_set_resizable (GTK_WINDOW(W), TRUE); // necessary to restore original size
            init(_FULLSCR_WIDTH, _FULLSCR_HEIGHT, _FULLSCR_SCALE); //... SCENE INIT (FULLSCREEN)
        }
    }
   if (keyval == ' '){ 
        if (!gtk_window_is_fullscreen ( GTK_WINDOW (W))) {
        gboolean has_it = gtk_window_get_decorated (GTK_WINDOW (W));
        gtk_window_set_decorated (GTK_WINDOW (W), !has_it);
        }
    }
    return TRUE;
}


// ... DRAW  ...
static void on_draw (GtkDrawingArea * area, cairo_t * cr, int width, int height, gpointer user_data){
    draw(cr); // ....................................... SCENE DRAW FUNCTION ...
}


// ... UPDATE ...
gboolean on_idle_loop(GtkWidget * widget){
    if (EXPORT){
        MICROSECONDS += INTERVAL;
        // printf("MICROSECONDS = %lu\n", MICROSECONDS);
        ELAPSED_SECONDS = (float)MICROSECONDS / 1000000.0;  // time converted to seconds
        FRN ++;
        if (FRN > NUMFRAMES +1){
        printf("TOTAL TIME : = %.2f\nTOTAL FRAMES : %d\n", ELAPSED_SECONDS, FRN);
        exit(0);
        }
        orbit(ELAPSED_SECONDS); // ......................... REV ENGINE FUNCTION ... 
        update();   // ................................ GEOMETRY UPDATE FUNCTION ...
        export_frame(FRN);
    }
    else{
        usleep(INTERVAL); //wait (time in microseconds)
        MICROSECONDS += INTERVAL;
        // printf("MICROSECONDS = %lu\n", MICROSECONDS);
        ELAPSED_SECONDS = (float)MICROSECONDS / 1000000.0;  // time converted to seconds
        orbit(ELAPSED_SECONDS); // ......................... REV ENGINE FUNCTION ... 
        update();   // ................................ GEOMETRY UPDATE FUNCTION ... 
    }
    // request gtk to redraw :
    gtk_widget_queue_draw(C);   
    return TRUE;
}


static void on_activate (GApplication * app){
    gtk_window_present (GTK_WINDOW (W));
}


static void on_shutdown (GApplication * application){
    g_application_quit(G_APPLICATION(application));
}


static void on_startup (GApplication * app, gpointer user_data){
    W = gtk_application_window_new (GTK_APPLICATION (app));
    gtk_window_set_default_size(GTK_WINDOW(W), WIDTH, HEIGHT);
    gtk_window_set_resizable (GTK_WINDOW(W), FALSE);
    gtk_window_set_decorated (GTK_WINDOW (W), FALSE);
    gtk_window_set_title (GTK_WINDOW (W), "orb");
    
    C = gtk_drawing_area_new ();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA (C), on_draw, NULL, NULL);
    gtk_window_set_child (GTK_WINDOW (W), C);
     
    GtkEventController * event_controller = gtk_event_controller_key_new ();
    gtk_widget_add_controller (GTK_WIDGET (W), event_controller);
    g_signal_connect_object (event_controller, "key-pressed", G_CALLBACK (on_key_pressed), C, G_CONNECT_SWAPPED);
    g_idle_add((GSourceFunc) on_idle_loop, (gpointer) C);
}


static void help(){
    printf("\n\t................................................\n");
    printf("\t.                * kapla.app *                 .\n");
    printf("\t. - start without args for screen display only .\n");
    printf("\t.                   q : quit                   .\n");    
    printf("\t.                   f : toggle fullscreen      .\n");
    printf("\t.             <space> : show window titlebar   .\n");
    printf("\t. - starting with a number n as argument       .\n");
    printf("\t.   will save n frames to the png folder       .\n");
    printf("\t.   ex: 'kapla.app 60' will save 60 frames     .\n");
    printf("\t................................................\n");
    printf("\t \\   ^__^            \n");
    printf("\t  \\  (oo/)\\_______    \n");
    printf("\t     (__)\\       )\\/\\\n");
    printf("\t         ||----w |   \n");
    printf("\t         ||     ||   \n\n"); 
}


int main (int argc, char * argv[]) {
    // get eventual startup 'option'
    help();
    FRN = 0;
    if (argc == 2){
        NUMFRAMES = atoi(argv[1]);
        }
    else{
        NUMFRAMES = 0;
    }
    
    // run for export
    if (NUMFRAMES) {
        EXPORT = 1;
        printf("starting app for export of %d frames...\n", NUMFRAMES);
        init(_PNG_WIDTH, _PNG_HEIGHT, _PNG_SCALE); //... SCENE INIT (FOR EXPORT)
    }
    // run for display
    else {
        EXPORT = 0;
        printf("starting app for display only\n");
        init(_WIN_WIDTH, _WIN_HEIGTH, _WIN_SCALE); //... SCENE INIT (WINDOWED)
    }
    
    // ... GTK INIT ...
    GtkApplication * app;
    app = gtk_application_new (APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "startup",  G_CALLBACK (on_startup), NULL);
    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
    g_signal_connect (app, "shutdown", G_CALLBACK (on_shutdown), NULL);

    int stat;
    stat = g_application_run (G_APPLICATION (app), 0, NULL);
    g_object_unref (app);
    return stat;
}
