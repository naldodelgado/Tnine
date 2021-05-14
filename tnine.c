/* COMO COMPILAR:
    -> gcc -o tnine tnine.c $(pkg-config --cflags gtk+-3.0 pkg-config --libs gtk+-3.0)
                                    ou
    -> gcc -o tnine tnine.c 'pkg-config --cflags gtk+-3.0 pkg-config --libs gtk+-3.0'
*/


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "header.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *grid;
GtkWidget *button;
GtkWidget *label;

void button_clicked(GtkWidget *widget, gpointer data) {
    //g_print("%s\n", (char*) data);
    //char * aux = malloc(256*sizeof(char)); 
    char * str = (char *) gtk_label_get_text((GtkLabel *) label);
    puts(str);
    gtk_label_set_text((GtkLabel *)label,strcat(str, (char *) data));
}



int main(int argc, char *argv[]) {
    gchar *values[12] = { "1", "2 abc", "3 def","4 ghi", "5 jkl", "6 mno","7 pqrs", "8 tuv", "9 wxyz", "* #","0", "SPACE"};

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),0,0);   // tamanho da janela
    gtk_window_set_title(GTK_WINDOW(window), "T9");
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    label = gtk_label_new("label");
    gtk_fixed_put(GTK_FIXED(fixed),label,5,5);   // posição da label

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);    
    int pos = 0;
    for (int i=0; i < 4; i++) {
        for (int j=0; j < 3; j++) {
            button = gtk_button_new_with_label(values[pos]);
            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
            g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(button_clicked),values[pos]);
            pos++;
        }
    }
    gtk_fixed_put(GTK_FIXED(fixed),grid,5,27);   // posição da tabela
    
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}