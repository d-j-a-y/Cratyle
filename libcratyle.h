/* === C R A T Y L E ========================================================= */
/*!
**    @legal
**    Copyright (c) 2013 Xavier Dubourdieu, Jérôme Blanchi
**
**    This file is part of Crayle.
**
**    Cratyle is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    Cratyle is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with Cratyle.  If not, see <http://www.gnu.org/licenses/>.
*/
/* ========================================================================= */

#ifndef LIBCRATYLE_H_INCLUDED
#define LIBCRATYLE_H_INCLUDED

#include <string.h>

#include <fcntl.h>
#include <ctype.h>

#include <stdio.h>


#define CRATYLE_DICO_INDEX 800
#define CRATYLE_DICO_SYNO 250


#define ERROR_GENERIC -1
#define ERROR_NO 0

#define FALSE 0
#define TRUE 1

#define CRATYLE_ESCAPE_SENTENCE "quitCRATYLE"
#define CRATYLE_CLEAR_SENTENCE "CLEARSCREEN"
#define CRATYLE_PROPRE_SENTENCE "CHATPROPRE"

#define CRATYLE_VERSION_TEXTE "// (ratyle //"

#define CRATYLE_TEXTMAX 255
//#define CRATYLE_MOTMAX 10

#define TAILLE_MAX_SEPARATEUR 10

/* change this definition for the correct port */
#define MINITEL1_MODEMDEVICE "/dev/ttyUSB0"
#define MINITEL2_MODEMDEVICE "/dev/ttyUSB1"
#define MINITEL3_MODEMDEVICE "/dev/ttyUSB2"
#define IMPRIM1_MODEMDEVICE "/dev/ttyUSB3"

typedef enum boolean {false, true} bool;

typedef enum cratyle_genre {genre_indefinit, feminin, masculin, neutre} genre;
typedef enum cratyle_nombre {nombre_indefinit, singulier, pluriel, invariable} nombre;

/*ICI est la chose*/
int Cratylation (char* strPhrase, char * strPhraseCratyle, int iFdImprim);
bool CratyleMot (char* strMot);
int CratyleImprime (char * strMot, int iFileDescriptor);

bool CratyleGenreIdentique(const char* strMotSynonime, const char * strMotCratyle);
bool CratyleNombreIdentique(const char* strMotSynonime, const char * strMotCratyle);

genre CratyleGenre(const char* strMot);
nombre CratyleNombre(const char* strMot, int* iBaseGenreNombreIndex);
char* CratyleMotSingulier(int iBaseGenreNombreIndex);
char* CratyleMotPluriel(const char* strMot);

void CratyleCase(char* strMot, int* PremiereLettre,int* FauxTout);
void CratyleInit();

char *covertToUpper(const char *str);


#endif

