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
#include "sharedimg.h"
#include "sound.h"
#include "proteggi.h"
#include "debug.h"

#include "calendario.h"

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
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Pixmap.H>


/* Variabili generiche */
int     cheat;
bool    firsttime;
int     chiusura;

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


#ifndef NOTIMER
    static  int  t_random;              // Attesa a random tra i vari eventi timer
#endif
int     fase_di_avvio;      // FIXME per il timer... inutile?
int     intro_active;       // Visualizza schermata introduttiva


static const char *dir_profilo = "TabbozNG";
static const char *file_profilo = "TabbozNG";
char              path_profilo[STR_MAX]="dummy.tbz";  // FIXME Path e file dove salvare (per ora non usato)


int vvc(int i);

static void     CalcolaSesso(void);

static void     InitTabboz(void);
static void     ResetMe(int);
static void     SalvaTutto(void);
static void     CaricaTutto(void);



/* Calcola Sesso - Maschietto o Femminuccia */
static void CalcolaSesso(void)
{
    if ( sesso == 'M' ) {
        ao='o';
        strcpy(un_una,"un");
    } else {
        ao='a';
        strcpy(un_una,"una");
        }
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
        intro_active        =  1;
        timer_active        =  0;
        sound_active        =  1;
        euro                =  0;
        sesso               = 'M';
        comp_mese           = rand() % 12 + 1;
        comp_giorno         = rand() % InfoMese[comp_mese-1].num_giorni + 1;
        strcpy(Nome,"TIZIO");
        strcpy(Cognome,"CAIO");
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
    CellularData.stato         = -1;

}


//*******************************************************************
// Formattazione iniziale Tabbozzo (scelta sesso, nome...) 14-01-2000
//*******************************************************************
//TAG2015 Questa routine usa una finestra simile al format di windows x creare un nuovo tabbozzo/a
//TAG2015 carino esteticamente ma sarebbe meglio creare una specie di wizard x scegliere nome cognome
//TAG2015 compleanno (non random) sesso residenza e le opzioni (difficolta suono etc)
// #pragma argsused
// BOOL FAR PASCAL FormatTabboz(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
//     static char tmpsesso;

//     if (message == WM_INITDIALOG) {
//         if (firsttime == 1) EnableWindow( GetDlgItem(hDlg,2), 0);

//         SendMessage(GetDlgItem(hDlg, 102), BM_SETCHECK, TRUE, 0L);
//         if (random(2) == 1) tmpsesso='M'; else tmpsesso='F';

//         //sprintf(buf,"prova");
//         //SendMessage(GetDlgItem(hDlg, 110), CB_ADDSTRING, 0, t);

//         return(TRUE);
//         }

//     if (message == WM_COMMAND) {
//         switch (LOWORD(wParam))    {
//             case 100: tmpsesso = 'M';
//                       break;
//             case 101: tmpsesso = 'F';
//                       break;
//             case 102: if (random(2) == 1) tmpsesso='M'; else tmpsesso='F';
//                       break;
//             case IDOK:
//                       ResetMe(0);
//                       sesso=tmpsesso;
//                       CalcolaSesso();
//                       EndDialog(hDlg, TRUE);
//                       return(TRUE);
//             case IDCANCEL:
//                            if (firsttime == 1) {
//                                sesso=tmpsesso;
//                                CalcolaSesso();
//                                EndDialog(hDlg, TRUE);
//                            }
//                            EndDialog(hDlg, TRUE);
//                            return(TRUE);

//             default: return(TRUE);
//         }
//     }

//     return(FALSE);
// }


/* Inizializza grafica e parametri di base */
static void InitTabboz(void)
{
    path_profilo[0]=0;

    /* Carica immagini shared */
    fl_register_images();
    CaricaSharedImgs();
    
    /* Opzioni globali di FLTK */
    Fl::option(Fl::OPTION_VISIBLE_FOCUS, false);  //disattiva tratteggio del pulsante selezionato

    /* Icona per la taskbar */
    Fl_Pixmap *icona_xpm = new Fl_Pixmap(tabboz_xpm);
    Fl_RGB_Image *icona = new Fl_RGB_Image(icona_xpm);
    Fl_Window::default_icon(icona);
    
    /* Etichette dei pulsanti per fl_message, fl_alert... */
    fl_close = "Chiudi";
    fl_cancel = "Annulla";
    fl_yes = "Sì";

    /* Inizializzazione dei numeri casuali... */
    srand(time(NULL));

    /* Inizializza un po' di variabile... */
    chiusura=0;                       // 0=resta dentro, 1=resetta, 2=salva ed esci

    Fortuna=0;                        // Uguale a me...
    AttesaSoldi=ATTESAMAX;            // attesa per avere soldi...
    timer_active=0;
    fase_di_avvio=1;
    tempo_pestaggio=0;
    current_tipa=0;
    logging=FALSE;

    /* Se il debug è attivo, abilita sempre il logging... */
    #ifdef TABBOZ_DEBUG
        logging = TRUE;
        openlog();
        sprintf(log_buf,"tabboz: Starting Tabboz Simulator %s %s",VERSION,__DATE__);
        writelog(log_buf);
    #endif
    
    firsttime=FALSE;

    #ifdef TABBOZ_WIN
        /* Parametro 'config' sulla linea di comando */
        //TAG2015 per ora commentiamo tutto sto pezzo ma è da controllare
        // if (_argc > 1)
        //     if ( !strcmp(_argv[1],"config") ) {
        //         hWndMain = 0; // Segnala che non esiste proc. principale.
        //         DialogBox(hInst,MAKEINTRESOURCE(CONFIGURATION),NULL,Configuration);
        //         FineProgramma("config");
        //         exit(0);
        //     }
        // if (intro_active)
        //     DialogBox(hInst,MAKEINTRESOURCE(LOGO),NULL,Logo);
        
        // /* Formattazione iniziale Tabbozzo */
        // if (firsttime == 1) {
        //     lpproc = MakeProcInstance(FormatTabboz, hInst);
        //     DialogBox(hInst, MAKEINTRESOURCE(15), hInst, lpproc);
        //     FreeProcInstance(lpproc);
        // }
    #endif
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
        firsttime=TRUE;

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

    TabbozProfilo.get("IntroActive",intro_active,-1);
    if (intro_active < 0) intro_active=1;

    TabbozProfilo.get("TimerActive",timer_active,-1);
    if (timer_active < 0) timer_active=0;

    TabbozProfilo.get("SoundActive",sound_active,-1);
    if (sound_active < 0) sound_active=1;

    TabbozProfilo.get("TemaGrafico",tema_grafico,"none",STR_MAX);
    Fl::scheme(tema_grafico);

    #ifndef TABBOZ_DEBUG
        TabbozProfilo.get("Logging",logging,FALSE);
        if(logging <= 0)
            logging=FALSE;
        else
            logging=TRUE;
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

//    ScooterProfilo.get("Antifurto",buf_i,0);
//    ScooterData.antifurto = new_check_i(buf_i);

    ScooterProfilo.get("Nome",ScooterData.nome,"Nessuno...",STR_MAX);

    /* carica dati cellulare */
    CellularProfilo.get("DualOnly",buf_i,-1);
    AbbonamentData.dualonly = new_check_i(buf_i);

    CellularProfilo.get("CreditoRest",buf_i,-1);
    AbbonamentData.creditorest = new_check_i(buf_i);

    CellularProfilo.get("NomeAbb",AbbonamentData.nome,0,STR_MAX);
    if(AbbonamentData.nome==0)  AbbonamentData.creditorest= -1;

    CellularProfilo.get("DualBand",buf_i,-1);
    CellularData.dual = new_check_i(buf_i);

    CellularProfilo.get("Stato",buf_i,-1);
    CellularData.stato = new_check_i(buf_i);

    CellularProfilo.get("Prezzo",buf_i,-1);
    CellularData.prezzo = new_check_i(buf_i);

    CellularProfilo.get("Nome",CellularData.nome,0,STR_MAX);
    if(CellularData.nome==0) CellularData.stato = -1;

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
    Giorno();

     // Guarda se qualche "bastardino" ha modificato dei valori nel registro...
    TabbozProfilo.get("SoftCheck",buf_i,0);
    if ((new_counter - buf_i) != 0) {
        if(!firsttime) {
            if(sound_active) TabbozPlaySound(1600);
            fl_message_title("Ma cazz...");
            fl_alert("Visto che ti sei divertito a pasticciare con il salvataggio,\ni parametri verranno resettati!");
        }
        ResetMe(0);
    }
}


/* Logga fine programma e salva tutto */
void FineProgramma(char const *caller)
{

    #ifdef TABBOZ_DEBUG
        sprintf(log_buf,"tabboz: FineProgramma chiamato da <%s>",caller);
        writelog(log_buf);
    #endif

    SalvaTutto();
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
    TabbozProfilo.set("IntroActive", intro_active);
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
//    ScooterProfilo.set("Antifurto",new_check_i(antifurto));
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


/* Ex Schermata About */
//FIXME l'unica cosa interessante è il cheat... nel tabboz originale si avvia cliccando 10
//FIXME volte sull'icona centrale quando il nome/cognome del tabbozzo corrispondono
//FIXME ai valori indicati sotto...
//    "Dino Lucci"
//        Soldi=Soldi+1000;
//        Reputazione=random(4);
//        Fama=random(40);
//    
//    "Giulio Lucci"
//        Soldi=Soldi+1000;
//        Reputazione=random(30);
//        Fama=random(5);
//
//    "Daniele Gazzarri"
//        ScooterData=ScooterMem[7];
//        benzina=850;
//        Reputazione=100;
//        
//    "Emanuele Caccialanza"
//        Soldi=Soldi+10000;
//        Fama=100;
//        
//    "Andrea Bonomi"
//        for (i=1;i<10;i++)
//          MaterieMem[i].voto=10;
//        CalcolaStudio();
//        if ( Rapporti > 1 )
//          Rapporti=100;
//        impegno=100;
//        numeroditta=1;
//        stipendio=5000;


/********************************************************************/
/* Logo...                                                          */
/********************************************************************/
//TAG2015 più che il logo è lo splash screen. Verrà implementata
//direttamente nella gui
// # pragma argsused

// BOOL FAR PASCAL Logo(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
// int    x,y,w,h;

//     if (message == WM_INITDIALOG) {

//     if (sound_active) TabbozPlaySound(0);

//     /* [[[ Posiziona il logo a centro dello schermo ]]] Veneedi' 17 Aprile 1998 */
//     /* GetWindowRect(hDlg, (LPRECT) &wrect);                                    */
//     /* w = wrect.right - wrect.left;                                            */
//     /* h = wrect.bottom - wrect.top;                        */

//     w = 522; /* dimensioni dell' immagine del logo */
//     h = 402;

//     x=GetSystemMetrics(SM_CXSCREEN);
//     y=GetSystemMetrics(SM_CYSCREEN);

//     x= (x - w) / 2;
//     y= (y - h) / 2;

//     MoveWindow(hDlg, x, y, w, h, 1);

//     if ( fase_di_avvio == 1)
//         SetTimer(hDlg, WM_TIMER, 10000, NULL);    /* 10 Secondi */

//     return(TRUE);
//     }

//     if (message == WM_TIMER) {
//     if ( fase_di_avvio == 1) {
//         KillTimer(hDlg, WM_TIMER);         /* Distrugge il timer... */
//         EndDialog(hDlg, TRUE);
//         }
//     }

//      if (message == WM_COMMAND) {
//     switch (LOWORD(wParam))
//     {
//          case IDOK:
//          case 202:
//          case 203:
//         if ( fase_di_avvio == 1) {
//             KillTimer(hDlg, WM_TIMER);
//             }
//         EndDialog(hDlg, TRUE);
//         return(TRUE);
//          default:
//         return(TRUE);
//     }
//      }

//      return(FALSE);
// }

/********************************************************************/
/* Spegnimi... 11 giugno 1998                                       */
/********************************************************************/
// //TAG2015 shutdown disabilitato, dubito sia portabile 'sta roba
// # pragma argsused
// BOOL FAR PASCAL Spegnimi(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
// int     x,y,w,h;
// static RECT   wrect;

//      if (message == WM_INITDIALOG) {
//         /* Centra la finestra... */
//         GetWindowRect(hDlg, (LPRECT) &wrect);
//         w = wrect.right - wrect.left;
//         h = wrect.bottom - wrect.top;

//         x=GetSystemMetrics(SM_CXSCREEN);
//         y=GetSystemMetrics(SM_CYSCREEN);

//         x= (x - w) / 2;
//         y= (y - h) / 2;

//         MoveWindow(hDlg, x, y, w, h, 1);
//         boolean_shutdown=1; // Uscita normale...

//         SendMessage(GetDlgItem(hDlg, 102), BM_SETCHECK, FALSE, 0L);
//         SendMessage(GetDlgItem(hDlg, 101), BM_SETCHECK, TRUE, 0L);
//         return(TRUE);

//     } else if (message == WM_COMMAND) {

//         switch (LOWORD(wParam)) {

//         case 101: // Un bug nella v 0.8.51pr impediva l' uscita corretta...
//             boolean_shutdown=1; // 1=uscita
//             return(TRUE);

//         case 102:
//             boolean_shutdown=2; // 2=shutdown
//             return(TRUE);

//         case 110:
//             MessageBox( hDlg,
//              "'Spegni il computer ed esci di casa'\n\nPubblicita' Progresso per il recupero dei giovani disadattati a causa dei computer sponsorizzata da Obscured Truckware.",
//              "Guida del Tabboz Simulator", MB_OK );
//             return(TRUE);

//         case IDOK:
// #ifdef TABBOZ32
//             SpegniISuoni();
// #endif
//             EndDialog(hDlg, TRUE);
//             return(TRUE);

//         case IDCANCEL:
//             boolean_shutdown=0; // non e' proprio un boolean, ma va bene lo stesso...
//             EndDialog(hDlg, TRUE);
//             return(TRUE);

//         default:
//             return(TRUE);
//         }
//      }

//      return(FALSE);
// }


//FIXME implementata in gui, manca il reset

/********************************************************************/
/* Configuration...                                                 */
/********************************************************************/
// # pragma argsused
// BOOL FAR PASCAL Configuration(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
//     FARPROC  lpproc;
// #ifdef TABBOZ_DEBUG
// static    int    temp_debug;
// #endif
//      if (message == WM_INITDIALOG) {
// #ifdef TABBOZ_DEBUG
//         temp_debug=debug_active;
// #endif

//         if (intro_active)
//             SendMessage(GetDlgItem(hDlg, 106), BM_SETCHECK, TRUE, 0L);
//         if (euro)
//             SendMessage(GetDlgItem(hDlg, 107), BM_SETCHECK, TRUE, 0L);
//         if (timer_active)
//             SendMessage(GetDlgItem(hDlg, 108), BM_SETCHECK, TRUE, 0L);

// #ifdef TABBOZ_DEBUG
//         if (debug_active)
//             SendMessage(GetDlgItem(hDlg, 109), BM_SETCHECK, TRUE, 0L);
// #endif

//         if (sound_active)
//             SendMessage(GetDlgItem(hDlg, 110), BM_SETCHECK, TRUE, 0L);

//         if ( Fortuna >= 20 ) SendMessage(GetDlgItem(hDlg, 101), BM_SETCHECK, TRUE, 0L); else
//         if ( Fortuna >= 15 ) SendMessage(GetDlgItem(hDlg, 102), BM_SETCHECK, TRUE, 0L); else
//         if ( Fortuna >= 10 ) SendMessage(GetDlgItem(hDlg, 103), BM_SETCHECK, TRUE, 0L); else
//         if ( Fortuna >=  5 ) SendMessage(GetDlgItem(hDlg, 104), BM_SETCHECK, TRUE, 0L); else
//         SendMessage(GetDlgItem(hDlg, 105), BM_SETCHECK, TRUE, 0L);

//         return(TRUE);
//     }
//     else if (message == WM_COMMAND)
//     {

//     switch (LOWORD(wParam))
//     {
//         case 101: Fortuna=20; return(TRUE);    /* Livelli di Difficolta' */
//         case 102: Fortuna=15; return(TRUE);
//         case 103: Fortuna=10; return(TRUE);
//         case 104: Fortuna= 5; return(TRUE);
//         case 105: Fortuna= 0; return(TRUE);
//         case 106:
//             intro_active=!intro_active;
//             return(TRUE);
//         case 107:
//             euro=!euro;
//             return(TRUE);
//         case 108:
//             timer_active=!timer_active;
//             return(TRUE);
// #ifdef TABBOZ_DEBUG
//         case 109:
//             debug_active=!debug_active;
//             return(TRUE);
// #endif
//         case 110:
//             sound_active=!sound_active;
//             return(TRUE);

//         case 203:    // Reset - 26 Marzo 1999
//             EndDialog(hDlg, TRUE);

//             // Se il tabboz e' chiamato con il parametro "config", hWndMain NON ESITE !
//             if (hWndMain != 0)
//                 ShowWindow(hWndMain, WIN_PICCOLO);

//             lpproc = MakeProcInstance(FormatTabboz, hInst);
//             DialogBox(hInst,
//                     MAKEINTRESOURCE(15),
//                     hDlg,
//                     lpproc);
//             FreeProcInstance(lpproc);

//             return(TRUE);

//         case IDOK:
//         case IDCANCEL:
// #ifdef TABBOZ_DEBUG
//             if (debug_active != temp_debug) {
//               if (debug_active) {
//                  openlog();
//                  writelog("tabboz: Start logging...");
//               } else {
//                  writelog("tabboz: Stop logging...");
//                  closelog();
//               }
//             }
// #endif
//             EndDialog(hDlg, TRUE);
//             return(TRUE);
//         default:
//             return(TRUE);
//     }
//      }

//      return(FALSE);
// }


//FIXME Schermata info tabbozzo, verrà implementata in futuro
//dato che non serve a nulla
/********************************************************************/
/* Personal Information...                                          */
/********************************************************************/
// # pragma argsused
// BOOL FAR PASCAL PersonalInfo(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
//      char          tmp[128];

//      if (message == WM_INITDIALOG) {
//         sprintf(tmp, " %d %s", comp_giorno,InfoMese[comp_mese-1].nome);
//         SetDlgItemText(hDlg, 103, tmp);            // Data di nascita
//         sprintf(tmp, "%d", (comp_giorno * 13 + comp_mese * 3 + 6070));
//         SetDlgItemText(hDlg, 104, tmp);            // Numero documento di nascita (inutile ma da' spessore...)

//         if (numeroditta < 1) {        // Professione
//             if (sesso == 'M')
//                 sprintf(tmp,"Studente");
//             else
//                 sprintf(tmp,"Studentessa");
//         } else
//             sprintf(tmp,"Sfruttat%c",ao);

//         SetDlgItemText(hDlg, 108, tmp);

//         sprintf(tmp,"Nat%c il", ao); SetDlgItemText(hDlg, 109, tmp); // Nata/o il
//         if (sesso == 'M') SetDlgItemText(hDlg, 110, "Celibe"); else SetDlgItemText(hDlg, 110, "Libera");

//         SetDlgItemText(hDlg, 111, Residenza);        // Residenza
//         SetFocus(GetDlgItem(hDlg, 111));

//         SetDlgItemText(hDlg, 107, Street);            // Indirizzo (inutile ma da' spessore...)
//         SetFocus(GetDlgItem(hDlg, 107));

//         SetDlgItemText(hDlg, 105, City);                // Citta' di nascita (inutile ma da' spessore...)
//         SetFocus(GetDlgItem(hDlg, 105));

//         SetDlgItemText(hDlg, 101, Cognome);            // Cognome
//         SetFocus(GetDlgItem(hDlg, 101));

//         SetDlgItemText(hDlg, QX_NOME, Nome);        // Nome
//         SetFocus(GetDlgItem(hDlg, QX_NOME));

//         return(TRUE);
//     }

//     else if (message == WM_COMMAND)
//     {

//       switch (LOWORD(wParam))
//       {
//          case 111:
//             GetDlgItemText(hDlg, wParam, Residenza, sizeof(Residenza));
//             break;

//          case 107:
//             GetDlgItemText(hDlg, wParam, Street, sizeof(Street));
//             break;

//          case 105:
//             GetDlgItemText(hDlg, wParam, City, sizeof(City));
//             break;

//          case 101:                  /* Cognome del tabbozzo */
//             GetDlgItemText(hDlg, wParam, Cognome, sizeof(Cognome));
//             break;

//          case QX_NOME:              /* Nome del tabbozzo */
//             GetDlgItemText(hDlg, wParam, Nome, sizeof(Nome));
//             break;

//          case IDOK:
//          case IDCANCEL:
//         EndDialog(hDlg, TRUE);
//         return(TRUE);

//          default:
//         return(TRUE);
//     }
//      }

//     return(FALSE);
// }


/* Routine che gestisce diverse situazioni quando i soldi sono < di quelli richiesti */
void nomoney(int tipo)
{
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
    
        case CELLULRABBONAM:
            fl_message_title("Non hai abbastanza soldi...");
            fl_alert("Forse non ti sei accorto di non avere abbastanza soldi, stronzett%c...",ao);
            if (Fama > 2)
                Fama-=1;
            break;
    }
}


#ifdef DEADCODE
//*******************************************************************
// Aggiorna la finestra principale
//*******************************************************************
void AggiornaPrincipale(HWND parent)
{
    char tmp[128];

    ShowWindow(parent, WIN_GRANDE);

    sprintf(tmp, "%s %s",Nome,Cognome);
    SetDlgItemText(parent, QX_NOME, tmp);

    SetDlgItemText(parent, QX_SOLDI, MostraSoldi(Soldi));

    sprintf(tmp, "%d/100", Fama);        // Figosita'
    SetDlgItemText(parent, 151, tmp);

    sprintf(tmp, "%d/100", Reputazione);    // Reputazione
    SetDlgItemText(parent, 152, tmp);

    sprintf(tmp, "%d/100", Studio);        // Profitto scolastico
    SetDlgItemText(parent, 153, tmp);

    if ( Rapporti != 0 ) {
        sprintf(tmp, "%s", Nometipa);    // Nometipa
        SetDlgItemText(parent, 155, tmp);
        sprintf(tmp, "%d/100", Rapporti);    // Rapporti con la tipa
        SetDlgItemText(parent, 154, tmp);
    } else {
        sprintf(tmp, " ");            // Nometipa
        SetDlgItemText(parent, 155, tmp);
        SetDlgItemText(parent, 154, tmp);
    }


    if (ScooterData.stato != -1) {
        sprintf(tmp, "%s", ScooterData.nome);
        SetDlgItemText(parent, 150, tmp);    // Nomescooter
        sprintf(tmp, "%d/100", ScooterData.stato);
        SetDlgItemText(parent, 156, tmp);    // Stato scooter
    } else {
        sprintf(tmp, " ");
        SetDlgItemText(parent, 150, tmp);    // Nomescooter
        SetDlgItemText(parent, 156, tmp);    // Stato scooter
    }

    SetDlgItemText(parent, 157, tmp);

    if ( sesso == 'M' )    {// Non usare la variabile "ao" xche' qui e' necessario
         DeleteMenu(GetMenu(parent), QX_TIPA, MF_BYCOMMAND);
         AppendMenu( GetSubMenu(GetMenu(parent),1), MF_STRING, QX_TIPA, "&Tipa...");
         SetDlgItemText(parent, 133, "Tipa"); // che ci sia scritto Tipa x il maschietto e
         SetDlgItemText(parent, 170, "Rapporto con la tipa");
    } else {                              //    Tipo x la femminuccia...
         DeleteMenu( GetMenu(parent), QX_TIPA, MF_BYCOMMAND);
         AppendMenu( GetSubMenu(GetMenu(parent),1), MF_STRING, QX_TIPA, "&Tipo...");
         SetDlgItemText(parent, 133, "Tipo");
         SetDlgItemText(parent, 170, "Rapporto con il tipo");
    }

}
#endif


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
    if(Rapporti) {
        main_txtbox_tipa->value(Nometipa);
        main_valbox_rapporti->value(Rapporti);
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


//*******************************************************************
// MainDlgBoxProc - handle Main dialog messages (modeless)
//
// This is a modeless dialog box procedure that controls this
// entire application.
//
// paramaters:
//             hDlg          - The window handle for this message
//             message       - The message number
//             wParam        - The WORD parmater for this message
//             lParam        - The LONG parmater for this message
//
//*******************************************************************
//TAG2015 questa è la mega-funzione che gestisce la finestra principale
//e spawna le altre. Non serve più ma va considerata per vedere quando
//fa i check logici e la gestione del tempo
// #pragma argsused

// #ifdef WIN32
// #pragma argsused
// BOOL CALLBACK _export TabbozWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// #else
// #pragma argsused
// BOOL FAR PASCAL TabbozWndProc(HWND hWnd, WORD message, WORD wParam, LONG lParam)
// #endif
// {
// static HICON      hIcon;
//          FARPROC  lpproc;

//     switch (message) {

//     case WM_ENDSESSION:
//          if (wParam)
//             FineProgramma("end session");
//          break;

//     case WM_QUERYDRAGICON:       // 25 Feb 1999 - Questa e' l' icona per ALT-TAB...
//          if (!hIcon)
//             hIcon = LoadIcon(hInst,MAKEINTRESOURCE(1));
//          return (long)hIcon;


//     case WM_DESTROY:
//          if (hIcon)
//             DestroyIcon(hIcon);
//          KillTimer(hWnd, WM_TIMER);
//          break;

//     case WM_SYSCOMMAND:
//          switch (LOWORD(wParam))
//          {
//          FARPROC lpproc;

//          case QX_ABOUT:
//              /* Display about box. */
//              lpproc = MakeProcInstance(About, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(ABOUT),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              return(TRUE);

//          case SC_CLOSE:

//             lpproc = MakeProcInstance(Spegnimi, hInst);
//             DialogBox(hInst,
//               MAKEINTRESOURCE(SPEGNIMI),
//               hWnd,
//               lpproc);
//             FreeProcInstance(lpproc);

//             if (boolean_shutdown != 0)
//                 EndDialog(hWnd,TRUE); // Chiudi la baracca...

//             return(TRUE);

//          }
//          return(FALSE);

//     case WM_INITDIALOG:
//          hIcon = LoadIcon(hInst,MAKEINTRESOURCE(1));
//          hWndMain = hWnd;
//          // Scrive quanti soldi ci sono... ( ed ora scrive anche molta altra roba...)
//          AggiornaPrincipale(hWnd);


// #ifndef NONETWORK
//          hModule = GetModuleHandle("WINSOCK.DLL");

//          NEThDlg=hWnd;

//          if (net_enable)
//         TabbozStartNet(NEThDlg);
// #endif

//          /* 11 Jun 98 - Modifika il menu' di sistema... */
//          AppendMenu(GetSystemMenu(hWnd, 0), MF_SEPARATOR, 0, 0);
//          AppendMenu(GetSystemMenu(hWnd, 0), MF_STRING, QX_ABOUT, "&About Tabboz Simulator...");

// //        AppendMenu( GetSubMenu(GetMenu(hWnd),1), MF_STRING, QX_ABOUT, "&Chiesa..."); // Aggiunge la chiesa ai negozi :-)))
// //        DeleteMenu(GetMenu(hWnd), QX_ABOUT, MF_BYCOMMAND); // Cancella l' about(per esempio...)
// //        EnableMenuItem(GetMenu(hWnd), QX_NETWORK, MF_GRAYED); // Disabilita un menu'

// #ifndef NONETWORK
// // Aggiunge la voce "Network..." al menu' "Special" - 04 Jan 1999
//          AppendMenu(GetSubMenu(GetMenu(hWnd),2), MF_SEPARATOR, 0, NULL);
//          AppendMenu(GetSubMenu(GetMenu(hWnd),2), MF_STRING, QX_NETWORK, "&Network...");
// #endif
// #ifdef PROMPT_ACTIVE
//          AppendMenu(GetSubMenu(GetMenu(hWnd),2), MF_SEPARATOR, 0, NULL);
//          AppendMenu(GetSubMenu(GetMenu(hWnd),2), MF_STRING, QX_PROMPT, "&Prompt...");
// #endif

//          DrawMenuBar(hWnd);


// /*        MessageBeep(0x0050); Crea un beep. Non e' necessario qui, ma e' solo x ricordarselo... */



//          /* Inizio implementazione timer: 9 giugno 1998 */
//          SetTimer(hWnd, WM_TIMER, 60000, NULL);     /* 60 secondi.. (il massimo e' 65534, 65 secondi...) */
//          t_random=6 + random(20);    /* 6 - 26 minuti tra un evento ed il seguente...*/
//          t_random=1;

//          fase_di_avvio=0;    /* 11 Giugno 1998 */
//          return TRUE;

//     case WM_TIMER :
//         if (timer_active == 1) {
//              /* Il timer viene contollato SOLO se la finestra e' ridotta ad ICONA */
//              if (IsIconic(hWndMain) != 0) {
//             if (t_random > 0) {
//                 /* Per un altro minuto siamo a posto... */
//                 t_random--;
//                 break;
//             }
//             t_random=12 + random(20);    /* 12 - 21 minuti tra un evento ed il seguente...*/
//             t_random=1;

//             KillTimer(hWnd, WM_TIMER);         /* Distrugge il timer... */
//             ShowWindow(hWndMain, SW_SHOWNORMAL); /* Ingrandisce la finestra */
//             Giorno(hWnd);

//             SetTimer(hWnd, WM_TIMER, 60000, NULL);     /* 60 secondi.. (il massimo e' 65534, 65 secondi...) */
//              }
//         }
//         return TRUE;

// #ifndef NONETWORK
//     case SOCKET_MESSAGE:
//         switch(WSAGETSELECTEVENT(lParam))
//         {

//              case FD_ACCEPT:
//              {
//             /* Get a pending accept */

//             clientSocket = accept(serverSocket,(LPSOCKADDR) &clientSockAddr, &addrLen);

//             /* Memorizza l' indirizzo dell' ultima connessione... */

//             sprintf(lastconnect,"%d.%d.%d.%d",
//                 clientSockAddr.sin_addr.s_net,clientSockAddr.sin_addr.s_host,
//                 clientSockAddr.sin_addr.s_lh,clientSockAddr.sin_addr.s_impno);


//             #ifdef TABBOZ_DEBUG
//             sprintf(tmp,"tabboz: Got a connection from %s",lastconnect);
//             writelog(tmp);
//             #endif

//             if (clientSocket == INVALID_SOCKET)
//             {
//                 #ifdef TABBOZ_DEBUG
//                 writelog("tabboz: ERROR: Unable to accept connection.");
//                 #endif
//                 break;
//             }

//             SendReceiveToClient((void *)clientSocket);

//             }
//         }
//         break;
// #endif

//     case WM_COMMAND:
//          switch (LOWORD(wParam))
//          {
//          case QX_LOAD:
//              OpenFileDlg(hWnd);
//              AggiornaPrincipale(hWnd);
//              break;

//          case QX_SAVE:
//              SaveFileDlg(hWnd);
//              AggiornaPrincipale(hWnd);
//              break;

//          case QX_CLOSE:

//             lpproc = MakeProcInstance(Spegnimi, hInst);
//             DialogBox(hInst,
//               MAKEINTRESOURCE(SPEGNIMI),
//               hWnd,
//               lpproc);
//             FreeProcInstance(lpproc);

//             if (boolean_shutdown != 0)
//                 EndDialog(hWnd,TRUE); // Chiudi la baracca...

//             return(TRUE);

//          case QX_ABOUT:
//              /* Display about box. */
//              lpproc = MakeProcInstance(About, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(ABOUT),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_LOGO:
//              lpproc = MakeProcInstance(Logo, hInst);
//              DialogBox(hInst,
//                   MAKEINTRESOURCE(LOGO),
//                     hWnd,
//                   lpproc);
//             FreeProcInstance(lpproc);

//             AggiornaPrincipale(hWnd);
//             break;
//         case QX_CONFIG:
//              /* Display configuration box. */
//              lpproc = MakeProcInstance(Configuration, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(CONFIGURATION),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
// //        case 251: /* Ex Immagine Tabbozzo */
//         case QX_INFO:
//              /* Display Personal Information box. */
//              lpproc = MakeProcInstance(PersonalInfo, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(PERSONALINFO),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_FAMIGLIA:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              /* Display Famiglia box. */
//              lpproc = MakeProcInstance(Famiglia, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(FAMIGLIA),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_DISCO:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              /* Display Disco box. */
//              lpproc = MakeProcInstance(Disco, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(DISCO),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_COMPAGNIA:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              /* Display Compagnia box. */
//              lpproc = MakeProcInstance(Compagnia, hInst);

//               DialogBox(hInst,
//                     MAKEINTRESOURCE(COMPAGNIA),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_SCUOLA:
//              if ( x_vacanza == 0 ) {
//                  ShowWindow(hWnd, WIN_PICCOLO);
//                  /* Display Scuola box. */
//                  lpproc = MakeProcInstance(Scuola, hInst);
//                   DialogBox(hInst,
//                         MAKEINTRESOURCE(SCUOLA),
//                         hWnd,
//                         lpproc);
//                  FreeProcInstance(lpproc);
//                  AggiornaPrincipale(hWnd);

//              } else {
//                  MessageBox( hWnd,
//                         "Non puoi andare a scuola in un giorno di vacanza !",
//                         "Scuola", MB_OK | MB_ICONINFORMATION);
//              }

//              break;
//         case QX_SCOOTER:
//              /* Display Scooter box. */
//              ShowWindow(hWnd, WIN_PICCOLO);

//              lpproc = MakeProcInstance(Scooter, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(SCOOTER),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_VESTITI:
//              /* Display Vestiti box. */
//              ShowWindow(hWnd, WIN_PICCOLO);

//              lpproc = MakeProcInstance(Vestiti, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(VESTITI),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_TABACCHI:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              RunTabacchi(hWnd);
//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_PALESTRA:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              RunPalestra(hWnd);
//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_CELLULAR:  // 31 Marzo 1999
//              ShowWindow(hWnd, WIN_PICCOLO);
//              lpproc = MakeProcInstance(Cellular, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(CELLULAR),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);
//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_VESTITI1:
//         case QX_VESTITI2:
//         case QX_VESTITI3:
//         case QX_VESTITI4:
//         case QX_VESTITI5:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              RunVestiti(hWnd, (wParam - QX_VESTITI1 + BAUHOUSE));
//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_TIPA:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              lpproc = MakeProcInstance(Tipa, hInst);
//              if (sesso == 'M')
//                  DialogBox(hInst,
//                         MAKEINTRESOURCE(TIPA),
//                         hWnd,
//                         lpproc);
//              else
//                  DialogBox(hInst,
//                         MAKEINTRESOURCE(190),
//                         hWnd,
//                         lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
//         case QX_LAVORO:
//              ShowWindow(hWnd, WIN_PICCOLO);
//              // Display Lavoro box.
//              lpproc = MakeProcInstance(Lavoro, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(LAVORO),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
// #ifdef PROMPT_ACTIVE
//         case QX_PROMPT:            /* Display Tabboz Simulator Prompt */
//              lpproc = MakeProcInstance(Prompt, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(PROMPT),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
// #endif
// #ifndef NONETWORK
//         case QX_NETWORK:    /* Tabboz Simulator Network Config/Stat */
//              lpproc = MakeProcInstance(Network, hInst);
//              DialogBox(hInst,
//                     MAKEINTRESOURCE(NETWORK),
//                     hWnd,
//                     lpproc);
//              FreeProcInstance(lpproc);

//              AggiornaPrincipale(hWnd);
//              break;
// #endif
//         default:
//              break;
//          }
//          break;

//      }

//      return FALSE;
// }


/* Calcola parametro "Studio" sommando i voti di tutte le materie
* moltiplicando x 10 e dividendo per n.ro materie */
void CalcolaStudio()
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


/* PROCEDURA PRINCIPALE */
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
            GUICartaID(TRUE);
            win_cartaid->position( (Fl::w() - win_cartaid->w() ) / 2, (Fl::h() - win_cartaid->h() ) / 2);   // centra finestra
            win_cartaid->show();
            fl_message_title("A new tabboz is born");
            fl_message("Benvenuto in Tabboz Simulator NG!\nIn questa finestra puoi personalizzare\nil personaggio (o accettare i valori di default...)");
            while(win_cartaid->shown()) Fl::wait();
            win_principale->show();
        }
        Fl::run();

        if(chiusura == NEWGAME) {   // nuova partita (resetta e ricomincia)
            #ifdef TABBOZ_DEBUG
                writelog("tabboz: new game (reset)");
            #endif
            ResetMe(0);
            firsttime = TRUE;
            chiusura = NOEXIT;
        }
    }
    while(chiusura != SAVEGAME);   // uscita normale (salva)

    FineProgramma("main"); // Salvataggio partita...
    #ifdef TABBOZ_DEBUG
        writelog("tabboz: standard exit (save & quit)");
    #endif

    closelog();
    return 0;
}


#ifdef DEADCODE
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