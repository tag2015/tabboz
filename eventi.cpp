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
#include "scuola.h"
#include "lavoro.h"
#include "scooter.h"
#include "telefono.h"

#include "eventi.h"
#include "gui/GUIEvento.h"
#include "gui/GUITipa.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>

static char txt_finestra[256];  // stringa per le finestre metallari/scooter/camion


/* Generatore Eventi (Casuali e Non) */
/* Se no_alerts = true, non vengono visualizzati i messagebox (utile per funzionamento automatico) */
void Evento(bool no_alerts)
{
    int     caso,i;
    char    tmp[128];
    char    messaggio[256];

    if (Fortuna < 0) Fortuna = 0;        // Prima che qualcuno bari...
    if (Fortuna > 100) Fortuna = 100;


    Giorno(no_alerts);  // avanza il calendario

    if (tempo_pestaggio > 0)
        tempo_pestaggio--;

/* Sigarette -------------------------------------------------------- */
    if (sizze > 0){
        sizze--;
        if (sizze == 0) {
            MsgIcona(ICONA_STOP);
            fl_message_title("Sei senza sigarette!");
            if (!no_alerts) fl_alert("Apri il tuo pacchetto di sigarette e lo trovi disperatamente vuoto...");
            if (Reputazione > 10) Reputazione -= 3;
            if (logging)
                writelog("eventi: Sigarette finite!");
        } else if (sizze < 3) {
            MsgIcona(ICONA_AVVISO);
            fl_message_title("Sigarette...");
            if (!no_alerts) fl_message("Ti accorgi che stai per finire le tue sizze.");
        }
    }


/* Cellulare ---------------------------------------------------- */
    if ((AbbonamentData.creditorest > 0) && (CellularData.stato > 0)) {
        AbbonamentData.creditorest-=1;
        if (Fama < 55) Fama++;
        if (AbbonamentData.creditorest == 0) {
            MsgIcona(ICONA_STOP);
            fl_message_title("Telefonino");
            if (!no_alerts) fl_alert("Cerchi di telefonare e ti accorgi di aver finito i soldi a tua disposizione...");
            if (logging)
                writelog("eventi: Cellulare - credito esaurito!");
        } else if (AbbonamentData.creditorest < 3) {
            MsgIcona(ICONA_AVVISO);
            fl_message_title("Telefonino");
            if (!no_alerts) fl_message("Ti accorgi che stai per finire la ricarica del tuo telefonino.");
        }
    }

    if ((CellularData.stato <= 0) && (CellularData.stato != -100)) {
        CellularData.stato=-100;
        MsgIcona(ICONA_STOP);
        fl_message_title("Telefonino KO");
        if (!no_alerts) fl_alert("Dopo una vita di duro lavoro, a furia di prendere botte,\nil tuo cellulare si spacca...");
        if (logging)
            writelog("eventi: Cellulare - distrutto!");
    }


/* Paghetta --------------------------------------------------------- */

    if (x_giornoset == 6) {        // Il Sabato c'e' la paghetta...

        if (Studio >= 45) {
            Soldi+=Paghetta;
            if(logging) {
                sprintf(log_buf,"eventi: Paghetta (%s)",MostraSoldi(Paghetta));
                writelog(log_buf);
            }

            if (Studio >= 80) {
                if (sound_active) TabbozPlaySound(1201);
                Soldi+=Paghetta;
                MsgIcona(ICONA_COOL);
                fl_message_title("Paghetta settimanale");
                if (!no_alerts) fl_message("Visto che vai bene a scuola, ti diamo il doppio della paghetta...");
                if (logging)
                    writelog("eventi: Paghetta doppia !!!");
            }

        } else {  // Studio < 45
            if (sound_active) TabbozPlaySound(1200);
            Soldi+=(Paghetta / 2);
            MsgIcona(ICONA_STOP);
            fl_message_title("Paghetta settimanale");
            if (!no_alerts) fl_message("Finchè non andrai bene a scuola, ti daremo solo metà della paghetta...");
            if (logging) {
                sprintf(log_buf,"eventi: Mezza paghetta (%s)...",MostraSoldi(Paghetta));
                writelog(log_buf);
            }
        }
    }


#ifndef NORANDOM
/* Rapporti Tipa ---------------------------------------------------- */
    if (Rapporti > 3) {
        i=rand() % 5 - 3;      // peggioramento random dei rapporti
        if (i > 0) {
            Rapporti--;
            #ifdef TABBOZ_DEBUG
                sprintf(tmp,"eventi: Peggioramento random rapporti (-1) i=%d",i);
                writelog(tmp);
            #endif
        }
    }

    if ((Rapporti > 0) && (Rapporti < 98)) {
        i=rand() % (((Rapporti + Fortuna + Fama )* 3) + 1);
        if (i < 10) {                    /* da 1 a 10, la donna ti molla... */
            if (sound_active) TabbozPlaySound(603);
            Rapporti=0;
            FigTipa=0;
            if (sesso == 'M') {
                MsgIcona(ICONA_STOP);
                fl_message_title("La tipa ti molla...");
                if (!no_alerts) fl_alert(StrEventi[MSG_TIPA+i]);  // 0<i<9, 10 possibili messaggi
            } else {
                MsgIcona(ICONA_STOP);
                fl_message_title("Vieni mollata...");
                if (!no_alerts) fl_alert(StrEventi[MSG_TIPO+i]);  // 0<i<9, 10 possibili messaggi
            }
            Reputazione-=(10 - i);    // quelle con numero piu' basso, sono peggiori...
            if (Reputazione < 0) Reputazione = 0;
            if (logging)
                writelog("eventi: Tipa/o ti molla...");
        }
    }


/* Lavoro ----------------------------------------------------------- */
    if (impegno > 3) {
        i= (rand() % 7) - 3;       // peggioramento random dell'impegno
        if (i > 0) {
            impegno--;
            #ifdef TABBOZ_DEBUG
                sprintf(tmp,"eventi: Peggioramento random impegno (-1) i=%d",i);
                writelog(tmp);
            #endif
        }
    }

    if (numeroditta > 0) {
        i = rand() % (impegno * 2 + Fortuna * 3);
        #ifdef TABBOZ_DEBUG
            sprintf(tmp,"eventi: Licenziamento random (se i<2) i=%d",i);
            writelog(tmp);
        #endif
        if (i < 2) {           // perdi il lavoro
            impegno=0;
            giorni_di_lavoro=0;
            stipendio=0;
            numeroditta=0;
            if (sound_active) TabbozPlaySound(504);
            MsgIcona(ICONA_STOP);
            fl_message_title("Perdi il lavoro...");
            if (!no_alerts) fl_alert("Un bel giorno ti svegli e scopri di essere stat%c licenziat%c.",ao,ao);
            if (logging)
                writelog("eventi: Perdi il lavoro...");
        }
    }


/* Eventi casuali --------------------------------------------------- */
    caso = rand() % (100+(Fortuna*2));

    #ifdef TABBOZ_DEBUG
        sprintf(tmp,"eventi: Evento casuale n. %d",caso);
        writelog(tmp);
    #endif

    if (caso < 51) {    // se il n.ro estratto è <=50, attiva un evento
        switch (caso) {
                       
            case  1:  // 1-10: Rissa con Metalloni o Manovali
            case  2:
            case  3:
            case  4:
            case  5:
            case  6:
            case  7:
            case  8:
            case  9:
            case 10:
                if (sesso == 'F') break; // Se sei una tipa non vieni pestata...
                Reputazione-=caso;
                if (Reputazione < 0) Reputazione = 0;

                if(sound_active) TabbozPlaySound(1400);

                i=rand() % 6;    /* estrae un metallaro a caso 0-5 */
                if(i<=4) {
                    if (!no_alerts) FinestraEvento(i,i,"Rissa con un metallaro",true);  //metallari
                }
                else {
                    if (!no_alerts) FinestraEvento(i,i,"Rissa con un manovale",false);  //manovale
                }
                if (logging) {
                    sprintf(log_buf,"eventi: Rissa con metallaro/manovale n. %d",i);
                    writelog(log_buf);
                }
                tempo_pestaggio=5;
                break;

// -------------- Scooter -----------------------------------------------------------------------

            case 11:  // 11-20: Eventi con lo scooter
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
                if ((ScooterData.stato > -1000) && (ScooterData.attivita == 1)) {  //BUGFIX & mancante
        
                    if (CellularData.stato > 0) {                    //incidente danneggia anche il cell
                        CellularData.stato-=rand() % 8;
                        // impostando a 0 lo rileva come rotto al prossimo evento
                        if (CellularData.stato < 0 ) CellularData.stato=0;  //FIXME rivedere condizioni 0 o -1
                    }

                    if(sound_active) TabbozPlaySound(1401);

                    if (caso < 15) {  // Camionista - ( caso 11-14) BUGFIX visto che danneggia + del muro, abbasssato di 2 i possibili casi
                        ScooterData.stato-=35;
                        if (!no_alerts) FinestraEvento(6,6,"Fai incazzare un camionista",false);  //camionista
                        if(logging)
                            writelog("eventi: Scooter - Ciocco con camionista...");
                    
                    } else {  // Muro ! ( caso 15 - 20) -------------------
                        ScooterData.stato-=20;
                        if (!no_alerts) FinestraEvento(7,7,"Incidente",false);  //muro
                        if(logging)
                            writelog("eventi: Scooter - A muro...");
                    }

                    Reputazione-=2;
                    if (Reputazione < 0) Reputazione = 0;
                    if (ScooterData.stato <= 0) {
                        MsgIcona(ICONA_STOP);
                        fl_message_title("Scooter Distrutto");
                        if (!no_alerts) fl_alert("Quando ti rialzi ti accorgi che il tuo scooter è ormai ridotto ad un ammasso di rottami.");
                        ScooterData.stato = 0;
                        ScooterData.attivita=0;  //anziche azzerare lo scooter, lo incidentiamo
                        if(logging)
                            writelog("eventi: Scooter distrutto (stato <=0)");
                    }
                }
                break;

// -------------- Figosita' --------------------------------------------------------------------

        case 21:            //  + gravi    21-30: sfighe varie
        case 22:            //  |
        case 23: Fama-=5;   //  |
        case 24:            //  |
        case 25: Fama-=1;   //  |
        case 26:            //  |
        case 27: Fama-=1;   //  |
        case 28:            // \|/
        case 29:            //  - gravi
        case 30:
            MsgIcona(ICONA_AVVISO);
            sprintf(tmp,"Sei fortunat%c...",ao);
            fl_message_title(tmp);
            if (!no_alerts) fl_alert(StrEventi[MSG_SFIGHE+(caso - 21)]);  // togliamo 21 da caso per renderlo 0-9
            Fama-=2;
            if (Fama < 0) Fama = 0;
            if(logging)
                writelog("eventi: Evento riguardante la figosita'...");
            break;

// -------------- Skuola --------------------------------------------------------------------------

        case 31:   // 31-40 eventi scolastici (peggiorano una materia)
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            if (!x_vacanza) {  // Durante i giorni di vacanza non ci sono eventi riguardanti la scuola

                i = (rand() % 9) + 1;  // materia a random 1-10
                strcpy(messaggio,StrEventi[MSG_SCUOLA+(caso - 31)]); // togliamo 31 da caso per renderlo 0-9
                strcat(messaggio,MaterieMem[i].nome);   //accoda nome materia al messaggio
                MsgIcona(ICONA_AVVISO);
                fl_message_title("Scuola...");
                if (!no_alerts) fl_alert(messaggio);
           
                MaterieMem[i].voto-=2;
                if(MaterieMem[i].voto < 2) MaterieMem[i].voto=2;
                CalcolaStudio();
                if(logging)
                    writelog("eventi: Evento riguardante la scuola...");
            }
            break;

// -------------- Tipa/o ---------------------------------------------------------------------------

        case 41:
        case 42: // 41-42: Una tipa/o ci prova...

            if (no_alerts) break;  // Salta evento interattivo se in modalità automatica
            if (Fama < 35) break;  // Figosita' < 35 = nessuna speranza...

            if(logging)
                writelog("eventi: Una tipa/o ci prova...");

            int     figTemp;
            int     i_nomeTemp;

            figTemp = (rand() % (Fama-30) ) + 30;   // Figosita' minima tipa = 30...

            if (sesso == 'M') {
                i_nomeTemp = rand() % NUM_TIPE;    // pesca il nome di una tipa
                sprintf(tmp,"Una tipa, di nome %s (Figosità %d/100), ci prova con te...\nCi stai ???",StrNomiTipe[i_nomeTemp],figTemp);
            } else {
                i_nomeTemp = rand() % NUM_TIPI;    // pesca il nome di un tipo
                sprintf(tmp,"Un tipo, di nome %s (Figosità %d/100), ci prova con te...\nCi stai ???",StrNomiTipi[i_nomeTemp],figTemp);
            }

            MsgIcona(ICONA_DOMANDA);
            fl_message_title("Qualcuno ti caga...");
            if( !fl_choice(tmp, "No...", "SI!!!", 0) ) {
                if ((figTemp >= 79) && (Rapporti < 1) && (sesso == 'M') ) { // scelta NO - Se non hai gia' una tipa e rifiuti una figona...
                    MsgIcona(ICONA_STOP);
                    fl_message_title("Idiota...");
                    fl_alert("Appena vengono a sapere che non ti vuoi mettere insieme ad una figona come quella, i tuoi amici ti prendono a scarpate.");
                    Reputazione-=4;
                    if (Reputazione < 0) Reputazione=0;
                }
                break;
            }
            // scelta SI
            // Controlla che tu non abbia gia' una tipa -------------------------
            if (Rapporti > 0) { // hai gia' una tipa..<<<<<<<<<<<<<<<<<<<<<<<<<<<
                GUICasanova(i_nomeTemp,figTemp);  // FIXME completare per la tabbozza
                win_duetipe->show();
                while(win_duetipe->shown()) Fl::wait();
                break;
            } else { // bravo, non hai una tipa...<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                if (sesso == 'M')
                    sprintf(Nometipa,"%s",StrNomiTipe[i_nomeTemp]);
                else
                    sprintf(Nometipa,"%s",StrNomiTipi[i_nomeTemp]);
                FigTipa=figTemp;
                Rapporti=45 + (rand() % 15);
                Fama+= (FigTipa / 10);
                if (Fama > 100) Fama=100;
                Reputazione+= (FigTipa / 13);
                if (Reputazione > 100) Reputazione=100;
            }
            break;


        case 43: // 43-44: Domande inutili...
        case 44:

            if (no_alerts) break;  // Salta evento interattivo se in modalità automatica

            if(logging)
                writelog("eventi: Domande inutili della tipa...");

            if ((Rapporti > 0) && (sesso == 'M')) {
                if (caso == 43) {
                    MsgIcona(ICONA_DOMANDA);
                    fl_message_title("Domande inutili della tipa...");
                    if ( fl_choice("Mi ami ???", "Sì", "No", 0) ) {
                        MsgIcona(ICONA_STOP);
                        fl_message_title("Risposta sbagliata...");
                        fl_alert("Sei sempre il solito stronzo... non capisco perchè resto ancora con uno come così...");
                        Rapporti-=45;
                        if (Rapporti < 5) Rapporti=5;
                    }
                } else {
                    MsgIcona(ICONA_DOMANDA);
                    fl_message_title("Domande inutili della tipa...");
                    if ( fl_choice("Ma sono ingrassata ???", "No", "Sì", 0) ) {
                        MsgIcona(ICONA_STOP);
                        fl_message_title("Risposta sbagliata...");
                        fl_alert("Sei un bastardo, non capisci mai i miei problemi...");
                        Rapporti-=20;
                        if (Rapporti < 5) Rapporti=5;
                    }
                }
            }
            break;

        case 45:
        case 46:
        case 47:
        case 48:
            #ifdef TABBOZ_DEBUG
                writelog("eventi: Evento riguardante la tipa/o (NON IMPLEMENTATO)");
            #endif
            break;

// -------------- Vari ed eventuali ----------------------------------------------------------------

        case 49:
        case 50:
            if (CellularData.stato > 0) {
                CellularData.stato -= (rand() % 8);    // 0 = 'morente', <0 = 'morto'
                if (CellularData.stato < 0 ) CellularData.stato=0;
                MsgIcona(ICONA_AVVISO);
                fl_message_title("Telefonino");
                if (!no_alerts) fl_alert("Il telefonino ti cade di tasca e vola per terra...");
                if(logging)
                    writelog("eventi: Telefonino - Cade...");
            }
            break;

        default:
            break;
        }
    }
#endif
}


/* Eventi casuali legati alla palestra */
void EventiPalestra(void)
{
    int i;

    i=rand() % (29 + (Fortuna / 2));

    if (i > 9) return;    /* eventi: 0 - 10) */

    MsgIcona(ICONA_AVVISO);
    fl_message_title("Palestra...");
    fl_alert(StrEventi[MSG_PALESTRA+i]);
    if (Reputazione > 10)
        Reputazione-=4;
    
    if (logging)
        writelog("eventi: Evento riguardante la palestra");
}


/* Dialog per eventi con immagine dedicata */
/* nro evento in elenco img condivise | nro stringa in elenco testi eventi | titolo finestra | orientamento immagine*/
void FinestraEvento(int n_evento, int n_testo, const char *titolo, bool verticale)
{
    char tail[128];
    char via[128];
    char *pos;

    strcpy(txt_finestra,StrEventiFinestra[n_evento]);  //copia testo evento
    
    pos = strstr(txt_finestra, "_NOMEVIA_");  // cerca token da sostituire con nome via 
    if(pos) {
        strcpy(tail, (pos+strlen("_NOMEVIA_")));  // crea stringa tail dalla precedente togliendo il token
        strcpy(via, StrNomiStrade[(rand() % 50)]);  //copia una via a caso
        strcpy(pos, via);  //accoda una via a caso
        strcpy( (pos+strlen(via)) , tail); //accoda rimanenza
    }

    if(verticale) {   // finestra a 2 colonne con immagine verticale
        GUIEventoVert(n_evento, txt_finestra);
        win_evento_v->label(titolo);
        win_evento_v->show();
        while(win_evento_v->shown()) Fl::wait();    // attende chiusura dialog
    } else {    // finestra con immagine sopra e testo sotto
        GUIEventoOriz(n_evento, txt_finestra);
        win_evento_o->label(titolo);
        win_evento_o->show();
        while(win_evento_o->shown()) Fl::wait();    // attende chiusura dialog

    }
}