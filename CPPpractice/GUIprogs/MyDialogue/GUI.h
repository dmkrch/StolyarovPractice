#ifndef GUI_H_SENTRY
#define GUI_H_SENTRY

#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <string.h>

class AppConfiguration
{
public:
    AppConfiguration(int main_window_width);

    int main_window_w;
    int main_window_h;
    int spacing;
    int input_widget_w;
    int input_widget_h;
    int output_widget_w;
    int output_widget_h;
    int button_w;
    int button_h;

    int input_widget_x;
    int input_widget_y;
    int output_widget_x;
    int output_widget_y;

    int button_x;
    int button_y;
};

class AppComponents
{
public:
    AppComponents(AppConfiguration s);

    Fl_Window* main_window;
    Fl_Text_Editor* input_widget;
    Fl_Text_Display* output_widget;
    Fl_Button* send_button;
};

void send_message_callback(Fl_Widget* w, void* data);

#endif