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

#include "proteggi.h"


int         new_counter;
static int	p_ruota1;
static int	p_ruota2;
static int  ruota1[8] = { 0xed0f,0xff0d,0x3392,0xabcd,0xc79c,0x23df,0x0706,0xc39c };
static int  ruota2[5] = { 0xb47f,0xc37b,0x1070,0x1999, 0xfb1e };


void clock_r1(int i1)
{
    int a1,a2;

    a1 = (i1 | ruota1[p_ruota1]) * (p_ruota2 + 1);
    p_ruota1++;
    if (p_ruota1 > 7) p_ruota1=0;

    a2 = (a1 & ruota2[p_ruota2]) * (p_ruota1 + 1);
    p_ruota2++;
    if (p_ruota2 > 4) p_ruota2=0;

    if (a2 >= a1)
        a2-=a1;
    else
        a2+=a1;

    new_counter+=a2;
}

/* Resetta il checksum e i valori che vengono usati per calcolarlo */
void new_reset_check()
{
    new_counter=1979;
    p_ruota1=0;
    p_ruota2=2;
}

/* Chiama il calcolatore di checksum. Ritorna il valore passato come parametro. Versione int */
int new_check_i(int i)
{
    clock_r1(i);
    return(i);
}