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

// Costi... (migliaia di lire)
#define UN_MESE      50
#define SEI_MESI    270
#define UN_ANNO     500

/* Abbonamenti Palestra ---------------------------------------------------------------------------- */
STSCOOTER PalestraMem[] = {
    {0,   0,   0,   0,   0,   0,  50,   0, ""},       // Un mese
    {0,   0,   0,   8,   0,   0, 270,   0, ""},       // Sei mesi
    {0,   0,   0,   9,   0,   0, 500,   0, ""},       // Un anno
    {0,   0,   0,   9,   0,   0,  14,   0, ""}        // Una lampada
};


void AggiornaPalestra(void);
void EventiPalestra(void);
