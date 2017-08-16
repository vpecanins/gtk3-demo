#ifndef _TREEVIEW_EXAMPLE_H
#define _TREEVIEW_EXAMPLE_H

#include <gtk/gtk.h>

void treeview_example_init(GtkTreeView * p_treeview);
void treeview_example_populate(GtkTreeStore *p_treestore, char * directory);

#endif
