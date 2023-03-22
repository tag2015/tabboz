// generated by Fast Light User Interface Designer (fluid) version 1.0308

#include "GUIScooter.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "GUITabboz.h"
#include "GUIConcessionario.h"
#include "GUIElaborare.h"
#include "../zarrosim.h"
#include "../dialogs.h"
#include "../sound.h"
#include "../sharedimg.h"
#include "../calendario.h"
#include "../scooter.h"

Fl_Double_Window *win_scooter=(Fl_Double_Window *)0;

static void cb_Concessionario(Fl_Button*, void*) {
  if (x_vacanza != 2) {
  GUIConcessionario();
  win_conce->show();
  win_scooter->deactivate();
}else {
  MsgIcona(ICONA_AVVISO);
  fl_message_title("Concessionario chiuso");
  fl_alert("Oh, tip%c... oggi il concessionario è chiuso...",ao);
};
}

Fl_Button *scooter_btn_usa=(Fl_Button *)0;

static void cb_scooter_btn_usa(Fl_Button* o, void*) {
  if(ParcheggiaScooter())
  o->label("Usa scooter");
else
  o->label("Parcheggia scooter");
o->redraw();
AggiornaScooter();
}

static void cb_Fai(Fl_Button*, void*) {
  FaiBenza();
}

static void cb_Elabora(Fl_Button*, void*) {
  fl_message_title("Elabora scooter");
if (ScooterData.stato == -1000) {
  MsgIcona(ICONA_DOMANDA);
  fl_alert("Mi spieghi come fai a elaborare lo scooter se non lo hai ???");
  return;
}

if (x_vacanza != 2) {
  GUIElaborare();
  win_elabora->show();
  win_scooter->deactivate();
}else {
  MsgIcona(ICONA_AVVISO);
  fl_message_title("Meccanico chiuso");
  fl_alert("Oh, tip%c... oggi il meccanico è chiuso...",ao);
};
}

static void cb_Ripara(Fl_Button*, void*) {
  RiparaScooter();
}

Fl_Output *sco_txt_nome=(Fl_Output *)0;

Fl_Output *sco_txt_speed=(Fl_Output *)0;

Fl_Output *sco_txt_cc=(Fl_Output *)0;

Fl_Output *sco_txt_stato=(Fl_Output *)0;

Fl_Output *sco_txt_benza=(Fl_Output *)0;

Fl_Value_Output *sco_val_soldi=(Fl_Value_Output *)0;

static void cb_sco_val_soldi(Fl_Value_Output* o, void*) {
  o->value(CALCSOLDI(Soldi));
}

static void cb_(Fl_Return_Button*, void*) {
  win_principale->activate();
AggiornaPrincipale();
win_scooter->hide();
}

#include <FL/Fl_Image.H>
static const unsigned char idata_scooter[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,
255,255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,255,96,96,64,255,160,160,128,255,255,0,0,255,0,0,0,255,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,255,0,0,255,
255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,255,0,0,0,255,96,96,64,255,96,96,64,255,0,0,0,255,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,255,0,
0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,
96,96,64,255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,255,0,0,255,
255,0,0,255,255,0,0,255,96,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
255,255,255,255,255,255,255,255,255,160,160,128,255,255,0,0,255,255,0,0,255,96,
0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,255,
255,255,255,255,255,255,255,255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,
0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,
0,0,0,255,255,0,0,255,96,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,
255,255,255,255,255,255,0,0,255,255,0,0,255,255,0,0,255,96,0,0,255,0,0,0,255,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,
96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,255,
0,0,0,255,0,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,96,0,0,255,0,0,0,255,
0,0,0,0,0,0,0,255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,
255,255,0,0,255,96,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,255,255,0,0,255,255,0,
0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,
255,0,0,255,255,0,0,255,96,0,0,255,0,0,0,255,0,0,0,255,96,96,64,255,96,96,64,
255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,96,0,0,255,96,0,0,255,0,0,0,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,255,
0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,
255,255,0,0,255,255,0,0,255,255,0,0,255,160,160,128,255,160,160,128,255,255,0,
255,255,0,0,0,255,0,0,0,255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,
255,0,0,255,96,0,0,255,96,0,0,255,255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,
255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,
255,255,0,0,255,255,0,0,255,255,0,0,255,96,0,0,255,0,0,0,255,0,0,0,255,96,96,64,
255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,96,0,0,255,255,0,0,255,255,0,0,255,
255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,255,0,0,
255,96,0,0,255,96,0,0,255,0,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,
255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,96,0,0,255,0,0,
0,255,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,
255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,255,
255,0,0,255,96,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,
64,255,160,160,128,255,160,160,128,255,0,0,0,255,0,0,0,255,255,0,0,255,255,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,255,0,0,255,96,0,0,
255,96,0,0,255,0,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,
255,0,0,0,255,96,96,64,255,0,0,0,255,0,0,0,255,96,0,0,255,0,0,0,255,0,0,0,0,0,0,
0,255,96,96,64,255,96,96,64,255,96,96,64,255,160,160,128,255,96,96,64,255,96,
96,64,255,0,0,0,255,0,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,
255,0,0,255,0,0,0,255,0,0,0,255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,
255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,
160,160,128,255,160,160,128,255,96,96,64,255,96,96,64,255,0,0,0,255,0,0,0,255,
255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,
0,255,96,96,64,255,255,0,0,255,255,0,0,255,255,0,0,255,160,160,128,255,160,
160,128,255,160,160,128,255,160,160,128,255,160,160,128,255,96,96,64,255,96,96,
64,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,
160,160,128,255,96,96,64,255,96,96,64,255,96,96,64,255,0,0,0,255,0,0,0,255,255,
0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,
255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,255,96,96,
64,255,96,96,64,255,160,160,128,255,160,160,128,255,96,96,64,255,96,96,64,255,
0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,96,96,
64,255,96,96,64,255,96,96,64,255,96,96,64,255,0,0,0,255,0,0,0,255,255,0,0,255,
255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,255,255,0,0,
255,255,0,0,255,255,0,0,255,0,0,0,255,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,
255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,
255,0,0,0,255,0,0,0,255,96,0,0,255,96,0,0,255,96,0,0,255,96,0,0,255,96,0,0,255,
96,0,0,255,96,0,0,255,96,0,0,255,96,0,0,255,96,0,0,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,255,96,96,64,255,96,96,64,255,96,96,64,255,96,96,64,255,0,0,0,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,
0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_scooter() {
  static Fl_Image *image = new Fl_RGB_Image(idata_scooter, 32, 32, 4, 0);
  return image;
}

Fl_Double_Window* GUIScooter() {
  { win_scooter = new Fl_Double_Window(510, 240, "Scooter");
    win_scooter->labelfont(1);
    win_scooter->labelsize(12);
    win_scooter->hotspot(win_scooter);
    { Fl_Button* o = new Fl_Button(10, 10, 240, 35, "Concessionario");
      o->callback((Fl_Callback*)cb_Concessionario);
    } // Fl_Button* o
    { scooter_btn_usa = new Fl_Button(10, 82, 240, 35, "Parcheggia scooter");
      scooter_btn_usa->callback((Fl_Callback*)cb_scooter_btn_usa);
      if(ScooterData.attivita==4) { scooter_btn_usa->label("Usa scooter"); scooter_btn_usa->redraw(); }
    } // Fl_Button* scooter_btn_usa
    { Fl_Button* o = new Fl_Button(10, 122, 240, 35, "Fai benza");
      o->callback((Fl_Callback*)cb_Fai);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(260, 165, 240, 30, "Elabora Scooter");
      o->callback((Fl_Callback*)cb_Elabora);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(260, 200, 240, 30, "Ripara Scooter");
      o->callback((Fl_Callback*)cb_Ripara);
    } // Fl_Button* o
    { Fl_Group* o = new Fl_Group(260, 10, 240, 150);
      o->box(FL_SHADOW_BOX);
      o->labelfont(1);
      o->labelsize(12);
      { Fl_Output* o = sco_txt_nome = new Fl_Output(275, 20, 210, 25);
        sco_txt_nome->box(FL_FLAT_BOX);
        sco_txt_nome->color(FL_BACKGROUND_COLOR);
        sco_txt_nome->textfont(1);
        sco_txt_nome->textsize(12);
        o->clear_visible_focus();
      } // Fl_Output* sco_txt_nome
      { Fl_Output* o = sco_txt_speed = new Fl_Output(350, 50, 130, 25, "Velocit\303\240 max ");
        sco_txt_speed->box(FL_EMBOSSED_BOX);
        sco_txt_speed->labelsize(12);
        o->clear_visible_focus();
      } // Fl_Output* sco_txt_speed
      { Fl_Output* o = sco_txt_cc = new Fl_Output(350, 75, 130, 25, "Cilindrata ");
        sco_txt_cc->box(FL_EMBOSSED_BOX);
        sco_txt_cc->labelsize(12);
        o->clear_visible_focus();
      } // Fl_Output* sco_txt_cc
      { Fl_Output* o = sco_txt_stato = new Fl_Output(350, 100, 130, 25, "Efficienza ");
        sco_txt_stato->box(FL_EMBOSSED_BOX);
        sco_txt_stato->labelsize(12);
        o->clear_visible_focus();
      } // Fl_Output* sco_txt_stato
      { Fl_Output* o = sco_txt_benza = new Fl_Output(350, 125, 130, 25, "Benzina ");
        sco_txt_benza->box(FL_EMBOSSED_BOX);
        sco_txt_benza->labelsize(12);
        o->clear_visible_focus();
      } // Fl_Output* sco_txt_benza
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(10, 180, 240, 50);
      o->box(FL_EMBOSSED_FRAME);
      { Fl_Value_Output* o = sco_val_soldi = new Fl_Value_Output(105, 192, 75, 25, "Soldi L.");
        sco_val_soldi->box(FL_FLAT_BOX);
        sco_val_soldi->labelfont(2);
        sco_val_soldi->labelsize(12);
        sco_val_soldi->step(1);
        sco_val_soldi->value(1e+08);
        sco_val_soldi->textfont(1);
        sco_val_soldi->callback((Fl_Callback*)cb_sco_val_soldi);
        if (euro) o->label("Soldi  €");
      } // Fl_Value_Output* sco_val_soldi
      { Fl_Return_Button* o = new Fl_Return_Button(185, 185, 60, 40);
        o->callback((Fl_Callback*)cb_);
        o->align(Fl_Align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE));
        o->image(ImgExit);
      } // Fl_Return_Button* o
      { Fl_Box* o = new Fl_Box(15, 184, 40, 40);
        o->image( image_scooter() );
      } // Fl_Box* o
      o->end();
    } // Fl_Group* o
    AggiornaScooter();
    win_scooter->set_modal();
    win_scooter->size_range(510, 240, 510, 240);
    win_scooter->end();
  } // Fl_Double_Window* win_scooter
  return win_scooter;
}
