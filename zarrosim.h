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

#ifndef TABBOZ_ZARROSIM_H
#define TABBOZ_ZARROSIM_H

/* Versione gioco... */
#define VERSION "1.0alpha1"

/* Per attivare il Debug... */
// #define TABBOZ_DEBUG

/* Per disattivare la possibilita' di giocare con la tabbozza */
#define NOTABBOZZA

/* Per disattivare gli eventi casuali (e gran parte del divertimento... da usare solo per debug) */
//#define NORANDOM

/* Per disattivare il timer di avanzamento automatico */
// #define NOTIMER
/* Intervallo timer - default: 1 ciclo (1 giorno del gioco) ogni 60 secondi */
#define TIMER_INTERVAL  60.0

/* Per abilitare parti non più necessarie (e non compilabili) */
// #define DEADCODE


/* DIALOG (identificativi finestre, molti non usati) */
#define MAIN            1
#define SCUOLA          10
#define LAVORO          20
#define PALESTRA        30
#define TIPA            40
#define COMPAGNIA       50
#define FAMIGLIA        60
#define SCOOTER         70
#define VESTITI         80
#define TABACCAIO       81
#define CELLULAR        82
#define DISCO           90

/* Attesa per soldi dai genitori (1 settimana) */
#define ATTESAMAX         6

/* Lunghezza stringhe massima */
#define STR_MAX          80

/* Tipi di uscita dal gioco da usare nella gui */
#define NOEXIT    0
#define NEWGAME   1
#define SAVEGAME  2

//typedef unsigned long   u_long;


/* STRUTTURA PER INFORMAZIONI VARIE */
typedef struct tagSTVARIE {
    bool        fuoriporta;     // luogo/servizio accessibile solo con scooter
    int         aux1;           // variabile ausiliaria
    int         aux2;           // variabile ausiliaria
    int         fama;           // figosita' minima richiesta
    int         rep;            // reputazione minima richiesta
    int         fama_inc;       // incremento figosità
    int         rep_inc;        // incremento reputazione
    int         prezzo;         // costo oggetto/servizio
    int         stato;          // condizione (1-100)
    char        nome[30];       // descrizione
  } STVARIE;


/* Variabili generiche */
extern  int     cheat;              // NON USATO
extern  bool    firsttime;          // 0: File profilo presente 1: Primo avvio o nuova partita
extern  int     chiusura;           // 0: Non uscire 1: Nuova partita 2: Salva ed esci


/* Caratteristiche tabbozzo */
extern  int       Fama;             // Figosità (1-100)
extern  int       Reputazione;      // Reputazione (1-100)
extern  int       Studio;           // Quanto vai bene a scuola (1 - 100)
extern  int       Soldi;            // Long...per forza! lo zarro ha tanti soldi... | Retrocesso a int, a 32bit è sufficiente
extern  int       Paghetta;         // Paghetta Settimanale...
extern  char      Nome[30];         // Nome del Tabbozzo
extern  char      Cognome[30];      // Cognome del Tabbozzo
extern  int       comp_giorno;      // giorno del compleanno
extern  int       comp_mese;        // mese del compleanno
extern  char      City[50];         // città di nascita
extern  char      Nometipa[30];     // Nome della tua tipa/o (se ce l'hai...)
extern  int       FigTipa;          // Figosità tipa/o (1-100)
extern  int       Rapporti;         // Stabilità relazione con tipa/o (1-100)
extern  int       Stato;            // Quanto stai male ??? Salute (1-100)
extern  int       DDP;              // DueDiPicche counter
extern  int       Fortuna;          // Fortuna del tabbozzo (1-100)

extern  int       tempo_pestaggio;  // Tempo trascorso da un pestaggio
extern  int       AttesaSoldi;      // Tempo prima che la famiglia ti dia altri soldi...

extern  char      sesso;            // M/F
extern  char      ao;               // lettera in funzione del sesso (tabbozza/tabbozzo)
extern  char      un_una[];         // articolo in funzione del sesso (un/una)


/* Accessori */
extern  int       current_testa;      // Grado di abbronzatura del tabbozzo
extern  int       current_giubbotto;  // Giubbotto attuale del tabbozzo
extern  int       current_pantaloni;  // Pantaloni attuali del tabbozzo
extern  int       current_scarpe;     // Scarpe attuali del tabbozzo
extern  int       current_tipa;       // Abbigliamento della tipa (nella finestra tipa)
extern  int       sizze;              // Numero di sigarette


/* Opzioni */
extern  int       sound_active;       // Abilita i suoni
extern  int       euro;               // Usa euro anzichè lire
extern  int       difficolta;         // Livello difficoltà 1-5
extern  int       timer_active;       // Abilita il timer
extern  char      tema_grafico[];     // Nome tema grafico di FLTK
extern  int       logging;            // Scrive eventi in file di log


extern  void  AggiornaPrincipale(void);
extern  void  CalcolaStudio(void);
extern  void  CalcolaSesso(void);
extern  char  *MostraSoldi(int i);
extern  void  nomoney(int tipo);
extern  void  ApplicaDifficolta(void);


/*Se euro disabilitato, calcola le lire moltiplicando x*1000. Altrimenti divide per 2 */
#define CALCSOLDI(x) ( (!euro) ? x*1000 : x/2 )

/*Calcola media voti passando totale e n.ro materie*/
#define MEDIAVOTI(tot,n) ( (float) tot / (n+1) )

#endif