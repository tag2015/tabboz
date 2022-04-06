// generated by Fast Light User Interface Designer (fluid) version 1.0308

#include "GUINegoziLauncher.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "GUITabboz.h"
#include "GUINegozioVestiti1.h"
#include "../zarrosim.h"
#include "../calendario.h"
#include "../negozi.h"
#include "../sound.h"

Fl_Double_Window *win_negozi=(Fl_Double_Window *)0;

static void cb_Back(Fl_Return_Button*, void*) {
  win_principale->activate();
win_negozi->hide();
}

static void cb_Bau(Fl_Button*, void*) {
  if (x_vacanza != 2) {
  GUINegozioVestiti_1();
  win_vestiti_1->show();
  win_negozi->hide();
  if(sound_active) TabbozPlaySound(204);
}else {
  fl_message_title("Negozio chiuso");
  fl_alert("Oh, tip%c... i negozi sono chiusi di festa...",ao);
};
}

static void cb_Tabaccaio(Fl_Button*, void*) {
  if (x_vacanza != 2) {
//  if(!win_vestiti_1)
//    GUINegozioVestiti_1();
//  win_vestiti_1->show();
//  win_negozi->hide();
  if(sound_active) TabbozPlaySound(204);
}else {
  fl_message_title("Tabaccaio chiuso");
  fl_alert("Rimani fiss%c a guardare la saracinesca del tabaccaio irrimediabilmente chiusa...",ao);
};
}

Fl_Double_Window* GUINegoziLauncher() {
  { win_negozi = new Fl_Double_Window(395, 215, "Negozi");
    win_negozi->color(FL_LIGHT3);
    win_negozi->labelfont(1);
    win_negozi->labelsize(12);
    win_negozi->hotspot(win_negozi);
    { Fl_Return_Button* o = new Fl_Return_Button(325, 155, 60, 50, "Back");
      o->callback((Fl_Callback*)cb_Back);
    } // Fl_Return_Button* o
    { Fl_Group* o = new Fl_Group(10, 25, 180, 180, "Abbigliamento");
      o->box(FL_EMBOSSED_FRAME);
      o->labelfont(1);
      o->labelsize(12);
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { Fl_Button* o = new Fl_Button(15, 30, 170, 30, "Bau House");
        o->callback((Fl_Callback*)cb_Bau);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(15, 65, 170, 30, "Blue Rider");
        o->deactivate();
      } // Fl_Button* o
      { new Fl_Button(15, 100, 170, 30, "Zoccolaro");
      } // Fl_Button* o
      { new Fl_Button(15, 135, 170, 30, "Footsmocker");
      } // Fl_Button* o
      { new Fl_Button(15, 170, 170, 30, "Footsmocker II");
      } // Fl_Button* o
      { new Fl_Button(15, 135, 170, 30, "Footsmocker");
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(205, 25, 180, 75, "Altri Negozi");
      o->box(FL_EMBOSSED_FRAME);
      o->labelfont(1);
      o->labelsize(12);
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { Fl_Button* o = new Fl_Button(210, 30, 170, 30, "Tabaccaio");
        o->callback((Fl_Callback*)cb_Tabaccaio);
      } // Fl_Button* o
      { new Fl_Button(210, 65, 170, 30, "Telefonia");
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    win_negozi->set_modal();
    win_negozi->size_range(395, 215, 395, 215);
    win_negozi->end();
  } // Fl_Double_Window* win_negozi
  return win_negozi;
}
