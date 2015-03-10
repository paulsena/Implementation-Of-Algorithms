//Compile: gcc -Wall -o wallpaper -g main.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
/**************************************************************
* Paul Senatillaka		Date: 3/1/10														*
* 91.350: Excursions in CS																		*
* Assignment: Mandlebrot Set																	*
* 																														*
***************************************************************/
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1000
#define MaxCount 100

GtkWidget *corna_text;
GtkWidget *cornb_text;
GtkWidget *side_text;

void setcolor (GdkColor *color, guint red, guint green, guint blue) {
	color -> red 		= red;
	color -> green 	=	green;
	color -> blue		= blue;
	color -> pixel	=	(gulong) ( color -> red * 65536 + 
															 color -> green * 256 + color -> blue );
															 
	return;
}

static gboolean Wallpaper( GtkWidget *widget, GtkWidget *wallpaper ) {
	
	float acorn, bcorn, size, ca, cb, zx, zy, xtemp;
	int i, j, count;
	
	GdkGC *gc = gdk_gc_new ( widget -> window );
	GdkColor color;
	
	acorn = atof( gtk_entry_get_text( GTK_ENTRY( corna_text) ) );
	bcorn = atof( gtk_entry_get_text( GTK_ENTRY( cornb_text) ) );
	size 	= atof( gtk_entry_get_text( GTK_ENTRY( side_text ) ) );

	for ( i = 0; i < SIZE; i++ ) {
		for ( j = 0; j < SIZE; j++ ) {
		
			count = 0;
			ca = acorn + i * size / SIZE;
			cb = bcorn + i * size / SIZE;		
			zx = 0;
			zy = 0;
			
			while ( ( count < MaxCount ) && (( zx * zx) + (zy * zy)) <= 4 ) {
				count = count + 1;
				
				xtemp = ( zx * zx ) - ( zy * zy );
				
				zy = 2 * zx * zy + cb;
				zx = xtemp + ca;
			}
			
			if ( count >= 3 * MaxCount/4 && count < MaxCount )
				setcolor ( &color, (guint)( 65535 ), (guint)(0), (guint)(0));
			else if ( count >= 2 * MaxCount/4 && count < 3 * MaxCount/4 )
				setcolor ( &color, (guint)( 0 ), (guint) ( 65535 ), (guint) ( 0 ));
			else if ( count >= 1 * MaxCount/4 && count < 2 * MaxCount/4 )
				setcolor ( &color, (guint)( 0 ), (guint) ( 0 ), (guint) (65535));
			else if ( count >= 0 * MaxCount/4 && count < 1 * MaxCount/4 )
				setcolor ( &color, (guint)( 65535 ), (guint) ( 65535 ), (guint) (0));
			if ( count == MaxCount )
				setcolor ( &color, (guint)( 0 ), (guint)( 0 ), (guint)( 0 ) );
			
			gdk_color_alloc ( gdk_window_get_colormap( widget -> window ), &color );
			gdk_gc_set_foreground ( gc, &color );
			gdk_draw_point ( wallpaper -> window, gc, i, j );
			
		}
	}
	
	return TRUE;
}

static void destroy( GtkWidget *widget, gpointer data )
{
    gtk_main_quit ();
}


int main( int argc, char *argv[] ) {
	
	GtkWidget *window;
	GtkWidget *calc_button;
	GtkWidget *vbox1;
	GtkWidget *hbox1;
	GtkWidget *draw_area;
	
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	corna_text = gtk_entry_new();
	cornb_text = gtk_entry_new();
	side_text	 = gtk_entry_new();
	calc_button = gtk_button_new_with_label("Generate");
	
	draw_area	= gtk_drawing_area_new();
	gtk_widget_set_size_request( draw_area, SIZE, SIZE );
	
	vbox1	=	gtk_vbox_new ( FALSE, 0 );
	hbox1 = gtk_hbox_new ( FALSE, 0 );

	gtk_container_add ( GTK_CONTAINER(window), vbox1 );
	
	gtk_box_pack_start( GTK_BOX( vbox1 ), hbox1, TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( vbox1 ), draw_area, TRUE, TRUE, 0 );
		
	gtk_box_pack_start( GTK_BOX( hbox1 ), corna_text, TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( hbox1 ), cornb_text, TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( hbox1 ), side_text, 	TRUE, TRUE, 0 );
	gtk_box_pack_start( GTK_BOX( hbox1 ), calc_button, TRUE, TRUE, 0 );
	
	g_signal_connect ( G_OBJECT ( window ), "delete_event", G_CALLBACK(destroy), NULL);
	g_signal_connect ( G_OBJECT ( calc_button ), "clicked", G_CALLBACK(Mandlebrot), draw_area);
	
	gtk_widget_show_all ( window );
	gtk_main();
		
	return (0);
}
