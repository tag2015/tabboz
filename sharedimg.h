
#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>

#define N_TESTA         5
#define N_GIUBBOTTO     7
#define N_PANTALONI     1
#define N_SCARPE        1

#define N_EVENTI        8

extern Fl_Shared_Image *ImgTesta[];
extern Fl_Shared_Image *ImgGiubbotto[];
extern Fl_Shared_Image *ImgPantaloni[];
extern Fl_Shared_Image *ImgScarpe[];

extern Fl_Shared_Image *ImgEventi[];


void CaricaSharedImgs();
