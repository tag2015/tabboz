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
#include <string.h>
#include <time.h>

#include "zarrosim.h"
#include "sharedimg.h"
#include "dialogs.h"
#include "sound.h"
#include "proteggi.h"
#include "debug.h"

#include "calendario.h"
#include "eventi.h"

#include "scuola.h"
#include "lavoro.h"
#include "scooter.h"
#include "telefono.h"

#include "tabboz.xpm"  // icona

#include "gui/GUITabboz.h"
#include "gui/GUIConfig.h"

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Preferences.H>
#include <FL/filename.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Pixmap.H>



/* Variabili generiche */
int     cheat;
bool    firsttime;
int     chiusura;
char    path_profilo[FL_PATH_MAX];


/* Caratteristiche tabbozzo */
int     Fama;
int     Reputazione;
int     Studio;
int     Soldi;
int     Paghetta;
char    Nome[30];
char    Cognome[30];
int     comp_giorno;
int     comp_mese;
char    City[50];
char    Nometipa[30];
int     FigTipa;
int     Rapporti;
int     Stato;
int     DDP;
int     Fortuna;

int     tempo_pestaggio;
int     AttesaSoldi;

char    sesso;
char    ao;
char    un_una[4];


/* Accessori */
int     current_testa;
int     current_giubbotto;
int     current_pantaloni;
int     current_scarpe;
int     current_tipa;
int     sizze;


/* Opzioni */
int     euro;
int     timer_active;
int     sound_active;
int     difficolta;
char    tema_grafico[STR_MAX];
int     logging;


static  int  t_random;      // Attesa a random tra i vari eventi timer


static const char *dir_profilo = "TabbozNG";
static const char *file_profilo = "TabbozNG";


static void    InitTabboz(void);
static void    ResetMe(int);
static void    SalvaTutto(void);
static void    CaricaTutto(void);
int            vvc(int i);



/* Aggiorna Finestra Principale */
void AggiornaPrincipale(void)
{
    char tmp[128];
     
    sprintf(tmp, "  %s %d %s",InfoSettimana[x_giornoset-1].nome,x_giorno,InfoMese[x_mese-1].nome);  // Calendario
    main_box_giorno->copy_label(tmp);
    main_valbox_rep->value(Reputazione);
    main_valbox_fama->value(Fama);
    main_valbox_studio->precision(1);
    main_valbox_studio->value(MEDIAVOTI(Studio,N_MATERIE));
    main_valbox_rapporti->value(Rapporti);
    if(Rapporti) {
        main_txtbox_tipa->value(Nometipa);
        main_valbox_rapporti->activate();
    }
    else {
        main_txtbox_tipa->value("Nessuna...");
        main_valbox_rapporti->deactivate();
    }
    if(euro) {
        main_valbox_soldi->label("€");
        main_valbox_paghetta->label("Paghetta  €");
        main_valbox_stipendio->label("Stipendio  €");
    } else {
        main_valbox_soldi->label("L.");
        main_valbox_paghetta->label("Paghetta  L.");
        main_valbox_stipendio->label("Stipendio  L.");
    }
    main_valbox_soldi->value(CALCSOLDI(Soldi));
    main_valbox_paghetta->value(CALCSOLDI(Paghetta));
    main_valbox_stipendio->value(CALCSOLDI(stipendio));
    if(stipendio)
        main_valbox_stipendio->activate();
    else
        main_valbox_stipendio->deactivate();
    main_fig_scarpe->image(ImgScarpe[current_scarpe]);   // Disegna immagine del tabbozzo/a
    main_fig_panta->image(ImgPantaloni[current_pantaloni]);
    main_fig_giub->image(ImgGiubbotto[current_giubbotto]);
    main_fig_testa->image(ImgTesta[current_testa]);

    if(ScooterData.stato!=-1000) {
        main_valbox_scooterstato->activate();
        if(ScooterData.attivita == 1)
            sprintf(tmp,"%s (in uso)",ScooterData.nome);
        else
            sprintf(tmp,"%s (%s)",ScooterData.nome,n_attivita[ScooterData.attivita]);
        main_txtbox_scooter->value(tmp);
        main_valbox_scooterstato->value(ScooterData.stato);
    } else {
        main_txtbox_scooter->value("--");
        main_valbox_scooterstato->value(0);
        main_valbox_scooterstato->deactivate();
    }
    win_principale->redraw();
}


/* Calcola parametro "Studio" sommando i voti di tutte le materie
* moltiplicando x 10 e dividendo per n.ro materie */
void CalcolaStudio(void)
{
    int i,i2;
    div_t x;

    i2=0;
    for (i=1;i<10;i++)
        i2+=MaterieMem[i].voto;

    i2=i2*10;
    x = div(i2,9);
    Studio=x.quot;
}


/* Calcola Sesso - Maschietto o Femminuccia */
void CalcolaSesso(void)
{
    if ( sesso == 'M' ) {
        ao='o';
        strcpy(un_una,"un");
    } else {
        ao='a';
        strcpy(un_una,"una");
        }
}


/* Converte la variabile soldi (in "millini") in stringa aggiungendo zeri
*  se è abilitato l'euro, semplicemente divide per 2 */
char *MostraSoldi(int i)
{
    static char tmp[128];

    if (euro)
        sprintf(tmp, "%d €", (i / 2) );
    else if (i == 0)
            sprintf(tmp, "0 L.");
        else
            sprintf(tmp, "%d000 L.", i);

    return tmp;
}


/* Routine che gestisce diverse situazioni quando i soldi sono < di quelli richiesti */
void nomoney(int tipo)
{
    if (sound_active) TabbozPlaySound(302);
    MsgIcona(ICONA_STOP);
    switch (tipo) {
        
        case DISCO:
            fl_message_title("Bella figura");
            fl_alert("Appena entrat%c ti accorgi di non avere abbastanza soldi per pagare il biglietto.\nUn energumeno buttafuori ti deposita gentilmente in un cassonetto della spazzatura poco distante dalla discoteca.",ao);
            if (Reputazione > 3 )
                Reputazione--;
            break;;
        
        case VESTITI:
            fl_message_title("Bella figura");
            fl_alert("Con cosa avresti intenzione di pagare, stronzett%c ???\nCaramelle ???",ao);
            if (Fama > 12 )
                Fama-=3;
            if (Reputazione > 4 )
                Reputazione-=2;
            break;;

        case PALESTRA:
            if (sesso == 'M') {
                fl_message_title("Non hai abbastanza soldi...");
                fl_alert("L'enorme istruttore di bodybulding ultra-palestrato ti suona come una zampogna\ne ti scaraventa fuori dalla palestra.");
            } else {
                fl_message_title("Non hai abbastanza soldi...");
                fl_alert("L'enorme istruttore di bodybulding ultra-palestrato ti scaraventa fuori dalla palestra.");
            }
            if (Fama > 14 )
                Fama-=4;
            if (Reputazione > 18 )
                Reputazione-=4;
            break;;
        
        case SCOOTER:
            if (sesso == 'M') {
                fl_message_title("Non hai abbastanza soldi...");
                fl_alert("L'enorme meccanico ti afferra con una sola mano, ti riempe di pugni,\ne non esita a scaraventare te ed il tuo motorino fuori dall'officina.");
                if (Reputazione > 7 )
                    Reputazione-=5;
                if (ScooterData.stato > 7 )
                    ScooterData.stato-=5;
            } else {
                fl_message_title("Non hai abbastanza soldi...");
                fl_alert("Con un sonoro calcio nel culo, vieni buttata fuori dall'officina.");
                if (Reputazione > 6 )
                    Reputazione-=4;
                if (Fama > 3 )
                    Fama-=2;
            }
            break;;
        
        case TABACCAIO:
            fl_message_title("Non hai abbastanza soldi...");
            fl_alert("Fai fuori dal mio locale, brut%c pezzente!\nEsclama il tabaccaio con un AK 47 in mano...",ao);
            if (Fama > 2)
                Fama-=1;
            break;;
    
        case CELLULAR:
            fl_message_title("Non hai abbastanza soldi...");
            fl_alert("Forse non ti sei accorto di non avere abbastanza soldi, stronzett%c...",ao);
            if (Fama > 2)
                Fama-=1;
            break;
    }
}


/* Legge il valore settato di difficolta e modifica i valori correlati */
void  ApplicaDifficolta(void)
{
    switch(difficolta) {
        case 1:     // per ora l'unico parametro influenzato è la fortuna
                Fortuna = 20;
                break;
        case 2:
                Fortuna = 15;
                break;
        case 3:
                Fortuna = 10;
                break;
        case 4:
                Fortuna = 5;
                break;
        case 5:
                Fortuna = 0;
    }
}



/****************** PROCEDURE LOCALI *******************/

/* Inizializza grafica e parametri di base */
static void InitTabboz(void)
{

    /* Carica immagini shared */
    fl_register_images();
    CaricaSharedImgs();
    
    /* Opzioni globali di FLTK */
    Fl::option(Fl::OPTION_VISIBLE_FOCUS, false);  //disattiva tratteggio del pulsante selezionato

    /* Icona per la taskbar */
    Fl_Pixmap *icona_xpm = new Fl_Pixmap(tabboz_xpm);
    Fl_RGB_Image *icona = new Fl_RGB_Image(icona_xpm);
    Fl_Window::default_icon(icona);
    
    /* Imposta le etichette dei pulsanti per fl_message, fl_alert e cancella l'icona */
    fl_close = "Chiudi";
    fl_cancel = "Annulla";
    fl_yes = "Sì";
    MsgInit();

    /* Inizializzazione dei numeri casuali... */
    srand(time(NULL));

    /* Inizializza un po' di variabile... */
    chiusura=0;                       // 0=resta dentro, 1=resetta, 2=salva ed esci

    Fortuna=0;                        // Uguale a me...
    AttesaSoldi=ATTESAMAX;            // attesa per avere soldi...
    timer_active=0;
    tempo_pestaggio=0;
    current_tipa=0;
    logging=false;

    /* Se il debug è attivo, abilita sempre il logging... */
    #ifdef TABBOZ_DEBUG
        logging = true;
        openlog();
        sprintf(log_buf,"tabboz: Starting Tabboz Simulator %s %s",VERSION,__DATE__);
        writelog(log_buf);
    #endif
    
    firsttime=false;
}


/* ResetMe - Reset del Tabboz Simulator */
static void ResetMe(int primavolta)
{

    Soldi             =   10;
    Paghetta          =   30;
    Reputazione       =    0;
    Fama              =    0;
    Rapporti          =    0;
    Stato             =  100;
    impegno           =    0;
    giorni_di_lavoro  =    0;
    numeroditta       =    0;
    stipendio         =    0;
    AttesaSoldi       =  ATTESAMAX;
    scad_pal_giorno   =    0;
    scad_pal_mese     =    0;

    Nometipa[0] =   0;
    FigTipa     =   0;

    for (int i=1;i<10;i++)
        MaterieMem[i].voto=2;   //BUGFIX partiamo dalla media del 2

    CalcolaStudio();

    x_mese         =  9;
    x_giorno       = 30;
    x_giornoset    =  1;
    x_anno_bisesto =  0;
    x_vacanza      =  0;

    if (primavolta) { // Se e' la prima volta che uso il tabboz resetta anche la configurazione...
        difficolta          =  5;
        timer_active        =  0;
        sound_active        =  1;
        euro                =  0;
        sesso               = 'M';
        comp_mese           = rand() % 12 + 1;
        comp_giorno         = rand() % InfoMese[comp_mese-1].num_giorni + 1;
        strcpy(Nome,"Johnny");
        strcpy(Cognome,"Tabboz");
        strcpy(City,"Milano");
        CalcolaSesso();
    }

    if (sesso == 'F') {
        strcpy(Nome,"Nessuna");
        strcpy(Cognome,"In Particolare");
    }

    sizze              =  0;
    current_testa      =  0;
    current_giubbotto  =  0;
    current_pantaloni  =  0;
    current_scarpe     =  0;

    ScooterData = ScooterMem[0];

    AbbonamentData.creditorest = -1;
    CellularData.stato         = -100;

}


/* Carica parametri da file profilo */
static void CaricaTutto(void)
{
    int  i;

    int    buf_i;            //buffer int
    char   buf_s[STR_MAX];   //buffer *char

    Fl_Preferences TabbozProfilo(Fl_Preferences::USER, dir_profilo, file_profilo);  //apre file configurazione/salvataggio
    Fl_Preferences ScooterProfilo(TabbozProfilo, "Scooter");
    Fl_Preferences CellularProfilo(TabbozProfilo, "Cellular");

    TabbozProfilo.getUserdataPath(path_profilo, FL_PATH_MAX);  // salva path profilo

    /* Prima che vengano caricate le informazioni... */
    /* azzera il checksum...                         */
    new_reset_check();

    /* Cerca le informazioni registrate */
    /* Fl_prefs supporta i tipi, le conversioni da stringa non servono più */

    /* carica parametri */
    TabbozProfilo.get("Soldi",buf_i,0);
    Soldi=new_check_i(buf_i);

    TabbozProfilo.get("Paghetta",buf_i,0);
    Paghetta=new_check_i(buf_i);
    
    TabbozProfilo.get("Reputazione",buf_i,0);
    Reputazione=vvc(new_check_i(buf_i));

    TabbozProfilo.get("Studio",buf_i,0);
    Studio=vvc(new_check_i(buf_i));
    
    TabbozProfilo.get("Fama",buf_i,0);
    Fama=vvc(new_check_i(buf_i));
    
    TabbozProfilo.get("Rapporti",buf_i,0);
    Rapporti=vvc(new_check_i(buf_i));
    
    TabbozProfilo.get("Stato",buf_i,0);
    Stato=vvc(new_check_i(buf_i));

    TabbozProfilo.get("DdP",buf_i,0);
    DDP=new_check_i(buf_i);

    TabbozProfilo.get("FigTipa",buf_i,0);
    FigTipa=vvc(new_check_i(buf_i));

    TabbozProfilo.get("Fortuna",buf_i,0);
    Fortuna=vvc(new_check_i(buf_i));

    TabbozProfilo.get("AttesaSoldi",buf_i,ATTESAMAX);
    AttesaSoldi=vvc(new_check_i(buf_i));
 
    /* carica voti materie e calcola studio */
    TabbozProfilo.get("Materie",buf_s,"",STR_MAX);
    if(buf_s[0]=='\0')  sprintf(buf_s,"CCCCCCCCC");      //BUGFIX partiamo dalla media del 2... 0 è esagerato
    for (i=1;i<10;i++) {
        MaterieMem[i].voto=buf_s[i-1] - 65;
        if ((MaterieMem[i].voto < 2) || (MaterieMem[i].voto > 10)) MaterieMem[i].voto=2;
    }
    CalcolaStudio();

    /* carica dati anagrafici */
    TabbozProfilo.get("Nome",Nome,"",STR_MAX);
    TabbozProfilo.get("Cognome",Cognome,"",STR_MAX);
    TabbozProfilo.get("Nometipa",Nometipa,"",STR_MAX);
    TabbozProfilo.get("City",City,"",STR_MAX);

    TabbozProfilo.get("SoftCheck",buf_i,0);  // Consideriamo che se il checksum è a 0 è il primo avvio
    if(!buf_i)
        firsttime=true;

    /* Se non e' gia' settato,setta il compleanno (a caso) */
    TabbozProfilo.get("CompMese",comp_mese,0);
    if (comp_mese < 1) comp_mese=rand() % 12 + 1;
    TabbozProfilo.get("CompGiorno",comp_giorno,0);
    if (comp_giorno < 1) comp_giorno=rand() % InfoMese[comp_mese-1].num_giorni + 1;

    /* carica dati calendario */
    /* Se e' la prima volta che parte il Tabboz Simulator, la data e' impostata al 30 Settembre */
    TabbozProfilo.get("Mese",x_mese,0);
    if (x_mese < 1) x_mese=9;
    
    TabbozProfilo.get("Giorno",x_giorno,0);
    if (x_giorno < 1) x_giorno=30;

    TabbozProfilo.get("GiornoSet",x_giornoset,0);
    if (x_giornoset < 1) x_giornoset=1;
    
    TabbozProfilo.get("AnnoBisestile",x_anno_bisesto,0);
    if ( (x_anno_bisesto > 3) || (x_anno_bisesto < 0) ) x_anno_bisesto=0;

    TabbozProfilo.get("ScadPalGiorno",buf_i,0);
    scad_pal_giorno = vvc(new_check_i(buf_i));

    TabbozProfilo.get("ScadPalMese",buf_i,0);
    scad_pal_mese = vvc(new_check_i(buf_i));

    /* carica dati lavoro */
    TabbozProfilo.get("NumeroDitta",buf_i,0);
    numeroditta = vvc(buf_i);

    TabbozProfilo.get("Impegno",buf_i,0);
    impegno = vvc(new_check_i(buf_i));

    TabbozProfilo.get("GiorniDiLavoro",buf_i,0);
    giorni_di_lavoro = vvc(new_check_i(buf_i));
    
    TabbozProfilo.get("Stipendio",buf_i,0);
    stipendio = new_check_i(buf_i);
    if (stipendio < 0) stipendio=0;

    /* carica dati accessori */
    TabbozProfilo.get("Sigarette",buf_i,0);
    sizze = new_check_i(buf_i);
    if (sizze < 0) sizze=0;

    TabbozProfilo.get("Testa",buf_i,0);
    current_testa = vvc(new_check_i(buf_i));

    TabbozProfilo.get("Giubbotto",buf_i,0);
    current_giubbotto = vvc(new_check_i(buf_i));

    TabbozProfilo.get("Pantaloni",buf_i,0);
    current_pantaloni = vvc(new_check_i(buf_i));

    TabbozProfilo.get("Scarpe",buf_i,0);
    current_scarpe = vvc(new_check_i(buf_i));

    /* carica opzioni */
    TabbozProfilo.get("Difficolta",difficolta,5);
    if ((difficolta < 1) || (difficolta > 5)) difficolta=5;
    ApplicaDifficolta();

    TabbozProfilo.get("Euro",euro,0);
    if (euro < 0) euro=0;
    
    #ifdef NOTABBOZZA
        sesso='M';
    #else
        TabbozProfilo.get("Sesso",buf_s,0);
        sesso=buf_s[0];
        if ((sesso != 'M') && (sesso != 'F')) sesso = 'M';
    #endif

    CalcolaSesso();

    TabbozProfilo.get("TimerActive",timer_active,-1);
    if (timer_active < 0) timer_active=0;

    TabbozProfilo.get("SoundActive",sound_active,-1);
    if (sound_active < 0) sound_active=1;

    TabbozProfilo.get("TemaGrafico",tema_grafico,"none",STR_MAX);
    Fl::scheme(tema_grafico);

    #ifndef TABBOZ_DEBUG
        TabbozProfilo.get("Logging",logging,false);
        if(logging <= 0)
            logging=false;
        else
            logging=true;
    #endif
    if(logging) openlog();

    /* carica dati scooter */
    ScooterProfilo.get("ID",buf_i,0);
    ScooterData.id = new_check_i(buf_i);
    if (ScooterData.id < 0) ScooterData.id=0;

    ScooterProfilo.get("Speed",buf_i,0);
    ScooterData.speed = new_check_i(buf_i);
    if (ScooterData.speed < 0) ScooterData.speed=0;

    ScooterProfilo.get("Marmitta",buf_i,0);
    ScooterData.marmitta = new_check_i(buf_i);
    if (ScooterData.marmitta < 0) ScooterData.marmitta=0;
    
    ScooterProfilo.get("Carburatore",buf_i,0);
    ScooterData.carburatore = new_check_i(buf_i);
    if (ScooterData.carburatore < 0) ScooterData.carburatore=0;

    ScooterProfilo.get("CC",buf_i,0);
    ScooterData.cc = new_check_i(buf_i);
    if (ScooterData.cc < 0) ScooterData.cc=0;
    
    ScooterProfilo.get("Filtro",buf_i,0);
    ScooterData.filtro = new_check_i(buf_i);
    if (ScooterData.filtro < 0) ScooterData.filtro=0;

    ScooterProfilo.get("Prezzo",buf_i,0);
    ScooterData.prezzo = new_check_i(buf_i);
    if (ScooterData.prezzo < 0) ScooterData.prezzo=0;

    ScooterProfilo.get("Attivita",buf_i,0);
    ScooterData.attivita = new_check_i(buf_i);
    if (ScooterData.attivita < 0) ScooterData.attivita=0;

    ScooterProfilo.get("Stato",buf_i,-1000);    // -1000 = nessuno
    ScooterData.stato = new_check_i(buf_i);

    ScooterProfilo.get("Benzina",buf_i,0);
    benzina = new_check_i(buf_i);
    if (benzina < 0) benzina=0;

    ScooterProfilo.get("Nome",ScooterData.nome,"Nessuno...",STR_MAX);

    /* carica dati cellulare */
    CellularProfilo.get("DualOnly",buf_i,-1);
    AbbonamentData.dualonly = new_check_i(buf_i);

    CellularProfilo.get("CreditoRest",buf_i,-1);
    AbbonamentData.creditorest = new_check_i(buf_i);

    CellularProfilo.get("NomeAbb",AbbonamentData.nome,0,STR_MAX);
    if(AbbonamentData.nome[0]==0)  AbbonamentData.creditorest= -1;

    CellularProfilo.get("DualBand",buf_i,-1);
    CellularData.dual = new_check_i(buf_i);

    CellularProfilo.get("Stato",buf_i,-1);
    CellularData.stato = new_check_i(buf_i);

    CellularProfilo.get("Prezzo",buf_i,-1);
    CellularData.prezzo = new_check_i(buf_i);

    CellularProfilo.get("Nome",CellularData.nome,0,STR_MAX);
    if(CellularData.nome[0]==0) CellularData.stato = -100;

    #ifdef TABBOZ_DEBUG
        sprintf(log_buf,"tabboz: (R) new_counter %d", new_counter);
        writelog(log_buf);
        TabbozProfilo.get("SoftCheck",buf_i,0);
        sprintf(log_buf,"tabboz: (R) read_counter %d", buf_i );
        writelog(log_buf);
        if(firsttime)
            writelog("firsttime=1, first run or empty savefile");
    #endif

    if (firsttime)
        ResetMe(1);

    /* Controllo eventuali errori nella data (o data non settata...) */
    /* FIXME si potrebbe implementare in vvc */
    if ( (x_giorno < 1) || (x_giorno > 31) )  x_giorno=1;
    if ( (x_mese < 1) || (x_mese > 12) )  x_mese=1;
    if ( (x_giornoset < 1) || (x_giornoset > 7) )  x_giornoset=1;

    x_giorno--;  //Per evitare che avanzi di giorno ogni volta che si apre il programma
    x_giornoset--;
    if(giorni_di_lavoro > 0)
        giorni_di_lavoro--;  // Come sopra
    AttesaSoldi++;  //Idem ma al contrario, per evitare che scenda ad ogni avvio
    Giorno(true);

     // Guarda se qualche "bastardino" ha modificato dei valori nel registro...
    TabbozProfilo.get("SoftCheck",buf_i,0);
    if ((new_counter - buf_i) != 0) {
        if(!firsttime) {
            if(sound_active) TabbozPlaySound(0001);
            MsgIcona(ICONA_STOP);
            fl_message_title("Ma cazz...");
            fl_alert("Visto che ti sei divertito a pasticciare con il salvataggio,\ni parametri verranno resettati!");
        }
        ResetMe(0);
    }
}


/* Salva i parametri nel profilo utente o in file specificato*/
static void SalvaTutto(void)
{
    char tmp[STR_MAX];
    
    Fl_Preferences TabbozProfilo(Fl_Preferences::USER, dir_profilo, file_profilo);  //apre file configurazione/salvataggio
    Fl_Preferences ScooterProfilo(TabbozProfilo, "Scooter");
    Fl_Preferences CellularProfilo(TabbozProfilo, "Cellular");


    /* resetta checksum per ricalcolo */
    new_reset_check();

    /* salva parametri */
    TabbozProfilo.set("Soldi",new_check_i(Soldi));
    TabbozProfilo.set("Paghetta",new_check_i(Paghetta));
    TabbozProfilo.set("Reputazione",new_check_i(Reputazione));
    TabbozProfilo.set("Studio",new_check_i(Studio));
    TabbozProfilo.set("Fama",new_check_i(Fama));
    TabbozProfilo.set("Rapporti",new_check_i(Rapporti));
    TabbozProfilo.set("Stato",new_check_i(Stato));
    TabbozProfilo.set("DdP",new_check_i(DDP));
    TabbozProfilo.set("FigTipa",new_check_i(FigTipa));
    TabbozProfilo.set("Fortuna",new_check_i(Fortuna));
    TabbozProfilo.set("AttesaSoldi",new_check_i(AttesaSoldi));

    /* salva voti materie */
    sprintf(tmp,"123456789");    // 9 materie
    for (int i=1;i<10;i++)
        tmp[i-1]=(char)(65 + MaterieMem[i].voto);
    TabbozProfilo.set("Materie", tmp);

    /* salva dati anagrafici */
    TabbozProfilo.set("Nome", Nome);
    TabbozProfilo.set("Cognome", Cognome);
    TabbozProfilo.set("Nometipa", Nometipa);
    TabbozProfilo.set("City", City);
    TabbozProfilo.set("CompMese", comp_mese);
    TabbozProfilo.set("CompGiorno", comp_giorno);

    /* salva dati calendario */
    TabbozProfilo.set("Mese", x_mese);
    TabbozProfilo.set("Giorno", x_giorno);
    TabbozProfilo.set("GiornoSet", x_giornoset);
    TabbozProfilo.set("AnnoBisestile", x_anno_bisesto);
    TabbozProfilo.set("ScadPalGiorno", new_check_i(scad_pal_giorno));
    TabbozProfilo.set("ScadPalMese", new_check_i(scad_pal_mese));

    /* salva dati lavoro */
    TabbozProfilo.set("NumeroDitta", numeroditta);
    TabbozProfilo.set("Impegno", new_check_i(impegno));
    TabbozProfilo.set("GiorniDiLavoro", new_check_i(giorni_di_lavoro));
    TabbozProfilo.set("Stipendio", new_check_i(stipendio));

    /* salva dati accessori */
    TabbozProfilo.set("Sigarette", new_check_i(sizze));
    TabbozProfilo.set("Testa", new_check_i(current_testa));
    TabbozProfilo.set("Giubbotto", new_check_i(current_giubbotto));
    TabbozProfilo.set("Pantaloni", new_check_i(current_pantaloni));
    TabbozProfilo.set("Scarpe", new_check_i(current_scarpe));

    /* salva opzioni */
    TabbozProfilo.set("Difficolta", difficolta);
    TabbozProfilo.set("Euro", euro);
    TabbozProfilo.set("TimerActive", timer_active);
    TabbozProfilo.set("SoundActive", sound_active);
    TabbozProfilo.set("TemaGrafico", tema_grafico);
    TabbozProfilo.set("Logging",logging);

    #ifndef NOTABBOZZA
        TabbozProfilo.set("Sesso", sesso);
    #endif

    /* salva dati scooter */
    ScooterProfilo.set("ID",new_check_i(ScooterData.id));
    ScooterProfilo.set("Speed",new_check_i(ScooterData.speed));
    ScooterProfilo.set("Marmitta",new_check_i(ScooterData.marmitta));
    ScooterProfilo.set("Carburatore",new_check_i(ScooterData.carburatore));
    ScooterProfilo.set("CC",new_check_i(ScooterData.cc));
    ScooterProfilo.set("Filtro",new_check_i(ScooterData.filtro));
    ScooterProfilo.set("Prezzo",new_check_i(ScooterData.prezzo));
    ScooterProfilo.set("Attivita",new_check_i(ScooterData.attivita));
    ScooterProfilo.set("Stato",new_check_i(ScooterData.stato));
    ScooterProfilo.set("Benzina",new_check_i(benzina));
    ScooterProfilo.set("Nome", ScooterData.nome);

    /* salva dati cellulare */
    CellularProfilo.set("DualOnly", new_check_i(AbbonamentData.dualonly));
    CellularProfilo.set("CreditoRest", new_check_i(AbbonamentData.creditorest));
    CellularProfilo.set("NomeAbb", AbbonamentData.nome);
    CellularProfilo.set("DualBand", new_check_i(CellularData.dual));
    CellularProfilo.set("Stato", new_check_i(CellularData.stato));
    CellularProfilo.set("Prezzo", new_check_i(CellularData.prezzo));
    CellularProfilo.set("Nome", CellularData.nome);

    TabbozProfilo.set("SoftCheck", new_counter);
    TabbozProfilo.set("Version", VERSION);

#ifdef TABBOZ_DEBUG
    sprintf(log_buf,"tabboz: (W) new_counter %d", new_counter);
    writelog(log_buf);
#endif

}


/* Verifica Valori Chiave (se tra min e max) */
int vvc(int i)
{
    if ( i < 0)
        return 0;
    else
        if ( i > 100)
            return 100;
        else
            return (i);
}


/* Se il timer è abilitato, questa funzione viene eseguita ogni TIMER_INTERVAL secondi */
void TimerCallback(void *)
{
    if (win_principale->shown() && !win_principale->visible() && timer_active) {  // timer controllato solo se ridotto a icona
        #ifdef TABBOZ_DEBUG
            writelog("timer: ciclo terminato!");
            sprintf(log_buf,"timer: prossimo evento fra %d cicli", t_random);
            writelog(log_buf);
        #endif
        if(t_random == 0) {    // quando arriva a 0, esegue un evento casuale
            Evento(true);
            t_random = 5 + ( rand() % 21);  // 5 - 25 cicli tra un evento ed il seguente...
        }
        else {  // altrimenti semplicemente passa al giorno successivo
            t_random--;
            Giorno(true);
        }
    }
    Fl::repeat_timeout(TIMER_INTERVAL, TimerCallback);    // ricarica il timer
}


/* PROCEDURA PRINCIPALE (MAIN) */
int main(int argc, char **argv)
{

    /* Inizializza il programma */
    InitTabboz();

    /* Carica dati */
    CaricaTutto();

    /* Finestra principale */
    do {
        win_principale = GUITabboz();
        win_principale->position( (Fl::w() - win_principale->w() ) / 2, (Fl::h() - win_principale->h() ) / 2);   // centra finestra
        win_principale->show(argc, argv);
        if(firsttime) {
            win_principale->hide();     //Al primo avvio, nascondiamo la principale e apriamo la finestra anagrafica
            GUICartaID(true);
            win_cartaid->position( (Fl::w() - win_cartaid->w() ) / 2, (Fl::h() - win_cartaid->h() ) / 2);   // centra finestra
            win_cartaid->hide();
            win_intro_help->position( (Fl::w() - win_intro_help->w() ) / 2, (Fl::h() - win_intro_help->h() ) / 2);   // centra finestra help
            win_intro_help->show();
            while(win_intro_help->shown()) Fl::wait();
            while(win_cartaid->shown()) Fl::wait();
            win_principale->show();
        }
        #ifndef NOTIMER
        Fl::add_timeout(TIMER_INTERVAL, TimerCallback);  // Inizializza il timer per l'avanzamento automatico dei giorni
        t_random = 5 + ( rand() % 21);  // 5 - 25 cicli tra un evento ed il seguente...
        #endif

        Fl::run();

        if(chiusura == NEWGAME) {   // nuova partita (resetta e ricomincia)
            #ifdef TABBOZ_DEBUG
                writelog("tabboz: new game (reset)");
            #endif
            ResetMe(0);
            firsttime = true;
            chiusura = NOEXIT;
        }
    }
    while(chiusura != SAVEGAME);   // uscita normale (salva)

    SalvaTutto();
    SpegniISuoni();
    #ifdef TABBOZ_DEBUG
        writelog("tabboz: standard exit (save & quit)");
    #endif

    closelog();
    return 0;
}


/* FIXME: Salva/Carica su file a scelta*/
#if 0
//*******************************************************************
// Dialog x la scelta del file da aprire...
//*******************************************************************

void OpenFileDlg(HWND hwnd)
{
#define OFN_LONGNAMES      0x00200000L

  static char szFileName[MAX_PATH];
  static OPENFILENAME ofn;
  memset(&(ofn), 0, sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hwnd;
  ofn.hInstance = hInst;
  ofn.lpstrFile = szFileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrDefExt = "tbz";
  ofn.lpstrFilter = "Tabboz Files (*.tbz)\000*.tbz\000";
  ofn.Flags = OFN_HIDEREADONLY | OFN_LONGNAMES | OFN_FILEMUSTEXIST;

  if(GetOpenFileName(&ofn)) {
        strcpy(nome_del_file_su_cui_salvare,szFileName);
        CaricaTutto();
        nome_del_file_su_cui_salvare[0]='\0';
  }
}

/*******************************************************************
Dialog x la scelta del file da salvare...
*******************************************************************/

void SaveFileDlg(HWND hwnd)
{
#define OFN_LONGNAMES      0x00200000L
  static char szFileName[256];
  static    OPENFILENAME ofn;
  memset(&(ofn), 0, sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hwnd;
  ofn.hInstance = hInst;
  ofn.lpstrFile = szFileName;
  ofn.nMaxFile = sizeof(szFileName);
  ofn.lpstrDefExt = "tbz";
  ofn.lpstrFilter = "Tabboz Files (*.tbz)\000*.tbz\000";
  ofn.Flags = OFN_HIDEREADONLY | OFN_LONGNAMES | OFN_OVERWRITEPROMPT | OFN_NOTESTFILECREATE;

  if(GetSaveFileName(&ofn)) {
        strcpy(nome_del_file_su_cui_salvare,szFileName);
        SalvaTutto();
        nome_del_file_su_cui_salvare[0]='\0';
  }
}
#endif


/* FIXME: Cheats */
/*
I cheat non sono implementati. Nel tabboz originale si attivano cliccando 10
volte sull'icona centrale nella schermata about se il nome/cognome del tabbozzo corrispondono
ai valori indicati sotto...
    "Dino Lucci"
        Soldi=Soldi+1000;
        Reputazione=random(4);
        Fama=random(40);

    "Giulio Lucci"
        Soldi=Soldi+1000;
        Reputazione=random(30);
        Fama=random(5);

    "Daniele Gazzarri"
        ScooterData=ScooterMem[7];
        benzina=850;
        Reputazione=100;

    "Emanuele Caccialanza"
        Soldi=Soldi+10000;
        Fama=100;

    "Andrea Bonomi"
        for (i=1;i<10;i++)
            MaterieMem[i].voto=10;
        CalcolaStudio();
        if ( Rapporti > 1 )
            Rapporti=100;
        impegno=100;
        numeroditta=1;
        stipendio=5000;
*/