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

//#include <mmsystem.h> // Per sndPlaySound

#include "zarrosim.h"

#include "scuola.h"
#include "lavoro.h"

#include "calendario.h"
#include "proteggi.h"

#include "debug.h"

#ifdef TABBOZ_WIN
#ifndef NONETWORK
#include "net.h"
#endif
#endif

/* Header per toolkit FLTK */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Preferences.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>

/* Header finestre GUI */
#include "gui/GUITabboz.h"


//static char sccsid[] = "@(#)" __FILE__ " " VERSION " (Andrea Bonomi) " __DATE__;

static const char *dir_profilo = "TabbozNG";
static const char *file_profilo = "TabbozNG";
char              path_profilo[STR_MAX]="dummy.tbz";  // FIMXE Path e file dove salvare (per ora non usato)


//extern void     Atinom(HANDLE hInstance);  //visualizza messaggio extra in about

/*verifica se valore è compreso in intervallo corretto*/
extern int      vvc(int i);

//extern ATOM     RegisterBMPTipaClass(HANDLE hInst);
//extern ATOM     RegisterBMPViewClass(HANDLE hInst);
//extern void     OpenFileDlg(HWND hwnd);
//extern void     SaveFileDlg(HWND hwnd);
static void     SalvaTutto(void);
static void     CaricaTutto(void);

// void TabbozPlaySound(int number)
// void SpegniISuoni()

/* FIXME spostare al posto giusto dopo implementazione scooter */
NEWSTSCOOTER ScooterData;
/* FIXME spostare al posto giusto dopo implementazione cell */
STCEL CellularData;
STABB AbbonamentData;

/* PRIMA LE VARIABILI GENERIKE... */

int     cheat;
char    Andrea[14];
char    Caccia[21];
char    Daniele[17];
char    Obscured[29];
int     firsttime;
int     fase_di_avvio;
int     ImgSelector;
int     TabbozRedraw;

/* DOPO LE CARATTERISTIKE... */

int     Fama;
int     Reputazione;
int     Studio;
int     Soldi;
int     Paghetta;
char    Nome[30];
char    Cognome[30];
int     comp_giorno;
int     comp_mese;
char    Nometipa[30];
char    City[50];       // Citta' di nascita
char    Residenza[50];  // Citta' dove vive
char    Street[50];     // Dove sto' tipo abita
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
int     current_gibbotto;
int     current_pantaloni;
int     current_scarpe;
int     current_tipa;
int     sizze;


/* Opzioni */

int     euro;
int     timer_active;       // Abilita il timer
int     sound_active;
int     intro_active;       // Visualizza schermata introduttiva


#ifdef DEADCODE
    HANDLE    hInst;                    // hInstance dell'applicazione
    HWND      hWndMain;                 // hWnd della finestra principale
    // #define WIN_PICCOLO SW_MINIMIZE
    // #define WIN_PICCOLO SW_SHOWMINIMIZED
    #define WIN_PICCOLO SW_HIDE
    #define WIN_GRANDE  SW_SHOWNORMAL
#endif

#ifndef NONETWORK
    extern  WSADATA      Data;
    extern  SOCKADDR_IN  serverSockAddr;
    extern  SOCKADDR_IN  clientSockAddr;
    extern  SOCKET       serverSocket;
    extern  SOCKET       clientSocket;
    extern  int          PortNumber;
    HANDLE  hModule;
#endif

static  int  t_random;              // Attesa a random tra i vari eventi timer

static  char boolean_shutdown;


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
void ResetMe(int primavolta)
{
    int   i;

    TabbozRedraw      =    1;
    Soldi             =   10;
    Paghetta          =   30;
    Reputazione       =    0;
    Fama              =    0;
    Rapporti          =    0;
    Stato             =  100;
    impegno           =    0;
    giorni_di_lavoro  =    0;
    numeroditta       =    0;
    AttesaSoldi       =  ATTESAMAX;

    strcpy(Residenza,"Milano");
    Nometipa[0]=0;

//FIXME Carica random di città/via dalla lista stringhe
//   LoadString(hInst, (400 + random(22) ), City, (sizeof(City)-1));
//    LoadString(hInst, (450 + random(50) ), tmp, (sizeof(tmp)-1));
//    sprintf(Street,"%s n. %d",tmp,(1 + random(150)));

    for (i=1;i<10;i++)
        MaterieMem[i].voto=2;   //BUGFIX partiamo dalla media del 2

    CalcolaStudio();

    #ifndef TAG2015_NOTEMPO
    x_mese         =  9;
    x_giorno       = 30;
    x_giornoset    =  1;
    x_anno_bisesto =  0;
    x_vacanza      =  0;
    #endif

    comp_mese      = rand() % 12 + 1;
    comp_giorno    = rand() % InfoMese[comp_mese-1].num_giorni + 1;


    if (primavolta) { // Se e' la prima volta che uso il tabboz resetta anche la configurazione...
        intro_active        =  1;
        timer_active        =  1;
        sound_active        =  1;
        euro                =  0;
        sesso               = 'M';
        strcpy(Nome,"Tizio");
        strcpy(Cognome,"Caio");
        CalcolaSesso();
    }

    if (sesso == 'F') {
        strcpy(Nome,"Nessuna");
        strcpy(Cognome,"In Particolare");
    }

    sizze             =  0;
    current_testa     =  0;
    current_gibbotto  =  0;
    current_pantaloni =  0;
    current_scarpe    =  0;

    #ifndef NONETWORK
        net_enable =  1;
        PortNumber = 79;
    #endif

    #ifndef TAG2015_NOSCOOTER
        ScooterData.stato    = -1;  
    #endif
    #ifndef TAG2015_NOCELL
        AbbonamentData.creditorest = -1;
        CellularData.stato         = -1;
    #endif
}

//*******************************************************************
// Formattazione iniziale Tabbozzo (scelta sesso, nome...) 14-01-2000
//*******************************************************************
//TAG2015 Questa routine non fa molto si può implementare in gui
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

//*******************************************************************
// InitTabboz
//*******************************************************************

static void InitTabboz(void)
{
    char tmp[128];
    
    // #ifdef TABBOZ_WIN
    //     FARPROC        lpproc;

    // // Init della liberia grafica...
    // BWCCRegister(hInst); // Fanculo ! Mi sono magiato il fegato prima di trovare
    // // questa funzione ! non c'e' nessuno documento fottuto che mi abbia aiutato !

    // #endif

    path_profilo[0]=0;
    Fl_Preferences TabbozProfilo(Fl_Preferences::USER, dir_profilo, file_profilo);  //apre file configurazione/salvataggio

    // Inizializzazione dei numeri casuali...
    srand(time(NULL));

    // Inizializza un po' di variabile...
    boolean_shutdown=0;               /* 0=resta dentro, 1=uscita, 2=shutdown */

    Fortuna=0;                        /* Uguale a me...               */
    #ifndef TAG2015_NOSCOOTER
        ScooterData=ScooterMem[0];        /* nessuno scooter              */
    #endif
    AttesaSoldi=ATTESAMAX;                 /* attesa per avere soldi...    */
    ImgSelector=0;                    /* W l' arte di arrangiarsi...  */
    timer_active=1;
    fase_di_avvio=1;
    tempo_pestaggio=0;
    current_tipa=0;

    #ifndef NONETWORK
        Data.wVersion=0;
    #endif

    if (LOGGING) {
        openlog();
        sprintf(tmp,"tabboz: Starting Tabboz Simulator %s %s",VERSION,__DATE__);
        writelog(tmp);
    }
    

    #ifdef TABBOZ_WIN
        // Ottieni i nomi dei creatori di sto coso...
        //LoadString(hInst, 10, Andrea,   sizeof(Andrea));
        //LoadString(hInst, 11, Caccia,   sizeof(Caccia));
        //LoadString(hInst, 12, Daniele,  sizeof(Daniele));
        //LoadString(hInst,  2, Obscured, sizeof(Obscured));

        // Registra la Classe BMPView - E' giusto metterlo qui ???
        //RegisterBMPViewClass(hInst);

        //Registra la Classe BMPTipa
        //RegisterBMPTipaClass(hInst);

        #ifndef NONETWORK
            /* Azzera l' ultima connessione dalla rete */
            sprintf(lastconnect,"none (Server is Down !)");
            sprintf(lastneterror,"Network Server is Down");
        #endif
    #endif

    firsttime=0;
    CaricaTutto();
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


//*******************************************************************
//  Carica le caratteristiche dal registro o da un file...
//*******************************************************************

static void CaricaTutto(void)
{
    int  i;

    int    buf_i;            //buffer int
    char   buf_s[STR_MAX];   //buffer *char

    Fl_Preferences TabbozProfilo(Fl_Preferences::USER, dir_profilo, file_profilo);  //apre file configurazione/salvataggio

    /* Prima che vengano caricate le informazioni... */
    /* azzera il checksum...                         */
    new_reset_check();

    /* Cerca le informazioni registrate */
    /* Fl_prefs supporta i tipi, le conversioni da stringa non servono più */

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

    TabbozProfilo.get("Nome",Nome,"",STR_MAX);
    TabbozProfilo.get("Cognome",Cognome,"",STR_MAX);
    TabbozProfilo.get("Nometipa",Nometipa,"",STR_MAX);
    TabbozProfilo.get("City",City,"",STR_MAX);
    //if(City[0] == '\0')
    //    firsttime=1;

    TabbozProfilo.get("Residenza",Residenza,"",STR_MAX);   //TAG2015 FIXME temporaneo usiamo residenza per controllo fistrun
    if(Residenza[0] == '\0')
        firsttime=1;

    TabbozProfilo.get("Street",Street,"",STR_MAX);

    // la serie di 9 "C" messe nella riga sotto NON E' CASUALE
    // non sostituirla con altre lettere !

    TabbozProfilo.get("Materie",buf_s,"",STR_MAX);
    if(buf_s[0]=='\0')  sprintf(buf_s,"CCCCCCCCC");      //BUGFIX partiamo dalla media del 2... 0 è esagerato
    for (i=1;i<10;i++) {
        MaterieMem[i].voto=buf_s[i-1] - 65;
        if ((MaterieMem[i].voto < 2) || (MaterieMem[i].voto > 10)) MaterieMem[i].voto=2;
    }
    CalcolaStudio();

    TabbozProfilo.get("Fortuna",buf_i,0);
    Fortuna=vvc(new_check_i(buf_i));

    TabbozProfilo.get("AttesaSoldi",buf_i,ATTESAMAX);
    AttesaSoldi=vvc(new_check_i(buf_i));

    /* Se non e' gia' settato,setta il compleanno (a caso) */
    TabbozProfilo.get("CompMese",comp_mese,0);
    if (comp_mese < 1) comp_mese=rand() % 12 + 1;
    TabbozProfilo.get("CompGiorno",comp_giorno,0);
    if (comp_giorno < 1) comp_giorno=rand() % InfoMese[comp_mese-1].num_giorni + 1;

#ifndef TAG2015_NOTEMPO
    // Se e' la prima volta che parte il Tabboz Simulator, la data e' impostata al 30 Settembre
    TabbozProfilo.get("Mese",x_mese,0);
    if (x_mese < 1) x_mese=9;
    
    TabbozProfilo.get("Giorno",x_giorno,0);
    if (x_giorno < 1) x_giorno=30;

    TabbozProfilo.get("GiornoSet",x_giornoset,0);
    if (x_giornoset < 1) x_giornoset=1;
    
    TabbozProfilo.get("AnnoBisestile",x_anno_bisesto,4);
    if ( (x_anno_bisesto > 3) || (x_anno_bisesto < 0) ) x_anno_bisesto=3;

    TabbozProfilo.get("ScadPalGiorno",buf_i,0);
    scad_pal_giorno = vvc(buf_i);

    TabbozProfilo.get("ScadPalMese",buf_i,0);
    scad_pal_mese = vvc(buf_i);
#endif

    TabbozProfilo.get("NumeroDitta",buf_i,0);
    numeroditta = vvc(buf_i);

    TabbozProfilo.get("Impegno",buf_i,0);
    impegno = vvc(new_check_i(buf_i));

    TabbozProfilo.get("GiorniDiLavoro",buf_i,0);
    giorni_di_lavoro = vvc(new_check_i(buf_i));
    
    TabbozProfilo.get("Stipendio",buf_i,0);
    stipendio = new_check_i(buf_i);
    if (stipendio < 0) stipendio=0;

    TabbozProfilo.get("Sigarette",buf_i,0);
    sizze = new_check_i(buf_i);
    if (sizze < 0) sizze=0;

    TabbozProfilo.get("Testa",buf_i,0);
    current_testa = vvc(new_check_i(buf_i));

    TabbozProfilo.get("Giubbotto",buf_i,0);
    current_gibbotto = vvc(new_check_i(buf_i));

    TabbozProfilo.get("Pantaloni",buf_i,0);
    current_pantaloni = vvc(new_check_i(buf_i));

    TabbozProfilo.get("Scarpe",buf_i,0);
    current_scarpe = vvc(new_check_i(buf_i));

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
    if (timer_active < 0) timer_active=1;

    TabbozProfilo.get("SoundActive",sound_active,-1);
    if (sound_active < 0) sound_active=1;

    #ifndef NONETWORK
        net_enable   = atoi (RRKey("NetEnable"));
        if (net_enable < 0) net_enable=1;
        PortNumber   = atoi (RRKey("NetPort"));
        if (PortNumber < 1) PortNumber=79;
    #endif

#ifndef TAG2015_NOSCOOTER
    ScooterData.speed = new_check_i(atoi (RRKey("Scooter\\Speed")));
    if (ScooterData.speed < 0) ScooterData.speed=0;

    ScooterData.marmitta = new_check_i(atoi (RRKey("Scooter\\Marmitta")));
    if (ScooterData.marmitta < 0) ScooterData.marmitta=0;
    
    ScooterData.carburatore = new_check_i(atoi (RRKey("Scooter\\Carburatore")));
    if (ScooterData.carburatore < 0) ScooterData.carburatore=0;
    
    ScooterData.cc = new_check_i(atoi (RRKey("Scooter\\CC")));
    if (ScooterData.cc < 0) ScooterData.cc=0;
    
    ScooterData.filtro = new_check_i(atoi (RRKey("Scooter\\Filtro")));
    if (ScooterData.filtro < 0) ScooterData.filtro=0;
    
    ScooterData.prezzo = new_check_i(atoi(RRKey("Scooter\\Prezzo")));
    if (ScooterData.prezzo < 0) ScooterData.prezzo=0;
    
    ScooterData.attivita = new_check_i(atoi(RRKey("Scooter\\Attivita")));
    if (ScooterData.attivita < 0) ScooterData.attivita=0;

    ScooterData.stato = new_check_i(atoi(RRKey("Scooter\\Stato")));  // -1 = nessuno

    benzina = new_check_i(atoi(RRKey("Scooter\\Benzina")));
    if (benzina < 0) benzina=0;

//    antifurto = atoi (RRKey("Scooter\\Antifurto") );

    if (TabbozReadKey("Scooter\\Nome",ScooterData.nome) == 0) sprintf(ScooterData.nome,"nessuno");
#endif
#ifndef TAG2015_NOCELL
    /* Cellulare */
    AbbonamentData.dualonly    = new_check_i(atoi (RRKey("Cellular\\DualOnly")));
    AbbonamentData.creditorest = new_check_i(atoi (RRKey("Cellular\\CreditoRest")));
    if (TabbozReadKey("Cellular\\NomeAbb",AbbonamentData.nome) == 0) AbbonamentData.creditorest= -1;

    CellularData.dual   = new_check_i(atoi (RRKey("Cellular\\DualBand")));
    CellularData.stato  = new_check_i(atoi (RRKey("Cellular\\Stato")));
    CellularData.prezzo = new_check_i(atoi (RRKey("Cellular\\Prezzo")));
    
    if (TabbozReadKey("Cellular\\Nome",CellularData.nome) == 0) CellularData.stato = -1;
#endif

    #ifdef TABBOZ_DEBUG
        sprintf(buf_s,"tabboz: (R) new_counter %d", new_counter);
        writelog(buf_s);
        TabbozProfilo.get("SoftCheck",buf_i,0);
        sprintf(buf_s,"tabboz: (R) read_counter %d", buf_i );
        writelog(buf_s);
        if(firsttime)
            writelog("firsttime=1, first run or empty savefile");
    #endif

    if (firsttime)
        ResetMe(1);

#ifndef TAG2015_NOTEMPO
    /* Controllo eventuali errori nella data (o data non settata...) */
    /* FIXME si potrebbe implementare in vvc, magari overloadato */
    if ( (x_giorno < 1) || (x_giorno > 31) )  x_giorno=1;
    if ( (x_mese < 1) || (x_mese > 12) )  x_mese=1;
    if ( (x_giornoset < 1) || (x_giornoset > 7) )  x_giornoset=1;

    x_giorno--;  //Per evitare che avanzi di giorno ogni volta che si apre il programma
    x_giornoset--;
    AttesaSoldi++;  //Idem ma al contrario, per evitare che scenda ad ogni avvio
    Giorno();
#endif

    // Guarda se qualche "bastardino" ha modificato dei valori nel registro...
    TabbozProfilo.get("SoftCheck",buf_i,0);
    if ((new_counter - buf_i) != 0) {
        if(!firsttime)
            fl_alert("Visto che ti sei divertito a pasticciare con il salvataggio,\ni parametri verranno resettati!");
        ResetMe(0);
    }
}


//*******************************************************************
//      Fine Programma
//*******************************************************************
void FineProgramma(char const *caller)
{
    char tmp[128];
    Fl_Preferences TabbozProfilo(Fl_Preferences::USER, dir_profilo, file_profilo);  //apre file configurazione/salvataggio

    if(LOGGING) {
        sprintf(tmp,"tabboz: FineProgramma chiamato da <%s>",caller);
        writelog(tmp);
    }

    #ifndef NONETWORK
        if (net_enable == 1) {
            WSACleanup();
            #ifdef TABBOZ_DEBUG
                writelog("tabboz: WSACleanup()");
            #endif
            }
    #endif

    if (path_profilo[0] == 0) {
        /* Salva lo stato del tabbozzo */
        /* 0.8.1pr 29 Novembre 1998 Ora non salva piu' nel WIN.INI con WriteProfileString,
        ma salva nel registro di configurazione... */
        //TabbozProfilo.set("Exe", _argv[0]);  FIXME a che serve salvare la commandline?

    }

    SalvaTutto();
}

//*******************************************************************
//      Salva le caratteristiche nel registro o su di un file
//*******************************************************************

static void SalvaTutto(void) {
    
    char tmp[STR_MAX];
    
    Fl_Preferences TabbozProfilo(Fl_Preferences::USER, dir_profilo, file_profilo);  //apre file configurazione/salvataggio

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
    TabbozProfilo.set("Residenza", Residenza);
    TabbozProfilo.set("Street", Street);
    TabbozProfilo.set("CompMese", comp_mese);
    TabbozProfilo.set("CompGiorno", comp_giorno);

#ifndef TAG2015_NOTEMPO
    TabbozProfilo.set("Mese", x_mese);
    TabbozProfilo.set("Giorno", x_giorno);
    TabbozProfilo.set("GiornoSet", x_giornoset);
    TabbozProfilo.set("AnnoBisestile",x_anno_bisesto);
    TabbozProfilo.set("ScadPalGiorno", scad_pal_giorno);
    TabbozProfilo.set("ScadPalMese", scad_pal_mese);
#endif

    /* salva dati lavoro */
    TabbozProfilo.set("NumeroDitta", numeroditta);
    TabbozProfilo.set("Impegno", new_check_i(impegno));
    TabbozProfilo.set("GiorniDiLavoro", new_check_i(giorni_di_lavoro));
    TabbozProfilo.set("Stipendio", new_check_i(stipendio));

    /* salva dati accessori */
    TabbozProfilo.set("Sigarette", new_check_i(sizze));
    TabbozProfilo.set("Testa", new_check_i(current_testa));
    TabbozProfilo.set("Giubbotto", new_check_i(current_gibbotto));
    TabbozProfilo.set("Pantaloni", new_check_i(current_pantaloni));
    TabbozProfilo.set("Scarpe", new_check_i(current_scarpe));

    /* salva opzioni */
    TabbozProfilo.set("Euro", euro);
    TabbozProfilo.set("IntroActive", intro_active);
    TabbozProfilo.set("TimerActive", timer_active);
    TabbozProfilo.set("SoundActive", sound_active);

#ifndef NOTABBOZZA
    TabbozProfilo.set("Sesso", sesso);
#endif

#ifndef NONETWORK
    sprintf(tmp,"%d",net_enable);
    TabbozAddKey("NetEnable", tmp);
    sprintf(tmp,"%d",PortNumber);
    TabbozAddKey("NetPort", tmp);
#endif

#ifndef TAG2015_NOSCOOTER
    /* salva dati scooter */
    sprintf(tmp,"%d",new_check_i(ScooterData.speed));
    TabbozAddKey("Scooter\\Speed", tmp);
    sprintf(tmp,"%d",new_check_i(ScooterData.marmitta));
    TabbozAddKey("Scooter\\Marmitta", tmp);
    sprintf(tmp,"%d",new_check_i(ScooterData.carburatore));
    TabbozAddKey("Scooter\\Carburatore", tmp);
    sprintf(tmp,"%d",new_check_i(ScooterData.cc));
    TabbozAddKey("Scooter\\CC", tmp);
    sprintf(tmp,"%d",new_check_i(ScooterData.filtro));
    TabbozAddKey("Scooter\\Filtro", tmp);
    sprintf(tmp,"%d",new_check_i(ScooterData.prezzo));
    TabbozAddKey("Scooter\\Prezzo", tmp);
    sprintf(tmp,"%d",new_check_i(ScooterData.attivita));
    TabbozAddKey("Scooter\\Attivita", tmp);

    sprintf(tmp,"%d",new_check_i(ScooterData.stato));
    TabbozAddKey("Scooter\\Stato", tmp);

    sprintf(tmp,"%d",new_check_i(benzina));
    TabbozAddKey("Scooter\\Benzina", tmp);

//    sprintf(tmp,"%d",antifurto);
//    TabbozAddKey("Scooter\\Antifurto", tmp);

    TabbozAddKey("Scooter\\Nome", ScooterData.nome);
#endif

#ifndef TAG2015_NOCELL
    /* salva dati cellulare */
    sprintf(tmp,"%d",new_check_i(AbbonamentData.dualonly));
    TabbozAddKey("Cellular\\DualOnly",tmp);
    sprintf(tmp,"%d",new_check_i(AbbonamentData.creditorest));
    TabbozAddKey("Cellular\\CreditoRest",tmp);

    TabbozAddKey("Cellular\\NomeAbb",AbbonamentData.nome);

    sprintf(tmp,"%d",new_check_i(CellularData.dual));
    TabbozAddKey("Cellular\\DualBand",tmp);
    sprintf(tmp,"%d",new_check_i(CellularData.stato));
    TabbozAddKey("Cellular\\Stato",tmp);
    sprintf(tmp,"%d",new_check_i(CellularData.prezzo));
    TabbozAddKey("Cellular\\Prezzo",tmp);

    TabbozAddKey("Cellular\\Nome",CellularData.nome);
#endif

    TabbozProfilo.set("SoftCheck", new_counter);
    TabbozProfilo.set("Version", VERSION);

#ifdef TABBOZ_DEBUG
    sprintf(tmp,"tabboz: (W) new_counter %d", new_counter);
    writelog(tmp);
#endif

}



/********************************************************************/
/* About...                                                         */
/********************************************************************/
//TAG2015 Schermata about, interessante per la questione cheat ma
//ovviamente per ora non vitale
// # pragma argsused
// BOOL FAR PASCAL About(HWND hDlg, WORD message, WORD wParam, LONG lParam)
// {
//      char          buf[128];
//      char          tmp[128];
//      int                  i;

//      if (message == WM_INITDIALOG) {
//         sprintf(tmp, "%s", Andrea);
//         SetDlgItemText(hDlg, 110, tmp);
//         sprintf(tmp, "%s", Caccia);
//         SetDlgItemText(hDlg, 111, tmp);
//         sprintf(tmp, "%s", Daniele);
//         SetDlgItemText(hDlg, 112, tmp);

//         sprintf(tmp, "%s, %s", VERSION,__DATE__);
//         SetDlgItemText(hDlg, 115, tmp);

//         sprintf(tmp, "%s", Obscured);    /* Obscured Truckware (se il nome e' diverso, crash ! ) */
//         SetDlgItemText(hDlg, 116, tmp);

//         cheat = 0;
//         return(TRUE);


//     } else if (message == WM_COMMAND) {
//     switch (LOWORD(wParam))
//     {
//        case IDOK:
//           EndDialog(hDlg, TRUE);
//           return(TRUE);
//         case IDCANCEL:
//           EndDialog(hDlg, TRUE);
//           return(TRUE);

//         case 203:
//         case 113:
//         //  Atinom(hDlg);
//           return(TRUE);

//         case 257:
//           cheat=cheat+1;
//           if (cheat >= 10) { /* Lunedi' 13 Aprile 1998 - Ora il trukko viene un attimo modificato... */

//             sprintf(buf,"%s %s",Nome,Cognome);

//             LoadString(hInst, 13, tmp, sizeof(tmp));  /* Dino... */
//             if (! strcmp(tmp,buf)) {
//                 Soldi=Soldi+1000;
//                 Reputazione=random(4);
//                 Fama=random(40);
//             }

//             LoadString(hInst, 14, tmp, sizeof(tmp));  /* Fratello di Dino... */
//             if (! strcmp(tmp,buf)) {
//                 Soldi=Soldi+1000;
//                 Reputazione=random(30);
//                 Fama=random(5);
//             }

//             if (! strcmp(Daniele,buf)) {    /* Murdock, ti regala una macchinina... */
//                 ScooterData=ScooterMem[7];
//                 benzina=850;
//                 Reputazione=100;
//             }

//             if (! strcmp(Caccia,buf)) {    /* Caccia fa' aumentare i dindi... */
//                 Soldi=Soldi+10000;
//                 Fama=100;
//             }


//             if (! strcmp(Andrea,buf)) {    /* Io porto la scuola e la tipa al 100% */
//                 for (i=1;i<10;i++)
//                     MaterieMem[i].voto=10;
//                 CalcolaStudio();
//                 if ( Rapporti > 1 )
//                     Rapporti=100;
//                 impegno=100;
//                 numeroditta=1;
//             stipendio=5000;
//             }


//             cheat = 0;
//             }
//         default:
//         return(TRUE);
//     }
//     }

//      return(FALSE);
// }

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



/********************************************************************/
/* Configuration...                                                 */
/********************************************************************/
// //Schermata config con impostazione difficoltà, etc. In futuro
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


/********************************************************************/
/* Personal Information...                                          */
/********************************************************************/
//TAG2015 Schermata info tabbozzo, verrà implementata in futuro
//dato che non serve a nulla
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


/********************************************************************/
/* Warning...                                                       */
/* 12 Maggio 1998 - Questa funzione non e' piu' usata da anni...    */
/********************************************************************/

#ifdef DEADCODE
# pragma argsused

/*    PortTool v2.2     4/8/1999    14:40          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
BOOL FAR PASCAL Warning(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
    char          buf[128];


    if (message == WM_INITDIALOG)
    return(TRUE);


/*    PortTool v2.2     4/8/1999    14:40          */
/*      Found   : WM_COMMAND          */
/*      Issue   : wParam/lParam repacking, refer to tech. ref. for details          */
     else if (message == WM_COMMAND)
     {

/*    PortTool v2.2     4/8/1999    14:40          */
/*      Found   : LOWORD          */
/*      Issue   : Check if LOWORD target is 16- or 32-bit          */
    switch (LOWORD(wParam))
    {
        case IDOK:
        EndDialog(hDlg, TRUE);
        return(TRUE);

         default:
        return(TRUE);
    }
    }

     return(FALSE);
}
#endif




/* Routine che gestisce diverse situazioni quando i soldi sono < di quelli richiesti */
void nomoney(int tipo)
{
    switch (tipo) {
        
        case DISCO:
//        sprintf(tmp,"Appena entrat%c ti accorgi di non avere abbastanza soldi per pagare il biglietto.\nUn energumeno buttafuori ti deposita gentilmente in un cassonetto della spazzatura poco distante dalla discoteca.",ao);
            fl_message_title("Bella figura");
            fl_alert("Appena entrat%c ti accorgi di non avere abbastanza soldi per pagare il biglietto.\nUn energumeno buttafuori ti deposita gentilmente in un cassonetto della spazzatura poco distante dalla discoteca.",ao);
            if (Reputazione > 3 )
                Reputazione--;
            break;;
        
        case VESTITI:
            fl_message_title("Bella figura");
            fl_alert("Con cosa avresti intenzione di pagare, stronzett%c ??? Caramelle ???",ao);
            if (Fama > 12 )
                Fama-=3;
            if (Reputazione > 4 )
                Reputazione-=2;
            break;;

        case PALESTRA:
            if (sesso == 'M') {
                fl_message_title("Non hai abbastanza soldi...");
                fl_alert("L'enorme istruttore di bodybulding ultra-palestrato ti suona come una zampogna e ti scaraventa fuori dalla palestra.");
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
                fl_alert("L'enorme meccanico ti affera con una sola mano, ti riempe di pugni, e non esita a scaraventare te ed il tuo motorino fuori dall'officina.");
                if (Reputazione > 7 )
                    Reputazione-=5;
                #ifndef TAG2015_NOSCOOTER
                if (ScooterData.stato > 7 )
                    ScooterData.stato-=5;
                #endif
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
            fl_alert("Fai fuori dal mio locale, brut%c pezzente! Esclama il tabaccaio con un AK 47 in mano...",ao);
        //sprintf(tmp,"Fai fuori dal mio locale, brut%c pezzente !, esclama il tabaccaio con un AK 47 in mano...",ao);
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

//*******************************************************************
// Aggiorna la finestra principale
//*******************************************************************
// void AggiornaPrincipale(HWND parent)
// {
// char tmp[128];

//      ShowWindow(parent, WIN_GRANDE);

//      sprintf(tmp, "%s %s",Nome,Cognome);
//      SetDlgItemText(parent, QX_NOME, tmp);

//      SetDlgItemText(parent, QX_SOLDI, MostraSoldi(Soldi));

//      sprintf(tmp, "%d/100", Fama);        // Figosita'
//      SetDlgItemText(parent, 151, tmp);

//      sprintf(tmp, "%d/100", Reputazione);    // Reputazione
//      SetDlgItemText(parent, 152, tmp);

//      sprintf(tmp, "%d/100", Studio);        // Profitto scolastico
//      SetDlgItemText(parent, 153, tmp);

//      if ( Rapporti != 0 ) {
//          sprintf(tmp, "%s", Nometipa);    // Nometipa
//          SetDlgItemText(parent, 155, tmp);
//          sprintf(tmp, "%d/100", Rapporti);    // Rapporti con la tipa
//          SetDlgItemText(parent, 154, tmp);
//      } else {
//          sprintf(tmp, " ");            // Nometipa
//          SetDlgItemText(parent, 155, tmp);
//          SetDlgItemText(parent, 154, tmp);
//      }


//      if (ScooterData.stato != -1) {
//         sprintf(tmp, "%s", ScooterData.nome);
//         SetDlgItemText(parent, 150, tmp);    // Nomescooter
//         sprintf(tmp, "%d/100", ScooterData.stato);
//         SetDlgItemText(parent, 156, tmp);    // Stato scooter
//      } else {
//         sprintf(tmp, " ");
//         SetDlgItemText(parent, 150, tmp);    // Nomescooter
//         SetDlgItemText(parent, 156, tmp);    // Stato scooter
//      }

//      SetDlgItemText(parent, 157, tmp);

//      if ( sesso == 'M' )    {// Non usare la variabile "ao" xche' qui e' necessario
//          DeleteMenu(GetMenu(parent), QX_TIPA, MF_BYCOMMAND);
//          AppendMenu( GetSubMenu(GetMenu(parent),1), MF_STRING, QX_TIPA, "&Tipa...");
//          SetDlgItemText(parent, 133, "Tipa"); // che ci sia scritto Tipa x il maschietto e
//          SetDlgItemText(parent, 170, "Rapporto con la tipa");
//      } else {                              //    Tipo x la femminuccia...
//          DeleteMenu( GetMenu(parent), QX_TIPA, MF_BYCOMMAND);
//          AppendMenu( GetSubMenu(GetMenu(parent),1), MF_STRING, QX_TIPA, "&Tipo...");
//          SetDlgItemText(parent, 133, "Tipo");
//          SetDlgItemText(parent, 170, "Rapporto con il tipo");
//      }

// }

/* Aggiorna Finestra Principale*/
void AggiornaPrincipale()
{
    char tmp[128];
     
//FIXME Nome e cognome, le variazioni per M o F, scooter

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
    main_valbox_soldi->value(CALCSOLDI(Soldi));
    main_valbox_paghetta->value(CALCSOLDI(Paghetta));
    main_valbox_stipendio->value(CALCSOLDI(stipendio));
    if(stipendio)
        main_valbox_stipendio->activate();
    else
        main_valbox_stipendio->deactivate();
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


/* Calcola Studio */
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


/* FIXME questa verrà implementata direttamente nella gui
void Atinom(HANDLE hInstance)
 {

     MessageBox( hInstance, "Il biglietto e' valido solo dopo la convalida.Il biglietto deve essere conservato per tutta la durata \
 del viaggio. Il diritto a viaggiare cessa al termine della tratta corrispondente al valore del biglietto. \
 Il passeggero che al controllo non fosse in grado di presentare il biglietto o lo presentasse irriconoscibile, \
 o comunque non valido, verra' abbattuto. La notifica del decesso verra' inviata ai parenti solo previo pagamento \
 delle spese postali.", "Norme di utilizzo", MB_OK | MB_ICONINFORMATION);

}
*/


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

/*********************************************************************/



//*******************************************************************
// PROCEDURA PRINCIPALE per la versione Windows.
// TAG2015 adesso è portabile, define andrebbero editati

#ifdef TABBOZ_WIN

//#pragma argsused
//int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdLine, int cmdShow)
int main(void)
{
    //hInst = hInstance;

    /* Inizializza il programma */
    InitTabboz();

    /* Finestra principale */
    //DialogBox(hInst,MAKEINTRESOURCE(1),NULL,TabbozWndProc);
    fl_register_images();
    win_principale = GUITabboz();
    win_principale->show();
    Fl::run();

    /* Chiusura */
    //TAG2015 Lasciamo perdere lo shutdown per ora
    // Nuova chiusura - 19 Giugno 1999, speriamo che ora non crashi piu'...
    // if (boolean_shutdown == 2) {
    //     FineProgramma("shutdown"); // Salvataggio partita...
    //     #ifdef TABBOZ_DEBUG
    //         if (debug_active) {
    //             writelog("tabboz: end (exit + shutdown)");
    //             closelog();
    //         }
    //     #endif
    //     ExitWindows(0, 0);

    // } else {
    //     FineProgramma("main"); // Salvataggio partita...
    //     #ifdef TABBOZ_DEBUG
    //         if (debug_active) {
    //             writelog("tabboz: end (standard exit)");
    //             closelog();
    //         }
    //     #endif
    // }

    FineProgramma("main"); // Salvataggio partita...
    if (LOGGING) {
        writelog("tabboz: end (standard exit)");
        closelog();
    }
    return 0;
}
#endif


//*******************************************************************
// 'Possibile' main per Linux usando le GTK+

/* TAG2015 visto che abbiamo optato per fltk queste non servono ma la
* ifdef per linux tanto vale tenerla per ora
*/

#ifdef LINUX

int main (int argc, char **argv)
 {
    /* Initialize i18n support */
    gtk_set_locale();

    /* Initialize the widget set */
    gtk_init (&argc, &argv);

    /* Inizializza il programma */
    InitTabboz();

    /* Create the main window */
    mainwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* Set up our GUI elements */
    ...

    /* Show the application window */
    gtk_widget_showall (mainwin);

    /* Let the user interact with our application */
    gtk_main();

    /* Chiusura */

   // salvataggio partita...

    gtk_exit (0);
 }

#endif


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

// // Inizia la riproduzione di un suono
// void TabbozPlaySound(int number)
// {
//     char filename[20];
//     sprintf(filename,"Tabs%04d.Wav",number);
//     sndPlaySound(filename, SND_ASYNC | SND_NODEFAULT);
// };



// void SpegniISuoni()
// {
//     PlaySound(NULL,NULL,0x0040);
// //    PlaySound(NULL,NULL,SND_PURGE);
// }



//*******************************************************************
// Copyright (c) 1997-2000 Andrea Bonomi
//*******************************************************************
