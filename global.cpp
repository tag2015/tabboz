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

#include "global.h"

/* IMPORTANTE */
/* Non è (ancora) possibile aggiungere altri eventi senza cambiare radicalmente la routine in eventi.cpp */


const char *StrEventi[] = {
    "Cerchi la rissa con un metallaro e lui ti spacca le ossa...",  // id=1000
    "Cadi in lago di merda tra le risate generali...",
    "Mentre cammini per il quartiere con la tua compagnia, un piccione ti caga in testa...",   // id=1021
    "Cadi nel laghetto di Parco Sempione.",
    "Mentre cammini per il quartiere con la tua compagnia, un cane ti piscia su una gamba...",
    "Un attacco di diarrea ti costringe a restare a casa.",
    "Bevi due bicchieri di birra e vomiti per tutta la sera.",
    "Sei seduto al bar con i tuoi amici, passa una ragazza e fai dei commenti... Poi si gira e ti accorgi che è un uomo.",
    "Sei fermo al semaforo, un TIR ti passa vicino e solleva un'ondata di fango.",
    "Ti perdi e non arrivi ad un appuntamento importante.",
    "La televisione si rompe e perdi l'ultima puntata di Tabboz News.",
    "Qualcuno non apprezza il modo in cui sei vestito.",
    "Senza una precisa ragione, picchi il prof di ",
    "Con lo scooter di un tuo amico, ti scontri contro la macchina del prof di ",
    "Sputi dalla finestra della tua classe e centri il prof di ",
    "Forse dovevi studiare di più ",
    "Non riesci a dire una parola durante l'interrogazione di ",
    "Offendi la moralità della madre del prof di ",
    "Ti sei dimenticato del compito in classe di ",
    "Non ti metti di impegno a studiare ",
    "Non ti impegni abbastanza delle ore di ",
    "Vai male in una interrogazione di ",
    "Sei sempre il solito!\nChe bisogno c'è di gridare solo perchè sono andata a letto con un tuo amico!\nSei proprio un insensibile. Addio.",  //id=1041
    "Ho trovato un ragazzo che vale 1000 volte te, quindi, visto che sono una ragazza emancipata, ora ti lascio e mi metto con lui.",
    "Non bestemmi, non dici parolacce e non picchi i bambini. Sei proprio noioso...",
    "Sei la persona più spregievole che io abbia mai incontrato sulla faccia della terra.\nSpero che resteremo amici.",
    "Ci ho riflettuto a lungo... vaffanculo !",
    "Cioè zerella, mollami !",
    "Sono in un momento molto delicato della mia vita, in cui ho bisogno di tempo per fare delle scelte.\nAddio.",
    "Forse è meglio se non ci vediamo più per un po' di tempo...",
    "Capiscimi... devo prendere un po' di tempo per pensare al nostro futuro...",
    "Ti amo troppo per poter restare ancora insieme a te.\nAddio.",
    "Cioè, insomma, cioè io, ecco, insomma.... Addio...",   //id = 1341
    "Credo che tu sia la mia migliore amica...",
    "Hai presente quella tua amica, quella che mi hai fatto conoscere l'altro giorno...",
    "Ohhh, tipa... Mi devi troppo mollaaaaaareee!",
    "Basta, sono stufo di tutte le tue paranoie! Non ti sopporto più!",
    "Cioè tipa, io sono uno spirito libero, cioè non posso... cioè dopo un po' io... ecco... cioè...",
    "Spero che così tu la smetta di rompermi i coglioni...",
    "Capiscimi... devo prendere un po' di tempo per pensare al nostro futuro...",
    "Forse è meglio se non ci vediamo più per un po' di tempo...",
    "Addio stronzetta...",
    "Guardi troppo a lungo la ragazza dell'istruttore di body-building e lui ti sacagna di botte.",     // id=1100
    "Mentre attraversi un corridoio della palestra vieni travolto da una Cyclette impazzita.",
    "Scopri di aver preso le pillole contro l'impotenza al posto degli anabolizzanti.",
    "Un guasto alle tubature fa piovere merda dalla tua doccia...",
    "Sollevando dei pesi, ti sbilanci e precipiti dalla finestra dietro le tue spalle.",
    "Giochicchiando con un bilancere, ti fracassi le palle.",
    "Per un simpatico scherzo, il tuo armadietto viene dato alle fiamme.",
    "Una ragazza ti guarda e ride per le vistose chiazze di sudore sotto le tue ascelle...",
    "Dopo 5 minuti di corsa cadi al suolo stremato...",
    "Ti perdi per i meandri della tua palestra, solo l'intervento del guardiano notturno può salvarti.",
};

const char *StrEventiFinestra[] = {
    "Cerchi la rissa con\nun metallaro che\npassa in\n_NOMEVIA_\ne lui ti spacca tutte\nle ossa.",
    "Incontri un metallaro\nin\n_NOMEVIA_\nlo minacci e lui ti\nspacca tutte le ossa.",
    "Insulti un gruppo di\nmetallari che\npassano in\n_NOMEVIA_\ne uno di questi ti\nspacca le ossa.",
    "Cerchi la rissa con\nun metallaro e lui ti\nspacca tutte le ossa.",
    "Mentre cammini per\n_NOMEVIA_\ncerchi la rissa con\nun metallaro e lui ti\nspacca tutte le ossa.",
    "Senza un preciso motivo, prendi per\nil culo un manovale che, essendo privo\ndi senso dell'umorismo, ti fa a pezzi.",
    "Facendo il pirla con lo scooter in\n_NOMEVIA_\nriesci a fare incazzare un camionista.",
    "Mentre giri per la città con il tuo scooter,\nincontri sfortunatamente un muro...",
};

const char *StrDomandeLavoro[][3] = {
    {
        "Di che colore era il cavallo bianco di Napoleone?",
        "In un lavoro in cantiere il vostro compagno viene travolto da una\ndecina di travi provenienti dall'alto, ne deducete che...",
        "Vi rendete conto di quello che state facendo?",
    },
    {
        "Qual è il lasso di tempo che intercorre tra l'arresto di un mafioso e\nla sua scarcerazione?",
        "Quando i vostri genitori credono opportuno non elargire la paghetta\nsettimanale, credete sia il caso di:",
        "E' vietato il sorpasso",
    },
    {
        "Indivinate, stronzoni, cos'è quell'oggetto tondo con un buco\nin mezzo, dal quale escono strani odori?",
        "Riteniamo che voi che leggete siate tutti dei disadattati e per di\npiù senza lavoro... Ah dimenticavamo, anche un po' stronzi!",
        "Come ci si comporta per aumentare la produttività?",
    },
    {
        "Quando si vuole preservare la democrazia bisogna:",
        "Viene prima l'uovo o la gallina?",
        "Quando dista la nebulosa del granchio dalla stella del buco strappato?",
    },
    {
        "Allo stadio sei in curva sud, in mezzo alla bolgia vedi una bella\nfigona che balla e si dimena a ritmo di samba...",
        "Che ruolo vorresti avere in una squadra di calcio?",
        "L'inquinamento atmosferico prodotto dai veicoli con motore a scoppio",
    },

};

const char *StrRisposteLavoro[][9] = {
    {
        "Verde",
        "Nero",
        "Rosso",
        "Presto avrete bisogno di un nuovo compagno...",
        "Quel burlone del gruista avrà nuovamente fatto uno dei sui scherzi.",
        "Dovete ammazzare subito il vostro compagno prima che soffra!",
        "Si",
        "No",
        "Forse",
    },
    {
        " 10 nano secondi",
        " 60 nano secondi",
        "-10 nano secondi (viene liberato prima dell'arresto effettivo)",
        "Prendere esempio da Gaetano Bresci.",
        "Non ho capito la domanda.",
        "Noooooo! Come farò adesso a mantenere il cellulare?",
        "in prossimità di centrali nucleari sovietiche.",
        "in tutte le strade percorse da camionisti infuriati ed ubriachi",
        "banchettando sul cruscotto con lupini e mascarpone.",
    },
    {
        "Parigi dall'alto.",
        "La mia faccia.",
        "Una marmitta catalitica!",
        "Lo andate a dire al budello di vostra madre nel casino!",
        "E io vi dico che siete degli sciocchini! ...ECCO!",
        "Andatevela a stroncare nel culo va!",
        "Una partita a poker con gli amici in ufficio.",
        "Assenteismo",
        "Ogni tanto si soddisfa sessualmente il direttore.",
    },
    {
        "Sciogliere il parlamento.",
        "Proclamarsi capo assoluto.",
        "Fare aereoplanini con la costituzione.",
        "L'uovo, sicuramente!",
        "La gallina perchè frutto di un'evoluzione!",
        "Io",
        "Tanto, tanto, tanto, tanto, tanto, tanto lontana!",
        "1.254.643.342 anni luce.",
        "Tanti metri quante le volte che è maiala!",
    },
    {
        "La fai a pezzi con un colpo di mortaio.",
        "Bah, non so ballare la samba.",
        "Ti travesti da brasileiro e le rifili il tuo mango.",
        "Attaccante, sono uno specialista nell'infilare le palle ovunque.",
        "Tutti! Gliela faccio vedere io come si gioca a calcio.",
        "Portiere, sono bravo a prendere le palle di tutti.",
        "Dipende dall'isolamento del reattore nucleare.",
        "Puo essere incrementato dall'uso di camion senza marmitte.",
        "Dipende dal camionista.",
    },
};

const char *StrNomiStrade[] = {
    "Via Lorenteggio",    // id=450
    "Corso Vercelli",
    "Viale Papiniano",
    "Via Forze Armate",
    "Via Pontaccio",
    "Via Padova",
    "Via Porpora",
    "Corso Buenos Aires",
    "Viale Monza",
    "Via Leoncavallo",
    "Via Bagarotti",
    "Via Viterbo",
    "Via Fratelli Zoia",
    "Via dei Ciclamini",
    "Via Bassi",
    "Viale Monte Ceneri",
    "Viale Certosa",
    "Via Lamarmora",
    "Corso XII Marzo",
    "Viale dei Mille",
    "Via Goldoni",
    "Via Melchiorre Gioia",
    "Corso Lodi",
    "Viale Umbria",
    "Viale Puglie",
    "Via Tertulliano",
    "Viale Cassala",
    "Viale Liguria",
    "Viale Beatrice D'Este",
    "Viale Filippetti",
    "Viale Toscana",
    "Viale Famagosta",
    "Via La Spezia",
    "Via Giambellino",
    "Via Inganni",
    "Via Savona",
    "Viale Lomellina",
    "Via Galileo Galilei",
    "Viale Faenza",
    "Viale Jenner",
    "Via Fiuggi",
    "Via Imbonati",
    "Via Pio II",
    "Viale Tunisia",
    "Via Pergolesi",
    "Via Sammartini",
    "Via Primaticcio",
    "Via Archimede",
    "Corso Venezia",
    "Via Karl Marx",
};


const char *StrNomiTipe[] = {
    "Marcella",   // id=200
    "Giovanna",
    "Concetta",
    "Elisa",
    "Federica",
    "Ilaria",
    "Simona",
    "Assunta",
    "Maria",
    "Elena",
    "Margherita",
    "Giorgia",
    "Silvia",
    "Teresa",
    "Grazia",
    "Elisabetta",
    "Alessia",
    "Chiara",
    "Alessandra",
    "Rosa",
};

const char *StrNomiTipi[] = {
    "Salvatore",
    "Rocco",
    "Kasko",
    "Svakko",
    "Punto",
    "Santo",
    "Krukko",
    "Fiskio",
    "Krampo",
    "Skianto",
    "Gervasio",
    "Pino",
    "Marco",
    "Antonio",
    "Gianpaolo",
    "Gianmaria",
    "Gustavo",
    "Riccardo",
    "Gianni",
    "Grankio",
};

const char *StrRisposteTipe[] = {
    "Non ti caga nemmeno di striscio...",  // id=300
    "Mi dispiace... insomma, ho già il ragazzo...",
    "Non vorrei offendere i tuoi sentimenti, ma mi fai proprio cagare...",
    "Ti amo troppo ma non potrei mai riuscire a stare con te...",
    "Sei la persona più spregevole che ho incontrato sulla faccia della terra...",
    "Meglio morire che mettermi con uno come te...",
    "Spero che tu stia scherzando... in caso contrario devo informati che il mio ragazzo è campione di lotta libera...",
    "Vorrei tanto mettermi con te, davvero... ora però devo prendermi una pausa per riflettere, spero che tu mi capisca...",
    "Sono già impegnata... se solo me lo avessi chiesto due giorni fa...",
    "Mi dispiace ma non credo che tu sia il mio tipo... Il mio amore è alto, biondo con gli occhi azzurri...",
    "No.",
    "Sono appena uscita da una storia molto triste ed ora non mi fido più di voi uomini.",
    "Voi uomini siete tutti stronzi... Chissà quante altre povere ragazze hai ingannato con il tuo sorrisetto di merda...",
    "Cioè zerella... non ci stò dentro...",
    "Mettermi con te ???? Ha, ha, ha !",
    "Nooooooo!",
    "Comincia a ritirarti su i pantaloni...",
    "Forse mi hai preso per la ragazza sbagliata...",
    "Vai a farti fottere...",
    "Oh scusa, mi sono dimenticata di dirti che sono impegnata..."
};
