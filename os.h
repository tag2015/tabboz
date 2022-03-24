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

/* Definizioni per i vari sistemi operativi... */

// #define TABBOZ_LINUX
// #define TABBOZ_WIN16
#define TABBOZ_WIN

// Linux
#ifdef TABBOZ_LINUX
#endif

// Windows 32bit
#ifdef TABBOZ_WIN
#define TABBOZ32  // 32 bit di default
//#include <windows.h>
#endif