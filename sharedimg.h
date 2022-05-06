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

#ifndef TABBOZ_SHAREDIMG_H
#define TABBOZ_SHAREDIMG_H

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>


/* N. di elementi in ciascun array di immagini */
#define N_TESTA         5
#define N_GIUBBOTTO     7
#define N_PANTALONI     6
#define N_SCARPE        9

#define N_EVENTI        9

#define N_DITTE         8


extern Fl_Shared_Image *ImgTesta[];
extern Fl_Shared_Image *ImgGiubbotto[];
extern Fl_Shared_Image *ImgPantaloni[];
extern Fl_Shared_Image *ImgScarpe[];

extern Fl_Shared_Image *ImgEventi[];

extern Fl_Shared_Image *ImgDitte[];

extern Fl_Shared_Image *ImgExit;

extern Fl_Shared_Image *ImgInfo;
extern Fl_Shared_Image *ImgDomanda;
extern Fl_Shared_Image *ImgAvviso;
extern Fl_Shared_Image *ImgStop;
extern Fl_Shared_Image *ImgCool;

void CaricaSharedImgs();

#endif