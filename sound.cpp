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

#include "os.h"

#include <stdio.h>
#include <stdlib.h>

#include "zarrosim.h"
#include "debug.h"

#include "sound.h"



/* Inizia la riproduzione di un suono */
void TabbozPlaySound(int number)
{
    char filename[STR_MAX];

    #ifdef TABBOZ_WIN
        sprintf_s(filename, (sizeof(filename)/sizeof(char)), "res\\wav\\tabs%04d.wav", number);
        PlaySoundA(filename, NULL, SND_FILENAME | SND_ASYNC);
        #ifdef TABBOZ_DEBUG
            sprintf(log_buf,"Riproduci suono: %s",filename);
            writelog(log_buf);
        #endif
    #endif
};


/* Interrompe suoni in riproduzione */
void SpegniISuoni(void)
{
    #ifdef TABBOZ_WIN
        PlaySoundA(NULL,NULL,SND_ASYNC);
    #endif
}
