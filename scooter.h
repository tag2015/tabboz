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

#include <stdio.h>

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


extern NEWSTSCOOTER ScooterData;
extern NEWSTSCOOTER ScooterMem[];

extern const char    *n_attivita[];
extern int           benzina;