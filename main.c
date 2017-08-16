#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <gtk/gtk.h>

#include "treeview_example.h"
#include "notebook_example.h"

static GtkBuilder *builder;
static GObject *window;

static GtkTreeView *p_treeview;
static GtkNotebook *p_notebook;

void button1_clicked (GtkWidget *widget, gpointer data)
{
	(void) widget;
	(void) data;
	g_print ("Hello World! Button 1 has been clicked.\n");
}

void button2_clicked (GtkWidget *widget, gpointer data)
{
	(void) widget;
	(void) data;
	
	static int clicktimes = 0;
	
	clicktimes++;
	
	g_print ("Button 2 has been clicked. %d times.\n", clicktimes);
}

void button3_clicked (GtkWidget *widget, gpointer data)
{
	(void) widget;
	(void) data;
	g_print ("Hello World! Button 3 has been clicked.\n");
}

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	/* Construct a GtkBuilder instance and load our UI description */
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "example.glade", NULL);

	/* Connect builder signals, needs to be compiled with -rdynamic */
	gtk_builder_connect_signals(builder, NULL);

	/* Connect signal handlers to the constructed widgets. */
	window = gtk_builder_get_object (builder, "window");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	/* Tabs */
	p_notebook = (GtkNotebook*) gtk_builder_get_object(builder, "notebook1");
	add_new_tab(p_notebook);
	add_new_tab(p_notebook);
	add_new_tab(p_notebook);
	
	/* Create tree store */
	p_treeview = (GtkTreeView*) gtk_builder_get_object(builder, "treeview1");

	treeview_example_init(p_treeview);

	gtk_main();

	return 0;
}

