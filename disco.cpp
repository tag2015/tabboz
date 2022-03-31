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

/* L'opzione CDROM è stata tolta... verrà sostituita dalla possibilità di */
/* riprodurre file audio personali (in futuro...)                         */

#include "zarrosim.h"
#include "debug.h"

#include "disco.h"
#include "calendario.h"

//static char sccsid[] = "@(#)" __FILE__ " " VERSION " (Andrea Bonomi) " __DATE__;


const STDISCO DiscoMem[] =
    {    { 0,  0, 0,  0, 0,  0,  "---"},
         { 0, 30, 2, 15, 1, 36,  ""   },
         { 0,  0, 1,  7, 4, 26,  ""   },
         { 0,  0, 1,  8, 1, 30,  ""   },
         { 0, 35, 3, 15, 1, 36,  ""   },
         { 0,  0, 2,  6, 3, 26,  ""   },
         { 0,  0, 2,  5, 2, 22,  ""   },
         { 0,  0, 3,  8, 1, 30,  ""   },
         { 1,  0, 2,  9, 7, 36,  ""   } };
//         |   |  |   |  |   |     \nome  
//         |   |  |   |   \   \costo
//         |   |  |   |    \giorno di chiusura (1=lunedi',etc... - 0=nessuno)
//         \   \  \   \incremento fama
//          \   \  \incremento reputazione
//           \   \figosita' minima x entrare (selezione all' ingresso)
//            \1=disco fuori porta - ci puoi arrivare solo se hai lo scooter...


/* Routine per il pagamento della Discoteca */
void PagaDisco(int scelta)
{
    char tmp[128];
    int prezzo;

    if ( (DiscoMem[scelta].fuoriporta) && (ScooterData.stato == -1) ) {
        fl_message_title("Discoteca fuori porta");
        fl_alert("Senza lo scooter non puoi andare nelle discoteche fuori porta...");
        //Evento(hInstance); FIXME Eventi
        return;
    }
    
    if (DiscoMem[scelta].g_chiusura == x_giornoset) {
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
            if (sound_active) //TabbozPlaySound(302); FIXME Suoni
            fl_message_title("Selezione all'ingresso");
            fl_alert("Mi dispiace signore, conciato così, qui non può entrare...\nVenga vestito meglio la prossima volta, signore.");
            if (Reputazione > 2) Reputazione--;
            if (Fama > 2) Fama--;
        } else {
            if (sound_active) // TabbozPlaySound(303 + random(3));  // suoni: 0303 -> 0305 FIXME SUONI
            Soldi-= prezzo;
            #ifdef LOGGING
                sprintf(tmp,"discoteca: Paga %s",MostraSoldi(DiscoMem[scelta].costo));
                writelog(tmp);
            #endif
            Fama+=DiscoMem[scelta].fama_inc;  //BUGFIX qui incrementava con la fama della disco anzichè il bonus
            Reputazione+=DiscoMem[scelta].rep_inc;
            if (Fama > 100) Fama=100;
            if (Reputazione > 100) Reputazione=100;
        }
    //Evento(hInstance); FIXME Evento
}



#ifdef DEADCODE
/********************************************************************/
/* Routine per il pagamento della Discoteca.                        */
/********************************************************************/

static void PagaDisco(HANDLE hInstance)
{
    char tmp[128];
    long Prezzo;

    if (numdisco != 0) {
        if (DiscoMem[numdisco].speed == 1) {
            if (ScooterData.stato == -1) {
                MessageBox(hInstance,
                    "Senza lo scooter non puoi andare nelle discoteche fuori porta...",
                    "Discoteca fuori porta", MB_OK | MB_ICONINFORMATION);
                Evento(hInstance);
                return;
            }
        }

        if (DiscoMem[numdisco].mass == x_giornoset) {
            MessageBox( hInstance,
                "Un cartello recita che oggi e' il giorno di chiusura settimanale...",
                "Giorno di chiusura", MB_OK | MB_ICONINFORMATION);
            return;
        }

        if (sesso == 'M')
            Prezzo=DiscoMem[numdisco].prezzo;
        else
            Prezzo=DiscoMem[numdisco].prezzo - 10;

        if (Prezzo > Soldi) {        /* check costo */
            nomoney(hInstance,DISCO);
        }
        else {
            if ((DiscoMem[numdisco].cc > Fama) && (sesso == 'M')) {            /* check selezione all'ingresso */
                if (sound_active) TabbozPlaySound(302);
                MessageBox( hInstance,
                    "Mi dispiace signore, conciato cosi', qui non puo' entrare...\nVenga vestito meglio la prossima volta, signore.",
                    "Selezione all' ingresso", MB_OK | MB_ICONINFORMATION);
                if (Reputazione > 2) Reputazione-=1;
                if (Fama > 2) Fama-=1;
            } else {
                if (sound_active) TabbozPlaySound(303 + random(3));  // suoni: 0303 -> 0305
                Soldi-= Prezzo;
                #ifdef TABBOZ_DEBUG
                    sprintf(tmp,"discoteca: Paga %s",MostraSoldi(DiscoMem[numdisco].prezzo));
                    writelog(tmp);
                #endif
                Fama+=DiscoMem[numdisco].fama;
                Reputazione+=DiscoMem[numdisco].xxx;
                if (Fama > 100) Fama=100;
                if (Reputazione > 100) Reputazione=100;
            }
        }
        Evento(hInstance);
    }
}


//******************************************************************
// Disco...
//******************************************************************

# pragma argsused
BOOL FAR PASCAL Disco(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
    char buf[1024];
    char tmp[1024];

#ifdef TABBOZ_WIN
#ifdef CDROM
    static char  mciTmp[1024];
    static int   mciLen;
    static DWORD mciReturn;
#endif
#endif

    if (message == WM_INITDIALOG) {
        numdisco=0;
        sprintf(buf, "O tip%c, in che disco andiamo ?",ao);
        SetDlgItemText(hDlg, 120, buf);
        SetDlgItemText(hDlg, 110, MostraSoldi(Soldi));
#ifdef TABBOZ_WIN
#ifdef CDROM
//        mciReturn=mciSendString("open cdaudio", mciTmp, mciLen, 0);
        mciReturn=mciSendString("set cdaudio time format tmsf", mciTmp, mciLen, 0);
//        mciReturn=mciSendString("set cdaudio door open", mciTmp, mciLen, 0);
//        mciReturn=mciSendString("close cdaudio", mciTmp, mciLen, 0);
#endif
#endif
        return(TRUE);
    }

    else if (message == WM_COMMAND) {
        switch (wParam) {
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
                numdisco=wParam-100;
                LoadString(hInst, wParam, buf, 1024);
                if (sesso == 'M')    // Le donne pagano meno...
                    sprintf(tmp,buf,MostraSoldi(DiscoMem[numdisco].prezzo));
                else
                    sprintf(tmp,buf,MostraSoldi(DiscoMem[numdisco].prezzo - 10));
                SetDlgItemText(hDlg, 120, tmp);
                return(TRUE);

#ifdef TABBOZ_WIN
#ifdef CDROM
            case 607: // Eject
                mciReturn=mciSendString("status cdaudio mode", mciTmp, mciLen, 0);
                sprintf(buf,"%s",mciTmp);
                SetDlgItemText(hDlg, 120, buf);
                if (! strcmp(mciTmp,"open") )
                    mciReturn=mciSendString("set cdaudio door close", mciTmp, mciLen, 0);
                else
                    mciReturn=mciSendString("set cdaudio door open", mciTmp, mciLen, 0);
                return(TRUE);
#endif
#endif

            case IDCANCEL:
                EndDialog(hDlg, TRUE);
                return(TRUE);

            case IDOK:
                PagaDisco(hDlg);
                EndDialog(hDlg, TRUE);
                return(TRUE);

            default:
                return(TRUE);

        }
    }
    return(FALSE);
}
#endif