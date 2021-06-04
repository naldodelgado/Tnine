/* COMO COMPILAR:
    -> gcc -o tnine tnine.c $(pkg-config --cflags gtk+-3.0 pkg-config --libs gtk+-3.0)
                                    ou
    -> gcc -o tnine tnine.c 'pkg-config --cflags gtk+-3.0 pkg-config --libs gtk+-3.0'
*/

#include <gtk/gtk.h>
#include "hash.c"

char *values[12] = { "1", "2 abc", "3 def","4 ghi", "5 jkl", "6 mno","7 pqrs", "8 tuv", "9 wxyz", "* #","0", "SPACE"};

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("%s\n", (char*)data);
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Window");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_widget_destroy), NULL);

    grid = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(window), grid);

    int pos=0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            button = gtk_button_new_with_label(values[pos]);
            g_signal_connect (button,"clicked",G_CALLBACK(print_hello),values[pos]);
            gtk_grid_attach(GTK_GRID(grid),button,j,i,1,1);
            pos++;
        }
    }

    gtk_widget_show_all(window);
}

int main(int argc, char** argv) {
    GtkApplication *app;
    int status;

    init_hash();

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);

    return status;
}