#include "GUI.h"

AppConfiguration::AppConfiguration(int main_window_width) :
        main_window_w(main_window_width)
{
    // setting sizes
    main_window_h = main_window_w * 0.66;
    spacing = main_window_w * 0.025;
    input_widget_h = main_window_w/9;
    input_widget_w = main_window_w - 3*spacing -
        input_widget_h;
    output_widget_w = main_window_w - 2*spacing;
    output_widget_h = main_window_h - 3*spacing -
        input_widget_h;
    button_w = input_widget_h;
    button_h = input_widget_h;

    // setting coordinates
    input_widget_x = spacing;
    input_widget_y = spacing*2 + output_widget_h;
    output_widget_x = spacing;
    output_widget_y = spacing;
    button_x = 2*spacing + input_widget_w;
    button_y = input_widget_y;
}

void send_message_callback(Fl_Widget* w, void* data)
{
    AppComponents* components = (AppComponents*)data;

    char* s = components->input_widget->buffer()->text();
    int size = components->input_widget->buffer()->length();

    components->output_widget->buffer()->append(s);

    fputs(s, stdout);
    fflush(stdout);

    components->input_widget->take_focus();
    components->input_widget->buffer()->text("");
}


AppComponents::AppComponents(AppConfiguration s)
{
     // main window
    main_window = new Fl_Window(s.main_window_w, s.main_window_h,
        "Chat with");

    //widget for input
    input_widget = new Fl_Text_Editor(s.input_widget_x,
    s.input_widget_y, s.input_widget_w, s.input_widget_h, "");

    Fl_Text_Buffer* input_Buffer = new Fl_Text_Buffer;
    input_widget->buffer(input_Buffer);
    input_widget->textsize(Fl_Fontsize(12));


    //button for sending message
    send_button = new Fl_Button(s.button_x, s.button_y,
        s.button_w, s.button_h, "Send!");

    send_button->callback(send_message_callback, this);


    //widget for output
    output_widget = new Fl_Text_Display(s.output_widget_x,
        s.output_widget_y, s.output_widget_w, s.output_widget_h, "");

    output_widget->textsize(Fl_Fontsize(12));

    Fl_Text_Buffer* output_buffer = new Fl_Text_Buffer;
    output_widget->buffer(output_buffer);

    main_window->end();
    main_window->show();
}