/* Routine di debugging */

#include <stdio.h>
#include <time.h>

#include "debug.h"

FILE *debugfile;

void openlog()
{
    debugfile = fopen("zarrosim.log", "w");
}

void closelog()
{
    fclose(debugfile);
}

void writelog(char const *s)
{
    time_t t;

    time(&t);
    fprintf(debugfile,"%24.24s %s\n",ctime(&t),s);
    fflush(debugfile); // Esegue il flush del file, cosi' anche se il Tabboz craschia si ha il file di log...
}