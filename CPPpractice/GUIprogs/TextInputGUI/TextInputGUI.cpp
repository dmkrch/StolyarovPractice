#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>


// some window size values
enum 
{
    spacing = 20,
    input_h = 30, // input height 
    label_w = 50, // width of input label
    button_w = 100,
    button_h = 40
};

static void say_callback(Fl_Widget* w, void* user)
{
    printf("%s\n", ((Fl_Input*)user)->value());
    ((Fl_Input*)user)->take_focus();
}

static void clear_callback(Fl_Widget* w, void* user)
{
    ((Fl_Input*)user)->value("");
    ((Fl_Input*)user)->take_focus();
}

static void quit_callback(Fl_Widget* w, void* )
{
      exit(0);
}


int main()
{
    Fl_Window* win = new Fl_Window( button_w*3 + 4*spacing,
        3*spacing + button_h + input_h, "buttons demo");

    // creating input widget
    int inp_w = button_w * 3 + 2 * spacing - label_w;
    Fl_Input* inp = new Fl_Input(spacing + label_w, spacing, 
        inp_w, input_h, "Type:");


    inp->callback(say_callback, inp);

    // creating buttons
    Fl_Button* sayButton = new Fl_Button(spacing, spacing*2 + input_h,
         button_w, button_h, "Say it!");

    sayButton->callback(say_callback, inp);

    Fl_Button* clearButton = new Fl_Button(spacing*2 + button_w, 
    spacing*2 + input_h, button_w, button_h, "Clear");

    clearButton->callback(clear_callback, inp);

    Fl_Button* quitButton = new Fl_Button(3*spacing + button_w*2, 
        spacing*2 + input_h, button_w, button_h, "Quit");

    quitButton->callback(quit_callback, 0);


    win->end();
    win->show();
    return Fl::run();
}