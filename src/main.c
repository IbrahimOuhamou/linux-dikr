//بسم الله الرحمن الرحيم

#include <string.h>
#include <strings.h>
#include <gtk-4.0/gtk/gtk.h>

enum {DIKR_LIST_DIKR_SELECT_NEXT, DIKR_LIST_DIKR_SELECT_PREV, DIKR_LIST_DIKR_COUNT_UP};
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
    struct dikr_list_dikr_t* data;
};

//will be turned into a pointer by the will of Allah
struct dikr_list_list_t* dikr_list_list;
struct dikr_list_dikr_t dikr_list_dikr = {.id = 0, .repeat_count = 3, .dikr="لا إله إلا الله"};
int repeat_count = 0;
int current_dikr = 0;

//int dikr_list_init_list(struct dikr_list_list_t* dikr_list);
void dikr_list_menu(GtkWidget* button, gpointer data);
void dikr_list_show_dikr(GtkWidget* button, gpointer data);
void dikr_list_navigate_list(GtkWidget* button, int flags);
void dikr_list_select_list(GtkWidget* button, struct dikr_list_list_t* list);
//when the state of the app is updated (i.e changed dikr, dikr button pressed, dikr list selected, changed or removed)
//void dikr_list_state_updated();

void activate(GtkApplication* app, gpointer data);

//temp vars
struct dikr_list_list_t* temp_list = NULL;

int main()
{
    g_print("in the name of Allah\n");

    struct dikr_list_dikr_t arr[3];
    arr[0].id=0; arr[0].dikr="بسم الله"; arr[0].repeat_count = 3;
    arr[1].id=1; arr[1].dikr="لا إله ﻹلا الله"; arr[1].repeat_count = 3;
    arr[2].id=2; arr[2].dikr="الله أكبر"; arr[2].repeat_count = 3;
    struct dikr_list_list_t dikr_list_list_local = {.size = sizeof(arr)/sizeof(arr[0]), .name="BismiAllah", .data = arr};
    temp_list = &dikr_list_list_local;

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

void dikr_list_menu(GtkWidget* button, gpointer data)
{
    dikr_list_list = NULL; current_dikr = 0; repeat_count = 0;
    GtkWidget* grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_FILL);
    
    GtkWidget* button_morning = gtk_button_new_with_label("الصباح");
    g_signal_connect(button_morning, "clicked", G_CALLBACK(dikr_list_select_list), temp_list);
    gtk_grid_attach(GTK_GRID(grid), button_morning, 0, 0, 1, 1);
    GtkWidget* button_evening = gtk_button_new_with_label("المساء");
    gtk_grid_attach(GTK_GRID(grid), button_evening, 0, 1, 1, 1);
    GtkWidget* button_night = gtk_button_new_with_label("الليل");
    gtk_grid_attach(GTK_GRID(grid), button_night, 0, 2, 1, 1);
    
    gtk_window_set_child(GTK_WINDOW(window), grid);
}

void dikr_list_select_list(GtkWidget* button, struct dikr_list_list_t* list)
{
    if(NULL == list) {g_print("got {list} as NULL\n"); dikr_list_menu(NULL, NULL); return;}
    dikr_list_list = list;
    dikr_list_show_dikr(NULL, NULL);
}

void dikr_list_show_dikr(GtkWidget* button, gpointer data)
{
    if(NULL == dikr_list_list)
    {
        dikr_list_menu(NULL, NULL);
        return;
    }
    GtkWidget* grid = gtk_grid_new();
    gtk_widget_set_valign(grid, GTK_ALIGN_FILL);
    gtk_widget_set_halign(grid, GTK_ALIGN_FILL);

    GtkWidget* button_menu = gtk_button_new_with_label("الرئيسية");
    g_signal_connect(button_menu, "clicked", G_CALLBACK(dikr_list_select_list), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_menu, 0, 0, 1, 1);

    GtkWidget* label = gtk_label_new(dikr_list_list->data[current_dikr].dikr);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 3, 3);

    GtkWidget* button_counter = gtk_button_new_with_label("counting");
    g_signal_connect(button_counter, "clicked", G_CALLBACK(dikr_list_navigate_list), DIKR_LIST_DIKR_COUNT_UP);
    gtk_grid_attach(GTK_GRID(grid), button_counter, 1, 4, 1, 1);

    gtk_window_set_child(GTK_WINDOW(window), grid);
}

void dikr_list_navigate_list(GtkWidget* button, int flags)
{
    switch(flags)
    {
        case DIKR_LIST_DIKR_COUNT_UP:
            if (dikr_list_list->data[current_dikr].repeat_count >= repeat_count+1)
            { 
                repeat_count+=1;
            }
        break;
        case DIKR_LIST_DIKR_SELECT_NEXT:
                current_dikr += 1;
        break;
        case DIKR_LIST_DIKR_SELECT_PREV:
            if (1 < repeat_count) current_dikr -= 1;
        break;
    };
    if(repeat_count >= dikr_list_list->data[current_dikr].repeat_count && dikr_list_list->size > current_dikr+1)
    {
        current_dikr+=1;
        repeat_count = 0;
    }
    /*
    printf("**********navigate list*************\n");
    printf("current_dikr == %d\n", current_dikr);
    printf("repeat_count == %d\n", repeat_count);
    printf("dikr_list_list->data[current_dikr].repeat_count == %d\n", dikr_list_list->data[current_dikr].repeat_count);
    printf("dikr_list_list->size == %d\n", dikr_list_list->size);
    */
    dikr_list_show_dikr(NULL, NULL);
}

