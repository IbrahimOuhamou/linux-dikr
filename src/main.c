//بسم الله الرحمن الرحيم

#include <gtk-4.0/gtk/gtk.h>

struct dikr_list_dikr_t
{
    int id;
    /*
     * const char* hadith; //might have the hadith and not just the dikr
     *
    */
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

int main()
{
    g_print("in the name of Allah\n");

    
}

