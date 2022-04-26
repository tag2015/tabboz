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


/* INFORMAZIONI SUI TELEFONINI */
typedef struct tagCEL {
    int         dual;           // Dual Band ?
    int         fama;           // figosita'
    int         stato;          // quanto e' intero (in percentuale)
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

extern   STCEL        CellularData;
extern   STCEL        CellularMem[];

extern   STABB        AbbonamentData;
extern   STABB        AbbonamentMem[];


void AggiornaCell(void);

bool CompraCellulare(int scelta);
bool VendiCellulare(void);
bool AbbonaCellulare(int scelta);