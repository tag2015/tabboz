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


/* Numero di elementi per ogni array di stringhe */

#define NUM_STRADE  50
#define NUM_TIPE    65
#define NUM_TIPI    50


/* "Indici" per l'array di stringhe degli eventi */

#define MSG_SFIGHE    2
#define MSG_SCUOLA    12
#define MSG_TIPA      22
#define MSG_TIPO      32
#define MSG_PALESTRA  42


extern const char *StrEventi[];                 // Stringhe usate nelle dialog semplici degli eventi
extern const char *StrEventiFinestra[];         // Stringhe usate nelle dialog con immagine degli eventi
extern const char *StrNomiStrade[];             // Nomi strade milanesi usate negli eventi

extern const char *StrOfferteLavoro[][3];       // Annunci di lavoro
extern const char *StrFinestraQuizLavoro[];     // Il titolo della finestra quiz
extern const char *StrTitoliQuizLavoro[];       // Introduzione della scheda
extern const char *StrDomandeLavoro[][3];       // Elenco domande scheda
extern const char *StrRisposteLavoro[][9];      // Elenco risposte scheda

extern const char *StrNomiTipe[];               // Elenco nomi tipe
extern const char *StrNomiTipi[];               // Elenco nomi tipi

extern const char *StrRisposteTipe[];           // Stringhe due di picche (dalle tipe)
extern const char *StrRisposteTipi[];           // Stringhe due di picche (dai tipi)