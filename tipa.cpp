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

#include "eventi.h"
#include "telefono.h"
#include "scooter.h"

#include "tipa.h"
#include "gui/GUITipa.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


const char *DescrizioneTipa(int f);
const char *DescrizioneTipo(int f);
int DueDiPicche(void);


/* Aggiorna Finestra Tipa */
void AggiornaTipa(void)
{
    if (Rapporti == 0) {
        if ( sesso == 'M')
            tipa_btn_cercatipa->label("Cerca Tipa");
        else
            tipa_btn_cercatipa->label("Cerca Tipo");

    tipa_grp_stats->deactivate();
    tipa_txt_nome->copy_label("Nessuna...");
    tipa_val_fama->value(0);
    tipa_val_rapporti->value(0);
    
    } else {
        if ( sesso == 'M')
            tipa_btn_cercatipa->label("Cerca Nuova Tipa");
        else
            tipa_btn_cercatipa->label("Cerca Nuovo Tipo");
        tipa_grp_stats->activate();
        tipa_txt_nome->copy_label(Nometipa);
        tipa_val_figosita->value(FigTipa);
        tipa_val_rapporti->value(Rapporti);
    }
    tipa_val_fama->value(Fama);
    if(AbbonamentData.creditorest>0)
        tipa_val_credito->value(CALCSOLDI(AbbonamentData.creditorest));
    else
        tipa_val_credito->value(0);
}


/* Cerca tipa - Randomizza un nome e figosità */
void CercaTipa(void)
{
    if(sesso == 'M')
        n_nuovatipa = rand() % NUM_TIPE;    // randomizza nome tipa
    else
        n_nuovatipa = rand() % NUM_TIPI;    // randomizza nome tipo
    fig_nuovatipa = rand() % 71 + 30;  // randomizza figosita 30 -> 100

    if (sesso == 'M') {
        cercatipa_txt_nome->value(StrNomiTipe[n_nuovatipa]);
        cercatipa_txt_giudizio->value(DescrizioneTipa(fig_nuovatipa));
    } else {
        cercatipa_txt_nome->value(StrNomiTipi[n_nuovatipa]);
        cercatipa_txt_giudizio->value(DescrizioneTipo(fig_nuovatipa));
    }
    cercatipa_val_figosita->value(fig_nuovatipa);
}


/* Check per vedere se riesce a rimorchiare la tipa/o */
bool Provaci(void)
{
    // Calcola se ce la fa o meno con la tipa...
    if ( ((fig_nuovatipa * 2) + ( rand() % 50)) <= ( Fama + Reputazione + (rand() % 30)) )  {
    
        // E' andata bene...
        MsgIcona(ICONA_COOL);
        if (sesso == 'M') {
            fl_message_title("E' andata bene!");
            fl_message("Con il tuo fascino nascosto da tabbozzo, seduci la tipa e ti ci metti insieme.");
        } else {
            fl_message_title("Qualcuno ti caga...");
            fl_message("Ora non ti puoi più lamentare di essere sola...");
        }
    return true;
    }

    return false;
}


/* 2 di picche (la vita e' bella...) - Calcola malus e ritorna un messaggio a caso */
int DueDiPicche(void)
{
    DDP++;    // log due di picche...
    
    Reputazione-=2;    // decremento reputazione
    if (Reputazione < 0) Reputazione=0;
    
    Fama-=2;    // decremento figosita'
    if (Fama < 0) Fama=0;

    return (rand() % 20);  // estrae una risposta (0-19)
}


/* Telefona tipa consumando credito del cell o soldi */
void TelefonaTipa(void)
{
    if (Rapporti <= 0)  {
        MsgIcona(ICONA_DOMANDA);
        fl_message_title("Non sei molto intelligente...");
        if (sesso == 'M')
            fl_alert("Scusa, che ragazza vorresti chiamare ???");
        else
            fl_alert("Scusa, che ragazzo vorresti chiamare, visto che sei sola ???");
        return;
    }
//FIXME questo check è sbagliato, bisogna separare i due casi (pochi soldi e nocell, oppure cell ma abbo basso)
    if ((Soldi <= 5) && ((AbbonamentData.creditorest < 2) && (CellularData.stato < 0) )) {
        MsgIcona(ICONA_AVVISO);
        fl_message_title("Non toccare quel telefono...");
        fl_alert("<< Sei fai ancora una telefonata, ti spezzo le gambe... >>\n disse tuo padre con una accetta in mano...");
    
    } else {
        if (Rapporti <= 60) Rapporti++;
        if (sound_active) TabbozPlaySound(602);
        if ((AbbonamentData.creditorest >= 2) && (CellularData.stato > -1))
            AbbonamentData.creditorest-=2;
        else
            Soldi-=5;
        #ifdef TABBOZ_DEBUG
            sprintf(log_buf,"tipa: Telefona alla tipa/o (%s)",MostraSoldi(5));
            writelog(log_buf);
        #endif
    }
    AggiornaTipa();
}


/* Esce con tipa se disponibile scooter e sufficienti soldi */
void EsciConTipa(void)
{
    if (Rapporti <= 0)  {
        MsgIcona(ICONA_DOMANDA);
        fl_message_title("Non sei molto intelligente...");
        if (sesso == 'M')
            fl_alert("Scusa, con che tipa vorresti uscire ???");
        else
            fl_alert("Scusa, ma con chi vorresti uscire ???");
        return;
    }

    MsgIcona(ICONA_AVVISO);

    if ((ScooterData.stato == -1000 ) && (sesso == 'M')) {
        fl_message_title("Compra uno scooter!");
        fl_alert("Finchè non comprerai lo scooter, non usciremo più insieme...");
        return;
    }

    // scooter scassato e/o incidentato
    if (((ScooterData.stato <= 35) || (ScooterData.attivita == 0)) && (sesso == 'M')) {
        fl_message_title("Ripara lo scooter!");
        fl_alert("Finchè non riparerai lo scooter, non usciremo più insieme...");
        return;
    }

    // scooter non in uso
    if ((ScooterData.attivita != 1) && (sesso == 'M')) {
        fl_message_title("Controlla lo scooter!");
        fl_alert("Finchè il tuo scooter resterà %s non potremo uscire insieme...",n_attivita[ScooterData.attivita]);
        return;
    }

    if (Soldi < 15) {
        if (sesso == 'M') {
            fl_message_title("Sei povero...");
            fl_alert("Se mi vuoi portare fuori, cerca di avere almeno un po' di soldi...");
        }
        else {
            fl_message_title("Che palle...");
            fl_alert("Oh tipa... cioè non posso pagare sempre tutto io, cioè ohhhh...");
        }
        return;
    }

    Soldi-=15;

    Rapporti+=5;
    if (Rapporti > 100) Rapporti=100;

    if ( FigTipa > Fama) Fama++;
    if (Fama > 100) Fama=100;

    benzina-=3;
    if (benzina < 1) benzina = 0;

    #ifdef TABBOZ_DEBUG
        sprintf(log_buf,"tipa: Esci con la tipa/o (%s)",MostraSoldi(15));
        writelog(log_buf);
    #endif

    CalcolaVelocita(false);
    AggiornaTipa();
}


/* Lascia tipa/o */
void LasciaTipa(void)
{
    char tmp[128];

    MsgIcona(ICONA_DOMANDA);
    if (Rapporti <= 0)  {
        if (sesso == 'M') {
            fl_message_title("Lascia Tipa");
            fl_alert("Scusa, che ragazza avresti intenzione di lasciare ???");
        }
        else {
            fl_message_title("Lascia Tipo");
            fl_alert("Scusa, che tipo avresti intenzione di lasciare, visto che sei sola come un cane ???");
        }
        return;
    }

    if (sesso == 'M') {
        fl_message_title("Lascia tipa?");
        sprintf(tmp,"Sei proprio sicuro di voler lasciare %s ?",Nometipa);
    }
    else {
        fl_message_title("Molla tipo?");
        sprintf(tmp,"Sei proprio sicura di voler lasciare %s ?",Nometipa);
    }

    if(! fl_choice(tmp,"Sì","No...",0)) {
        if (sound_active) TabbozPlaySound(603);
        Rapporti=0;
        
        // se molli una figa perdi rep...
        if ((FigTipa >= 79) && (sesso == 'M')) {
            MsgIcona(ICONA_STOP);
            fl_message_title("Idiota...");
            fl_message("Appena vengono a sapere quello che hai fatto, i tuoi amici ti prendono a scarpate.\nQualcuno, più furbo di te, va a consolarla...");
            Reputazione-=8;
            if (Reputazione < 0) Reputazione=0;
        }

        // se molli un roito guadagni rep...
        if ((FigTipa <= 40) && (sesso == 'M')) {
            Reputazione+=4;
            if (Reputazione > 100) Reputazione=100;
        }
        Evento();
    }
    AggiornaTipa();
}


/* Abbina una descrizione (breve) alla figosita' di una tipa */
const char *DescrizioneTipa(int f)
{
    if      (f > 97) return "Ultramegafiga";
    else if (f > 90) return "Fighissima";
    else if (f > 83) return "Molto figa";
    else if (f > 72) return "Figa";
    else if (f > 67) return "Abbastanza figa";
    else if (f > 55) return "Interessante";
    else if (f > 45) return "Passabile";
    else if (f > 35) return "Può piacere..";
    else             return "E' un tipo...";
}


/* Abbina una descrizione (breve) alla figosita' di un tipo */
const char *DescrizioneTipo(int f)
{
    if      (f > 97) return "Ultramegafigo";
    else if (f > 90) return "Bellissimo";
    else if (f > 83) return "Molto figo";
    else if (f > 72) return "Bello";
    else if (f > 67) return "Abbastanza figo";
    else if (f > 55) return "Interessante";
    else if (f > 45) return "Passabile";
    else if (f > 35) return "Puo' piacere..";
    else             return "Inutile...";
}
