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

#ifndef TABBOZ_DISCO_H
#define TABBOZ_DISCO_H

typedef struct tagSTDISCO {
    bool        fuoriporta;     // raggiungibile solo con scooter
    int         fama;           // figosita' minima x entrare (selezione all' ingresso)
    int         rep_inc;        // incremento reputazione
    int         fama_inc;       // incremento figosità
    int         g_chiusura;     // giorno di chiusura (1=lunedi... 0=nessuno)
    int         costo;          // costo ingresso intero
    char        nome[30];       // nome della disco
} STDISCO;

extern const STDISCO  DiscoMem[];

void PagaDisco(int scelta);

#endif