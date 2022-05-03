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
#include "eventi.h"

#include "palestra.h"
#include "gui/GUIPalestra.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


/* Abbonamenti Palestra */
STVARIE PalestraMem[] = {
    {0, 0, 0, 0, 0, 0, 0,  50,  0, ""},       // Un mese
    {0, 0, 0, 0, 0, 8, 0, 270,  0, ""},       // Sei mesi
    {0, 0, 0, 0, 0, 9, 0, 500,  0, ""},       // Un anno
    {0, 0, 0, 0, 0, 9, 0,  14,  0, ""}        // Una lampada
};


/* Aggiorna finestra palestra */
void AggiornaPalestra(void)
{
    char tmp[128];

    pal_soldi->value(CALCSOLDI(Soldi));
    pal_fama->value(Fama);

    if (scad_pal_giorno < 1)
        sprintf(tmp, "N/A");
    else
        sprintf(tmp, "%d %s",scad_pal_giorno,InfoMese[scad_pal_mese-1].nome);
    pal_txtscadenza->value(tmp);

    switch (current_testa) {     // Scrive il grado di abbronzatura...
        case  1: sprintf(tmp,"Lieve");  break;
        case  2: sprintf(tmp,"Media");  break;
        case  3: sprintf(tmp,"Pesante");  break;
        case  4: sprintf(tmp,"Carbonizzat%c...",ao);   break;
        default: sprintf(tmp,"Mozzarella");
    }
    pal_txtfaccia->value(tmp);
}


/* Aumenta figosità (se abbonato alla palestra...) */
void VaiInPalestra(void)
{
    if (scad_pal_giorno < 1) {
        MsgIcona(ICONA_AVVISO);
        fl_message_title("Palestra");
        fl_message("Prima di poter venire in palestra devi fare un abbonamento!");
    } else {
        if (sound_active) TabbozPlaySound(201);
        if (Fama < 82) Fama+=2;  //BUGFIX solo 1 volta al giorno, ma incrementa +2 anzichè +1
        if(rand() % 2)  //BUGFIX Solo il 50% di probabilità, per compensare l'evento obbligatorio
            EventiPalestra();
        Evento();    //BUGFIX Bisogna chiamare Evento se no il calendario non avanza
        AggiornaPalestra();
    }
}


/* Aumentà figosità (con moderazione...) */
void FaiLampada(void)
{
    int     i;

    if (PalestraMem[3].prezzo > Soldi) {
        nomoney(PALESTRA);
    } else {
        if (current_testa < 3) {
            current_testa++;    // Grado di abbronzatura
            if (Fama < 20) Fama++;    // Da 0 a 3 punti in piu' di fama
            if (Fama < 45) Fama++;    // ( secondo quanta se ne ha gia')
            if (Fama < 96) Fama++;
        } else {
            current_testa=4; // Carbonizzato...
            if (Fama > 8) Fama-=8;
            if (Reputazione > 5) Reputazione-=5;
            MsgIcona(ICONA_STOP);
            fl_message_title("Lampada");
            fl_alert("L'eccessiva esposizione del tuo corpo ai raggi ultravioletti,\nprovoca un avanzato grado di carbonizzazione\ne pure qualche piccola mutazione genetica...");
        }
        if (sound_active) TabbozPlaySound(202);
        Soldi-=PalestraMem[3].prezzo;
        #ifdef TABBOZ_DEBUG
            sprintf(log_buf,"palestra: Lampada - paga %s",MostraSoldi(PalestraMem[3].prezzo));
            writelog(log_buf);
        #endif
    }
    i=rand() % (5 + Fortuna);
    if (i==0) Evento();
    AggiornaPalestra();
}


/* Per sottoscrivere un abbonamento alla palestra */
void CompraAbbonamento(int scelta)
{
    if (scad_pal_giorno > 0 ) {
        MsgIcona(ICONA_INFO);
        fl_message_title("Palestra");
        fl_message("Hai già un abbonamento, perchè te ne serve un altro ???");
        return;
    }
    if (PalestraMem[scelta].prezzo > Soldi) {
        nomoney(PALESTRA);
        return;
    } else {
        Soldi-= PalestraMem[scelta].prezzo;
        if(logging) {
            sprintf(log_buf,"palestra: Nuovo abbonamento (Paga %s)",MostraSoldi(PalestraMem[scelta].prezzo));
            writelog(log_buf);
        }
        switch(scelta) {
            
            case 0: // UN MESE
                    scad_pal_mese = x_mese + 1;
                    scad_pal_giorno = x_giorno;
                    if (scad_pal_mese > 12) scad_pal_mese-=12;
                    // Quello che segue evita che la palestra scada un giorno tipo il 31 Febbraio
                    if (scad_pal_giorno > InfoMese[scad_pal_mese-1].num_giorni) scad_pal_giorno = InfoMese[scad_pal_mese-1].num_giorni;
                    break;;

            case 1: // SEI MESI
                    scad_pal_mese = x_mese + 6;
                    scad_pal_giorno = x_giorno;
                    if (scad_pal_mese > 12) scad_pal_mese-=12;
                    // Quello che segue evita che la palestra scada un giorno tipo il 31 Febbraio
                    if (scad_pal_giorno > InfoMese[scad_pal_mese-1].num_giorni) scad_pal_giorno = InfoMese[scad_pal_mese-1].num_giorni;
                    break;;

            case 2: // UN ANNO (meno un giorno...)
                    scad_pal_mese = x_mese;
                    scad_pal_giorno = x_giorno - 1;
                    if ( scad_pal_giorno < 1) {
                        scad_pal_mese--;
                        if ( scad_pal_mese < 1) scad_pal_mese+=12;
                        scad_pal_giorno=InfoMese[scad_pal_mese-1].num_giorni;
                    }
                    break;;
        }
    }
    Evento();
    AggiornaPalestra();
}


#ifdef DEADCODE
//# pragma argsused
//BOOL FAR PASCAL Palestra(HWND hDlg, WORD message, WORD wParam, LONG lParam)
//void Palestra()
//{

    char    tmp[128];
    int     i;

    // if (message == WM_INITDIALOG) {
    // AggiornaPalestra(hDlg);
    // for (i=0; i<4; i++)
    //     SetDlgItemText(hDlg, 120 + i , MostraSoldi(PalestraMem[i].prezzo));

    // return(TRUE);
    // }

    //  else if (message == WM_COMMAND)
    //  {
//    switch (wParam)
    
    {





         case 115:    // Abbonamenti
         case 116:
         case 117:
 



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
    //}

//     return(FALSE);
//}
#endif