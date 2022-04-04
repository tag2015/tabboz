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


//# pragma argsused
//BOOL FAR PASCAL Palestra(HWND hDlg, WORD message, WORD wParam, LONG lParam)
void Palestra()
{

    char    tmp[128];
    int     i;

    if (message == WM_INITDIALOG) {
    AggiornaPalestra(hDlg);
    for (i=0; i<4; i++)
        SetDlgItemText(hDlg, 120 + i , MostraSoldi(PalestraMem[i].prezzo));

    return(TRUE);
    }

     else if (message == WM_COMMAND)
     {
    switch (wParam)
    {

         case 110:    // Vai in palestra
        if (scad_pal_giorno < 1) {
              MessageBox( hDlg,
                    "Prima di poter venire in palestra devi fare un abbonamento !",
                    "Palestra", MB_OK | MB_ICONINFORMATION);
        } else {
              if (sound_active) TabbozPlaySound(201);
              if (Fama < 82) Fama++;
              EventiPalestra(hDlg);
              AggiornaPalestra(hDlg);
              /* Evento(hDlg); */

        }
        return(TRUE);

         case 111:    // Lampada
            if (PalestraMem[3].prezzo > Soldi) {
                nomoney(hDlg,PALESTRA);
            } else {
                if (current_testa < 3) {
                    current_testa++; // Grado di abbronzatura
                    if (Fama < 20) Fama++;    // Da 0 a 3 punti in piu' di fama
                    if (Fama < 45) Fama++;    // ( secondo quanta se ne ha gia')
                    if (Fama < 96) Fama++;
                } else {
                    current_testa=4; // Carbonizzato...
                    if (Fama > 8) Fama-=8;
                    if (Reputazione > 5) Reputazione-=5;
                    MessageBox( hDlg, "L' eccessiva esposizione del tuo corpo ai raggi ultravioletti,\
 provoca un avanzato grado di carbonizzazione e pure qualche piccola mutazione genetica...", "Lampada", MB_OK  | MB_ICONSTOP);
                }
                TabbozRedraw = 1;    // E' necessario ridisegnare l' immagine del Tabbozzo...

                if (sound_active) TabbozPlaySound(202);
                Soldi-=PalestraMem[3].prezzo;
                #ifdef TABBOZ_DEBUG
                sprintf(tmp,"lampada: Paga %s",MostraSoldi(PalestraMem[3].prezzo));
                writelog(tmp);
                #endif
            }
            i=random(5 + Fortuna);
            if (i==0) Evento(hDlg);
            AggiornaPalestra(hDlg);
            return(TRUE);

         case 115:    // Abbonamenti
         case 116:
         case 117:
        if (scad_pal_giorno > 0 ) {
                  MessageBox( hDlg,
                    "Hai gia' un abbonamento, perche' te ne serve un altro ???",
                    "Palestra", MB_OK | MB_ICONINFORMATION);
                  return(TRUE);
            }

        if (PalestraMem[wParam-115].prezzo > Soldi) {
            nomoney(hDlg,PALESTRA);
            return(TRUE);
        } else {
            Soldi-= PalestraMem[wParam-115].prezzo;
            #ifdef TABBOZ_DEBUG
            sprintf(tmp,"palestra: Paga %s",MostraSoldi(PalestraMem[wParam-115].prezzo));
            writelog(tmp);
            #endif
        }

        switch (wParam)
        {
        case 115: scad_pal_mese = x_mese + 1;      // UN MESE
              scad_pal_giorno = x_giorno;
              if (scad_pal_mese > 12) scad_pal_mese-=12;
              // Quello che segue evita che la palestra scada un giorno tipo il 31 Febbraio
              if (scad_pal_giorno > InfoMese[scad_pal_mese-1].num_giorni) scad_pal_giorno = InfoMese[scad_pal_mese-1].num_giorni;
            break;;

        case 116: scad_pal_mese = x_mese + 6;      // SEI MESI
              scad_pal_giorno = x_giorno;
              if (scad_pal_mese > 12) scad_pal_mese-=12;
              // Quello che segue evita che la palestra scada un giorno tipo il 31 Febbraio
              if (scad_pal_giorno > InfoMese[scad_pal_mese-1].num_giorni) scad_pal_giorno = InfoMese[scad_pal_mese-1].num_giorni;
            break;;

        case 117: scad_pal_mese = x_mese;          // UN ANNO ( meno un giorno...)
              scad_pal_giorno = x_giorno - 1;
              if ( scad_pal_giorno < 1) {
                scad_pal_mese--;
                if ( scad_pal_mese < 1) scad_pal_mese+=12;
                scad_pal_giorno=InfoMese[scad_pal_mese-1].num_giorni;
              }
            break;;
        }

        Evento(hDlg);
        AggiornaPalestra(hDlg);
        return(TRUE);


         case IDCANCEL:
        EndDialog(hDlg, TRUE);
        return(TRUE);

         case IDOK:
        EndDialog(hDlg, TRUE);
        return(TRUE);

         default:
        return(TRUE);
    }
     }

     return(FALSE);
}


/* Eventi casuali legati alla palestra */
void EventiPalestra(void)
{
int i;
char messaggio[128];

    i=random(29 + (Fortuna / 2));

    if (i > 9) return;    /* eventi: 0 - 10) */

    LoadString(hInst, (1100 + i), (LPSTR)messaggio, 255);

    MessageBox( hInstance,
    (LPSTR)messaggio,
        "Palestra...", MB_OK | MB_ICONSTOP);

    if (Reputazione > 10)
        Reputazione-=4;


#ifdef TABBOZ_DEBUG
    writelog("eventi: Evento riguardante la palestra");
#endif
}


/* Aggiorna finestra palestra */
void AggiornaPalestra(void)
{
char tmp[128];

    SetDlgItemText(parent, 104, MostraSoldi(Soldi));
    sprintf(tmp, "%d/100", Fama);
    SetDlgItemText(parent, 105, tmp);

    if (scad_pal_giorno < 1) {
        sprintf(tmp, "Nessun Abbonamento");
        SetDlgItemText(parent, 106, tmp);
    } else {
         sprintf(tmp, "Scadenza abbonamento: %d %s",scad_pal_giorno,InfoMese[scad_pal_mese-1].nome);
         SetDlgItemText(parent, 106, tmp);
    }

    // Scrive il grado di abbronzatura... 4 Marzo 1999
    switch (current_testa) {
    case  1: sprintf(tmp,"Abbronzatura Lieve");      break;
    case  2: sprintf(tmp,"Abbronzatura Media");    break;
    case  3: sprintf(tmp,"Abbronzatura Pesante");  break;
    case    4: sprintf(tmp,"Carbonizzat%c...",ao);   break;
    default: sprintf(tmp,"Non abbronzat%c",ao);
    }
    SetDlgItemText(parent, 107, tmp);
}
