#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "header.h"

GtkWidget *label;

void button_clicked(GtkWidget *widget, gpointer data) {
    g_print("%s\n", (char*) data);
    char * aux = malloc(256*sizeof(char)); 
    //const char * str = (char *) gtk_label_get_text((GtkLabel *) label);
    //strcat(aux,str);
    //strcat(aux,(char*)data);
    gtk_label_set_text((GtkLabel *)label,(char *) data);
}



int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    
    GtkWidget *button;
    gchar *values[12] = { "1", "2 abc", "3 def","4 ghi", "5 jkl", "6 mno","7 pqrs", "8 tuv", "9 wxyz", "* #","0", "SPACE"};

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 0);
    gtk_window_set_title(GTK_WINDOW(window), "T9");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    label = gtk_label_new("label");

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    int i = 0;
    int j = 0;
    int pos = 0;
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 3, 1);
    for (i=1; i < 5; i++) {
        for (j=0; j < 3; j++) {
            button = gtk_button_new_with_label(values[pos]);
            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
            g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(button_clicked),values[pos]);
            pos++;
        }
    }
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}