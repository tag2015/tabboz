/*             Tabboz Simulator NG            */
/*                                            */
/* Copyright 2022-2023 Walter Agazzi          */
/* Original Copyright 1997-2000 Andrea Bonomi */

/*
    This file is part of Tabboz Simulator NG.

    Tabboz Simulator NG is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tabboz Simulator NG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tabboz Simulator NG.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "zarrosim.h"
#include "sharedimg.h"

#include "dialogs.h"


/* Ottiene un puntatore all'icona delle dialog, e "cancella" l'icona predefinita */
void MsgInit()
{
    Fl_Box *icona_msg = (Fl_Box *) fl_message_icon();
    icona_msg->copy_label("");
    icona_msg->box(FL_NO_BOX);
    icona_msg->align(FL_ALIGN_IMAGE_BACKDROP);
}


/* Cambia icona della prossima dialog */
void MsgIcona(int scelta)
{
    Fl_Box *icona_msg = (Fl_Box *) fl_message_icon();
    icona_msg->show();
    
    switch(scelta) {
        case 0: icona_msg->hide();
                break;
        case 1: icona_msg->image(ImgInfo);
                break;
        case 2: icona_msg->image(ImgAvviso);
                break;
        case 3: icona_msg->image(ImgStop);
                break;
        case 4: icona_msg->image(ImgDomanda);
                break;
        case 5: icona_msg->image(ImgCool);
                break;
    }

}