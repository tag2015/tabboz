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
#include "dialogs.h"
#include "sound.h"

#include "calendario.h"
#include "eventi.h"

#include "lavoro.h"
#include "gui/GUILavoro.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


int    numeroditta;
int    stipendio;
int    giorni_di_lavoro;
int    impegno;

bool crocette_risposte[3][3]={0};

bool GiornoDiLavoro(const char *titolo_dialog);


STVARIE LavoroMem[] =
    {   {0, 0, 0, 0, 0, 0, 0, 0, 0, "---"},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, "Magneti Budelli"}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0, "Acciaierie Diamine"},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, "TestMec"},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, "T.I.B.B."},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, "October Heavy"},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, "Arlond's"},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, "286 - Computer d'annata"},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, "Ricopio" }
    };
//       |                    \stipendio base
//       \lavoro fuori porta (solo con lo scooter puoi arrivarci...)

// FIXME: Implementare finestre dettagli aziende (inutili ma divertenti)


/* Aggiorna caselle stipendio - impegno */
void AggiornaLavoro(void)
{
    if (numeroditta < 1) {    // Nessun lavoro
        lavoro_txt_ditta->value("---");
        lavoro_val_stipendio->value(0);
        lavoro_val_stipendio->deactivate();
        lavoro_val_impegno->value(0);
        lavoro_val_impegno->deactivate();
        lavoro_val_impegno_percent->deactivate();
    } else {
        lavoro_txt_ditta->value(LavoroMem[numeroditta].nome);
        lavoro_val_stipendio->activate();
        lavoro_val_stipendio->value(CALCSOLDI(stipendio));
        lavoro_val_impegno->activate();
        lavoro_val_impegno->value(impegno);
    }
    lavoro_val_soldi->value(CALCSOLDI(Soldi));
    win_lavoro->redraw();
}


/* Controlla quizzone e stabilisce se assunto o no */
void ControllaRisposte(int n_ditta, int n_scheda)
{
    int Rcheck = 0;

    /* n_scheda potrebbe servire in futuro se mai le risposte avranno un senso */
    /* attualmente non servono a nulla... controlliamo semplicemente che sia stata data una sola risposta per domanda */
    for(int i=0;i<3;i++) {
        if (crocette_risposte[0][i]) Rcheck+=1;
        if (crocette_risposte[1][i]) Rcheck+=10;
        if (crocette_risposte[2][i]) Rcheck+=100;
    }

    if (Rcheck != 111) {    // + di una crocetta per risposta o nessuna risposta...
        MsgIcona(ICONA_STOP);
        if (sesso == 'M') {
            fl_message_title("Sei un po' stupido...");
            fl_alert("Mi spieghi perchè dovremmo assumere qualcuno che non è neanche in grado di mettere delle crocette su un foglio ???");
        }
        else {
            fl_message_title("Sei un po' stupida...");
            fl_alert("Signorina, mi spieghi perchè dovremmo assumere qualcuno che non è neanche in grado di mettere delle crocette su un foglio ???");
        }
        Evento(false);
        AggiornaLavoro();
        return;
    }

    if (( Reputazione + Fortuna + (rand() % 80) ) > (rand() % 200) ) {   // 3 risposte date, OK - con rep bassa e fortuna=0, la prob assunzione è circa del 25%
        impegno=10 + (rand() % 20);    // impegno iniziale random 10-29
        giorni_di_lavoro=1;
        stipendio=1000 + ( (rand() % 10) * 100);    // stipendio random tra 1 mil e 1.9 mil
        numeroditta=n_ditta + 1;  //nelle dialog l'indice parte da zero

        if (sound_active) TabbozPlaySound(505);
        MsgIcona(ICONA_COOL);
        fl_message_title("Hai trovato lavoro!");
        if (sesso == 'M')
            fl_alert("SEI STATO ASSUNTO!\nOra sei un felice dipendente della %s !", LavoroMem[numeroditta].nome);
        else
            fl_alert("SEI STATA ASSUNTA!\nOra sei una felice dipendente della %s !", LavoroMem[numeroditta].nome);

    } else {
        if (sound_active) TabbozPlaySound(504);
        MsgIcona(ICONA_STOP);
        fl_message_title("Niente da fare...");
        if (sesso == 'M')
            fl_alert("Mi dispiace ragazzo, ma non sei riuscito a superare il test...\nOra puoi anche portare la tua brutta faccia fuori dal mio ufficio,\nprima che ti faccia buttare fuori a calci... Grazie e arrivederci...");
        else
            fl_alert("Mi dispiace signorina, ma non è riuscita a superare il test...\nSe ne vada immediatamente, grazie...");
        if (Reputazione > 10)
            Reputazione-=2;
    }
    Evento(false);
    AggiornaLavoro();
}


/* Per rassegnare le dimissioni */
void Licenziati(void)
{
    char tmp[128];

    if (!GiornoDiLavoro("Licenziati"))
        return;  //se è festa o disoccupato

    MsgIcona(ICONA_DOMANDA);
    fl_message_title("Mi licenzio!");
    sprintf(tmp,"Sei proprio sicur%c di voler dare le dimissioni dalla %s ?",ao,LavoroMem[numeroditta].nome);
    if(! fl_choice(tmp,"Sì, mi sono rotto","Ci ho ripensato...", 0)) {
        numeroditta=0;
        impegno=0;
        giorni_di_lavoro=0;
        stipendio=0;
        Evento(false);
    }
    AggiornaLavoro();
}


/* Calcola i soldi spettanti dopo licenziamento */
void CalcolaTFR(void) {
    int tfr;
    tfr = stipendio * (giorni_di_lavoro / 30.0 );
    MsgIcona(ICONA_INFO);
    fl_message_title("Trattamento di fine rapporto");
    fl_message("Il tuo T.F.R. ammonta a %s", MostraSoldi(tfr));
    Soldi+=tfr;
}


/* Incrementa l'impegno */
void Lavora(void)
{
    if (! GiornoDiLavoro("Lavora"))
        return;
    if (impegno < 85)
        impegno++;
    if (sound_active) TabbozPlaySound(501);
    Evento(false);
    AggiornaLavoro();

}


/* Aumenta impegno perdendo rep e fama */
void FaiIlLeccaculo(void)
{
    if (sesso == 'M') {
        if (! GiornoDiLavoro("Fai il leccaculo"))
            return;
        } else {
            if (! GiornoDiLavoro("Fai la leccaculo"))
            return;
        }
    if (sound_active) TabbozPlaySound(503);
    
    if (Reputazione > 20 )    /* Facendo il leccaculo perdi reputazione e fama... */
        Reputazione-=1;
    if (impegno < 99)
        impegno++;

    if( (rand() % (Fortuna+3)) == 0 )    // evento casuale per sfigati
        Evento(false);

    AggiornaLavoro();
}


/* Routine per incrementare stipendio se impegno è molto alto */
void ChiediAumento(void)
{

    if (!GiornoDiLavoro("Chiedi aumento salario"))
        return; //se è festa o disoccupato

    fl_message_title("Chiedi un aumento");

    if (impegno > 90) {
        if ((30 + Fortuna) > (30 + rand() % 50)) {
            MsgIcona(ICONA_COOL);
            fl_message("Forse per questa volta potremmo darti qualcosina in più...");
            if (sound_active) TabbozPlaySound(1100);

            //stipendio+=((random(1)+1) * 100);  // questa formula non funziona perchè random(1) restituisce interi
            stipendio+=( (rand() % 10) + 10 ) * 10;   // BUGFIX questa sì

            impegno-=30;
            Evento(false);
        } else {
            MsgIcona(ICONA_AVVISO);
            if (sesso == 'M' )  // visto che l'impegno è >90, sfanculata politically correct
                fl_alert("Siamo soddisfatti del tuo rendimento, ma attualmente\nnon possiamo applicare variazioni agli emolumenti per i dipendenti.");
            else
                fl_alert("Siamo soddisfatti del tuo rendimento, ma attualmente\nnon possiamo applicare variazioni agli emolumenti per i dipendenti.");
            impegno-=20;
            Evento(false);
        }
    } else {
        MsgIcona(ICONA_STOP);
        fl_alert("Che cosa vorresti??? SCORDATELO!!!!");
    }    
    AggiornaLavoro();
}


/* Aumenta rep perdendo impegno */
void Sciopera(void)
{
    if (! GiornoDiLavoro("Sciopera"))
        return;
    if (sound_active) TabbozPlaySound(502);

    if (Reputazione < 85 )
        Reputazione+=10;
    if (impegno > 19 )
    impegno-=15;

    if( (rand() % (Fortuna+3)) == 0 )    // evento casuale per sfigati
        Evento(false);

    Evento(false);    // due eventi? azz...
    AggiornaLavoro();
}


/* Controlla che sia un giorno lavorativo e che il tabbozzo non sia disoccupato */
bool GiornoDiLavoro(const char *titolo_dialog)
{

    fl_message_title(titolo_dialog);
    MsgIcona(ICONA_AVVISO);
    if (numeroditta < 1)  {
        fl_alert("Forse non ti ricordi che sei disokkupat%c...",ao);
        return false;
    }

    if ( ( x_vacanza == 2 ) || (x_giornoset == 6) ) {  // BUGFIX le ditte sono chiuse al sabato...
        fl_alert("Arrivat%c davanti ai cancelli della ditta li trovi irrimediabilmente chiusi...",ao);
        return false;
        }

    return true;
}