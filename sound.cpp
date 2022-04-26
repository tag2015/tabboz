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

#include "os.h"

#include <stdio.h>
#include <stdlib.h>

#include "sound.h"


/* Inizia la riproduzione di un suono */
void TabbozPlaySound(int number)
{
    char filename[20];

    sprintf_s(filename, (sizeof(filename)/sizeof(char)), "tabs%04d.wav", number);
    #ifdef TABBOZ_WIN
        PlaySoundA(filename, NULL, SND_FILENAME | SND_ASYNC);
    #endif
};


/* Interrompe suoni in riproduzione */
void SpegniISuoni(void)
{
    #ifdef TABBOZ_WIN
        PlaySoundA(NULL,NULL,SND_ASYNC);
    #endif
}
