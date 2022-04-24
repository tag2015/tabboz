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
#include <string.h>
#include <time.h>

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>

#include "zarrosim.h"
#include "global.h"
#include "eventi.h"
#include "telefono.h"
#include "scooter.h"

#include "sound.h"
#include "debug.h"

#include "tipa.h"
#include "gui/GUITipa.h"


// static char sccsid[] = "@(#)" __FILE__ " " VERSION " (Andrea Bonomi) " __DATE__;


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
    tipa_txt_nome->value("Nessuna...");
    tipa_val_fama->value(0);
    tipa_val_rapporti->value(0);
    
    } else {
        if ( sesso == 'M')
            tipa_btn_cercatipa->label("Cerca Nuova Tipa");
        else
            tipa_btn_cercatipa->label("Cerca Nuovo Tipo");
        tipa_grp_stats->activate();
        tipa_txt_nome->value(Nometipa);
        tipa_val_figosita->value(FigTipa);
        tipa_val_rapporti->value(Rapporti);
    }
    tipa_val_fama->value(Fama);
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
//    win_cercatipa->redraw();
}


/* Check per vedere se riesce a rimorchiare la tipa/o */
bool Provaci(void)
{

    // Calcola se ce la fa o meno con la tipa...
    if ( ((fig_nuovatipa * 2) + ( rand() % 50)) <= ( Fama + Reputazione + (rand() % 30)) )  {
    
        // E' andata bene...
        if (sesso == 'M') {
            fl_message_title("E' andata bene!");
            fl_message("Con il tuo fascino nascosto da tabbozzo, seduci la tipa e ti ci metti insieme.");
        } else {
            fl_message_title("Qualcuno ti caga...");
            fl_message("Ora non ti puoi più lamentare di essere sola...");
        }
    return TRUE;
    }

    return FALSE;
}


/* Telefona tipa consumando credito del cell o soldi */
void TelefonaTipa(void)
{
    char tmp[128];

    if (Rapporti <= 0)  {
        fl_message_title("Non sei molto intelligente...");
        if (sesso == 'M')
            fl_alert("Scusa, che ragazza vorresti chiamare ???");
        else
            fl_alert("Scusa, che ragazzo vorresti chiamare, visto che sei sola ???");
        return;
    }
//FIXME questo check è sbagliato, bisogna separare i due casi (pochi soldi e nocell, oppure cell ma abbo basso)
    if ((Soldi <= 5) && ((AbbonamentData.creditorest < 2) && (CellularData.stato < 0) )) {
        fl_message_title("Non toccare quel telefono...");
        fl_alert("<< Sei fai ancora una telefonata, ti spezzo le gambe... >>\n disse tuo padre con una accetta in mano...");
    
    } else {
        if (Rapporti <= 60) Rapporti++;
        if (sound_active) TabbozPlaySound(602);
        if ((AbbonamentData.creditorest >= 2) && (CellularData.stato > -1))
            AbbonamentData.creditorest-=2;
        else
            Soldi-=5;
        #ifdef LOGGING
            sprintf(tmp,"tipa: Telefona alla tipa/o (%s)",MostraSoldi(5));
            writelog(tmp);
        #endif
    }
    AggiornaTipa();
}


/* Esce con tipa se disponibile scooter e sufficienti soldi */
void EsciConTipa(void)
{
    char tmp[128];

    if (Rapporti <= 0)  {
        fl_message_title("Non sei molto intelligente...");
        if (sesso == 'M')
            fl_alert("Scusa, con che tipa vorresti uscire ???");
        else
            fl_alert("Scusa, ma con chi vorresti uscire ???");
        return;
    }

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

    #ifdef LOGGING
        sprintf(tmp,"tipa: Esci con la tipa/o (%s)",MostraSoldi(15));
        writelog(tmp);
    #endif

    CalcolaVelocita(FALSE);
    AggiornaTipa();
}


/* Lascia tipa/o */
void LasciaTipa(void)
{
    char tmp[128];

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


// ------------------------------------------------------------------------------------------
// Tipa...
// ------------------------------------------------------------------------------------------

// # pragma argsused
// BOOL FAR PASCAL        Tipa(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
//          char          buf[128];
//          char               tmp[128];
//          FARPROC              lpproc;
//          int                lasciaoraddoppia;

//      if (message == WM_INITDIALOG) {
//         if (sesso == 'M') spostamento=0; else spostamento=100;
//         AggiornaTipa(hDlg);
//         tipahDlg=hDlg;
//         return(TRUE);
//         }

//      else if (message == WM_COMMAND)
//      {
//     switch (wParam)
//     {
//          case 110:            // Cerca tipa
//             lpproc = MakeProcInstance(CercaTipa, hInst);
//             DialogBox(hInst,
//                     MAKEINTRESOURCE(CERCATIPA + spostamento),
//                     hDlg,
//                     lpproc);
//             FreeProcInstance(lpproc);

//             AggiornaTipa(hDlg);
//         return(TRUE);




// ------------------------------------------------------------------------------------------
// Due Donne - 22 Aprile 1999
// ------------------------------------------------------------------------------------------
/*
# pragma argsused
BOOL FAR PASCAL DueDonne(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
     char          tmp[255];

     if (message == WM_INITDIALOG) {
            sprintf(tmp, "Resto con %s", Nometipa);
            SetDlgItemText(hDlg, 2, tmp);
            if (!strcmp(Nometipa,nomeTemp)) { // Se le tipe si chiamano tutte e due con lo stesso nome
                if (sesso == 'M') sprintf(tmp, "Preferisco quella nuova");
                else sprintf(tmp, "Preferisco quello nuovo");
            } else
                sprintf(tmp, "Preferisco %s", nomeTemp);
            SetDlgItemText(hDlg, 102, tmp);
            return(TRUE);

     } else if (message == WM_COMMAND) {
            switch (wParam)
            {
            case 101:        // Ottima scelta...
              if (sesso == 'M')
                    sprintf(tmp,"Mentre sei appartato con la %s, arriva la tua ragazza, %s, ti tira uno schiaffo e ti lascia.\
Capendo finalmente di che pasta sei fatto, anche la %s si allontana...",nomeTemp,Nometipa,nomeTemp);
              else
                    sprintf(tmp,"%s viene a sapere che di %s, gli spacca la faccia e ti molla...\
Dopo questa tragica esperienza anche %s sparisce...",Nometipa,nomeTemp,nomeTemp);

              Rapporti=0;
              Reputazione-=8;
              if (Reputazione < 0) Reputazione=0;
              Fama-=4;
              if (Fama < 0) Fama=0;

              MessageBox( hDlg,
                tmp ,
                "La vita e' bella", MB_OK | MB_ICONSTOP);
              EndDialog(hDlg, TRUE);
              return(TRUE);

            case 102:       // Preferisci quella nuova...
                sprintf(Nometipa,"%s",nomeTemp);
                FigTipa=figTemp;
                Rapporti=30+random(15);
                Fama+=FigTipa / 10; if (Fama > 100) Fama=100;
                Reputazione+= FigTipa / 13; if (Reputazione > 100) Reputazione=100;
                EndDialog(hDlg, TRUE);
                return(TRUE);

            case IDCANCEL: // Resti con la tua vecchia ragazza, bravo...
            default:
                EndDialog(hDlg, TRUE);
                return(TRUE);
            }
     }

     return(FALSE);
}*/





/*FIXME controllo 2 tipe da fare in gui */

//                 // ...ma comunque controlla che tu non abbia gia' una tipa -------------------------
//                 if (Rapporti > 0) { // hai gia' una tipa..
//                     FARPROC lpproc = MakeProcInstance(DueDonne, hInst);
//                     DialogBox(hInst,
//                     MAKEINTRESOURCE(92 + spostamento),
//                     hDlg,
//                     lpproc);
//                 FreeProcInstance(lpproc);
//                 } else { // bravo, no hai una tipa...
//                     sprintf(Nometipa,"%s",nomeTemp);
//                     FigTipa=figTemp;
//                     Rapporti=30+random(15);
//                     Fama+=FigTipa / 10; if (Fama > 100) Fama=100;
//                     Reputazione+= FigTipa / 13; if (Reputazione > 100) Reputazione=100;
//             }
//             } else {
//                 FARPROC lpproc;

//                 // 2 di picche... -------------------------------------------------------
//                 if (sound_active) TabbozPlaySound(601);

//                 lpproc = MakeProcInstance(DueDiPicche, hInst);
//                 DialogBox(hInst,
//                     MAKEINTRESOURCE(95),
//                     hDlg,
//                     lpproc);
//                 FreeProcInstance(lpproc);

//             }
//             Evento(hDlg);
//             EndDialog(hDlg, TRUE);
//             return(TRUE);

//          default:
//             return(TRUE);
//         }
//      }

//      return(FALSE);
// }


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


/* 2 di picche (la vita e' bella...) - Calcola malus e ritorna un messaggio a caso */
int DueDiPicche(void)
{
    static int i;

    DDP++;    // log due di picche...
    
    Reputazione-=2;    // decremento reputazione
    if (Reputazione < 0) Reputazione=0;
    
    Fama-=2;    // decremento figosita'
    if (Fama < 0) Fama=0;

    i=rand() % 20;  // estrae una risposta (0-19)

    return i;

//FIXME quand'è che avviene questa condizione?
/*    } else if (message == WM_COMMAND) {
        switch (wParam)
        {
            case 201:
            i++;
            if (i > 5) {
                sprintf(tmp,"Fino ad ora hai preso %d due di picche !\nNon ti preoccupare, capita a tutti di prendere qualche due di picche nella vita ...",DDP);
                MessageBox( hDlg,
                    tmp, "La vita e' bella...", MB_OK | MB_ICONINFORMATION);
                i = 0;
                }
            return(TRUE);

            case IDCANCEL:
            case IDOK:
                EndDialog(hDlg, TRUE);
                return(TRUE);

         default:
                return(TRUE);
        }
     }

     return(FALSE); */
}


#ifdef DEADCODE
/* 2 di picche (la vita e' bella...) */
BOOL FAR PASCAL DueDiPicche(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
     char          tmp[1024];
     static int      i;

     if (message == WM_INITDIALOG) {    // un giorno fortunato...
        DDP++;                // log due di picche...
        Reputazione-=2;                 // decremento reputazione
        if (Reputazione < 0) Reputazione=0;

        Fama-=2;            // decremento figosita'
        if (Fama < 0) Fama=0;

    // IN QUESTA PARTE C'ERA UN BUG CHE FACEVA CRASCIARE IL TABBOZ SIMULATOR...

        if (sesso == 'M' )
            i=300+random(20);        // 300 -> 319 [sfighe varie]
        else
            i=1300+random(20);        // 300 -> 319 [sfighe varie]

        LoadString(hInst, i, (LPSTR)tmp, 1024);
        SetDlgItemText(hDlg, 105, tmp);

        i=0;

        return(TRUE);
    } else if (message == WM_COMMAND) {
        switch (wParam)
        {
            case 201:
            i++;
            if (i > 5) {
                sprintf(tmp,"Fino ad ora hai preso %d due di picche !\nNon ti preoccupare, capita a tutti di prendere qualche due di picche nella vita ...",DDP);
                MessageBox( hDlg,
                    tmp, "La vita e' bella...", MB_OK | MB_ICONINFORMATION);
                i = 0;
                }
            return(TRUE);

            case IDCANCEL:
            case IDOK:
                EndDialog(hDlg, TRUE);
                return(TRUE);

         default:
                return(TRUE);
        }
     }

     return(FALSE);
}
#endif



// ------------------------------------------------------------------------------------------
// 4 gennaio 1999
// ------------------------------------------------------------------------------------------
/*
# pragma argsused
BOOL FAR PASCAL MostraSalutieBaci(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
    if (message == WM_INITDIALOG) {
        return(TRUE);
    } else if (message == WM_COMMAND) {

        switch (wParam) {

            case 205:
            case IDOK:
            case IDCANCEL:
                EndDialog(hDlg, TRUE);
                return(TRUE);

            default:
                return(TRUE);
            }
        }
    return(FALSE);
}
*/