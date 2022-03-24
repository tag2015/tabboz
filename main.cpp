#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>

#include "gui/GUITabboz.h"

int main(void)
{
	win_principale = GUITabboz();
	win_principale->show();
	return Fl::run();
}
