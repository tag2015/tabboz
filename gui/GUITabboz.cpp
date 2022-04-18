// generated by Fast Light User Interface Designer (fluid) version 1.0308

#include "GUITabboz.h"
#include <FL/fl_ask.H>
#include "../zarrosim.h"
#include "../calendario.h"
#include "../scuola.h"
#include "../lavoro.h"
#include "../negozi.h"
#include "GUIScuola.h"
#include "GUILavoro.h"
#include "GUIPalestra.h"
#include "GUITipa.h"
#include "GUICompagnia.h"
#include "GUIFamiglia.h"
#include "GUIScooter.h"
#include "GUINegoziLauncher.h"
#include "GUIDisco.h"
#include "GUITestbed.h"
int scelta_gui; 

Fl_Double_Window *win_principale=(Fl_Double_Window *)0;

Fl_Menu_Item menu_[] = {
 {"Menu", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Esci", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

static void cb_Scuola(Fl_Button*, void*) {
  GUITabbozScuola();
win_scuola->show();
win_principale->deactivate();
}

#include <FL/Fl_Image.H>
static const unsigned char idata_b_scuola[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,
0,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,255,0,0,0,255,170,170,170,255,170,170,170,255,0,0,0,255,0,0,0,
255,170,170,170,255,170,170,170,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,255,0,0,0,255,170,170,170,255,170,170,170,255,0,0,0,255,0,0,0,
255,170,170,170,255,170,170,170,255,0,0,0,255,0,0,0,255,101,152,101,255,0,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,255,170,170,170,255,170,170,170,255,0,0,0,
255,0,0,0,255,170,170,170,255,170,170,170,255,0,0,0,255,0,0,0,255,101,152,101,
255,0,0,0,255,0,0,0,255,170,170,170,255,170,170,170,255,0,0,0,255,0,0,0,255,0,0,
0,255,204,152,102,255,102,50,0,255,153,101,51,255,0,0,0,255,101,152,101,255,0,
50,50,255,101,152,101,255,0,0,0,255,0,0,0,255,170,170,170,255,170,170,170,255,
0,0,0,255,0,0,0,255,203,152,50,255,0,0,0,255,0,0,0,255,204,152,102,255,102,50,
0,255,153,101,51,255,0,0,0,255,101,152,101,255,0,50,50,255,0,0,0,255,170,170,
170,255,170,170,170,255,0,0,0,255,0,0,0,255,203,152,50,255,203,152,50,255,203,
152,50,255,0,0,0,255,0,0,0,255,204,152,102,255,102,50,0,255,153,101,51,255,0,0,
0,255,101,152,101,255,0,50,50,255,0,0,0,255,204,203,102,255,152,101,0,255,203,
152,50,255,203,152,50,255,203,152,50,255,203,152,50,255,203,152,50,255,0,0,0,
255,0,0,0,255,204,152,102,255,102,50,0,255,153,101,51,255,0,0,0,255,101,152,101,
255,0,50,50,255,0,0,0,255,204,203,102,255,152,101,0,255,203,152,50,255,203,152,
50,255,203,152,50,255,203,152,50,255,203,152,50,255,0,0,0,255,0,0,0,255,204,
152,102,255,102,50,0,255,153,101,51,255,0,0,0,255,101,152,101,255,0,50,50,255,0,
0,0,255,204,203,102,255,152,101,0,255,203,152,50,255,203,152,50,255,203,152,
50,255,203,152,50,255,203,152,50,255,0,0,0,255,0,0,0,255,204,152,102,255,102,
50,0,255,153,101,51,255,0,0,0,255,101,152,101,255,0,50,50,255,0,0,0,255,204,
203,102,255,152,101,0,255,203,152,50,255,203,152,50,255,203,152,50,255,203,152,
50,255,203,152,50,255,0,0,0,255,0,0,0,255,204,152,102,255,102,50,0,255,153,101,
51,255,0,0,0,255,101,152,101,255,0,50,50,255,0,0,0,255,204,203,102,255,152,101,
0,255,203,152,50,255,203,152,50,255,203,152,50,255,203,152,50,255,203,152,50,
255,0,0,0,255,0,0,0,255,204,152,102,255,102,50,0,255,153,101,51,255,0,0,0,255,
101,152,101,255,0,50,50,255,0,0,0,255,204,203,102,255,152,101,0,255,203,152,50,
255,203,152,50,255,203,152,50,255,203,152,50,255,203,152,50,255,0,0,0,255,0,0,0,
255,204,152,102,255,102,50,0,255,153,101,51,255,0,0,0,255,101,152,101,255,0,50,
50,255,0,0,0,255,204,203,102,255,152,101,0,255,203,152,50,255,203,152,50,255,
203,152,50,255,203,152,50,255,203,152,50,255,0,0,0,255,0,0,0,0,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,255,101,152,101,255,0,50,50,255,0,0,0,255,204,203,102,255,
152,101,0,255,203,152,50,255,203,152,50,255,203,152,50,255,203,152,50,255,0,0,0,
255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,
255,204,203,102,255,152,101,0,255,203,152,50,255,203,152,50,255,0,0,0,255,0,0,0,
255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_b_scuola() {
  static Fl_Image *image = new Fl_RGB_Image(idata_b_scuola, 16, 16, 4, 0);
  return image;
}

static void cb_Lavoro(Fl_Button*, void*) {
  GUILavoro();
win_lavoro->show();
win_principale->deactivate();
}

static void cb_Palestra(Fl_Button*, void*) {
  if (x_vacanza != 2) {
  GUITabbozPalestra();
  win_palestra->show();
  win_principale->deactivate();
}else {
  fl_message_title("Palestra chiusa");
  fl_alert("Il tuo fisico da atleta dovrà aspettare...\nvisto che oggi la palestra è chiusa...");
};
}

static void cb_Tipa(Fl_Button*, void*) {
  GUITipa();
win_tipa->show();
win_principale->deactivate();
}

static const unsigned char idata_b_tipa[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,98,139,199,232,97,139,199,247,95,136,198,234,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,119,149,205,228,83,132,197,255,89,132,197,234,0,0,0,0,
0,0,0,0,0,0,0,0,127,0,0,31,204,120,122,63,127,0,0,15,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,129,154,207,143,43,125,196,255,119,149,205,228,89,132,
197,234,0,0,0,0,215,124,126,63,221,107,107,227,231,85,86,255,226,52,50,255,222,
72,70,255,211,82,78,171,128,105,148,47,166,175,226,63,156,166,220,63,86,96,165,
31,105,126,191,63,90,149,209,255,33,91,174,191,0,0,0,0,0,0,0,0,234,147,150,47,
226,85,87,255,218,29,35,227,201,18,24,95,189,14,22,63,192,14,15,127,208,49,52,
255,163,109,139,255,77,127,207,255,72,124,204,255,76,130,204,255,91,141,206,239,
34,100,183,223,43,59,157,15,0,0,0,0,0,0,0,0,215,88,88,213,210,24,26,227,204,18,
28,15,0,0,0,0,0,0,0,0,143,160,213,159,89,127,203,255,213,50,47,255,128,21,48,
143,47,63,162,47,42,87,177,127,55,119,190,255,27,76,161,175,0,0,0,0,0,0,0,0,0,0,
0,0,210,59,59,255,187,12,14,111,0,0,0,0,0,0,0,0,105,115,183,47,98,129,199,255,
47,78,173,127,204,60,53,207,185,6,0,191,0,0,0,0,0,0,0,0,113,139,193,127,34,98,
173,255,33,47,137,47,0,0,0,0,0,0,0,0,203,40,39,255,165,5,8,79,0,0,0,0,0,0,0,0,
96,112,181,111,61,94,178,255,49,66,166,15,192,41,34,191,183,5,0,191,0,0,0,0,0,
0,0,0,33,47,137,15,61,111,179,255,26,67,153,127,0,0,0,0,0,0,0,0,191,30,28,239,
173,4,2,159,0,0,0,0,0,0,0,0,86,103,174,127,42,72,163,255,127,0,0,15,198,28,19,
239,174,3,0,159,0,0,0,0,0,0,0,0,0,0,0,0,49,95,168,255,27,65,151,127,0,0,0,0,0,0,
0,0,168,19,15,143,182,2,0,255,171,36,30,95,0,0,0,0,72,84,162,63,47,76,161,255,
114,34,72,207,199,11,1,255,145,0,0,63,0,0,0,0,0,0,0,0,46,70,153,95,33,87,165,
255,30,53,142,79,0,0,0,0,0,0,0,0,127,0,0,15,165,1,0,191,185,9,1,255,177,14,9,
223,173,10,4,191,74,58,123,255,40,55,136,255,121,45,78,159,0,0,0,0,0,0,0,0,42,
62,148,63,35,77,158,239,27,65,151,207,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
145,0,0,95,174,24,18,207,185,3,0,255,150,5,9,159,31,57,144,207,38,66,151,255,38,
65,150,239,35,63,149,223,29,67,153,255,28,62,149,207,30,55,143,47,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,168,47,43,127,169,0,0,255,0,0,0,0,0,0,0,0,
31,50,139,95,30,53,142,127,30,54,143,127,30,52,142,95,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,175,24,19,220,178,24,21,255,175,0,0,255,186,
37,30,255,168,5,0,185,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,166,35,31,191,165,0,0,255,175,0,0,84,
175,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,150,18,16,127,150,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static Fl_Image *image_b_tipa() {
  static Fl_Image *image = new Fl_RGB_Image(idata_b_tipa, 16, 16, 4, 0);
  return image;
}

static void cb_Compagnia(Fl_Button*, void*) {
  GUITabbozCompagnia();
compa_val_rep->value(Reputazione);
win_compagnia->show();
win_principale->deactivate();
}

static const unsigned char idata_b_compagnia[] =
{0,0,0,0,0,0,0,0,0,0,0,19,0,0,0,97,0,0,0,115,0,0,0,65,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,65,0,0,0,115,0,0,0,97,0,0,0,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
66,45,31,16,238,113,84,52,255,130,99,65,255,87,63,36,255,14,9,4,181,0,0,0,8,0,
0,0,8,14,9,4,181,87,63,36,255,130,99,65,255,113,84,52,255,45,31,16,238,0,0,0,
66,0,0,0,0,0,0,0,11,31,21,9,234,92,62,28,255,92,62,28,255,92,62,28,255,94,63,
28,255,79,53,24,255,2,1,0,130,2,1,0,130,79,53,24,255,92,62,28,255,92,62,28,255,
94,63,28,255,92,62,28,255,31,21,9,234,0,0,0,11,0,0,0,73,66,44,20,255,95,65,30,
255,117,83,46,255,168,132,91,255,224,176,121,255,129,91,47,255,24,16,7,213,24,
16,7,213,92,62,28,255,105,72,36,255,140,106,67,255,215,172,123,255,174,129,78,
255,74,50,23,255,0,0,0,73,19,13,7,156,212,152,79,255,255,203,141,255,255,222,
183,255,255,226,190,255,254,216,169,255,242,181,108,255,120,88,52,255,120,88,52,
255,242,182,109,255,254,215,167,255,255,226,190,255,255,223,184,255,255,204,142,
255,212,152,78,255,19,13,7,156,4,3,1,110,172,121,60,254,255,204,141,255,255,221,
179,255,255,224,187,255,204,168,124,255,120,85,46,255,121,88,51,255,121,88,51,
255,120,85,46,255,204,168,125,255,255,224,187,255,255,220,179,255,255,203,140,
255,171,121,60,254,4,3,1,110,0,0,0,17,18,24,6,219,218,183,107,255,255,217,171,
255,240,206,164,255,97,67,33,255,89,60,27,255,89,60,27,255,90,61,27,255,106,72,
34,255,97,67,33,255,240,206,164,255,255,217,170,255,218,183,106,255,18,24,6,
219,0,0,0,17,10,19,3,175,87,149,29,255,141,182,76,255,217,205,143,255,164,152,
74,255,116,81,39,255,129,93,53,255,160,125,85,255,222,183,138,255,237,188,131,
255,145,102,53,255,164,152,74,255,217,205,143,255,141,182,76,255,87,149,29,255,
10,19,3,175,47,76,11,250,136,184,30,255,168,202,39,255,173,203,38,255,180,153,
59,255,243,180,102,255,255,213,162,255,255,226,189,255,255,225,189,255,255,213,
161,255,243,179,101,255,180,153,59,255,173,203,38,255,167,202,38,255,135,183,30,
255,47,76,11,250,21,33,4,200,122,171,21,255,163,200,33,255,178,207,36,255,167,
169,41,255,234,174,95,255,255,211,157,255,255,223,184,255,255,223,184,255,255,
211,156,255,234,174,94,255,167,169,41,255,177,207,36,255,162,199,33,255,121,170,
20,255,21,33,4,200,0,0,0,25,9,15,1,163,50,73,10,240,73,102,14,255,77,107,15,
255,112,116,39,255,251,205,144,255,255,219,174,255,255,219,174,255,251,205,143,
255,112,116,39,255,77,107,15,255,73,102,14,255,50,73,10,240,9,15,1,163,0,0,0,25,
0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,53,35,65,11,250,100,165,36,255,190,196,133,255,
218,202,128,255,218,202,128,255,190,196,133,255,100,165,36,255,35,65,11,250,0,0,
0,53,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,105,157,26,255,
153,194,36,255,171,202,49,255,170,203,40,255,170,203,40,255,170,202,49,255,153,
193,36,255,104,157,26,255,0,0,0,112,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,90,96,139,20,255,153,191,26,255,184,211,38,255,190,214,40,255,190,
213,40,255,184,210,38,255,152,191,26,255,96,139,20,255,0,0,0,90,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,9,14,1,158,67,97,11,253,116,155,23,
255,136,178,27,255,136,178,27,255,116,155,23,255,67,97,11,253,9,14,1,158,0,0,0,
3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,
0,0,91,0,0,0,116,0,0,0,116,0,0,0,91,0,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0};
static Fl_Image *image_b_compagnia() {
  static Fl_Image *image = new Fl_RGB_Image(idata_b_compagnia, 16, 16, 4, 0);
  return image;
}

static void cb_Famiglia(Fl_Button*, void*) {
  GUITabbozFamiglia();
win_famiglia->show();
win_principale->deactivate();
}

static const unsigned char idata_b_famiglia[] =
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,119,119,119,255,0,0,0,255,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,255,119,119,119,255,170,170,170,255,119,119,119,255,0,0,0,255,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,255,119,119,119,255,170,170,170,255,221,221,221,255,170,170,
170,255,119,119,119,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,85,
85,85,255,85,85,85,255,85,85,85,255,0,0,0,255,119,119,119,255,170,170,170,255,
221,221,221,255,221,221,221,255,221,221,221,255,170,170,170,255,119,119,119,255,
0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,68,68,68,255,68,68,68,255,0,0,0,
255,119,119,119,255,170,170,170,255,221,221,221,255,221,221,221,255,221,221,221,
255,221,221,221,255,221,221,221,255,170,170,170,255,119,119,119,255,0,0,0,255,0,
0,0,0,0,0,0,0,0,0,0,255,34,34,34,255,0,0,0,255,119,119,119,255,170,170,170,
255,221,221,221,255,221,221,221,255,221,221,221,255,221,221,221,255,221,221,221,
255,221,221,221,255,221,221,221,255,170,170,170,255,119,119,119,255,0,0,0,255,0,
0,0,0,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,221,221,221,255,119,119,119,255,
119,119,119,255,119,119,119,255,119,119,119,255,119,119,119,255,119,119,119,255,
170,170,170,255,119,119,119,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,255,
170,170,170,255,0,0,0,255,221,221,221,255,119,119,119,255,0,0,0,255,0,0,0,255,0,
0,0,255,0,0,0,255,0,0,0,255,170,170,170,255,119,119,119,255,0,0,0,255,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,255,221,221,221,255,0,0,0,255,221,221,221,255,119,119,
119,255,0,0,0,255,34,0,0,255,34,0,0,255,34,0,0,255,0,0,0,255,170,170,170,255,
119,119,119,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,221,221,221,255,0,0,
0,255,221,221,221,255,119,119,119,255,0,0,0,255,34,0,0,255,102,50,0,255,102,
50,0,255,0,0,0,255,170,170,170,255,119,119,119,255,0,0,0,255,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,255,221,221,221,255,0,0,0,255,221,221,221,255,119,119,119,255,0,0,
0,255,34,0,0,255,102,50,0,255,102,50,0,255,0,0,0,255,170,170,170,255,119,119,
119,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,221,221,221,255,0,0,0,255,
221,221,221,255,119,119,119,255,0,0,0,255,34,0,0,255,102,50,0,255,102,50,0,255,
0,0,0,255,170,170,170,255,119,119,119,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,255,170,170,170,255,0,0,0,255,221,221,221,255,119,119,119,255,0,0,0,255,
34,0,0,255,102,50,0,255,102,50,0,255,0,0,0,255,170,170,170,255,119,119,119,255,
0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,119,119,119,255,0,0,0,255,119,119,
119,255,119,119,119,255,0,0,0,255,34,0,0,255,102,50,0,255,102,50,0,255,0,0,0,
255,119,119,119,255,119,119,119,255,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,
0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,
255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,0,0,0,0,0};
static Fl_Image *image_b_famiglia() {
  static Fl_Image *image = new Fl_RGB_Image(idata_b_famiglia, 16, 16, 4, 0);
  return image;
}

static void cb_Scooter(Fl_Button*, void*) {
  GUIScooter();
win_scooter->show();
win_principale->deactivate();
}

static void cb_Negozi(Fl_Button*, void*) {
  if(!OfferteDiNatale()){  //Costume non acq
  GUINegoziLauncher();
  win_principale->deactivate();
  win_negozi->show();
} else
  AggiornaPrincipale();
}

static void cb_Disco(Fl_Button*, void*) {
  GUITabbozDisco();
win_disco->show();
win_principale->deactivate();
}

Fl_Box *main_box_nome=(Fl_Box *)0;

Fl_Box *main_box_figurino=(Fl_Box *)0;

Fl_Box *main_box_giorno=(Fl_Box *)0;

static const unsigned char idata_calendario[] =
{0,0,0,0,0,0,0,0,0,0,0,1,41,41,41,68,145,145,145,202,38,38,38,72,0,0,0,4,0,
0,0,1,0,0,0,1,0,0,0,4,50,50,50,60,155,155,155,199,41,41,41,68,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,220,0,0,255,199,0,0,255,203,181,181,255,230,230,230,255,201,
179,179,255,199,0,0,255,220,0,0,255,220,0,0,255,199,0,0,255,206,184,184,255,230,
230,230,255,205,182,182,255,199,0,0,255,220,0,0,255,0,0,0,0,0,0,0,1,220,0,0,255,
210,7,7,255,214,196,196,255,227,227,227,255,213,196,196,255,208,3,3,255,237,2,2,
255,237,2,2,255,207,1,1,255,214,197,197,255,227,227,227,255,214,196,196,255,207,
0,0,255,220,0,0,255,0,0,0,1,0,0,0,1,220,0,0,255,218,11,11,255,174,161,161,255,
224,224,224,255,174,159,159,255,206,20,20,255,225,18,18,255,225,14,14,255,204,9,
9,255,174,158,158,255,224,224,224,255,174,158,158,255,215,0,0,255,220,0,0,255,
0,0,0,1,0,0,0,1,220,0,0,255,235,15,15,255,189,40,40,255,152,28,28,255,188,31,
31,255,221,30,30,255,223,27,27,255,222,22,22,255,215,18,18,255,181,13,13,255,
146,8,8,255,180,6,6,255,230,1,1,255,220,0,0,255,0,0,0,1,0,0,0,1,220,0,0,255,243,
19,19,255,233,59,59,255,232,51,51,255,231,45,45,255,227,40,40,255,225,35,35,
255,223,30,30,255,221,27,27,255,220,23,23,255,219,20,20,255,220,17,17,255,237,4,
4,255,220,0,0,255,0,0,0,1,0,0,0,1,201,201,201,255,252,252,252,255,252,252,252,
255,252,252,252,255,252,252,252,255,252,252,252,255,252,252,252,255,252,252,252,
255,251,251,251,255,247,247,247,255,247,247,247,255,255,255,255,255,252,252,252,
255,201,201,201,255,0,0,0,1,0,0,0,1,201,201,201,255,252,252,252,255,252,252,252,
255,252,252,252,255,245,245,245,255,203,203,203,255,238,238,238,255,202,202,202,
255,199,199,199,255,184,184,184,255,255,255,255,255,254,254,254,255,252,252,252,
255,201,201,201,255,0,0,0,1,0,0,0,1,201,201,201,255,252,252,252,255,252,252,252,
255,252,252,252,255,203,203,203,255,175,175,175,255,251,251,251,255,249,249,249,
255,232,232,232,255,194,194,194,255,251,251,251,255,250,250,250,255,248,248,248,
255,200,200,200,255,0,0,0,1,0,0,0,1,201,201,201,255,252,252,252,255,251,251,251,
255,252,252,252,255,252,252,252,255,174,174,174,255,250,250,250,255,248,248,248,
255,188,188,188,255,229,229,229,255,246,246,246,255,243,243,243,255,239,239,239,
255,200,200,200,255,0,0,0,1,0,0,0,1,201,201,201,255,252,252,252,255,251,251,251,
255,251,251,251,255,251,251,251,255,174,174,174,255,250,250,250,255,232,232,232,
255,186,186,186,255,224,224,224,255,223,223,223,255,221,221,221,255,219,219,219,
255,199,199,199,255,0,0,0,1,0,0,0,1,201,201,201,255,252,252,252,255,251,251,251,
255,251,251,251,255,251,251,251,255,174,174,174,255,249,249,249,255,190,190,190,
255,224,224,224,255,221,221,221,255,252,252,252,255,253,253,253,255,224,224,224,
255,203,203,203,255,0,0,0,0,0,0,0,0,201,201,201,255,251,251,251,253,251,251,251,
255,251,251,251,255,251,251,251,255,251,251,251,255,248,248,248,255,243,243,243,
255,235,235,235,255,219,219,219,255,253,253,253,255,226,226,226,255,255,255,255,
255,204,204,204,255,0,0,0,0,0,0,0,0,188,188,188,255,239,239,239,241,251,251,251,
253,252,252,252,255,252,252,252,255,252,252,252,255,249,249,249,255,246,246,246,
255,236,236,236,255,216,216,216,255,224,224,224,255,255,255,255,255,247,247,247,
255,199,199,199,255,0,0,0,0,0,0,0,0,149,149,149,255,191,191,191,255,195,195,195,
255,195,195,195,255,195,195,195,255,195,195,195,255,195,195,195,255,195,195,195,
255,195,195,195,255,195,195,195,255,196,196,196,255,197,197,197,255,194,194,194,
255,149,149,149,255,0,0,0,0,0,0,0,0,132,132,132,196,145,145,145,255,145,145,145,
255,145,145,145,255,145,145,145,255,145,145,145,255,145,145,145,255,145,145,145,
255,145,145,145,255,145,145,145,255,145,145,145,255,145,145,145,255,145,145,145,
255,138,138,138,224,0,0,0,0};
static Fl_Image *image_calendario() {
  static Fl_Image *image = new Fl_RGB_Image(idata_calendario, 16, 16, 4, 0);
  return image;
}

Fl_Output *main_txtbox_tipa=(Fl_Output *)0;

Fl_Value_Output *main_valbox_rapporti=(Fl_Value_Output *)0;

Fl_Value_Output *main_valbox_soldi=(Fl_Value_Output *)0;

static void cb_main_valbox_soldi(Fl_Value_Output* o, void*) {
  o->value(CALCSOLDI(Soldi));
}

Fl_Value_Output *main_valbox_paghetta=(Fl_Value_Output *)0;

static void cb_main_valbox_paghetta(Fl_Value_Output* o, void*) {
  o->value(CALCSOLDI(Paghetta));
}

Fl_Value_Output *main_valbox_stipendio=(Fl_Value_Output *)0;

static void cb_main_valbox_stipendio(Fl_Value_Output* o, void*) {
  o->value(CALCSOLDI(stipendio));
}

Fl_Value_Output *main_valbox_rep=(Fl_Value_Output *)0;

Fl_Value_Output *main_valbox_fama=(Fl_Value_Output *)0;

Fl_Value_Output *main_valbox_studio=(Fl_Value_Output *)0;

static void cb_main_valbox_studio(Fl_Value_Output* o, void*) {
  o->precision(1);
o->value(MEDIAVOTI(Studio,N_MATERIE));
}

Fl_Box *main_fig_scarpe=(Fl_Box *)0;

Fl_Box *main_fig_panta=(Fl_Box *)0;

Fl_Box *main_fig_giub=(Fl_Box *)0;

Fl_Box *main_fig_testa=(Fl_Box *)0;

static void cb_(Fl_Button*, void*) {
  Giorno();
AggiornaPrincipale();
}

static void cb_T(Fl_Button*, void*) {
  GUITestbed();
win_testbed->show();
win_principale->deactivate();
}

static void cb_1(Fl_Button*, void*) {
  Soldi+=1000;
main_valbox_soldi->value(CALCSOLDI(Soldi));
}

Fl_Group *main_grp_scooter=(Fl_Group *)0;

Fl_Output *main_txtbox_scooter=(Fl_Output *)0;

Fl_Value_Output *main_valbox_scooterstato=(Fl_Value_Output *)0;

Fl_Double_Window* GUITabboz() {
  { win_principale = new Fl_Double_Window(475, 450, "Tabboz Simulator Next Generation!");
    win_principale->align(Fl_Align(FL_ALIGN_TOP_LEFT));
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 475, 20);
      o->labeltype(FL_NO_LABEL);
      o->hide();
      o->deactivate();
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    { Fl_Group* o = new Fl_Group(10, 330, 145, 110, "Sbatti...");
      o->box(FL_EMBOSSED_FRAME);
      o->labeltype(FL_NO_LABEL);
      o->labelsize(12);
      { Fl_Button* o = new Fl_Button(15, 335, 135, 30, "Scuola");
        o->image( image_b_scuola() );
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Scuola);
        o->align(Fl_Align(256|FL_ALIGN_INSIDE));
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(15, 370, 135, 30, "Lavoro");
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Lavoro);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(15, 405, 135, 30, "Palestra");
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Palestra);
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(165, 330, 145, 110, "Social!");
      o->box(FL_EMBOSSED_FRAME);
      o->labeltype(FL_NO_LABEL);
      o->labelsize(12);
      { Fl_Button* o = new Fl_Button(170, 335, 135, 30, "Tipa");
        o->image( image_b_tipa() );
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Tipa);
        o->align(Fl_Align(256));
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(170, 370, 135, 30, "Compagnia");
        o->image( image_b_compagnia() );
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Compagnia);
        o->align(Fl_Align(256));
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(170, 405, 135, 30, "Famiglia");
        o->image( image_b_famiglia() );
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Famiglia);
        o->align(Fl_Align(256));
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(320, 330, 145, 110, "Scialla!");
      o->box(FL_EMBOSSED_FRAME);
      o->labeltype(FL_NO_LABEL);
      o->labelsize(12);
      { Fl_Button* o = new Fl_Button(325, 335, 135, 30, "Scooter");
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Scooter);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(325, 370, 135, 30, "Negozi");
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Negozi);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(325, 405, 135, 30, "Disco");
        o->labelfont(2);
        o->callback((Fl_Callback*)cb_Disco);
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    { Fl_Box* o = main_box_nome = new Fl_Box(10, 10, 140, 25, "Nome Tabbozzo");
      main_box_nome->box(FL_SHADOW_BOX);
      main_box_nome->color(FL_BACKGROUND2_COLOR);
      main_box_nome->labelfont(3);
      main_box_nome->labelsize(12);
      o->label(Nome);
    } // Fl_Box* main_box_nome
    { main_box_figurino = new Fl_Box(10, 30, 140, 280);
      main_box_figurino->box(FL_SHADOW_BOX);
    } // Fl_Box* main_box_figurino
    { main_box_giorno = new Fl_Box(160, 10, 305, 30, "  Luned\303\254 31 Gennaio");
      main_box_giorno->box(FL_EMBOSSED_FRAME);
      main_box_giorno->image( image_calendario() );
      main_box_giorno->labelfont(3);
      main_box_giorno->align(Fl_Align(260|FL_ALIGN_INSIDE));
    } // Fl_Box* main_box_giorno
    { Fl_Group* o = new Fl_Group(160, 65, 145, 95, "Tipa");
      o->box(FL_EMBOSSED_FRAME);
      o->labelfont(1);
      o->labelsize(12);
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { Fl_Output* o = main_txtbox_tipa = new Fl_Output(167, 75, 120, 25, "Tipa");
        main_txtbox_tipa->box(FL_FLAT_BOX);
        main_txtbox_tipa->color(FL_BACKGROUND_COLOR);
        main_txtbox_tipa->labeltype(FL_NO_LABEL);
        main_txtbox_tipa->labelfont(1);
        main_txtbox_tipa->textsize(12);
        main_txtbox_tipa->align(Fl_Align(FL_ALIGN_CENTER));
        o->value(Nometipa);
        o->clear_visible_focus();
      } // Fl_Output* main_txtbox_tipa
      { main_valbox_rapporti = new Fl_Value_Output(240, 110, 35, 25, "Rapporto ");
        main_valbox_rapporti->box(FL_SHADOW_BOX);
        main_valbox_rapporti->color(FL_BACKGROUND2_COLOR);
        main_valbox_rapporti->labelsize(12);
        main_valbox_rapporti->maximum(0);
        main_valbox_rapporti->value(100);
        main_valbox_rapporti->textfont(1);
      } // Fl_Value_Output* main_valbox_rapporti
      { Fl_Box* o = new Fl_Box(275, 114, 20, 16, "%");
        o->labelfont(1);
      } // Fl_Box* o
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(160, 180, 305, 65, "Soldi");
      o->box(FL_EMBOSSED_FRAME);
      o->labelfont(1);
      o->labelsize(12);
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { main_valbox_soldi = new Fl_Value_Output(180, 200, 100, 25, "L.");
        main_valbox_soldi->box(FL_EMBOSSED_BOX);
        main_valbox_soldi->color(FL_BACKGROUND2_COLOR);
        main_valbox_soldi->labelsize(12);
        main_valbox_soldi->maximum(0);
        main_valbox_soldi->step(1);
        main_valbox_soldi->value(1e+10);
        main_valbox_soldi->textfont(5);
        main_valbox_soldi->callback((Fl_Callback*)cb_main_valbox_soldi);
      } // Fl_Value_Output* main_valbox_soldi
      { main_valbox_paghetta = new Fl_Value_Output(380, 185, 80, 25, "Paghetta  L.");
        main_valbox_paghetta->tooltip("Paghetta settimanale");
        main_valbox_paghetta->box(FL_EMBOSSED_BOX);
        main_valbox_paghetta->color(FL_BACKGROUND2_COLOR);
        main_valbox_paghetta->labelsize(12);
        main_valbox_paghetta->maximum(0);
        main_valbox_paghetta->step(1);
        main_valbox_paghetta->value(50000);
        main_valbox_paghetta->textfont(5);
        main_valbox_paghetta->callback((Fl_Callback*)cb_main_valbox_paghetta);
      } // Fl_Value_Output* main_valbox_paghetta
      { main_valbox_stipendio = new Fl_Value_Output(380, 215, 80, 25, "Stipendio  L.");
        main_valbox_stipendio->tooltip("Se non sei disoccupato...");
        main_valbox_stipendio->box(FL_EMBOSSED_BOX);
        main_valbox_stipendio->color(FL_BACKGROUND2_COLOR);
        main_valbox_stipendio->labelsize(12);
        main_valbox_stipendio->maximum(0);
        main_valbox_stipendio->step(1);
        main_valbox_stipendio->value(1e+07);
        main_valbox_stipendio->textfont(5);
        main_valbox_stipendio->callback((Fl_Callback*)cb_main_valbox_stipendio);
      } // Fl_Value_Output* main_valbox_stipendio
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(315, 65, 150, 95, "Tabbo-stats");
      o->box(FL_EMBOSSED_FRAME);
      o->labelfont(1);
      o->labelsize(12);
      o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { main_valbox_rep = new Fl_Value_Output(405, 70, 35, 25, "Reputazione ");
        main_valbox_rep->box(FL_SHADOW_BOX);
        main_valbox_rep->color(FL_BACKGROUND2_COLOR);
        main_valbox_rep->labelsize(12);
        main_valbox_rep->maximum(0);
        main_valbox_rep->value(100);
        main_valbox_rep->textfont(1);
      } // Fl_Value_Output* main_valbox_rep
      { main_valbox_fama = new Fl_Value_Output(405, 100, 35, 25, "Figosit\303\240 ");
        main_valbox_fama->tooltip("L\'innato carisma del tabbozzo");
        main_valbox_fama->box(FL_SHADOW_BOX);
        main_valbox_fama->color(FL_BACKGROUND2_COLOR);
        main_valbox_fama->labelsize(12);
        main_valbox_fama->maximum(0);
        main_valbox_fama->value(100);
        main_valbox_fama->textfont(1);
      } // Fl_Value_Output* main_valbox_fama
      { main_valbox_studio = new Fl_Value_Output(405, 130, 35, 25, "Media Voti ");
        main_valbox_studio->tooltip("Media scolastica");
        main_valbox_studio->box(FL_SHADOW_BOX);
        main_valbox_studio->color(FL_BACKGROUND2_COLOR);
        main_valbox_studio->labelsize(12);
        main_valbox_studio->maximum(0);
        main_valbox_studio->textfont(1);
        main_valbox_studio->callback((Fl_Callback*)cb_main_valbox_studio);
      } // Fl_Value_Output* main_valbox_studio
      { Fl_Box* o = new Fl_Box(440, 74, 15, 16, "%");
        o->labelfont(1);
      } // Fl_Box* o
      { Fl_Box* o = new Fl_Box(440, 104, 15, 16, "%");
        o->labelfont(1);
      } // Fl_Box* o
      o->end();
    } // Fl_Group* o
    { main_fig_scarpe = new Fl_Box(45, 245, 60, 65);
    } // Fl_Box* main_fig_scarpe
    { main_fig_panta = new Fl_Box(20, 127, 110, 150);
    } // Fl_Box* main_fig_panta
    { main_fig_giub = new Fl_Box(43, 80, 60, 65);
    } // Fl_Box* main_fig_giub
    { main_fig_testa = new Fl_Box(42, 36, 60, 65);
    } // Fl_Box* main_fig_testa
    { Fl_Group* o = new Fl_Group(390, 15, 70, 20);
      { Fl_Button* o = new Fl_Button(390, 15, 20, 20, ">>");
        o->callback((Fl_Callback*)cb_);
        if(!TABBOZ_DEBUG) o->hide();
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(440, 15, 20, 20, "T");
        o->callback((Fl_Callback*)cb_T);
        if(!TABBOZ_DEBUG) o->hide();
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(415, 15, 20, 20, "$");
        o->callback((Fl_Callback*)cb_1);
        if(!TABBOZ_DEBUG) o->hide();
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    { main_grp_scooter = new Fl_Group(160, 270, 305, 35, "Scooter");
      main_grp_scooter->box(FL_EMBOSSED_FRAME);
      main_grp_scooter->labelfont(1);
      main_grp_scooter->labelsize(12);
      main_grp_scooter->align(Fl_Align(FL_ALIGN_TOP_LEFT));
      { Fl_Output* o = main_txtbox_scooter = new Fl_Output(165, 275, 200, 25, "Scooter");
        main_txtbox_scooter->box(FL_FLAT_BOX);
        main_txtbox_scooter->color(FL_BACKGROUND_COLOR);
        main_txtbox_scooter->labeltype(FL_NO_LABEL);
        main_txtbox_scooter->labelfont(1);
        main_txtbox_scooter->textsize(12);
        main_txtbox_scooter->align(Fl_Align(FL_ALIGN_CENTER));
        o->clear_visible_focus();
      } // Fl_Output* main_txtbox_scooter
      { main_valbox_scooterstato = new Fl_Value_Output(405, 275, 35, 25, "Stato ");
        main_valbox_scooterstato->box(FL_SHADOW_BOX);
        main_valbox_scooterstato->color(FL_BACKGROUND2_COLOR);
        main_valbox_scooterstato->labelsize(12);
        main_valbox_scooterstato->maximum(0);
        main_valbox_scooterstato->value(100);
        main_valbox_scooterstato->textfont(1);
      } // Fl_Value_Output* main_valbox_scooterstato
      { Fl_Box* o = new Fl_Box(440, 279, 15, 16, "%");
        o->labelfont(1);
      } // Fl_Box* o
      main_grp_scooter->end();
    } // Fl_Group* main_grp_scooter
    AggiornaPrincipale();
    win_principale->size_range(475, 450, 475, 450);
    win_principale->end();
  } // Fl_Double_Window* win_principale
  return win_principale;
}
