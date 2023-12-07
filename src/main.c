//بسم الله الرحمن الرحيم

#include <gtk-4.0/gtk/gtk.h>

int dikr_list_selected_id = 0;


const char* dikr_list_morning[] = {
    "أصبحنا على فطرة الإسلام و على كلمة الإخلاص و على دين نبينا محمد صلى الله عليه و سلم و على ملة أبينا إبراهيم حنيفا مسلما و ما كان من المشركين",
    "أصبحت أثني عليك حمدا, و أشهد أنه لا إله إلا أنت"
};

const char* dikr_list_evening[] = {
    "رضيت بالله ربا و بالإسلام دينا و بمحمد نبيا و رسولا"
};

const char** dikr_list_selected_list = dikr_list_morning;

void activate(GtkApplication* app, gpointer data);

//selects dikr list ('dikr_lis_morning' for now)
void dikr_list_select_list(GtkWidget* widget, gpointer data);
void dikr_list_menu(GtkWidget* widget, gpointer data);
void dikr_list_select_next(GtkWidget* widget, gpointer data);
void dikr_list_select_prev(GtkWidget* widget, gpointer data);

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

    dikr_list_selected_id = 0;

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget* button_morning_dikr = gtk_button_new_with_label("morning");
    g_signal_connect(button_morning_dikr, "clicked", G_CALLBACK(dikr_list_select_list), dikr_list_morning);

    GtkWidget* button_evening_dikr = gtk_button_new_with_label("evening");
    g_signal_connect(button_evening_dikr, "clicked", G_CALLBACK(dikr_list_select_list), dikr_list_evening);

    gtk_box_append(GTK_BOX(box), button_morning_dikr);
    gtk_box_append(GTK_BOX(box), button_evening_dikr);
}

void dikr_list_select_list(GtkWidget* widget, gpointer data)
{
    if(NULL == dikr_list_selected_list)
    {
        dikr_list_menu(NULL, NULL);
        return;
    }
    //for now will select morning dikr only
    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_valign(box, GTK_ALIGN_FILL);
    gtk_widget_set_halign(box, GTK_ALIGN_FILL);
    //gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    GtkWidget* label = gtk_label_new(dikr_list_morning[dikr_list_selected_id]);
    gtk_box_append(GTK_BOX(box), label);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);


    GtkWidget* box_bottom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box_bottom);

    if(dikr_list_selected_id < (sizeof(dikr_list_morning) / sizeof(dikr_list_morning[0])))
    {
        GtkWidget* button_dikr_list_select_next = gtk_button_new_with_label("<-");
        g_signal_connect(button_dikr_list_select_next, "clicked", G_CALLBACK(dikr_list_select_next), NULL);
        gtk_box_append(GTK_BOX(box_bottom), button_dikr_list_select_next);
    }

    GtkWidget* button_dikr_list_select_home = gtk_button_new_with_label("HOME");
    g_signal_connect(button_dikr_list_select_home, "clicked", G_CALLBACK(dikr_list_menu), NULL);
    gtk_box_append(GTK_BOX(box_bottom), button_dikr_list_select_home);

    if(0 < dikr_list_selected_id)
    {
        GtkWidget* button_dikr_list_select_prev = gtk_button_new_with_label("->");
        g_signal_connect(button_dikr_list_select_prev, "clicked", G_CALLBACK(dikr_list_select_prev), NULL);
        gtk_box_append(GTK_BOX(box_bottom), button_dikr_list_select_prev);
    }
    gtk_window_set_child(GTK_WINDOW(window), box);
}

void dikr_list_select_next(GtkWidget* widget, gpointer data)
{
    if(dikr_list_selected_id+1 >= (sizeof(dikr_list_morning) / sizeof(dikr_list_morning[0])))
    {
        return;
    }

    dikr_list_selected_id += 1;
    dikr_list_select_list(NULL, data);
}

void dikr_list_select_prev(GtkWidget* widget, gpointer data)
{
    if(0 == dikr_list_selected_id)
    {
        return;
    }

    dikr_list_selected_id-=1;
    dikr_list_select_list(NULL, NULL);
}

