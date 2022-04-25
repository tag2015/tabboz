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

#include "zarrosim.h"
#include "sound.h"
#include "debug.h"

#include "scooter.h"
#include "eventi.h"

#include "compagnia.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


/* Gareggia con lo scooter... */
void GareggiaScooter(void)
{
    int i, si_no;

    fl_message_title("Gareggia con lo scooter");
    if (ScooterData.stato == -1000) {
        fl_message("Con quale scooter vorresti gareggiare, visto che non lo possiedi?");
        return;
    }
    if (ScooterData.attivita != 1) {
        fl_message("Purtroppo non puoi gareggiare visto che il tuo scooter è %s.",n_attivita[ScooterData.attivita]);
        return;
    }
    if (sound_active) TabbozPlaySound(701);
    i= 1 + rand() % 6;    // estrae tipo di scooter sfidante
    si_no=fl_choice("Accetti la sfida con un tabbozzo che ha un %s?", "Lo spakko!", "Ho paura...", 0, ScooterMem[i].nome);
    if (ScooterData.stato > 30) ScooterData.stato-=rand() % 2;  // BUG? perchè danneggia lo scooter anche se rifiuto la gara?
    switch(si_no) {
        case 0: { // sfida accettata
            // if ( (ScooterMem[i].speed + 70 + random(50)) > (ScooterData.speed + ScooterData.stato + Fortuna) ) {
            if ( (ScooterMem[i].speed + 80 + rand() % 40) > (ScooterData.speed + ScooterData.stato + Fortuna) ) {
                // perdi
                if (Reputazione > 80)
                    Reputazione-=3;
                if (Reputazione > 10)
                    Reputazione-=2;
                fl_message_title("Hai perso...");
                fl_message("Dopo pochi metri si vede l'inferiorità del tuo scooter...");
            } else {
                // vinci
                Reputazione+=10;
                if (Reputazione > 100) Reputazione=100;
                fl_message_title("Hai vinto!");
                fl_message("Con il tuo scooter, bruci l'avversario in partenza...");
            }
        break;
        }
        case 1: { //sfida rifiutata
            if (Reputazione > 80)        // Se non accetti la sfida, perdi rep...
                Reputazione-=3;
            if (Reputazione > 10)
                Reputazione-=2;
        }
    }
    benzina-=5;
    if (benzina < 1) benzina = 0;
    CalcolaVelocita(FALSE);
    Evento();
}


/* Esci con la compagnia... */
void EsciCompagnia(void)
{
    if (Reputazione < 57)    // Uscendo con la propria compagnia si puo' arrivare solamente a reputazione = 57
        Reputazione+=1;
    if (Reputazione < 37)    // Se la rep e' bassa, sale + in fretta
        Reputazione+=1;
    if (Reputazione < 12)
        Reputazione+=1;

    Evento();
}


/* Chiama la compagnia...*/
void ChiamaCompagnia(void)
{
    fl_message_title("Chiama la Compagnia");
    if (Reputazione < 16) {
        fl_message("Con la scarsa reputazione che hai, tutti trovano qualcosa di meglio da fare piuttosto che venire...");
        Evento();
        return;
    }
    if (tempo_pestaggio > 0) {
        if ( (rand() % 2)== 1) {
            fl_message("Dopo aver visto i tuoi amici, chi ti ha picchiato non si farà più vedere in giro per un bel pezzo...");
            if (Reputazione < 80)
                Reputazione+=3;
            } else {
            fl_message("Anche i tuoi amici, al gran completo, vengono sacagnati di botte da chi ti aveva picchiato,\naccorgendosi così che non sei solo tu ad essere una chiavica, ma lo sono anche loro...");
            if (Reputazione < 95)
                Reputazione+=5;
            }
        tempo_pestaggio=0;  // BUGFIX si può contrattaccare una sola volta x pestaggio
        Evento();
    } else {
        fl_message_title("Chiama la Compagnia (perchè?)");
        fl_message("Visto che non c'è nessuno da minacciare, tutti se ne vanno avviliti...");
    }
}