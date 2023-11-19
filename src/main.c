//بسم الله الرحمن الرحيم

#include <gtk-4.0/gtk/gtk.h>

const char* dikr_list_morning[] = {"أصبحنا على فطرة الإسلام و على كلمة الإخلاص و على دين نبينا محمد صلى الله عليه و سلم و على ملة أبينا إبراهيم حنيفا مسلما و ما كان من المشركين"};

void activate(GtkApplication* app, gpointer data);

//selects dikr list ('dikr_lis_morning' for now)
void dikr_list_select(GtkWidget* widget, gpointer data);
void dikr_list_menu(GtkWidget* widget, gpointer data);

static GtkWidget* window;

int main(int argc, char* argv[])
{
    gtk_init();
    g_print("in the name of Allah\n");

    GtkApplication* app = gtk_application_new("BismiAllah.BismiAllah.BismiAllah", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

void activate(GtkApplication* app, gpointer data)
{
    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "desktop dikr");

    dikr_list_menu(NULL, NULL);

    gtk_widget_show(window);
}

void dikr_list_menu(GtkWidget* widget, gpointer data)
{
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget* button_morning_dikr = gtk_button_new_with_label("morning");
    g_signal_connect(button_morning_dikr, "clicked", G_CALLBACK(dikr_list_select), NULL);

    gtk_box_append(GTK_BOX(box), button_morning_dikr);
}

void dikr_list_select(GtkWidget* widget, gpointer data)
{
    //for now will select morning dikr only
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* label = gtk_label_new(dikr_list_morning[0]);
    gtk_box_append(GTK_BOX(box), label);

    gtk_window_set_child(GTK_WINDOW(window), box);
}

