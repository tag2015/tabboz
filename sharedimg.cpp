/*             Tabboz Simulator             */
/* (C) Copyright 1997-2000 by Andrea Bonomi */

/*
    This file is part of Tabboz Simulator.

    Tabboz Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tabboz Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tabboz Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "os.h"

#include <stdio.h>
#include <stdlib.h>

#include "sharedimg.h"


Fl_Shared_Image *ImgTesta[N_TESTA];
Fl_Shared_Image *ImgGiubbotto[N_GIUBBOTTO];
Fl_Shared_Image *ImgPantaloni[N_PANTALONI];
Fl_Shared_Image *ImgScarpe[N_SCARPE];

Fl_Shared_Image *ImgEventi[N_EVENTI];

Fl_Shared_Image *ImgDitte[N_DITTE];

Fl_Shared_Image *ImgExit;


/* Carica da file le immagini condivise (usate in più finestre) */
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

    for(int i=0; i < N_EVENTI; ++i) {
        sprintf(path, "res/pic/eventi_%d.png",i);
        ImgEventi[i] = Fl_Shared_Image::get(path);
    }

    for(int i=0; i < N_DITTE; ++i) {
        sprintf(path, "res/pic/ditta_%d.png",i);
        ImgDitte[i] = Fl_Shared_Image::get(path);
    }

    ImgExit = Fl_Shared_Image::get("gui/icons/b_exit.png");
}
