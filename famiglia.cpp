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

#include "zarrosim.h"
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
        if (((Studio - Paghetta +  Fortuna) > ( 75 + rand() % 50)) && (Paghetta < 96) ) {  //BUGFIX qui c'era & anzichè &&
            sprintf(tmp,"Va bene... ti daremo %s di paghetta in più...",MostraSoldi(5));
            fl_message_title("Aumento paghetta !");
            fl_message(tmp);
            Paghetta+=5;
            Evento();
        } else {
            fl_message_title("Errore irrecuperabile");
            fl_alert("Vedi di scordartelo...\nDovrà passare molto tempo prima che ti venga aumentata la paghetta...");
            Evento();
        }
    } else {
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
            AttesaSoldi=ATTESAMAX;
            Soldi+=10;
            #ifdef LOGGING
                sprintf(tmp,"famiglia: paghetta extra (%s)",MostraSoldi(10));
                writelog(tmp);
            #endif
            Evento();
        } else {
            fl_message_title("Non te li diamo");
            fl_alert("Ma insomma! Non puoi continuamente chiedere soldi!\nAspetta ancora qualche giorno. Fai qualche cosa di economico nel frattempo...");
            Evento();
        }
    } else {
        sprintf(tmp,"Quando andrai meglio a scuola potrai tornare a chiederci dei soldi, non ora.\nMa non lo sai che per la tua vita è importante studiare, e dovresti impegnarti\ndi più, perchè quando ti impegni i risultati si vedono, solo che sei svogliat%c\ne non fai mai nulla, mi ricordo che quando ero giovane io era tutta un'altra cosa...\nallora sì che i giovani studiavano...",ao);
        fl_message_title("Errore irrecuperabile");
        fl_alert(tmp);
    }
    fam_val_soldi->value(CALCSOLDI(Soldi));
}


/* Chiedi 100k a papà */
void ChiediSoldiPapa(void)
{
    if (sound_active) //TabbozPlaySound(801);  FIXME Sound
    fl_message_title("Errore irrecuperabile");
    fl_alert("Non pensarci neanche lontanamente...");
    Evento();
}


/* codice originale */
#ifdef DEADCODE
# pragma argsused
BOOL FAR PASCAL Famiglia(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
     char        tmp[1024];

     if (message == WM_INITDIALOG) {
        sprintf(tmp,"Papa', mi dai %s ?",MostraSoldi(100));
        SetDlgItemText(hDlg, 103, tmp);
        SetDlgItemText(hDlg, 104, MostraSoldi(Soldi));
        SetDlgItemText(hDlg, 105, MostraSoldi(Paghetta));
        return(TRUE);
    } else if (message == WM_COMMAND) {
        switch (LOWORD(wParam))
        {
            case 101:                   /* Chiedi aumento paghetta */
                if (Studio > 40) {
                    if (((Studio - Paghetta +  Fortuna) > ( 75 + random(50))) & (Paghetta < 96) ) {
                        sprintf(tmp,"Va bene... ti daremo %s di paghetta in piu'...",MostraSoldi(5));
                        MessageBox( hDlg, tmp,
                          "Aumento paghetta !", MB_OK | MB_ICONINFORMATION);
                        Paghetta+=5;
                        Evento(hDlg);
                    } else {
                        MessageBox( hDlg,
                        "Vedi di scordartelo... Dovra' passare molto tempo prima che ti venga aumentata la paghetta...",
                            "Errore irrecuperabile", MB_OK | MB_ICONHAND);
                        Evento(hDlg);
                    }
                } else {
                    MessageBox( hDlg,
                        "Quando andrai meglio a scuola, forse...",
                        "Errore irrecuperabile", MB_OK | MB_ICONHAND);
            }
            SetDlgItemText(hDlg, 105, MostraSoldi(Paghetta));
            return(TRUE);

         case 102:                   // Chiedi paghetta extra
            if (Studio >= 40) {
                if (Attesa == 0) {
                                        Attesa=ATTESAMAX;
                    Soldi+= 10 ;
                    #ifdef TABBOZ_DEBUG
                    sprintf(tmp,"famiglia: paghetta extra (%s)",MostraSoldi(10));
                    writelog(tmp);
                    #endif
                    Evento(hDlg);
                } else {
                    MessageBox( hDlg,
                    "Ma insomma ! Non puoi continuamente chiedere soldi ! Aspetta ancora qualche giorno. Fai qualche cosa di economico nel frattempo...",
                    "Non te li diamo", MB_OK | MB_ICONHAND);
                    Evento(hDlg);
                }
            } else {
                sprintf(tmp,"Quando andrai meglio a scuola potrai tornare a chiederci dei soldi, non ora. \
Ma non lo sai che per la tua vita e' importante studiare, e dovresti impegnarti \
di piu, perche' quando ti impegni i risultati si vedono, solo che sei svogliat%c \
e non fai mai nulla, mi ricordo che quando ero giovane io era tutta un altra cosa... \
allora si' che i giovani studiavano...",ao);

                MessageBox( hDlg,tmp,
                    "Errore irrecuperabile", MB_OK | MB_ICONHAND);
            }

            SetDlgItemText(hDlg, 104, MostraSoldi(Soldi));
            return(TRUE);

         case 103:                   // Papa, mi dai 100000 lire ?
            if (sound_active) TabbozPlaySound(801);
                MessageBox( hDlg,
                    "Non pensarci neanche lontanamente...",
                    "Errore irrecuperabile", MB_OK | MB_ICONHAND);
                Evento(hDlg);
                return(TRUE);

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
#endif
