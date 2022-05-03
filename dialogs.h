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

#ifndef TABBOZ_DIALOGS_H
#define TABBOZ_DIALOGS_H

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>

#define ICONA_NO 0
#define ICONA_INFO 1
#define ICONA_AVVISO 2
#define ICONA_STOP 3
#define ICONA_DOMANDA 4
#define ICONA_COOL 5


void MsgInit();
void MsgIcona(int);

#endif