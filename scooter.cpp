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
#include "debug.h"

#include "calendario.h"
#include "eventi.h"

#include "scooter.h"
#include "gui/GUIScooter.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/fl_ask.H>


NEWSTSCOOTER ScooterData;

NEWSTSCOOTER ScooterMem[] = {
    {0,   0,  0, 0, 0, 0,     0,  0, -1000, "---",                         0},
    {1,  65,  0, 0, 0, 0,  2498,  1,   100, "Malagutty Firecow",           5},
    {2,  75,  0, 1, 1, 1,  4348,  1,   100, "Honda F98",                  10},
    {3, 105,  1, 1, 2, 1,  6498,  1,   100, "Mizzubisci R200 Millenium",  15},

    {4,  75,  0, 0, 1, 1,  4298,  1,   100, "Malagutty Firecow+",          7},
    {5, 100,  0, 1, 2, 1,  5998,  1,   100, "Malagutty Firecow II",       10},
    {6, 100,  0, 1, 2, 1,  6348,  1,   100, "Honda F98s",                 13},

    {7, 250,  0, 5, 5, 0,  1450,  1,   100, "Lexux LS400 ",               60}
};

const char  *n_carburatore[]= { "12/10", "16/16", "19/19", "20/20", "24/24" , "custom" };
const char  *n_cc[]=          { "50cc", "70cc", "90cc", "120cc", "150cc", "3969cc" };
const char  *n_marmitta[]=    { "standard", "silenziosa", "rumorosa", "rumorosissima" };
const char  *n_filtro[]=      { "standard", "P1", "P2", "P2+" , "Extreme" };

const char  *n_attivita[]=    { "incidentato", "funzionante", "ingrippato", "invasato" , "parcheggiato", "sequestrato", "a secco" };
int         benzina;


/* Questa tabella controlla che il carburatore selezionato sia adatto al cilindro/pistone montato e
* viceversa. I valori sono bonus o malus (-) e possono rendere il motorino invasato o grippato */
const int elaborazione[]= {
       65,     70,   -100,   -100,   -100,   -100,
       70,     80,     95,   -100,   -100,   -100,
    -1000,     90,    100,    115,   -100,   -100,
    -1000,  -1000,    110,    125,    135,   -100,
    -1000,  -1000,  -1000,    130,    150,   -100,
    -1000,  -1000,  -1000,  -1000,  -1000,    250
};

/* Costo dei vari pezzi di motorino*/
int    PezziMem[][5] = {
    { 100, 400,  500,  600,      },   /* marmitte    */
    { 100, 300,  470,  650,  800 },   /* carburatori */
    { 150, 200,  400,  800, 1000 },   /* cc          */
    {  20,  50,  120,  270,  400 },   /* filtro      */
};



/* Aggiorna finestra */
void AggiornaScooter(void)
{
    char tmp[128];
    div_t      d;

    sco_val_soldi->value(CALCSOLDI(Soldi));

    if (ScooterData.stato != -1000) {

        sco_txt_nome->value(ScooterData.nome);

        if (ScooterData.attivita == 1) {
            sprintf(tmp, "%d Km/h",ScooterData.speed);
            sco_txt_speed->value(tmp);
        } else {
            sprintf(tmp, "%s!", n_attivita[ScooterData.attivita]);
            sco_txt_speed->value(tmp);
        }

        sco_txt_cc->value(n_cc[ScooterData.cc]);

        sprintf(tmp, "%d%%", ScooterData.stato);
        if(ScooterData.stato<=35)
            sco_txt_stato->textcolor(FL_RED);
        else
            sco_txt_stato->textcolor(FL_BLACK);
        sco_txt_stato->value(tmp);


        d = div(benzina,10);
        sprintf(tmp, "%d.%dl", d.quot, d.rem);
        sco_txt_benza->value(tmp);

    } else {
        sco_txt_nome->value("Nessuno scooter");
        sco_txt_speed->value("--");
        sco_txt_cc->value("--");
        sco_txt_stato->value("--");
        sco_txt_benza->value("--");
    }
    win_scooter->redraw();
}


/* Calcola la velocita' massima dello scooter, secondo marmitta, carburatore, etc... */
void CalcolaVelocita(bool scooter_nuovo)
{
    /* 28 Novembre 1998 0.81pr Bug ! Se lo scooter era ingrippato, cambiando il filtro
    dell' aria o la marmitta la velocita' diventava un numero negativo... */

    ScooterData.speed = (ScooterData.marmitta * 5) + (ScooterData.filtro * 5)
                        + elaborazione[ScooterData.cc + (ScooterData.carburatore * 6 )];

    ScooterData.attivita = 1;    // Sano...

    /* 26 Novembre 1998 0.81pr  Arggg!!! Un bug !!! */
    /* Se lo scooter sta' per essere comprato, non fa' questi noiosi check... */
    if (!scooter_nuovo) {  //FIXME ricontollare questi check
        if (ScooterData.speed <= -500 ) ScooterData.attivita = 3;    // Invasato
        else if (ScooterData.speed <= -1 ) ScooterData.attivita = 2;    // Ingrippato

        if (benzina < 1) ScooterData.attivita = 6;    // A secco

        if (ScooterData.attivita != 1) {
            MsgIcona(ICONA_AVVISO);
            fl_message_title("Attenzione");
            fl_alert("Il tuo scooter è %s!", n_attivita[ScooterData.attivita]);
        }
    }
}


/* Routine controllo soldi e incentivi rottamazione */
void AcquistaScooter(int scelta)
{
    int  incentivo = 0;

    if (ScooterData.stato != -1000) {  //BUGFIX check cambiato, perchè prima rottamava anche se poi non bastavano i soldi x comprare quello nuovo...
        incentivo=1000;
        MsgIcona(ICONA_INFO);
        fl_message_title("Incentivi");
        fl_message("Per il tuo vecchio scooter da rottamare,\nti diamo %s di supervalutazione...",MostraSoldi(1000));
    }
    if (ScooterMem[scelta].prezzo > (Soldi+incentivo)) {
        MsgIcona(ICONA_STOP);
        fl_message_title("Non hai abbastanza soldi!");
        fl_alert("Ti piacerebbe comprare lo scooter, vero?\nPurtroppo, non hai abbastanza soldi...");
        if (Reputazione > 3 )
            Reputazione-=1;
    } else {
        Soldi+=incentivo;
        Soldi-=ScooterMem[scelta].prezzo;
        if (logging) {
            if(incentivo) {
                sprintf(log_buf,"scooter: Incentivo rottamazione %s",MostraSoldi(1000));
                writelog(log_buf);
            }
            sprintf(log_buf,"scooter: Acquista uno scooter per %s",MostraSoldi(ScooterMem[scelta].prezzo));
            writelog(log_buf);
        }
        ScooterData=ScooterMem[scelta];
        benzina=20;
        MsgIcona(ICONA_COOL);
        fl_message_title("Scooter nuovo!");
        fl_message("Fai un giro del quartiere per farti vedere con lo scooter nuovo...");
        Reputazione+=4;
        if (Reputazione > 100) Reputazione=100;
        CalcolaVelocita(true);    
    }
    Evento();
}


/* Routine per parcheggiare/riprendere lo scooter */
bool ParcheggiaScooter(void)
{
    fl_message_title("Parcheggia lo scooter");

    if (ScooterData.stato == -1000) {
        MsgIcona(ICONA_DOMANDA);
        fl_alert("Mi spieghi come fai a parcheggiare lo scooter se non lo hai ???");
        return false;
        }

    switch (ScooterData.attivita) {
        case 1: 
            ScooterData.attivita = 4;
            return true;
        case 4:
            ScooterData.attivita = 1;
            return false;
        default:
            MsgIcona(ICONA_AVVISO);
            fl_alert("Mi spieghi come fai a parcheggiare lo scooter visto che è %s ???",n_attivita[ScooterData.attivita]);
    };
    return false;
}


/* Routine per rifornire lo scooter */
void FaiBenza(void)
{
    fl_message_title("Fai benza");
    if (ScooterData.stato == -1000) {
        MsgIcona(ICONA_DOMANDA);
        fl_alert("Mi spieghi come fai a far benzina allo scooter se non lo hai ???");
        return;
    }

    switch (ScooterData.attivita) {
        case 1:
        case 2:
        case 3:
        case 6:
                if (Soldi < 10) {
                    MsgIcona(ICONA_AVVISO);
                    fl_alert("Al distributore automatico puoi fare un minimo di %s di benzina...",MostraSoldi(10));
                    break;
                }
                if (benzina == 50) {
                    MsgIcona(ICONA_AVVISO);
                    fl_message_title("Un genio");
                    fl_alert("Arrivato dal benzinaio,\nti accorgi che il serbatoio è già pieno...");
                    break;
                }
                Soldi-=10;
                #ifdef TABBOZ_DEBUG
                    sprintf(log_buf,"scooter: Paga benzina (%s)",MostraSoldi(10));
                    writelog(log_buf);
                #endif
                benzina=50;    // 5 litri, il massimo che puo' contenere...
                if (ScooterData.cc == 5) benzina = 850;  // 85 litri, x la macchinina un po' figa...
                CalcolaVelocita(false);
                MsgIcona(ICONA_INFO);
                fl_message("Fai %s di benzina e riempi lo scooter...",MostraSoldi(10));
                break;

        default:MsgIcona(ICONA_AVVISO);
                fl_message("Mi spieghi come fai a far benzina allo scooter visto che è %s ???",n_attivita[ScooterData.attivita]);
    };
    AggiornaScooter();
}


/* Routine per riportare efficienza al 100% o risolvere altri problemi */
void RiparaScooter(void)
{

    char tmp[128];
    int costo;  // Importante lo static !!! FIXME e perché visto che lo ricalcola sempre?

    MsgIcona(ICONA_DOMANDA);
    fl_message_title("Ripara Scooter");    
    if (ScooterData.stato != -1000) {
        if (ScooterData.stato == 100)
            fl_message("Che motivi hai per voler riparare il tuo scooter\nvisto che è al 100%% di efficienza ???");
        else {
            if ( x_vacanza != 2 ) {

                switch(ScooterData.attivita) {

                    case 0: // Scooter incidentato
                        fl_message_title("Ripari lo scooter?");  // HACK fl_choice non va d'accordo con il %%
                        sprintf(tmp,"Il tuo scooter è un rottame!\nSe proprio vuoi per %s posso riportarlo al 20%s di efficienza...", MostraSoldi(1000),"%%");
                        if (! fl_choice(tmp,"OK!","Lascio perdere...",0)) {
                            if(Soldi < 1000)
                                nomoney(SCOOTER);
                            else {
                                if (sound_active) TabbozPlaySound(102);
                                ScooterData.stato=20;
                                Soldi-=1000;
                                CalcolaVelocita(false);
                                if (logging) {
                                    sprintf(log_buf,"scooter: Paga riparazione emergenza (%s)",MostraSoldi(1000));
                                    writelog(log_buf);
                                }
                            }
                            Evento();  //avanziamo il calendario solo se accettiamo
                        }
                        break;

                    case 2:   // Scooter grippato/invasato
                    case 3:
                        fl_message_title("Ripari lo scooter?");
                        sprintf(tmp,"Il tuo scooter è %s!\nPer %s posso rimetterti carburatore e cilindro originali...", n_attivita[ScooterData.attivita], MostraSoldi(500));
                        if (! fl_choice(tmp,"OK!","Faccio da solo!",0)) {
                            if(Soldi < 500)
                                nomoney(SCOOTER);
                            else {
                                if (sound_active) TabbozPlaySound(102);
                                ScooterData.carburatore = ScooterMem[ScooterData.id].carburatore;
                                ScooterData.cc = ScooterMem[ScooterData.id].cc;
                                Soldi-=500;
                                CalcolaVelocita(false);
                                if (logging) {
                                    sprintf(log_buf,"scooter: Paga ripristino (%s)",MostraSoldi(500));
                                    writelog(log_buf);
                                }
                            }
                            Evento();  //avanziamo il calendario solo se accettiamo
                        }
                        break;

                    case 1:  //Scooter funzionante/parcheggiato/a secco
                    case 4:
                    case 6:
                        /* BUGFIX Il costo delle riparazioni è stato ritoccato, ( prezzo/100->prezzo/120 ) perchè con gli incentivi veniva a costare meno nuovo... */
                        costo = (ScooterData.prezzo / 120 * (100 - ScooterData.stato)) + 10;  //calcola il costo della riparazione dello scooter...
                        fl_message_title("Ripari lo scooter?");  // HACK fl_choice non va d'accordo con il %%
                        sprintf(tmp,"Per %s, posso riportare il tuo scooter al 100%s di efficienza...", MostraSoldi(costo),"%%");
                        if (! fl_choice(tmp,"OK!","Lascio perdere...",0)) {
                            if(Soldi < costo)
                                nomoney(SCOOTER);
                            else {
                                if (sound_active) TabbozPlaySound(102);
                                ScooterData.stato=100;
                                Soldi-=costo;
                                CalcolaVelocita(false);
                                if (logging) {
                                    sprintf(log_buf,"scooter: Paga riparazione (%s)",MostraSoldi(costo));
                                    writelog(log_buf);
                                }
                            }
                            Evento();  //avanziamo il calendario solo se accettiamo
                        }
                        break;
                }
                AggiornaScooter();
            } else {
                MsgIcona(ICONA_AVVISO);
                fl_alert("Oh, tip%c... oggi il meccanico è chiuso...",ao);
            }
        }
    } else {
        MsgIcona(ICONA_DOMANDA);
        fl_message("Mi spieghi come fai a farti riparare lo scooter se non lo hai ???");
    }
}



/* Routine per vendere lo scooter attuale */
bool VendiScooter(void)
{
    char        tmp[128];
    static int  offerta;  /* importante lo static !!! */
    div_t       lx;

    lx=div(ScooterData.prezzo, 100);

    fl_message_title("Vendi scooter");

    if (ScooterData.attivita == 0) { // Scooter incidentato
        MsgIcona(ICONA_AVVISO);
        fl_alert("Non ritiriamo scooter incidentati!\nRiparalo, prima... oppure te lo supervalutiamo se ne compri uno nuovo");
        return false;
    }

    if ( (ScooterData.attivita == 1) || (ScooterData.attivita == 4) || (ScooterData.attivita == 6))
        offerta=(lx.quot * (ScooterData.stato - 10 - (rand() % 10)));  // Scooter funzionante, parcheggiato o senza benza
    else
        offerta=(lx.quot * (ScooterData.stato - 50 - (rand() % 10)));  // Scooter grippato, invasato o altro

    if (offerta < 50) offerta = 50;  //se vale meno di 50.000, viene pagato 50.000 (condizione che non serve a nulla)

    MsgIcona(ICONA_DOMANDA);
    sprintf(tmp,"Per il tuo scooter possiamo darti %s ... va bene?",MostraSoldi(offerta));
    if(!fl_choice(tmp, "Ok", "No!", 0)) {
        ScooterData = ScooterMem[0];  // nessuno scooter
        benzina = 0;                  // serbatoio vuoto
        ScooterData.stato = -1000;
        ScooterData.attivita = 0;
        Soldi += offerta;
        if (logging) {
            sprintf(log_buf,"scooter: Vendi lo scooter per %s",MostraSoldi(offerta));
            writelog(log_buf);
        }
        return true;
    }
    return false;
}


/* Routine di acquisto generika di un pezzo di motorino */
bool CompraUnPezzo(PezziMoto pezzo, int scelta)
{
    char  tmp[256];

    MsgIcona(ICONA_DOMANDA);
    fl_message_title("Sei sicuro?");
    switch (pezzo) {
        case MARMITTA:
            if(!euro)
                sprintf(tmp, "Vuoi passare ad una marmitta %s?\nPrezzo: L. %d (manodopera inclusa)", n_marmitta[scelta], CALCSOLDI(PezziMem[MARMITTA][scelta]));
            else
                sprintf(tmp, "Vuoi passare ad una marmitta %s?\nPrezzo: € %d (manodopera inclusa)", n_marmitta[scelta], CALCSOLDI(PezziMem[MARMITTA][scelta]));
            break;
        case CARB:
            if(!euro)
                sprintf(tmp, "Vuoi passare ad un carburatore %s?\nPrezzo: L. %d (manodopera inclusa)\n\nATTENZIONE: una combinazione errata carburatore/gruppo termico può rendere\nil motorino grippato o ingolfato!!!", n_carburatore[scelta], CALCSOLDI(PezziMem[CARB][scelta]));
            else
                sprintf(tmp, "Vuoi passare ad un carburatore %s?\nPrezzo: € %d (manodopera inclusa)\n\nATTENZIONE: una combinazione errata carburatore/gruppo termico può rendere\nil motorino grippato o ingolfato!!!", n_carburatore[scelta], CALCSOLDI(PezziMem[CARB][scelta]));
            break;
        case CC:
            if(!euro)
                sprintf(tmp, "Vuoi passare ad un gruppo termico da %s?\nPrezzo: L. %d (manodopera inclusa)\n\nATTENZIONE: una combinazione errata carburatore/gruppo termico può rendere\nil motorino grippato o ingolfato!!!", n_cc[scelta], CALCSOLDI(PezziMem[CC][scelta]));
            else
                sprintf(tmp, "Vuoi passare ad un gruppo termico da %s?\nPrezzo: € %d (manodopera inclusa)\n\nATTENZIONE: una combinazione errata carburatore/gruppo termico può rendere\nil motorino grippato o ingolfato!!!", n_cc[scelta], CALCSOLDI(PezziMem[CC][scelta]));
            break;
        case FILTRO:
            if(!euro)
                sprintf(tmp, "Vuoi passare ad un filtro aria %s?\nPrezzo: L. %d (manodopera inclusa)", n_filtro[scelta], CALCSOLDI(PezziMem[FILTRO][scelta]));
            else
                sprintf(tmp, "Vuoi passare ad un filtro aria %s?\nPrezzo: € %d (manodopera inclusa)", n_filtro[scelta], CALCSOLDI(PezziMem[FILTRO][scelta]));
            break;
    }
    if(fl_choice(tmp,"OK!","No...", 0))
        return true;

    if (Soldi < PezziMem[pezzo][scelta]) {
        nomoney(SCOOTER);
        return false;
    }
    Soldi -= PezziMem[pezzo][scelta];
    if (sound_active) TabbozPlaySound(103);

    switch (pezzo) {
        case MARMITTA: /* marmitte ----------------------------------------------------------- */
            if (logging) {
                sprintf(tmp, "scooter: Paga marmitta (%s)", MostraSoldi(PezziMem[pezzo][scelta]));
                writelog(tmp);
            }
            ScooterData.marmitta = scelta; /* (1 - 3 ) */
            CalcolaVelocita(false);
            return true;

        case CARB: /* carburatore -------------------------------------------------------- */
            if (logging) {
                sprintf(tmp, "scooter: Paga carburatore (%s)", MostraSoldi(PezziMem[pezzo][scelta]));
                writelog(tmp);
            }
            ScooterData.carburatore = scelta; /* ( 1 - 4 ) */
            CalcolaVelocita(false);
            return true;

        case CC: /* cc ----------------------------------------------------------------- */
            if (logging) {
                sprintf(tmp,"scooter: Paga cilindro e pistone (%s)",MostraSoldi(PezziMem[pezzo][scelta]));
                writelog(tmp);
            }
            /* Piccolo bug della versione 0.6.91, qui c'era scritto ScooterData.marmitta */
            /* al posto di ScooterData.cc :-) */
            ScooterData.cc = scelta; /* ( 1 - 4 ) */
            CalcolaVelocita(false);
            return true;

        case FILTRO:   /* filtro dell' aria -------------------------------------------------- */
            if (logging) {
                sprintf(tmp,"scooter: Paga filtro dell' aria (%s)",MostraSoldi(PezziMem[pezzo][scelta]));
              writelog(tmp);
            }
            ScooterData.filtro = scelta; /* (1 - 4) */
            CalcolaVelocita(false);
            return true;

        default:
            return false;
    }
}


/* FIXME: inutile
char *MostraSpeed(void)
{
    char tmp[128];

    switch (ScooterData.attivita) {
        case 1:    sprintf(tmp, "%dKm/h",  ScooterData.speed);
                   break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:   sprintf(tmp, "(%s)",n_attivita[ScooterData.attivita]);
                  break;
        default:  sprintf(tmp, "");
    };

    return tmp;
}*/