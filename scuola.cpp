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
#include "calendario.h"
#include "eventi.h"
#include "sound.h"

#include "debug.h"

#include "scuola.h"
#include "gui/GUIScuola.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Value_Output.H>

//static char sccsid[] = "@(#)" __FILE__ " " VERSION " (Andrea Bonomi) " __DATE__;


STMATERIE MaterieMem[] =
	{   {"---",                   0},
		{"Agraria",               0},
		{"Fisica",                0},
		{"Attivita' culturali",   0},
		{"Attivita' matematiche", 0},
		{"Scienze industriali",   0},
		{"Elettrochimica",        0},
		{"Petrolchimica",         0},
		{"Filosofia aziendale",   0},
		{"Metallurgia",           0} 
	};
		                   /*     |   */
                           /*     \ voto in una materia */


void ScriviVoti(void);
bool CheckVacanza(void);


/* Aggiorna Finestra Scuola*/
void AggiornaScuola(void)
{
    CalcolaStudio();
    ScriviVoti();
    scuola_val_soldi->value(CALCSOLDI(Soldi));
    scuola_val_rep->value(Reputazione);
    scuola_val_studio->value(Studio);
    scuola_val_media->precision(1);  //TAG2015 mostra media decimale
    scuola_val_media->value(MEDIAVOTI(Studio,N_MATERIE));
    if(scuola_val_media->value() < 5)              // aggiunge colore ai voti
        scuola_val_media->textcolor(FL_RED);
    else if (scuola_val_media->value() > 7)
        scuola_val_media->textcolor(FL_DARK_GREEN);
    else
        scuola_val_media->textcolor(FL_BLACK);
//     if (ScuolaRedraw == 1) ScriviVoti(parent);
//     SetDlgItemText(parent, 104, MostraSoldi(Soldi));
//     sprintf(tmp, "%d/100", Reputazione);
//     SetDlgItemText(parent, 105, tmp);
//     sprintf(tmp, "%d/100", Studio);
//     SetDlgItemText(parent, 106, tmp);
//     sprintf(tmp, "%d",MaterieMem[scelta].xxx);
//     SetDlgItemText(parent, scelta + 119, tmp);
//
}


/* Studia materia selezionata */
void StudiaMateria(int scelta)
{
    if (!CheckVacanza()) {
        if (Reputazione > 10 )	/* Studiare costa fatica... */
            Reputazione-=5; /* (oltre che Reputazione e Fama...) */
        if (Fama > 5 )
            Fama-=1;
        MaterieMem[scelta].voto+=1;
        if (MaterieMem[scelta].voto > 10) MaterieMem[scelta].voto=10;

    Evento();
    AggiornaScuola();  //siccome l'evento potrebbe alterare i voti, meglio risolverlo prima
    }
}


/* Corrompi prof. della materia selezionata */
void CorrompiProf(int scelta)
{
    int i, si_no;
    char tmp[128];

    if (!CheckVacanza()) {
        i=30 + (rand() % 30 * 2);   //I valori dei soldi e' meglio che siano sempre pari, in modo da facilitare la divisione x gli euro...
        sprintf(tmp,"Mah... forse per %s potrei dimenticare i tuoi ultimi compiti in classe...",MostraSoldi(i) );
		fl_message_title("Corrompi il professore?");
        si_no=fl_choice(tmp, "Ok...", "No", 0);
    switch(si_no){
        case 0: { // Si
                if (Soldi >= i) {
                    Soldi-=i;
                    #ifdef LOGGING
                        sprintf(tmp,"scuola: Corrompi un professore per %s",MostraSoldi(i));
                        writelog(tmp);
                    #endif
                    MaterieMem[scelta].voto+=3;
                    if (MaterieMem[scelta].voto > 10 )
                        MaterieMem[scelta].voto=10;
                } else {
                    if (MaterieMem[scelta].voto >= 4 )   //BUGFIX qui era <2 ??? Se >=4 abbassa di 2
                        MaterieMem[scelta].voto-=2;
                    else
                        MaterieMem[scelta].voto=2;       // BUGFIX negli altri casi limita a 2
                    fl_message_title("Errore Critico");
                    fl_alert("Cosa ??? Prima cerchi di corrompermi, poi si scopre che non hai abbastanza soldi !!!");
 				}
                break;
        }
        case 1: {} // No
    }
    Evento();
    AggiornaScuola();
    }
}


/* Minaccia o Seduci prof. della materia selezionata */
void MinacciaSeduciProf(int scelta)
{
    if (!CheckVacanza()) {
        if (sesso == 'M') { // Maschietto - minaccia prof.
            if ((Reputazione >= 30) || (rand() % 10 < 1)) {    //TAG2015 rep>30 è sufficiente per minacciare?
                MaterieMem[scelta].voto+=2;
                if (MaterieMem[scelta].voto > 10) MaterieMem[scelta].voto=10;
            } else {
                if (sound_active) TabbozPlaySound(402);
                fl_message_title("Bella figura...");
                fl_alert("Cosa ??? Credi di farmi paura piccolo pezzettino di letame vestito da zarro...\nDeve ancora nascere chi può minacciarmi...");
                if (Reputazione > 3 )    //FIXME questi andrebbero ripensati
                    Reputazione-=2;
                if (MaterieMem[scelta].voto > 2 )
                    MaterieMem[scelta].voto-=1;
            }
        } else { // Femminuccia - seduci prof.
            if ((Fama >= 50) || (rand() % 10 < 2)) {
                MaterieMem[scelta].voto+=2;
                if (MaterieMem[scelta].voto > 10) MaterieMem[scelta].voto=10;
            } else {
                fl_message_title("Bella figura...");
                fl_alert("Infastidito dalla tua presenza, il prof ti manda via a calci.");
                if (Reputazione > 3 )
                    Reputazione-=2;
                if (MaterieMem[scelta].voto > 2 )
                    MaterieMem[scelta].voto-=1;
            }
        }
    Evento();
    AggiornaScuola();
    }
}


/* Scrive i voti nelle apposite caselle */
void ScriviVoti(void)
{
    int i;

    for (i=0;i<N_MATERIE;i++) {
        Fl_Value_Output *casella = (Fl_Value_Output *) grp_voti->child(i);    // grp_voti è il gruppo contenente le ValueBox per i voti
        casella->value(MaterieMem[i+1].voto);
        if(casella->value() < 5)              // aggiunge colore ai voti
            casella->textcolor(FL_RED);
        else if (casella->value() > 7)
            casella->textcolor(FL_DARK_GREEN);
        else
            casella->textcolor(FL_BLACK);
    }
}


/* Controlla se è un giorno di vacanza (feste programmate e estate) */
bool CheckVacanza(void)
{
    if ( x_vacanza != 0 ) {
        fl_message_title("Scuola chiusa...");
		fl_alert("Non puoi andare a scuola in un giorno di vacanza!");
        return(true);
    }
 	else
        return(false);
}



/*codice originale*/
#ifdef DEADCODE
# pragma argsused
BOOL FAR PASCAL Scuola(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
    char  tmp[128];
    int   i,i2;

    if (message == WM_INITDIALOG) {
		scelta=1;
		SendMessage(GetDlgItem(hDlg, 110), BM_SETCHECK, TRUE, 0L); /* Seleziona agraria */

		sprintf(tmp, "Corrompi il prof di %s",MaterieMem[1].nome);
		SetDlgItemText(hDlg, 101, tmp);
		if (sesso == 'M')
			sprintf(tmp, "Minaccia il prof di %s",MaterieMem[1].nome);
		else
			sprintf(tmp, "Seduci il prof di %s",MaterieMem[1].nome);
		SetDlgItemText(hDlg, 102, tmp);
		sprintf(tmp, "Studia %s",MaterieMem[1].nome);
		SetDlgItemText(hDlg, 103, tmp);
        CalcolaStudio();
		ScriviVoti(hDlg);  /* Scrive i voti, soldi, reputazione e studio nelle apposite caselle */
		return(TRUE);

	} else if (message == WM_COMMAND) {
	switch (wParam)
	{
		case 101:                    /* Corrompi i professori */
			if (! CheckVacanza(hDlg)) {
				i=30 + (random(30) * 2); /* 21 Apr 1998 - I valori dei soldi e' meglio che siano sempre pari, in modo da facilitare la divisione x gli euro... */
				sprintf(tmp,"Ma... forse per %s potrei dimenticare i tuoi ultimi compiti in classe...",MostraSoldi(i) );
				i2=MessageBox( hDlg, tmp,
					  "Corrompi i professori", MB_YESNO | MB_ICONQUESTION);

				if (i2 == IDYES) {
					if (Soldi >= i) {
						 Soldi-=i;
						 #ifdef TABBOZ_DEBUG
						 sprintf(tmp,"scuola: Corrompi un professore per %s",MostraSoldi(i));
						 writelog(tmp);
						 #endif
						 MaterieMem[scelta].xxx+=3;
						 if (MaterieMem[scelta].xxx > 10 )
						MaterieMem[scelta].xxx=10;
					} else {
						 if (MaterieMem[scelta].xxx < 2 )
						MaterieMem[scelta].xxx-=2;
						 MessageBox( hDlg,
				"Cosa ??? Prima cerchi di corrompermi, poi si scopre che non hai abbastanza soldi !!!",
				  "Errore critico", MB_OK | MB_ICONSTOP);
					}
				}

				Evento(hDlg);
				Aggiorna(hDlg);
			}
			return(TRUE);

		case 102:                    /* Minaccia-Seduci i professori */
			if (! CheckVacanza(hDlg)) {
				if (sesso == 'M') { // Maschietto - minaccia prof.
					if ((Reputazione >= 30) || (random(10) < 1)) {
						MaterieMem[scelta].xxx+=2;
						if (MaterieMem[scelta].xxx > 10) MaterieMem[scelta].xxx=10;
					} else {
						if (sound_active) TabbozPlaySound(402);
						MessageBox( hDlg,
					"Cosa ??? Credi di farmi paura piccolo pezzettino di letame vestito da zarro... Deve ancora nasce chi puo' minacciarmi...",
					  "Bella figura", MB_OK | MB_ICONINFORMATION);
						if (Reputazione > 3 )
							Reputazione-=2;

						if (MaterieMem[scelta].xxx > 2 )
							MaterieMem[scelta].xxx-=1;
					}
				} else { // Femminuccia - seduci prof.
					if ((Fama >= 50) || (random(10) < 2)) {
						MaterieMem[scelta].xxx+=2;
						if (MaterieMem[scelta].xxx > 10) MaterieMem[scelta].xxx=10;
					} else {
						if (sound_active) TabbozPlaySound(402);
						MessageBox( hDlg,
							"Infastidito dalla tua presenza, il prof ti manda via a calci.",
							"Bella figura", MB_OK | MB_ICONINFORMATION);
						if (Reputazione > 3 )
							Reputazione-=2;

						if (MaterieMem[scelta].xxx > 2 )
							MaterieMem[scelta].xxx-=1;
					}
				}




				Aggiorna(hDlg);
				Evento(hDlg);
				}

			return(TRUE);



		case 103:                    /* Studia */
			if (! CheckVacanza(hDlg)) {
				if (Reputazione > 10 )	/* Studiare costa fatica... */
					Reputazione-=5; /* (oltre che Reputazione e Fama...) */

				if (Fama > 5 )
					Fama-=1;

				MaterieMem[scelta].xxx+=1;
				if (MaterieMem[scelta].xxx > 10) MaterieMem[scelta].xxx=10;

				Aggiorna(hDlg);
				Evento(hDlg);
				}

			return(TRUE);

		 case 110:
		 case 111:
		 case 112:
		 case 113:
		 case 114:
		 case 115:
		 case 116:
		 case 117:
		 case 118:
			scelta=wParam-109;
			sprintf(tmp, "Corrompi il prof di %s",MaterieMem[scelta].nome); SetDlgItemText(hDlg, 101, tmp);
			if (sesso == 'M')
				sprintf(tmp, "Minaccia il prof di %s",MaterieMem[scelta].nome);
			else
				sprintf(tmp, "Seduci il prof di %s",MaterieMem[scelta].nome);
			SetDlgItemText(hDlg, 102, tmp);
			sprintf(tmp, "Studia %s",MaterieMem[scelta].nome);              SetDlgItemText(hDlg, 103, tmp);
			return(TRUE);

		 case IDOK:
			EndDialog(hDlg, TRUE);
			return(TRUE);
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