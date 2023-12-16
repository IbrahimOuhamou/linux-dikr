//بسم الله الرحمن الرحيم

#include <gtk-4.0/gtk/gtk.h>

//
GtkWidget* window = NULL;

struct dikr_list_dikr_t
{
    int id;
    /*
     * const char* hadith; //might have the hadith and not just the dikr
    */
    int repeat_count;
    const char* dikr;
    /*
     * const char* translation; char language[2];
     * or
     * const char* hadith
    */
};

struct dikr_list_list_t
{
    int size;
    //the name of the list
    const char* name;
    //should contain the adkar
    struct dikr_list_dikr_t data[];
};

struct dikr_list_list_t dikr_list;

int dikr_list_init_list(struct dikr_list_list_t* dikr_list);
int dikr_list_menu(GtkWidget* button, gpointer data);

void activate(GtkApplication* app, gpointer data);

int main()
{
    g_print("in the name of Allah\n");

    GtkApplication* app = gtk_application_new("BismiAllah.BismiAllah.BismiAllah", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    return status;
}

void activate(GtkApplication* app, gpointer data)
{
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "daily dikr");

    dikr_list_menu(NULL, NULL);

    gtk_widget_show(window);
}

int dikr_list_init_list(struct dikr_list_list_t* dikr_list)
{
}

int dikr_list_menu(GtkWidget* button, gpointer data)
{
    GtkWidget* grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_FILL);
    
    GtkWidget* button_morning = gtk_button_new_with_label("الصباح");
    gtk_grid_attach(GTK_GRID(grid), button_morning, 0, 0, 1, 1);
    GtkWidget* button_evening = gtk_button_new_with_label("المساء");
    gtk_grid_attach(GTK_GRID(grid), button_evening, 0, 1, 1, 1);
    GtkWidget* button_night = gtk_button_new_with_label("الليل");
    gtk_grid_attach(GTK_GRID(grid), button_night, 0, 2, 1, 1);
    
    gtk_window_set_child(GTK_WINDOW(window), grid);
    return 0;
}

