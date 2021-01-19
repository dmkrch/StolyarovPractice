#include "GUI.h"

int main()
{
    AppConfiguration s(500);
    AppComponents* components = new AppComponents(s);

    return Fl::run();
}