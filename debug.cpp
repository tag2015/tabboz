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


#include <stdio.h>
#include <string.h>
#include <time.h>

#include "zarrosim.h"

#include "debug.h"

/* Header per toolkit FLTK */
#include <FL/filename.H>


FILE *debugfile = NULL;
char  log_buf[128] = "";


void openlog()
{
    char  log_path[FL_PATH_MAX];
    strcpy(log_path, path_profilo);
    strcat(log_path, "zarrosim.log");
    if(!debugfile)
        debugfile = fopen(log_path, "w");
    if(debugfile)
        fprintf(debugfile,"Aperto log: %s\n", log_path);
}


void closelog()
{
    if(debugfile)
        fclose(debugfile);
}


void writelog(char const *s)
{
    time_t t;

    time(&t);
    if(debugfile) {
        fprintf(debugfile,"%24.24s %s\n",ctime(&t),s);
        fflush(debugfile); // Esegue il flush del file, cosi' anche se il Tabboz craschia si ha il file di log...
    }
}