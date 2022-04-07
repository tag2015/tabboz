
#include <stdio.h>
#include <stdlib.h>


#include "sharedimg.h"


Fl_Shared_Image *ImgTesta[N_TESTA];
Fl_Shared_Image *ImgGiubbotto[N_GIUBBOTTO];
Fl_Shared_Image *ImgPantaloni[N_PANTALONI];
Fl_Shared_Image *ImgScarpe[N_SCARPE];


void CaricaSharedImgs()
{
    char path[128];

    for(int i=0; i < N_TESTA; ++i) {
        sprintf(path, "res/pic/testa_%d.png",i);
        ImgTesta[i] = Fl_Shared_Image::get(path);
    }
    for(int i=0; i < N_GIUBBOTTO; ++i) {
        sprintf(path, "res/pic/giubbotto_%d.png",i);
        ImgGiubbotto[i] = Fl_Shared_Image::get(path);
    }
    for(int i=0; i < N_PANTALONI; ++i) {
        sprintf(path, "res/pic/pantaloni_%d.png",i);
        ImgPantaloni[i] = Fl_Shared_Image::get(path);
    }
    for(int i=0; i < N_SCARPE; ++i) {
        sprintf(path, "res/pic/scarpe_%d.png",i);
        ImgScarpe[i] = Fl_Shared_Image::get(path);
    }


}
