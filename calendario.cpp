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

#include "scuola.h"
#include "lavoro.h"
#include "eventi.h"  // per gli auguri di natale

#include "debug.h"

#include "calendario.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>

#include "gui/GUITabboz.h"  // Per aggiornare la data sulla finestra principale

//static char sccsid[] = "@(#)" __FILE__ " " VERSION " (Andrea Bonomi) " __DATE__;


typedef struct tagVACANZE {
    char   const *nome;          // nome del giorno di vacanza
    int    giorno;               // giorno
    int    mese;                 // mese
    char   const *descrizione;   // descrizione giorno di vacanza
} STVACANZE;

const STMESI InfoMese[] = {
    {"Gennaio",   31},
    {"Febbraio",  28},
    {"Marzo",     31},
    {"Aprile",    30},
    {"Maggio",    31},
    {"Giugno",    30},
    {"Luglio",    31},
    {"Agosto",    31},
    {"Settembre", 30},
    {"Ottobre",   31},
    {"Novembre",  30},
    {"Dicembre",  31}
};


const STGIORNI InfoSettimana[] = {
    {"Lunedì",     0},
    {"Martedì",    0},
    {"Mercoledì",  0},
    {"Giovedì",    0},
    {"Venerdì",    0},
    {"Sabato",     0},
    {"Domenica",   1}
};


const STVACANZE InfoVacanze[] =
    { {"Capodanno",                 1,   1, "Oggi è Capodanno !"},
      {"Epifania",                  6,   1, "Epifania..."},
      {"Anniversario Liberazione", 25,   4, "Oggi mi sento liberato"},
      {"Festa dei Lavoratori",      1,   5, "Nonostante nella tua vita, tu non faccia nulla, oggi fai festa anche tu..."},
      {"Ferragosto",               15,   8, "Oggi e' ferragosto..."},
      {"Tutti i Santi",             1,  11, "Figata, oggi è vacanza..."},
      {"Sant'Ambrogio",             7,  12, "Visto che siamo a Milano, oggi facciamo festa."},
      {"Immacolata Concezione",     8,  12, "Oggi è festa..."},
      {"Natale",                   25,  12, "Buon Natale !!!"},
      {"Santo Stefano",            26,  12, "Buon Santo Stefano..."},
      { NULL,                       0,   0, NULL} };


int  x_giorno;         // giorno corrente (1-31)
int  x_giornoset;      // giorno settimana corrente (1-7)
int  x_mese;           // mese corrente (1-12)
int  x_anno_bisesto;   // anno bisestile (contatore 0-3, 0 è anno bisesto)

int  x_vacanza;        // 0: giorno lavorativo | 1: vacanza tipo 1 (negozi aperti) | 2: vacanza tipo 2 (negozi chiusi)

int  scad_pal_giorno;  // Giorno e mese in cui scadra' l' abbonamento alla palestra
int  scad_pal_mese;


/* Giorno - Incrementa il giorno corrente controllando il calendario e attiva eventi programmati*/
void Giorno(void)
{
    
    char tmp[255];
    bool auguri_tipa = FALSE;

    x_giorno++;
    if (x_giorno > InfoMese[x_mese-1].num_giorni) {
        if ((x_mese == 2) && (x_anno_bisesto == 0) && (x_giorno == 29)) {
            fl_message_title("Anno Bisestile");
            fl_message("Anno bisesto, anno funesto...");
        } else {
            x_giorno=1;
            x_mese++;
        }
    }

    if (x_mese > 12) {
        x_mese = 1;
        x_anno_bisesto++;
        if (x_anno_bisesto > 3) x_anno_bisesto=0;
    }

    x_giornoset++;
    if (x_giornoset > 7) {
        x_giornoset=1;
        if (current_testa > 0 ) {
            current_testa--;    // Ogni 7 giorni diminuisce l' abbronzatura FIXME cosi decrementa sempre al lunedi
        }
    }

    /* Decrementa contatore giorni per soldi aggiuntivi dalla famiglia */
    if(AttesaSoldi>0)
        AttesaSoldi--;

    /* ---------------> S T I P E N D I O <--------------- */
    if (impegno > 0)  {

        giorni_di_lavoro++;
        
        if ((x_giorno == 27) && (giorni_di_lavoro > 3)) {
            int totale_stipendio;
            if ( giorni_di_lavoro > 29)
                totale_stipendio=stipendio;  // se g.d.l. > 29, stipendio intero...
            else
                totale_stipendio = stipendio * (giorni_di_lavoro / 30.0 );  // se g.d.l. < 29, calcolato per i giorni effettivi

            giorni_di_lavoro=1;

            fl_message_title("Stipendio!");
            fl_message("Visto che sei stat%c %s brav%c dipendente sottomess%c, ora ti arriva il tuo misero stipendio di %s",ao, un_una, ao, ao, MostraSoldi(totale_stipendio));
            Soldi+=totale_stipendio;

            #ifdef LOGGING
                sprintf(tmp,"giorno: Stipendio (%s)",MostraSoldi(totale_stipendio));
                writelog(tmp);
            #endif
        }
    }


    /* ---------------> P A L E S T R A <---------------  */
    if (scad_pal_mese == x_mese)
        if (scad_pal_giorno == x_giorno) {
            fl_message_title("Palestra");
            fl_message("E' appena scaduto il tuo abbonamento della palestra...");
            scad_pal_giorno = 0;
            scad_pal_mese = 0;
            #ifdef LOGGING
                writelog("giorno: E' scaduto l'abbonamento alla palestra");
            #endif
            }


    x_vacanza=0;     // 0 = giorno lavorativo
    current_tipa=0;  // imposta vestiti standard della tipa

    switch (x_mese) {       /* Vacanze di TIPO 1 (negozi aperti) */
        case 1: /* Gennaio --------------------------------------------------------- */
                if (x_giorno < 7 ) {       /* Vacanze di Natale */
                    x_vacanza=1;
                    if (Rapporti > 0 ) current_tipa=1;  /* Tipa vestita da Babbo Natale...*/
                }
                break;

        case 6: /* Giugno ---------------------------------------------------------- */
                if (x_giorno == 15) {
                    fl_message_title("Ultimo giorno di scuola");
                    fl_message("Da domani iniziano le vacanza estive!");
                }
                if ((x_giorno == 22) && (win_principale)) {  /* Mostra pagella (controlla se inizializzato)*/
                    if(MostraPagella()) {
                        fl_message_title("Studiare paga...");
                        fl_message("Visto che sei stato promosso,\nti diamo un po' di mancia...");
                        Soldi+=200;
                        if(Paghetta<30)     // Se è inferiore, riporta al valore standard
                            Paghetta=30;
                    } else {
                        fl_message_title("Too cool for school");
                        fl_message("Visto che ti sei fatto bocciare,\npaghetta dimezzata!!!");
                        Paghetta/=2;
                        if(Paghetta<5)
                            Paghetta=5;    //al massimo scendiamo a 5000 lire
                    }
                }
                if (x_giorno > 15)  /* inizio vacanze estive */
                    x_vacanza=1;
                break;
        
        case 7: /* Luglio e ------------------------------------------------------ */
        case 8: /* Agosto -------------------------------------------------------- */
                x_vacanza=1;
                if ((Rapporti > 93) && (FigTipa > 95 ))
                    current_tipa=2;   /* Tipa al mare...*/
                break;

        case 9: /* Settembre ------------------------------------------------------- */
                if (x_giorno < 15) x_vacanza=1;   /* Vacanze Estive */
                if (x_giorno == 15) {
                    fl_message_title("Primo giorno di scuola");
                    fl_message("Questa mattina devi tornare a scuola...");
                    for (int i=1;i<10;i++)    /* Azzera le materie... */
                        MaterieMem[i].voto=2;
                    CalcolaStudio();    
                }
                break;

        case 12: /* Dicembre -------------------------------------------------------- */
                if (x_giorno > 22) { /* Inizio Vacanze di Natale */
                    x_vacanza=1;
                    if (Rapporti > 0 ) current_tipa=1; /* Tipa vestita da Babbo Natale... */
                }
                if (x_giorno == 25) {  /* Natale */
                    if ((current_pantaloni == 19) && (current_gibbotto == 19)) {
                        fl_message_title("Natale...");
                        fl_message("Con il tuo vestito da Babbo Natale riesci a stupire tutti...");
                        Fama+=20;
                        if (Fama > 100) Fama=100;
                    }
                    if (Rapporti > 30) { /* Buon Natale dalla tipa */
                        FinestraEvento(8,8,"Tanti Auguri",FALSE);
                        auguri_tipa = TRUE;
                    }
                }
                if ((x_giorno == 28) && ((current_pantaloni == 19) || (current_gibbotto == 19))) {
                    fl_message_title("Natale...");
                    fl_message("Natale è già passato... Togliti quel dannato vestito...");
                    Fama-=5;
                    if (Fama < 0) Fama=0;
                }
                break;

    }

    /* Domeniche e festivita' varie - Vacanze di TIPO 2 (negozi chiusi)*/

    if (x_giornoset == 7 ) x_vacanza=2;    /* Domenica */

    int i = 0;
    while( InfoVacanze[i].giorno != 0 ) {
        if (InfoVacanze[i].mese == x_mese)
            if (InfoVacanze[i].giorno == x_giorno) {
                if(auguri_tipa)  break; // se già visualizzato "buon natale", usciamo dal ciclo
                fl_message_title(InfoVacanze[i].nome);
                fl_message(InfoVacanze[i].descrizione);
                x_vacanza=2;        /* 2 = sono chiusi anche i negozi... */
            }
        i++;
    }
        

    #ifdef LOGGING
        /* Mostra data e soldi */
        sprintf(tmp, "giorno: %s %d %s, %s",InfoSettimana[x_giornoset-1].nome,x_giorno,InfoMese[x_mese-1].nome,MostraSoldi(Soldi));
        writelog(tmp);
    #endif

    /* Aggiorna il calendario sulla finestra principale */
    if(win_principale) {   // Controlla che sia inizializzata altrimenti crasha tutto
        sprintf(tmp, "  %s %d %s",InfoSettimana[x_giornoset-1].nome,x_giorno,InfoMese[x_mese-1].nome);  // Calendario
        main_box_giorno->copy_label(tmp);
        win_principale->redraw();
    }

}