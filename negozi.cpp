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
#include "global.h"
#include "dialogs.h"
#include "sound.h"
#include "debug.h"

#include "calendario.h"
#include "eventi.h"

#include "negozi.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>



STVARIE VestitiMem[] = {
    {0, 0, 0, 0, 0,  0, 0,    0,  0, "---"},
    {0, 0, 0, 0, 0,  8, 0,  348,  0, ""},    // -- Giubbotto "Fatiscenza"
    {0, 0, 0, 0, 0,  9, 0,  378,  0, ""},    //    Fatiscenza silver
    {0, 0, 0, 0, 0,  9, 0,  378,  0, ""},    //    Fatiscenza verde
    {0, 0, 0, 0, 0, 10, 0,  418,  0, ""},    //    Fatiscenza bianco
    {0, 0, 0, 0, 0,  8, 0,  248,  0, ""},    //    Giacca di pelle
    {0, 0, 0, 0, 0,  7, 0,  298,  0, ""},    //    Cappotto fluo
    {0, 0, 0, 0, 0,  0, 0,   58,  0, ""},    //    Cappotto da Babbo Natale

    {0, 0, 0, 0, 0,  3, 0,   90,  0, ""},    // -- Pantaloni gessati
    {0, 0, 0, 0, 0,  5, 0,  170,  0, ""},    //    Pantaloni tuta
    {0, 0, 0, 0, 0,  6, 0,  248,  0, ""},    //    Pantaloni in plastika
    {0, 0, 0, 0, 0,  5, 0,  190,  0, ""},    //    Pantaloni scacchiera
    {0, 0, 0, 0, 0,  5, 0,  190,  0, ""},    //    Pantaloni scacchiera
    {0, 0, 0, 0, 0,  0, 0,    0,  0, ""},    //    Pantaloni da Babbo Natale

    {0, 0, 0, 0, 0,  4, 0,  122,  0, ""},    // -- Simil-Nike nere
    {0, 0, 0, 0, 0,  4, 0,  122,  0, ""},    //    "      "   gialle
    {0, 0, 0, 0, 0,  4, 0,  122,  0, ""},    //    "      "   pastello
    {0, 0, 0, 0, 0,  4, 0,  142,  0, ""},    //    Imbalance
    {0, 0, 0, 0, 0,  5, 0,  166,  0, ""},    //    Imbalance Shocking
    {0, 0, 0, 0, 0,  6, 0,  220,  0, ""},    //    Buffalo
    {0, 0, 0, 0, 0,  6, 0,  230,  0, ""},    //    Buffalo Prugna
    {0, 0, 0, 0, 0,  2, 0,   58,  0, ""},    //    Scarpe con mattoni...
};


/* Sigarette */
STVARIE SizzeMem[] = {
    { 0,  5,  5, 0, 0, 2, 0,  6, 0, "Barclay"},
    { 0,  8,  7, 0, 0, 1, 0,  6, 0, "Camel"},
    { 0,  7,  6, 0, 0, 2, 0,  6, 0, "Davidoff Superior Lights"},
    { 0,  7,  6, 0, 0, 2, 0,  6, 0, "Davidoff Mild"},
    { 0, 13,  9, 0, 0, 2, 0,  6, 0, "Davidoff Classic"},
    { 0,  9,  7, 0, 0, 1, 0,  5, 0, "Diana Blu"},
    { 0, 12,  9, 0, 0, 1, 0,  5, 0, "Diana Rosse"},
    { 0,  8,  7, 0, 0, 0, 0,  6, 0, "Dunhill Lights"},
    { 0,  7,  5, 0, 0, 0, 0,  6, 0, "Merit"},
    { 0, 14, 10, 0, 0, 0, 0,  6, 0, "Gauloises Blu"},
    { 0,  7,  6, 0, 0, 0, 0,  6, 0, "Gauloises Rosse"},
    { 0, 13, 10, 0, 0, 1, 0,  6, 0, "Unlucky Strike"},
    { 0,  9,  7, 0, 0, 1, 0,  6, 0, "Unlucky Strike Lights"},
    { 0,  8,  6, 0, 0, 2, 0,  6, 0, "Malborro Medium"},    // dovrebbero essere come le lights
    { 0, 12,  9, 0, 0, 2, 0,  6, 0, "Malborro Rosse"},
    { 0,  8,  6, 0, 0, 2, 0,  6, 0, "Malborro Lights"},
    { 0, 11, 10, 0, 0, 0, 0,  5, 0, "MS Rosse"},
    { 0,  9,  8, 0, 0, 0, 0,  5, 0, "MS Mild"},
    { 0,  9,  7, 0, 0, 1, 0,  5, 0, "Poll Mon Blu"},
    { 0, 12,  9, 0, 0, 1, 0,  5, 0, "Poll Mon Rosse"},
    { 0, 12, 10, 0, 0, 2, 0,  6, 0, "Philip Morris"},
    { 0,  4,  4, 0, 0, 2, 0,  6, 0, "Philip Morris Super Light"},
    { 0, 10,  9, 0, 0, 1, 0,  5, 0, "Armadis"},
    { 0, 11,  9, 0, 0, 0, 0,  5, 0, "Winston"}
};
/*        |   |                                                    */
/*        |   \nicotina * 10 ( 7 = nicotina 0.7, 10 = nicotina 1 ) */
/*        \condensato                                              */



/* Routine per il pagamento dei vestiti... */
void PagaQualcosa (int scelta)
{
    if (scelta) {
        if (VestitiMem[scelta].prezzo > Soldi) {
            nomoney(VESTITI);
        } else {
            Soldi -= VestitiMem[scelta].prezzo;
            if (sound_active) TabbozPlaySound(207);

            if(scelta <= I_PANTALONI)    // Giubbotti
                current_giubbotto=scelta-I_GIUBBOTTO;
            else if (scelta <= I_SCARPE)    // Pantaloni
                current_pantaloni=scelta-I_PANTALONI;
            else    // Scarpe
                current_scarpe=scelta-I_SCARPE;

            if (logging) {
                sprintf(log_buf,"negozi: Paga %s",MostraSoldi(VestitiMem[scelta].prezzo));
                writelog(log_buf);
            }
            Fama+=VestitiMem[scelta].fama_inc;  // FIXME bisognerebbe rendere i bonus permanenti
            if (Fama > 100) Fama=100;
        }
        Evento(false);
    }
}


/* Routine per pagare le sigarette */
void PagaSizze(int scelta)
{
    if (scelta != -1) {
        if (SizzeMem[scelta].prezzo > Soldi) {
            nomoney(TABACCAIO);
        }
        else {
            Soldi -= SizzeMem[scelta].prezzo;
            if (logging) {
                sprintf(log_buf, "tabaccaio: Paga %s", MostraSoldi(SizzeMem[scelta].prezzo));
                writelog(log_buf);
            }
            Fama += SizzeMem[scelta].fama_inc;
            if (Fama > 100)
                Fama = 100;
            sizze += 20;
            if (sound_active) TabbozPlaySound(206);
        }
        MsgIcona(ICONA_AVVISO);
        fl_message_title("ART. 46 L. 29/12/1990 n. 428");
        fl_alert(StrTabacco[rand() % 7]); // messaggio random contro il fumo

        Evento(false);
    }
}


/* Proposta vestito rosso se in periodo natalizio */
bool OfferteDiNatale(void)
{
    char tmp[128];

    if ((x_mese == 12) && (Soldi >= VestitiMem[GIUBBOTTO_BABBO].prezzo)) {
        if ((x_giorno > 14) && ( x_giorno < 25) && (current_giubbotto!=GIUBBOTTO_BABBO) && (current_pantaloni!=(PANTALONI_BABBO - I_PANTALONI))) {
            sprintf(tmp,"Vuoi comperare, per %s, un meraviglioso vestito da Babbo Natale ?",MostraSoldi(VestitiMem[GIUBBOTTO_BABBO].prezzo));
            MsgIcona(ICONA_DOMANDA);
            fl_message_title("Offerte Natalizie...");
            if(fl_choice(tmp,"No","Si!",0)) {
                current_giubbotto=GIUBBOTTO_BABBO;
                current_pantaloni=PANTALONI_BABBO - I_PANTALONI;
                Soldi-=VestitiMem[GIUBBOTTO_BABBO].prezzo;
                return true;  //se compriamo il vestito (per far chiudere il launcher negozi)
            }
        }
    }
    return false;  //in tutti gli altri casi
}