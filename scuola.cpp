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
#include <ctype.h>

#include "zarrosim.h"
#include "dialogs.h"
#include "sound.h"
#include "debug.h"

#include "calendario.h"
#include "eventi.h"

#include "scuola.h"
#include "gui/GUIScuola.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Value_Output.H>


STMATERIE MaterieMem[] =
	{   {"---",                   0},
		{"Agraria",               0},
		{"Fisica",                0},
		{"Attività culturali",   0},
		{"Attività matematiche", 0},
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
    scuola_val_media->precision(1);  // mostra media decimale
    scuola_val_media->value(MEDIAVOTI(Studio,N_MATERIE));
    if(scuola_val_media->value() < 5)              // aggiunge colore ai voti
        scuola_val_media->textcolor(FL_RED);
    else if (scuola_val_media->value() > 7)
        scuola_val_media->textcolor(FL_DARK_GREEN);
    else
        scuola_val_media->textcolor(FL_BLACK);
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
        if (sound_active) TabbozPlaySound(403);
        if (MaterieMem[scelta].voto > 10) MaterieMem[scelta].voto=10;

    Evento(false);
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
	    MsgIcona(ICONA_DOMANDA);
		sprintf(tmp,"Mah... forse per %s potrei dimenticare i tuoi ultimi compiti in classe...",MostraSoldi(i) );
		fl_message_title("Corrompi il professore?");
        si_no=fl_choice(tmp, "Ok...", "No", 0);
    switch(si_no){
        case 0: { // Si
                if (Soldi >= i) {
                    Soldi-=i;
                    if (sound_active) TabbozPlaySound(207);
                    #ifdef TABBOZ_DEBUG
                        sprintf(log_buf,"scuola: Corrompi un professore per %s",MostraSoldi(i));
                        writelog(log_buf);
                    #endif
                    MaterieMem[scelta].voto+=3;
                    if (MaterieMem[scelta].voto > 10 )
                        MaterieMem[scelta].voto=10;
                } else {
                    if (MaterieMem[scelta].voto >= 4 )   //BUGFIX qui era <2 ??? Se >=4 abbassa di 2
                        MaterieMem[scelta].voto-=2;
                    else
                        MaterieMem[scelta].voto=2;       // BUGFIX negli altri casi limita a 2
                    MsgIcona(ICONA_STOP);
					fl_message_title("Errore Critico");
                    fl_alert("Cosa ??? Prima cerchi di corrompermi, poi si scopre che non hai abbastanza soldi !!!");
 				}
                break;
        }
        case 1: {} // No
    }
    Evento(false);
    AggiornaScuola();
    }
}


/* Minaccia o Seduci prof. della materia selezionata */
void MinacciaSeduciProf(int scelta)
{
    MsgIcona(ICONA_STOP);

    if (!CheckVacanza()) {
        if (sesso == 'M') { // Maschietto - minaccia prof.
            if ((Reputazione >= 30) || (rand() % 10 < 1)) {    //FIXME rep>30 è sufficiente per minacciare?
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
    Evento(false);
    AggiornaScuola();
    }
}


/* Mostra la pagella... ritorna true/false per promosso/bocciato*/
bool MostraPagella(void)
{
    char    tmp[1024];
    int     i;
    int     insuf=0, grav_insuf=0;

    GUIPagella();			// mostra finestra pagella
    win_pagella->position( (Fl::w() - win_pagella->w() ) / 2, (Fl::h() - win_pagella->h() ) / 2);   // centra finestra
    win_pagella->show();
    for (i=0;i<N_MATERIE;i++) {
        Fl_Value_Output *casella = (Fl_Value_Output *) pag_voti->child(i);    // pag_voti è il gruppo contenente le ValueBox per i voti
        Fl_Round_Button *materia = (Fl_Round_Button *) pag_materie->child(i);
        casella->value(MaterieMem[i+1].voto);
        if(casella->value() < 6) {     // evidenzia insufficienze
			casella->textcolor(FL_RED);
            if(casella->value() < 5) {
                grav_insuf++;
	            materia->labelcolor(FL_RED);
			}
			else
				materia->labelcolor(FL_BLACK);
            insuf++;
        } else {
			casella->labelcolor(FL_BLACK);
		}
    }

    pag_gravinsuf->value(grav_insuf);
    pag_insuf->value(insuf-grav_insuf);
	if(grav_insuf>0)
		pag_gravinsuf->textcolor(FL_RED);
	else
		pag_gravinsuf->textcolor(FL_BLACK);		

    if (Fama > 75)                    // Condotta... + un e' figo, + sembra un bravo ragazzo...
        pag_condotta->value(9);
    else
        pag_condotta->value(8);

    if( (grav_insuf > 2) || (insuf > 4) ) {
        if (sound_active) TabbozPlaySound(401);
        sprintf(tmp, "NON AMMESS%c",toupper(ao));        /* bocciato/a */
        pag_giudizio->copy_label(tmp);
		pag_giudizio->labelcolor(FL_RED);
		pag_btn->copy_label("Ma vaff...");
		if(logging)
        	writelog("calendario: Pagella... Bocciato !!!");
        while(win_pagella->shown()) Fl::wait();   //attende chiusura
		return false;
    
	} else {
        if (sound_active) TabbozPlaySound(400);
        sprintf(tmp, "AMMESS%c",toupper(ao));        /* promosso/a */
        pag_giudizio->copy_label(tmp);
		pag_giudizio->labelcolor(FL_BLACK);
		pag_btn->copy_label("Vacanze!!!");
		if(logging)
        	writelog("calendario: Pagella... Promosso...");
        while(win_pagella->shown()) Fl::wait();   //attende chiusura
		return true;
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
    MsgIcona(ICONA_AVVISO);

    if ( x_vacanza != 0 ) {
        fl_message_title("Scuola chiusa...");
		fl_alert("Non puoi andare a scuola in un giorno di vacanza!");
        return(true);
    }
 	else
        return(false);
}