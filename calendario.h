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

typedef struct tagMESI {
    char        nome[20];       // nome del mese o giorno
    int         num_giorni;     // giorni del mese o festivo si/no
  } STMESI, STGIORNI;

extern STMESI InfoMese[];
extern STGIORNI InfoSettimana[];


extern   int  x_giorno;
extern   int  x_giornoset;
extern   int  x_mese;
extern   int  x_anno_bisesto;

extern   int  x_vacanza;

extern   int  scad_pal_giorno;
extern   int  scad_pal_mese;


void  Giorno(void);