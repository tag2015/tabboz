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

#ifndef TABBOZ_SCOOTER_H
#define TABBOZ_SCOOTER_H

/* STRUTTURA INFORMAZIONI SUGLI SCOOTER */
typedef struct tagNEWSTSCOOTER {
    int         id;             // Identificativo numerico scooter
    int         speed;          // Velocità (calcolata base + elaborazioni)
    int         marmitta;       // Marmitta ( +0, +7, +12, +15)
    int         carburatore;    // Carburatore ( 0 - 4 )
    int         cc;             // Cilindrata ( 0 - 4 )
    int         filtro;         // Filtro dell'aria ( +0, +5, +10, +15)
    int         prezzo;         // Costo dello scooter (modifiche incluse)
    int         attivita;       // Attività scooter (vedere n_attivita)
    int         stato;          // Quanto è intero (in percentuale); -1000 nessuno scooter
    char        nome[30];       // Nome dello scooter
    int         fama;           // Figosità scooter
} NEWSTSCOOTER;

enum PezziMoto {
    MARMITTA,
    CARB,
    CC,
    FILTRO,
};

extern NEWSTSCOOTER ScooterData;        // Dati scooter del tabbozzo
extern NEWSTSCOOTER ScooterMem[];       // Array scooter disponibili in concessionario

extern int           PezziMem[][5];     // Costo dei vari pezzi
extern const char    *n_carburatore[];  // Descrizioni carburatori
extern const char    *n_cc[];           // Cilindrate
extern const char    *n_marmitta[];     // Descrizioni marmitte
extern const char    *n_filtro[];       // Descrizioni filtri aria

extern const char    *n_attivita[];     // situazione scooter (ok, a secco, ingrippato...)
extern int           benzina;           // Benzina nel serbatoio


void    AggiornaScooter(void);
void    CalcolaVelocita(bool scooter_nuovo);

void    AcquistaScooter(int scelta);
bool    VendiScooter(void);

bool    ParcheggiaScooter(void);
void    FaiBenza(void);
void    RiparaScooter(void);

bool    CompraUnPezzo(PezziMoto pezzo, int scelta);

#endif