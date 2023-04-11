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

#include "os.h"

#include <stdio.h>
#include <stdlib.h>

#include "zarrosim.h"
#include "dialogs.h"
#include "sound.h"
#include "debug.h"

#include "eventi.h"

#include "famiglia.h"
#include "gui/GUIFamiglia.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


/* Chiedi aumento paghetta */
void ChiediAumentoPaghetta(void)
{
    char tmp[128];

    if (Studio > 40) {
        if (((Studio - Paghetta +  Fortuna) > ( 75 + rand() % 50)) && (Paghetta < 96) ) {  //BUGFIX qui c'era & anzichè &&. Cmq la prob è irrisoria andrebbe modificato
            sprintf(tmp,"Va bene... ti daremo %s di paghetta in più...",MostraSoldi(5));
            MsgIcona(ICONA_COOL);
            fl_message_title("Aumento paghetta !");
            fl_message(tmp);
            Paghetta+=5;
            Evento();
        } else {
            MsgIcona(ICONA_AVVISO);
            fl_message_title("Errore irrecuperabile");
            fl_alert("Vedi di scordartelo...\nDovrà passare molto tempo prima che ti venga aumentata la paghetta...");
            Evento();
        }
    } else {
        MsgIcona(ICONA_AVVISO);
        fl_message_title("Errore irrecuperabile");
        fl_alert("Quando andrai meglio a scuola, forse...");
    }
    fam_val_paghetta->value(CALCSOLDI(Paghetta));
}


/* Chiedi soldi extra */
void ChiediSoldiExtra(void)
{
    char tmp[500];

    if (Studio >= 40) {
        if (AttesaSoldi == 0) {
            AttesaSoldi=ATTESAMAX+1;
            Soldi+=10;
            MsgIcona(ICONA_COOL);
            fl_message_title("Soldi extra!");
            if (!euro)
                fl_message("E va bene, possiamo darti %d L. ...",CALCSOLDI(10));
            else
                fl_message("E va bene, possiamo darti %d € ...",CALCSOLDI(10));
            if (logging) {
                sprintf(tmp,"famiglia: paghetta extra (%s)",MostraSoldi(10));
                writelog(tmp);
            }
            Evento();
        } else {
            MsgIcona(ICONA_AVVISO);
            fl_message_title("Non te li diamo");
            fl_alert("Ma insomma! Non puoi continuamente chiedere soldi!\nAspetta ancora qualche giorno. Fai qualche cosa di economico nel frattempo...");
            Evento();
        }
    } else {
        MsgIcona(ICONA_AVVISO);
        sprintf(tmp,"Quando andrai meglio a scuola potrai tornare a chiederci dei soldi, non ora.\nMa non lo sai che per la tua vita è importante studiare, e dovresti impegnarti\ndi più, perchè quando ti impegni i risultati si vedono, solo che sei svogliat%c\ne non fai mai nulla, mi ricordo che quando ero giovane io era tutta un'altra cosa...\nallora sì che i giovani studiavano...",ao);
        fl_message_title("Errore irrecuperabile");
        fl_alert(tmp);
    }
    fam_val_soldi->value(CALCSOLDI(Soldi));
}


/* Chiedi 100k a papà */
void ChiediSoldiPapa(void)
{
    if (sound_active) TabbozPlaySound(801);
    MsgIcona(ICONA_STOP);
    fl_message_title("Errore irrecuperabile");
    fl_alert("Non pensarci neanche lontanamente...");
    Evento();
}