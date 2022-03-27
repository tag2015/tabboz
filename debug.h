/* Routine di debugging */

extern  FILE  *debugfile;   // file di log

void   openlog(void);       // Apre file di log
void   closelog(void);      // Chiude file di log
void   writelog(char *s);   // Aggiunge stringa a file di log