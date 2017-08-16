#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <gtk/gtk.h>

#include "notebook_example.h"

static const gchar button_style[] =
		"* {\n"
#if !GTK_CHECK_VERSION (3, 20, 0)
		"	-GtkButton-default-border : 0;\n"
		"	-GtkButton-default-outside-border : 0;\n"
		"	-GtkButton-inner-border: 0;\n"
		"	-GtkWidget-focus-line-width : 0;\n"
		"	-GtkWidget-focus-padding : 0;\n"
#endif
		"	padding: 0;\n"
"}";

void add_new_tab(GtkNotebook * p_notebook)
{
	/* Icon */
	GtkWidget * p_icon  = gtk_image_new_from_icon_name("text-x-generic", GTK_ICON_SIZE_MENU);
	
	/* Label */
	GtkWidget * p_label = gtk_label_new("New Tab");
	gtk_widget_set_margin_start((GtkWidget*) p_label, 0);
	gtk_widget_set_margin_end((GtkWidget*) p_label, 0);
	gtk_widget_set_margin_top((GtkWidget*) p_label, 0);
	gtk_widget_set_margin_bottom((GtkWidget*) p_label, 0);
	
	/* Close button */
	GtkWidget * p_button = gtk_button_new_from_icon_name ("window-close", GTK_ICON_SIZE_MENU);
	GtkCssProvider *css;
	GError *error = NULL;
	
	gtk_button_set_relief((GtkButton*) p_button, GTK_RELIEF_NONE);
	
	/* make it as small as possible */
	css = gtk_css_provider_new ();
	if (gtk_css_provider_load_from_data (css, button_style,
	                                     -1, &error))
	{
		GtkStyleContext *context;

		context = gtk_widget_get_style_context (GTK_WIDGET (p_button));
		gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (css),
			                        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		g_object_unref (css);
	}
	else
	{
		g_warning ("%s", error->message);
		g_error_free (error);
	}
	
	/* Pack Icon, Label & Button into a Box */
	GtkWidget * p_box   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
	
	gtk_box_pack_start((GtkBox*) p_box, (GtkWidget*) p_icon, TRUE, TRUE, 0);
	gtk_box_pack_start((GtkBox*) p_box, (GtkWidget*) p_label, TRUE, TRUE, 0);
	gtk_box_pack_start((GtkBox*) p_box, (GtkWidget*) p_button, TRUE, TRUE, 0);
	
	/* Need to show widgets in order for proper size allocation */
	gtk_widget_show((GtkWidget*) p_icon);
	gtk_widget_show((GtkWidget*) p_label);
	gtk_widget_show((GtkWidget*) p_button);
	gtk_widget_show((GtkWidget*) p_box);
	
	/* Scintilla window */
	GtkWidget * p_editor = gtk_label_new("Tab contents");
	
	/* Append and show tab */
	gtk_notebook_append_page(p_notebook, p_editor, (GtkWidget*) p_box);
	gtk_notebook_set_show_tabs(p_notebook, TRUE);
	
	gtk_widget_show_all((GtkWidget*) p_notebook);
	
	printf("Number of pages: %d\n", gtk_notebook_get_n_pages(p_notebook));
}

