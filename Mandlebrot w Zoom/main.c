/**************************************************************
 * Paul Senatillaka
 * Date: 3/1/10
 * 91.350: Excursions in CS			
 * Assignment: Mandlebrot Set with Zoom	
 * Compile: gcc -Wall -o mandlebrotZoom -g main.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
 ***************************************************************/
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIZE 750
#define MaxCount 75

GtkWidget *corna_text;
GtkWidget *cornb_text;
GtkWidget *size_text;
GtkWidget *draw_area;
GtkWidget *calc_button;


    GtkWidget *window;
    GtkWidget *calc_button;
    GtkWidget *vbox1;
    GtkWidget *labelhbox1;
    GtkWidget *hbox1;
    GtkWidget *draw_area;
    GtkWidget *corna_label;
    GtkWidget *cornb_label;
    GtkWidget *size_label;

int processingMandlebrot;

void setcolor(GdkColor *color, guint red, guint green, guint blue) {
    color -> red = red;
    color -> green = green;
    color -> blue = blue;
    color -> pixel = (gulong) (color -> red * 65536 + color -> green * 256 + color -> blue);

    return;
}

void SetMandlebrotColor (int count, GdkColor *color) {
/*
            if (count >= 3 * MaxCount / 4 && count < MaxCount)
                setcolor(color, (guint) (65535), (guint) (0), (guint) (0));
            else if (count >= 2 * MaxCount / 4 && count < 3 * MaxCount / 4)
                setcolor(color, (guint) (0), (guint) (65535), (guint) (0));
            else if (count >= 1 * MaxCount / 4 && count < 2 * MaxCount / 4)
                setcolor(color, (guint) (0), (guint) (0), (guint) (65535));
            else if (count >= 0 * MaxCount / 4 && count < 1 * MaxCount / 4)
                setcolor(color, (guint) (65535), (guint) (65535), (guint) (0));
            if (count == MaxCount)
                setcolor(color, (guint) (0), (guint) (0), (guint) (0));
*/

    if (count ==  MaxCount )
        setcolor(color, (guint) (0), (guint) (0), (guint) (0));
    else if ( count <  MaxCount / 4 )
        setcolor(color, (guint) (0), (guint) (0), (guint) (0));
    else
        setcolor(color, (guint) ((count % 16)*4369), (guint) (0), (guint) (0));
}

static gboolean Mandlebrot(GtkWidget *widget, GtkWidget *wallpaper) {

    processingMandlebrot = 1;

    float acorn, bcorn, size, ca, cb, zx, zy, xtemp, zx2, zy2;
    int i, j, count;

    GdkGC *gc = gdk_gc_new(widget -> window);
    GdkColor color;

    acorn = atof(gtk_entry_get_text(GTK_ENTRY(corna_text)));
    bcorn = atof(gtk_entry_get_text(GTK_ENTRY(cornb_text)));
    size =  atof(gtk_entry_get_text(GTK_ENTRY(size_text)));

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {

            count = 0;
            ca = acorn + i * size / SIZE;
            cb = bcorn + j * size / SIZE;
            zx = 0;
            zy = 0;

            do {
                count = count + 1;

                zx2 = pow(zx,2);
                zy2 = pow(zy,2);

                xtemp = zx2 - zy2;

                zy = 2 * zx * zy + cb;
                zx = xtemp + ca;
            } while ((count < MaxCount) && (zx2 + zy2) <= 4);

            SetMandlebrotColor(count,&color);

            gdk_color_alloc(gdk_window_get_colormap(widget -> window), &color);
            gdk_gc_set_foreground(gc, &color);
            gdk_draw_point(wallpaper -> window, gc, i, j);
        }
    }

    processingMandlebrot = 0;

    return TRUE;
}

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}



static gboolean
button_press_event( GtkWidget *widget, GdkEventButton *event )
{
    float x, y, acorn, bcorn, size;
    char acornString[10], bcornString[10], sizeString[10];

    x = event->x;
    y = event->y;

    //draw_brush (widget, event->x, event->y);
    if ( processingMandlebrot == 0 && x < SIZE && y < SIZE ) {

        // Get settings from txt box and convert to float
        acorn = atof(gtk_entry_get_text(GTK_ENTRY(corna_text)));
        bcorn = atof(gtk_entry_get_text(GTK_ENTRY(cornb_text)));
        size = atof(gtk_entry_get_text(GTK_ENTRY(size_text)));

        // Perform transform
        acorn = acorn + ( (x - SIZE/2)/SIZE  )  ;
        bcorn = bcorn + ( (y - SIZE/2)/SIZE  )  ;
        size = size - .05;

        // Convert float back to string
        sprintf(acornString,"%f",acorn);
        sprintf(bcornString,"%f",bcorn);
        sprintf(sizeString,"%f",size);

        // Set txt box with updated string values
        gtk_entry_set_text( GTK_ENTRY(corna_text) , acornString );
        gtk_entry_set_text( GTK_ENTRY(cornb_text) , bcornString );
        gtk_entry_set_text( GTK_ENTRY(size_text) , sizeString );

        printf("%f %f \n", event->x, event->y);
        //Mandlebrot(widget,draw_area);
        g_signal_emit_by_name( G_OBJECT(calc_button), "clicked" );

    }

  return TRUE;
}


int main(int argc, char *argv[]) {





    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);


    corna_text = gtk_entry_new();
    cornb_text = gtk_entry_new();
    size_text = gtk_entry_new();

    gtk_entry_set_text( GTK_ENTRY(corna_text), ".1" );
    gtk_entry_set_text( GTK_ENTRY(cornb_text), ".25" );
    gtk_entry_set_text( GTK_ENTRY(size_text), ".5" );

    corna_label = gtk_label_new( "Corn A" );
    cornb_label = gtk_label_new( "Corn B" );
    size_label = gtk_label_new( "Size" );


    calc_button = gtk_button_new_with_label("Generate");

    draw_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(draw_area, SIZE, SIZE);


    gtk_signal_connect (GTK_OBJECT (draw_area), "button_press_event",
		      (GtkSignalFunc) button_press_event, NULL);

    gtk_widget_set_events (draw_area, GDK_BUTTON_PRESS_MASK);
    

    labelhbox1 = gtk_hbox_new(FALSE, 0);
    vbox1 = gtk_vbox_new(FALSE, 0);
    hbox1 = gtk_hbox_new(FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox1);

    gtk_box_pack_start(GTK_BOX(vbox1), labelhbox1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox1), hbox1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox1), draw_area, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox1), corna_text, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), cornb_text, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), size_text, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox1), calc_button, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(labelhbox1), corna_label, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(labelhbox1), cornb_label, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(labelhbox1), size_label, TRUE, TRUE, 0);


    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(destroy), NULL);
    g_signal_connect(G_OBJECT(calc_button), "clicked", G_CALLBACK(Mandlebrot), draw_area);

    gtk_widget_show_all(window);
    gtk_main();

    g_signal_emit_by_name( G_OBJECT(calc_button), "clicked" );

    return (0);
}
