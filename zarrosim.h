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

/* Versione gioco... */
#define VERSION "Version 0.92q"

/* Per attivare il Debug... */
#define TABBOZ_DEBUG

/* Per attivare il logging */
#define LOGGING 1

/* Per disattivare la possibilita' di giocare con la tabbozza */
#define NOTABBOZZA

/* Per disabilitare la rete... */
#define NONETWORK

/* Per attivare il Prompt ... */
// #define PROMPT_ACTIVE

/* Abilita parti non più necessarie (e non compilabili) */
// #define DEADCODE

// static char copyright[] ="@(#) Copyright (c) 1997-2001 Andrea Bonomi, Emanuele Caccialanza, Daniele Gazzarri.\nAll rights reserved.\n";


/* Define per la gui originale */
#ifdef DEADCODE
#define IDOK            1
#define IDCANCEL        2
#define IDABORT         3
#define IDYES           6
#define IDNO            7

#define QX_NOME         102
#define QX_SOLDI        105
#define QX_LOAD         106
#define QX_SAVE         107
#define QX_CLOSE        108

#define QX_ADDW         119
#define QX_NOREDRAW     120
#define QX_REDRAW       121

#define QX_ABOUT        120
#define QX_LOGO         121

#define QX_SCOOTER      130
#define QX_VESTITI      131
#define QX_DISCO        132
#define QX_TIPA         133
#define QX_COMPAGNIA    134
#define QX_FAMIGLIA     135
#define QX_SCUOLA       136
#define QX_LAVORO       137
#define QX_INFO         139
#define QX_CONFIG       140
#define QX_TABACCHI     141
#define QX_PALESTRA     142
#define QX_VESTITI1     143
#define QX_VESTITI2     144
#define QX_VESTITI3     145
#define QX_VESTITI4     146
#define QX_VESTITI5     147
#define QX_PROMPT       150
#define QX_NETWORK      151
#define QX_CELLULAR     155
#endif

/* DIALOG (identificativi finestre, molti non usati) */

#define MAIN            1
#define ABOUT           2
#define WARNING         3
#define DISCO           4
#define FAMIGLIA        5
#define COMPAGNIA       6
#define SCOOTER         7
#define VESTITI         8
#define TIPA            9
#define SCUOLA          10
#define PERSONALINFO    11
#define LOGO            12
#define LAVORO          13
#define CONFIGURATION   14
#define SPEGNIMI        16
#define NETWORK         17
#define PROMPT          20

#define ACQUISTASCOOTER 70
#define VENDISCOOTER    71
#define RIPARASCOOTER   72
#define TAROCCASCOOTER  73

#define BAUHOUSE        80
#define ZOCCOLARO       81
#define FOOTSMOCKER     82
#define ALTRIVESTITI4   83
#define ALTRIVESTITI5   84
#define ALTRIVESTITI6   85

#define TABACCAIO       88
#define PALESTRA        89

#define CERCATIPA       91
#define LASCIATIPA      92
#define ESCICONLATIPA   93
#define DUEDIPICCHE     95

#define CELLULAR        120
#define COMPRACELLULAR  121
#define VENDICELLULAR   122
#define CELLULRABBONAM  123


// Attesa per soldi dai genitori
#define ATTESAMAX         5

// Lunghezza stringhe massima
#define STR_MAX          80

//typedef unsigned long   u_long;

/* INFORMAZIONI MATERIE SCOLASTICHE */
typedef struct tagSTMATERIE {
    char        nome[30];       // nome della materia
    int         voto;           // voto materia
  } STMATERIE;

/* INFORMAZIONI SUGLI SCOOTER  (ora usato solo per cose generiche...)  */
typedef struct tagSTSCOOTER {
    int         speed;          // velocita' massima
    int         cc;             // cilindrata
    int         xxx;            // [future espansioni]
    int         fama;           // figosita' scooter
    int         mass;           // massa sooter
    int         maneuver;       // manovrabilita'
    int         prezzo;         // costo dello scooter (modifiche incluse)
    int         stato;          // quanto e' intero (in percentuale); -1 nessuno scooter
    char        nome[30];       // nome dello scooter
  } STSCOOTER;

/* NUOVE INFORMAZIONI SUGLI SCOOTER */
typedef struct tagNEWSTSCOOTER {
    int         speed;          // 01  Velocita'
    int         marmitta;       // 02  Marmitta       ( +0, +7, +12, +15)
    int         carburatore;    // 03  Carburatore    ( 0 - 4 )
    int         cc;             // 04  Cilindrata     ( 0 - 4 )
    int         filtro;         // 05  Filtro dell'aria    ( +0, +5, +10, +15)
    int         prezzo;         // 06  Costo dello scooter (modifiche incluse)
    int         attivita;       // 07  Attivita' scooter
    int         stato;          // 08  Quanto e' intero (in percentuale); -1 nessuno scooter
    char        nome[30];       // 09  Nome dello scooter
    int         fama;           // 10  Figosita' scooter
  } NEWSTSCOOTER;

/* INFORMAZIONI SUI TELEFONINI */
typedef struct tagCEL {
    int         dual;           // Dual Band ?
    int         fama;           // figosita'
    int         stato;          // quanto e' intero (in percuntuale)
    int         prezzo;
    char        nome[30];       // nome del telefono
  } STCEL;

/* INFORMAZIONI SULLE COMPAGNIE DEI TELEFONINI */
typedef struct tagABB {
    int         abbonamento;    // 0 = Ricarica, 1 = Abbonamento
    int         dualonly;       // Dual Band Only ?
    int         creditorest;    // Credito Restante...
    int         fama;           // figosita'
    int         prezzo;
    char        nome[30];       // nome del telefono
  } STABB;


extern   NEWSTSCOOTER ScooterData;
extern   NEWSTSCOOTER ScooterMem[];

extern   STCEL        CellularData;
extern   STCEL        CellularMem[];

extern   STABB        AbbonamentData;
extern   STABB        AbbonamentMem[];


#ifdef PROMPT_ACTIVE
extern   int  prompt_mode;
#endif

/* PRIMA LE VARIABILI GENERIKE... */

extern  int     cheat;
extern  int     scelta;
extern  char    Andrea[14];
extern  char    Caccia[21];
extern  char    Daniele[17];
extern  int     ImgSelector;
extern  int     TabbozRedraw;   // E' necessario ridisegnare il Tabbozzo ???
extern  int     ScuolaRedraw;   // E' necessario ridisegnare la scuola ???
extern  char    showscooter;


/* DOPO LE CARATTERISTIKE... */

extern  int       Attesa;           // Tempo prima che ti diano altri soldi...
extern  int       Fama;             // Figosità
extern  int       Reputazione;
extern  int       Studio;           // Quanto vai bene a scuola (1 - 100)
extern  int       Soldi;            // Long...per forza! lo zarro ha tanti soldi... | Retrocesso a int, a 32bit è sufficiente
extern  int       Paghetta;         // Paghetta Settimanale... | vedi sopra
extern  char      Nome[30];
extern  char      Cognome[30];
extern  int       comp_giorno;      // giorno del compleanno
extern  int       comp_mese;        // mese del compleanno
extern  char      Nometipa[30];
extern  int       FigTipa;          // Figosità tipa/o
extern  int       Rapporti;         // Stabilità relazione con tipa/o
extern  int       Stato;
extern  int       DDP;              // DueDiPicche
extern  int       AttPaghetta;
extern  int       Fortuna;
extern  int       numeroditta;
extern  int       impegno;
extern  int       giorni_di_lavoro; // Serve x calcolare lo stipendio SOLO per il primo mese...
extern  int       stipendio;
extern  int       benzina;
extern  int       antifurto;        // NON IMPLEMENTATO
extern  int       sizze;
extern  int       tempo_pestaggio;    // Tempo trascorso da un pestaggio
extern  int       current_testa;      // Grado di abbronzatura del tabbozzo
extern  int       current_gibbotto;   // Vestiti attuali del tabbozzo...
extern  int       current_pantaloni;
extern  int       current_scarpe;
extern  int       current_tipa;
extern  int       sound_active;
extern  int       euro;
extern  char      sesso;              // M/F
extern  char      ao;                 // lettera in funzione del sesso (tabbozza/tabbozzo)
extern  char      un_una[];
extern  char      *n_attivita[];      // situazione scooter 

/* Supporto Rete */
#ifndef NONETWORK
    extern   int     net_enable;         // Rete Attiva/Disattiva
    extern   char    lastneterror[255];
    extern   char    lastconnect[255];
    extern   int     addrLen;
    extern   HWND    NEThDlg;            // Punta alla procedura principale...
    extern   void    TabbozStartNet(HANDLE hDlg);
#endif

/*Altri define e prototipi per la vecchia gui */
#ifdef DEADCODE
/* POI LE STRONZATE PER LE FINESTRELLE... */

#ifdef TABBOZ_WIN
extern  HANDLE    hInst;
extern  HWND      hWndMain;
extern  HANDLE    hdlgr;
#endif

/* ED I PROTOTIPI FUNZIONI... */

#ifdef TABBOZ_WIN
extern  int   PASCAL       WinMain(HANDLE hInstance, HANDLE hPrevInstance,
               LPSTR lpszCmdLine, int cmdShow);
extern  BOOL FAR PASCAL MainDlgBoxProc(HWND hDlg, WORD message,
               WORD wParam, LONG lParam);
#endif

extern  BOOL FAR PASCAL    About(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Warning(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Disco(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Famiglia(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Compagnia(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Tipa(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Lavoro(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Scuola(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Scooter(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Vestiti(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Configuration(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    PersonalInfo(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Logo(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Tabaccaio(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Palestra(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Setup(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Spegnimi(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Network(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    MostraSalutieBaci(HWND hDlg, WORD message, WORD wParam, LONG lParam);
extern  BOOL FAR PASCAL    Cellular(HWND hDlg, WORD message, WORD wParam, LONG lParam);
#endif

#ifdef PROMPT_ACTIVE
    extern  BOOL FAR PASCAL    Prompt(HWND hDlg, WORD message, WORD wParam, LONG lParam);
#endif

extern  void  AggiornaPrincipale();
extern  void  FineProgramma(char const *caller);

extern  void  CalcolaStudio(void);
extern  char  *MostraSoldi(int i);
extern  void  nomoney(int tipo);


//TAG2015 quelle sotto x ora commentate ma servono
// extern  void  TabbozPlaySound(int number);
//extern  void   CalcolaVelocita(HANDLE hDlg);
//extern  void Evento(HWND hWnd);
//extern  void RunPalestra(HWND hDlg);
//extern  void RunTabacchi(HWND hDlg);
//extern  void RunVestiti(HWND hDlg,int numero);

/* TAG2015 define temporanei per escludere parti non ancora implementate */

//per disabilitare la gestione di calendario/date
//#define TAG2015_NOTEMPO
#define TAG2015_NOSCOOTER
#define TAG2015_NOCELL

/*Se euro disabilitato, calcola le lire moltiplicando x*1000. Altrimenti divide per 2 */
#define CALCSOLDI(x) ( (!euro) ? x*1000 : x/2 )

/*Calcola media voti passando totale e n.ro materie*/
#define MEDIAVOTI(tot,n) ( (float) tot / (n+1) )
