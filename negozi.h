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

#ifndef TABBOZ_NEGOZI_H
#define TABBOZ_NEGOZI_H

/* Locazione di inizio dei vestiti nell'array */
#define I_GIUBBOTTO 0
#define I_PANTALONI 7
#define I_SCARPE 13

/* Locazioni vestiti speciali */
#define GIUBBOTTO_BABBO 7
#define PANTALONI_BABBO 13

extern STVARIE VestitiMem[];
extern STVARIE SizzeMem[];

void PagaQualcosa(int scelta);
void PagaSizze(int scelta);

bool OfferteDiNatale(void);

#endif