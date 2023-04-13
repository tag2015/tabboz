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

#include "calendario.h"
#include "scooter.h"
#include "eventi.h"

#include "disco.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


/* FIXME L'opzione CDROM è stata tolta... verrà sostituita dalla possibilità di */
/* riprodurre file audio personali (in futuro...)                               */



const STDISCO DiscoMem[] = {
    { 0,  0, 0,  0, 0,  0,  "---"},
    { 0, 30, 2,  5, 1, 36,  ""   },
    { 0,  0, 2,  1, 4, 26,  ""   },
    { 0,  0, 2,  2, 1, 30,  ""   },
    { 0, 35, 3,  5, 1, 36,  ""   },
    { 0,  0, 2,  1, 3, 26,  ""   },
    { 0,  0, 1,  1, 2, 22,  ""   },
    { 0,  0, 2,  3, 1, 30,  ""   },
    { 1,  0, 2,  4, 7, 36,  ""   }
};//  |   |  |   |  |   |    |
//    |   |  |   |  |   |     \nome  
//    |   |  |   |   \   \costo
//    |   |  |   |    \giorno di chiusura (1=lunedi',etc... - 0=nessuno)
//    \   \  \   \incremento fama
//     \   \  \incremento reputazione
//      \   \figosita' minima x entrare (selezione all' ingresso)
//       \1=disco fuori porta - ci puoi arrivare solo se hai lo scooter...



/* Routine per il pagamento della Discoteca */
void PagaDisco(int scelta)
{
    char tmp[128];
    int prezzo;

    if ( (DiscoMem[scelta].fuoriporta) && (ScooterData.attivita != 1) ) {
        MsgIcona(ICONA_AVVISO);
        fl_message_title("Discoteca fuori porta");
        fl_alert("Senza uno scooter funzionante non puoi andare nelle discoteche fuori porta...");
        Evento(false);
        return;
    }
    
    if (DiscoMem[scelta].g_chiusura == x_giornoset) {
        MsgIcona(ICONA_AVVISO);
        fl_message_title("Giorno di chiusura");
        fl_alert("Un cartello recita che oggi è il giorno di chiusura settimanale...");
        return;
    }

    if (sesso == 'M')
        prezzo=DiscoMem[scelta].costo;
    else
        prezzo=DiscoMem[scelta].costo - 10;  // ingresso ridotto

    if (prezzo > Soldi)    // check costo
        nomoney(DISCO);
    else
        if ((DiscoMem[scelta].fama > Fama) && (sesso == 'M')) {    // check selezione all'ingresso
            if (sound_active) TabbozPlaySound(302);
            MsgIcona(ICONA_STOP);
            fl_message_title("Selezione all'ingresso");
            fl_alert("Mi dispiace signore, conciato così, qui non può entrare...\nVenga vestito meglio la prossima volta, signore.");
            if (Reputazione > 2) Reputazione--;
            if (Fama > 2) Fama--;
        } else {
            if (sound_active) TabbozPlaySound(303 + rand() % 3);  // suoni: 0303 -> 0305
            Soldi-= prezzo;
            if(logging) {
                sprintf(tmp,"discoteca: Paga ingresso %s",MostraSoldi(prezzo));
                writelog(tmp);
            }
            Fama+=DiscoMem[scelta].fama_inc;  //BUGFIX qui incrementava con la fama della disco anzichè il bonus
            Reputazione+=DiscoMem[scelta].rep_inc;
            if (Fama > 100) Fama=100;
            if (Reputazione > 100) Reputazione=100;
        }
    Evento(false);
}