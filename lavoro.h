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
#ifndef TABBOZ_LAVORO_H
#define TABBOZ_LAVORO_H

/* Numero di ditte */
#define NUM_DITTE 8

/* Numero schede quiz colloquio*/
#define NUM_SCHEDEQUIZ  10


extern STVARIE LavoroMem[];

extern  int   numeroditta;              // Ditta in cui sei impiegato (-1 se disoccupato)
extern  int   stipendio;                // Stipendio mensile
extern  int   giorni_di_lavoro;         // Serve x calcolare lo stipendio SOLO per il primo mese...
extern  int   impegno;                  // Impegno sul lavoro (1-100)

extern bool crocette_risposte[3][3];    // Crocette inserite nel quiz


void AggiornaLavoro(void);
void ControllaRisposte(int n_ditta, int n_scheda);

void Licenziati(void);
void CalcolaTFR(void);

void Lavora(void);
void FaiIlLeccaculo(void);
void ChiediAumento(void);
void Sciopera(void);

#endif