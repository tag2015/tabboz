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
#include "dialogs.h"
#include "sound.h"
#include "debug.h"

#include "calendario.h"

#include "telefono.h"
#include "gui/GUITelefonia.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


/* Dati cellulare del tabbozzo */
STCEL CellularData;

/* Elenco cellulari disponibili */
STCEL CellularMem[] = {
    {0,  2, 100, 290, "Motorolo d170" },
    {0,  7, 100, 590, "Motorolo 8700" },
    {1, 10, 100, 990, "MacroTAC 8900" },
};

/* Dati abbonamento cell del tabbozzo */
STABB AbbonamentData;

/* Elenco sim disponibili e costi ricarica */
STABB AbbonamentMem[] = {
    {1,  0,   50,  1,  100,  "Onmitel"},    // Abbonamenti
    {1,  0,   50,  1,  100,  "DIM"},
    {1,  1,  100,  1,  100,  "Vind"},
    {0,  0,   50,  1,   60,  "Onmitel"},    // Ricariche
    {0,  0,  100,  1,  110,  "Onmitel"},
    {0,  0,   50,  1,   60,  "DIM"},        // Ricariche
    {0,  0,  100,  1,  110,  "DIM"},
    {0,  1,   50,  1,   50,  "Vind"},       // Ricariche
    {0,  1,  100,  1,  100,  "Vind"},
    };



/* Aggiorna finestra telefonia */
void AggiornaCell(void)
{
    tel_val_soldi->value(CALCSOLDI(Soldi));

    if (CellularData.stato > -1)
        tel_txt_nome->value(CellularData.nome);
    else
        tel_txt_nome->value("-- nessuno --");

    if (AbbonamentData.creditorest > -1) {
        tel_txt_abb->value(AbbonamentData.nome);
        tel_txt_credito->value(MostraSoldi(AbbonamentData.creditorest));    // Credito
    } else {
        tel_txt_abb->value("-- nessuno --");
        tel_txt_credito->value(" -- ");
    }
    win_telefonia->redraw();
}


/* Routine controllo soldi e aggiorna cell/figosità */
bool CompraCellulare(int scelta)
{
    if (Soldi < CellularMem[scelta].prezzo) { // Controlla se ha abbastanza soldi...
        nomoney(CELLULRABBONAM);
        return false;
    }

    Soldi-=CellularMem[scelta].prezzo;
    CellularData=CellularMem[scelta];
    Fama+=CellularMem[scelta].fama;
    if (Fama > 100) Fama=100;

    if(logging)
        writelog("telefono: Compra cellulare");
    return true;
}


/* Routine per vendere cellulare usato */
bool VendiCellulare(void)
{
    char  tmp[128];
    int offerta;

    fl_message_title("Vendi Telefonino");
    if (CellularData.stato > -1) {
        offerta=CellularData.prezzo/2 + 15;
        MsgIcona(ICONA_DOMANDA);
        sprintf(tmp,"Ti posso dare %s per il tuo telefonino... vuoi vendermelo ?",MostraSoldi(offerta));
        if( ! fl_choice(tmp,"Ok","No",0) ) {
            CellularData.stato=-1;
            Soldi+=offerta;
            return true;
        } else {
            MsgIcona(ICONA_AVVISO);
            fl_alert("Allora vai a farti fottere, pirletta!");
        }
    } else {
        MsgIcona(ICONA_DOMANDA);
        fl_alert("Che telefonino vuoi vendere, pirletta?");
    }

    return false;
}


/* FIXME visualizzare prezzi leggendoli dalla matrice nella gui */
/* FIXME dual band non è considerato */

/* Routine acquisto abbonamento (sim) e ricariche cellulare */
bool AbbonaCellulare(int scelta)
{
    if (Soldi < AbbonamentMem[scelta].prezzo) {    // Controlla se ha abbastanza soldi...
        nomoney(CELLULRABBONAM);
        return false;
    }

    if (AbbonamentMem[scelta].abbonamento == 1) {    // Abbonamento, no problem...
        Soldi-=AbbonamentMem[scelta].prezzo;
        AbbonamentData=AbbonamentMem[scelta];
        if ((sound_active) && (CellularData.stato > -1)) TabbozPlaySound(602);
        return true;
    
    } else {    // Ricarica...
        if (( AbbonamentData.creditorest > -1) && ( !strcmp(AbbonamentData.nome,AbbonamentMem[scelta].nome))) {
            Soldi-=AbbonamentMem[scelta].prezzo;
            AbbonamentData.creditorest+=AbbonamentMem[scelta].creditorest;
            if ((sound_active) && (CellularData.stato > -1)) TabbozPlaySound(602);
            return true;
            
        } else {
            MsgIcona(ICONA_DOMANDA);
            fl_message_title("Telefonino");
            fl_alert("Oh, che te ne fai di una ricarica se non hai la sim ???");
            return false;
        }
    }
    return false;
}