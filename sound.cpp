/*
     This file is part of Tabboz Simulator.

    Tabboz Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Nome-Programma is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "os.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef TABBOZ_WIN
    #include <windows.h>
    #include <mmsystem.h>
#endif

#include "sound.h"


/* Inizia la riproduzione di un suono */
void TabbozPlaySound(int number)
{
    char filename[20];
    sprintf(filename,"Tabs%04d.Wav",number);
    PlaySound(TEXT(filename), SND_ASYNC | SND_NODEFAULT);
};


/* Chiude il subsystem audio */
void SpegniISuoni()
{
    PlaySound(NULL,NULL,0x0040);
    PlaySound(NULL,NULL,SND_PURGE);
}
