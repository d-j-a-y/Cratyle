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

#include "libcratyle.h"
#include "libminitel.h"

extern char* CratyleDico[CRATYLE_DICO_INDEX][CRATYLE_DICO_SYNO];
extern char* CratyleBaseGenreNombre[CRATYLE_DICO_INDEX][3];

extern int CratyleIndex[CRATYLE_DICO_INDEX];

extern int CratyleDicoIndex;


/**
 * CratyleMot
 * @Param : premiere chaine
 * @Param : seconde chaine
 * @Return : TRUE le genre identique, FALSE sinon. Si neutre toujours TRUE
 */
bool CratyleMot (char * strMot)
{

    int k = 0;
    while(CratyleDico[k][0] != '\0')
    {
        if (strcasecmp(strMot, CratyleDico[k++][0] ) == 0)
        {
            return true;
        }
    }

    return false;
}


/**
 * CratyleGenreIdentique
 * @Param : premiere chaine
 * @Param : seconde chaine
 * @Return : TRUE le genre identique, FALSE sinon. Si neutre toujours TRUE
 */
bool CratyleGenreIdentique(const char* strMotSynonime, const char * strMotCratyle)
{

    genre genreSynonime = CratyleGenre(strMotSynonime);
    genre genreCratyle = CratyleGenre(strMotCratyle);

    if(genreSynonime == genreCratyle || genreCratyle == neutre || genreSynonime == neutre)
        return true;

    return false;
}

/**
 * CratyleNombreIdentique
 * @Param : premiere chaine
 * @Param : seconde chaine
 * @Return : TRUE le nombre identique, FALSE sinon. Si invariable toujours TRUE
 */
bool CratyleNombreIdentique(const char* strMotSynonime, const char * strMotCratyle)
{

    nombre nombreSynonime = CratyleNombre(strMotSynonime, NULL);
    nombre nombreCratyle = CratyleNombre(strMotCratyle, NULL);

    if(nombreSynonime == nombreCratyle) // || nombreCratyle == invariable || nombreSynonime == invariable)
        return true;

    return false;
}

/**
 * CratyleGenre
 * @Param : la chaine de caractere dont le genre est a determiner
 * @Return : un genre du genre du mot
 */
genre CratyleGenre(const char* strMot)
{
    genre enumGenre = genre_indefinit;
    int iIndex = -1, iMotTrouve = -1;

    //TODO faire une recherche plus rapide (recursif du milieu et hop)
    while((CratyleBaseGenreNombre[++iIndex][0] != '\0') && ((iMotTrouve = strcmp(strMot, CratyleBaseGenreNombre[iIndex][0])) != 0));

    if (iMotTrouve == 0)
    {
        switch (*CratyleBaseGenreNombre[iIndex][1])
        {
        case 'M' : enumGenre = masculin; break;
        case 'F' : enumGenre = feminin; break;
        case 'N' : enumGenre = neutre; break;
        }
    }

    return enumGenre;
}

/**
 * CratyleNombre
 * @Param : char* strMot, la chaine de caractere dont le nombre est a determiner
 * @Param : int* iBaseGenreNombreIndex, si non NULL, index du mot dans la base si trouvé, sinon -1
 * @Return : le nombre du mot
 */
nombre CratyleNombre(const char* strMot, int* iBaseGenreNombreIndex)
{
    nombre enumNombre = nombre_indefinit;
    int iIndex = -1, iMotTrouve = -1;

    //TODO faire une recherche plus rapide (recursif du milieu et hop)
    while((CratyleBaseGenreNombre[++iIndex][0] != '\0') && ((iMotTrouve = strcasecmp(strMot, CratyleBaseGenreNombre[iIndex][0])) != 0));

    if (iBaseGenreNombreIndex) *iBaseGenreNombreIndex = -1;
    if (iMotTrouve == 0)
    {
        switch (*(CratyleBaseGenreNombre[iIndex][1]+sizeof(char)))
        {
        case 'S' : enumNombre = singulier; break;
        case 'P' : enumNombre = pluriel; break;
        case 'I' : enumNombre = invariable; break;
        }

        if (iBaseGenreNombreIndex) *iBaseGenreNombreIndex = iIndex;
    }

    return enumNombre;
}

/**
 * CratyleMotSingulier
 * @Param : int iBaseGenreNombreIndex, index du mot dans la base
 * @Return : char* , du mot au singulier. Attention, l'appelant doit liberer la mémoire
 */
char * CratyleMotSingulier(int iBaseGenreNombreIndex)
{
    char* strMotAuSingulier = NULL;

    if (iBaseGenreNombreIndex == -1 )
        return NULL;

    if (CratyleBaseGenreNombre[iBaseGenreNombreIndex][2] != 0)
    {
        strMotAuSingulier = malloc(strlen(CratyleBaseGenreNombre[iBaseGenreNombreIndex][2])*sizeof(char));
        if (strMotAuSingulier != NULL) strcpy(strMotAuSingulier, CratyleBaseGenreNombre[iBaseGenreNombreIndex][2]);
    }

    return strMotAuSingulier;

}

/**
 * CratyleMotPluriel
 * @Param : const char* strMot, un mot
 * @Return : char* , du mot au pluriel. Attention, l'appelant doit liberer la mémoire
 */
char* CratyleMotPluriel(const char* strMot)
{

    char* strMotPluriel = NULL;

    int iIndex = -1, iMotTrouve = -1;

    //TODO faire une recherche plus rapide (recursif du milieu et hop)  CratyleIndexBaseGenreNombre (int* iIndex)
    while((CratyleBaseGenreNombre[++iIndex][0] != '\0') && ((iMotTrouve = strcmp(strMot, CratyleBaseGenreNombre[iIndex][0])) != 0));

    if (iMotTrouve == 0)
    {
        //le pluriel suit le singulier dans la base : iIndex+1
        //on verifie que le mot suivant soit au pluriel et que ce soit le pluriel du mot voulu.
        if ( ( *(CratyleBaseGenreNombre[iIndex+1][1]+sizeof(char)) == 'P' ) )
        {
            if(CratyleBaseGenreNombre[iIndex+1][2] != 0)
            {
                if (strcmp (strMot,CratyleBaseGenreNombre[iIndex+1][2]) == 0)
                {
                    strMotPluriel = malloc(strlen(CratyleBaseGenreNombre[iIndex+1][0])*sizeof(char));
                    if (strMotPluriel != NULL) strcpy(strMotPluriel, CratyleBaseGenreNombre[iIndex+1][0]);
                }
            }
        }
    }

    return strMotPluriel;
}

/**
 * CratyleImprime
 *  @Param : strMot , quoi que l'on imprime
 *  @Param : iFileDescriptor, de l'imprimante
 *  @Return : un code d'erreur
 */
int CratyleImprime (char * strMot, int iFileDescriptor)
{
    static int iCaracteresImprime = 0;

    if (!strMot || !iFileDescriptor) return ERROR_GENERIC;

    iCaracteresImprime = iCaracteresImprime + strlen(strMot) + 1;

    //Si on depasse le buffer (2 pages) du minitel, on vide le buffer
    if(iCaracteresImprime > PENBOX_CARACTERE_MAX )
    {
        iCaracteresImprime = 0;
        MINITELEnvoyerCaractere(iFileDescriptor, MINITEL_EFFACEMENT_DE_PAGE);

    }

    printf("CratyleImprime %s - nb : %d\n", strMot, iCaracteresImprime);

	MINITELEnvoyerTexte(iFileDescriptor, (const unsigned char*)strMot);
    MINITELEnvoyerTexte(iFileDescriptor, (const unsigned char*)" ");

    return ERROR_NO;
}

/**
 * CratyleInit
 * @Param :
 * @Return :
 */
void CratyleInit()
{
    int iMot = -1, iSyno = -1;

        while((CratyleDico[++iMot][0] != '\0') )
        {
            while ((CratyleDico[iMot][++iSyno]) != '\0');

            CratyleIndex[iMot] = iSyno-1;

            iSyno=-1;
        }
        CratyleDicoIndex = iMot;
/*
        for (iMot = 0 ; iMot < CratyleDicoIndex; iMot++)
        {
            iSyno = rand() % CratyleDicoIndex;
            printf("%i ",iSyno);
        }
*/
}

/**
 * CratyleCase
 * @Param : char* strMot, mot dont la case est a tester
 * @Param : int* PremiereLettre, indique que la premiere lettre est en MAJ
 * @Param : int* FauxTout, indique que tout n'est pas en MAJ
 * @Return : void
 */
void CratyleCase(char * strMot, int *PremiereLettre,int *FauxTout)
{
    *PremiereLettre = 0;
    *FauxTout = 0;
    if (!islower(strMot[0]))
        *PremiereLettre = 1;
    if(strlen(strMot) > 1 && !islower(strMot[1]))
        *FauxTout = 1;
}

/**
 * covertToUpper
 * @Param : const char*, la chaine a passer en UPPERCASE
 * @Return : char* , du mot au singulier. Attention, l'appelant doit liberer la mémoire
 */
char *covertToUpper(const char *str)
{
    char *newstr, *p;
    p = newstr = strdup(str);
    while(*p++=toupper(*p));

    return newstr;
}

/**
 * Cratylation
 * @Param : char* strPhrase, premiere chaine
 * @Param : char* strPhraseCratyle, seconde chaine
 * @Param : int iFdImprim, Descripteur de fichier de l'imprimante
 * @Return : int, Code d'erreur
 */
int Cratylation (char* strPhrase, char * strPhraseCratyle, int iFdImprim)
{
    int iMot = -1, iSyno = 0;
    bool bCratyleOui = false;
//    char strPhraseTemp[CRATYLE_TEXTMAX]="";
    int nbr_mots = 0; /* Comptabilise le nombre de mots */

    const char strDelimiters[] = " <>+\\{}'\".,;:?*=!()[]&%$#";
//    const char strDelimitersAlphaNUm[] = "ABCEDEFGHIJKLMNOPQRSTUVabcdefghijklmnopqrstuv0123456789wxyzWXYZ";
    char *strPhraseCopy;
//    char *strPhraseCopy2;
    char *strMot, *strMotSingulier = NULL, *strMotPluriel = NULL, *strMotCratyle = NULL;
    char strSeparateur [TAILLE_MAX_SEPARATEUR]= "";
    int Tentative = 0,  iSeparateur =0;


    if (strPhrase == NULL)
        return ERROR_GENERIC;

/* Make writable copy.  */
    strPhraseCopy = strdup (strPhrase);
//    strPhraseCopy2 = strdup (strPhrase);

    strMot = strtok (strPhraseCopy, strDelimiters);

    int iTaille = 0; /* Taille du mot le plus grand */
    int iTailleDuMot = 0; /* Taille du mot actuel */
    int CasePremiereLettre = 0, CaseFauxTout = 0;
    bool bLangueDePlaton = false;
    nombre NombreDuMot = nombre_indefinit;
    int iBaseGenreNombreIndex = -1;
    bool bGenreIndentique = false, bNombreIdentique = false, bSensIdentique = false;


    while(strMot != NULL)
    {
        bLangueDePlaton = false;
        bSensIdentique = false;

        printf("Cratylation en cours : %s - %i\n", strMot, ++nbr_mots);

        iTaille += iSeparateur;

        if (nbr_mots == 1)
        {
            if (strMot != strPhraseCopy)
            {
                iSeparateur = (strMot - (strPhraseCopy+(sizeof(char)*(iTaille))));
                memcpy(strSeparateur,strPhraseCopy+(sizeof(char)*(iTaille+iTailleDuMot)), iSeparateur);
                strSeparateur[iSeparateur] = '\0';

            }
        }
        else
        {
            if (strMot != strPhraseCopy+(iTaille))
            {
                iSeparateur = (strMot - (strPhraseCopy+(sizeof(char)*(iTaille))));
                int k = 0;
                for (k =0 ; k < iSeparateur; k++)
                    strSeparateur[k] = strPhrase[iTaille+k];
                strSeparateur[iSeparateur] = '\0';
            }

        }
        iTailleDuMot = strlen(strMot);
        iTaille += iTailleDuMot;

        CratyleCase(strMot, &CasePremiereLettre, &CaseFauxTout);

        //Est un mot au pluriel, si oui, cherchez le singulier du mot
        NombreDuMot = CratyleNombre(strMot, &iBaseGenreNombreIndex);
        if (NombreDuMot == pluriel)
        {
            strMotSingulier = CratyleMotSingulier(iBaseGenreNombreIndex);
        }

//        printf("DEbug 1 \n");

        bLangueDePlaton = CratyleMot(strMot);

        // Est ce un mot d'origine du texte
        if(bLangueDePlaton)
        {
            //On imprime et on cratyle pas
            if (iFdImprim != 0) CratyleImprime(strMot, iFdImprim);
        }
        else
        {
    //        while((CratyleDico[++iMot][0] != '\0') )
            iMot = rand() % CratyleDicoIndex;
            while((CratyleDico[iMot][0] != '\0') && (Tentative++ < (CratyleDicoIndex*2)) && (bCratyleOui == false))
            {
    //            int iMotPosition = 0, iMotTaille = 0;
                while ((CratyleDico[iMot][++iSyno]) != '\0' && bCratyleOui == false)
                {
//                    printf("iSyno %i ",iSyno);
//printf("DEbug 2 \n");
                    bSensIdentique = false;

                    if (NombreDuMot == pluriel)
                    {
                        if (strcasecmp(strMotSingulier, CratyleDico[iMot][iSyno] ) == 0)
                        {
                            strMotPluriel = CratyleMotPluriel(CratyleDico[iMot][0]);
                            printf("Le pluriel de %s est %s \n", CratyleDico[iMot][0], strMotPluriel);
                            bSensIdentique = true;
                        }
                    }
                    else
                    {
                        if (strcasecmp(strMot, CratyleDico[iMot][iSyno] ) == 0)
                        {
                            bSensIdentique = true;
                        }
                    }

//printf("DEbug 3 \n");

                    if(bSensIdentique)
                    {
                        bGenreIndentique = CratyleGenreIdentique(CratyleDico[iMot][iSyno], CratyleDico[iMot][0]);
                        bNombreIdentique = CratyleNombreIdentique(CratyleDico[iMot][iSyno], CratyleDico[iMot][0]);

                        if (bGenreIndentique && bNombreIdentique)
                        {
                            bCratyleOui = true;

                            if (NombreDuMot == pluriel && strMotPluriel != NULL)
                                strMotCratyle = strMotPluriel;
                            else
                                strMotCratyle = (char*)CratyleDico[iMot][0];

                            printf("iSyno dans l'identique %i ",iSyno);
                            printf("Cratylation oui!: %s -> %s\n", CratyleDico[iMot][iSyno], strMotCratyle);
//printf("DEbug 4 \n");

                            if (nbr_mots == 1)
                            {
                                if(CaseFauxTout)
                                {
                                    char *upstr;
                                    upstr = covertToUpper(strMotCratyle);
                                    sprintf(strPhraseCratyle, "%s%s",strSeparateur, upstr);
                                    free (upstr);
                                }
                                else
                                    sprintf(strPhraseCratyle, "%s%s", strSeparateur,strMotCratyle);

//printf("DEbug 5 \n");
                                printf("Cratylation oui!: sptrintf %s, \n",strPhraseCratyle);
                            }
                            else
                            {
//printf("DEbug 6 \n");
        //                    bCratyleOui = true;
                                if(CaseFauxTout)
                                {
                                    char *upstr;
                                    upstr = covertToUpper(strMotCratyle);
                                    sprintf(strPhraseCratyle, "%s%s%s",strPhraseCratyle, strSeparateur, upstr);
//printf("DEbug 7 \n");
                                    free (upstr);
//printf("DEbug 8 \n");
                                }
                                else
                                {
//printf("DEbug 9 \n");
                                    if((strlen(strPhraseCratyle)+strlen(strMotCratyle)+1+iSeparateur) < CRATYLE_TEXTMAX)
        //TODO ponctuation reeel
                                        sprintf(strPhraseCratyle, "%s%s%s",strPhraseCratyle, strSeparateur, strMotCratyle);
                                    else
                                        printf("Cratylation non! Dépassement mememoire, augmenter CRATYLE_TEXTMAX et recompil!\n");
//printf("DEbug 10 \n");
        //                    else iMotPosition =  ((long)strMot - (long)strPhrase)/(int)sizeof(strMot);
        //                    while(strPhrase[iMotPosition+iMotTaille] != '\0' && isalpha(strPhrase[iMotPosition+iMotTaille++]) );
                //            snprintf(strPhraseTemp, CRATYLE_TEXTMAX*sizeof(char), "%s",
                                }
                            }
//printf("DEbug 11 \n");
                        }
//printf("DEbug 12 \n");

                    }
//printf("DEbug 13 \n");
                    if (NombreDuMot == pluriel && strMotPluriel != NULL)
                    {
                        free(strMotPluriel);
                        strMotPluriel = NULL;
                    }
//printf("DEbug 14 \n");
                }

                iSyno = 0;
                iMot = rand() % CratyleDicoIndex;
            }
        }
        Tentative = 0;
        iMot = -1;

        if(bCratyleOui == false)
        {
            if (nbr_mots == 1)
            {
                sprintf(strPhraseCratyle, "%s%s", strSeparateur,strMot);
            }
            else
            {
                if(strlen(strPhraseCratyle)+strlen(strMot)+1+iSeparateur < CRATYLE_TEXTMAX)
                {
//TODO ponctuation reeel
                    sprintf(strPhraseCratyle, "%s%s%s",strPhraseCratyle, strSeparateur, strMot);
                }
                else
                    printf("Cratylation non ! Dépassement mememoire, augmenter CRATYLE_TEXTMAX et recompil!\n");
            }
        }

        if (strMotSingulier != NULL)
        {
            free(strMotSingulier);
            strMotSingulier = NULL;
        }
        iBaseGenreNombreIndex = -1;
        bCratyleOui = false;
        strMot = strtok (NULL, strDelimiters);
    }

    free(strPhraseCopy);
//    free(strPhraseCopy2);

    if (strPhrase[strlen(strPhrase)-1] == '?')
        if (strPhrase[strlen(strPhrase)-2] == ' ')
            sprintf (strPhraseCratyle,"%s ?", strPhraseCratyle);
        else
            sprintf (strPhraseCratyle,"%s?", strPhraseCratyle);
    else if (strPhrase[strlen(strPhrase)-1] == '!')
    {
        if (strPhrase[strlen(strPhrase)-2] == ' ')
            sprintf (strPhraseCratyle,"%s !", strPhraseCratyle);
        else
            sprintf (strPhraseCratyle,"%s!", strPhraseCratyle);
    }

    printf("strPhraseCratyle : %s\n", strPhraseCratyle);
//    strcpy(strPhrase, strPhraseCratyle);

    return ERROR_NO;


//    int fin_boucl = 0; /* =1 lorsque le point à été détecter (car fin de la phrase) */

//    int separateur = 0; /*pour eviter deux ou plus espaces concecutif*/
/*
    char strCratyleMot[200]="", strMot[200]="";
    int i=0,j=0,n=0,w=1,m=0;

    char strCratylePhrase[CRATYLE_TEXTMAX]="";

    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

    while(strPhrase[i] !='\0')
    {
       ++nc;
    //           if (c == '\n')
    //               ++nl;
//TODO verfifier tout les caracteres. isalpha
        if (strPhrase[i]== ' ' || strPhrase[i]== ','|| strPhrase[i]== '.' || strPhrase[i]== ';'|| strPhrase[i]== ':' || strPhrase[i]== '!'|| strPhrase[i]== '?'|| strPhrase[i]=='(' || strPhrase[i]==')' || strPhrase[i]== '['|| strPhrase[i]== ']'|| strPhrase[i]== '{'|| strPhrase[i]== '}' || strPhrase[i]=='"'  )
        {
            state = OUT;
            separateur++;
            n = 0;
        }
        else
        {
            iTailleDuMot++;
            if (state == OUT)
            {

                for (j = 0 ; j < iTailleDuMot ; j++)
                   strMot[j] = strPhrase[i-(iTailleDuMot+separateur)+j];

//                strncpy(strMot, strPhrase[i-(iTailleDuMot+separateur)], i-iTailleDuMot-separateur);
                state = IN;
                ++nw;
                iTailleDuMot=0;
            }

        }
        i++;
    }

*/

   #define IN   1  /* inside a word */
   #define OUT  0  /* outside a word */
/*
    while(strPhrase[i]!='\0')
    {



        if(strPhrase[i]== ' ' || strPhrase[i]== ','|| strPhrase[i]== '.' || strPhrase[i]== ';'|| strPhrase[i]== ':' || strPhrase[i]== '!'|| strPhrase[i]== '?'|| strPhrase[i]=='(' || strPhrase[i]==')' || strPhrase[i]== '['|| strPhrase[i]== ']'|| strPhrase[i]== '{'|| strPhrase[i]== '}' || strPhrase[i]=='"'  )
        {
            if(!separateur)
            {
                separateur = 1;
                if(n)
                {
                    strMot[n]='\0';
                //printf("\n %s",t);
                    n=-1;
                    printf("Cratylation : %s", strMot);
                    if(CratyleMot(strMot, strCratyleMot))  w++;

                    sprintf(strCratylePhrase, "%s%s%c", strCratylePhrase, strCratyleMot, strPhrase[i]);
                    m=1;
                }
            }
        }
        else
        {
            separateur = 0;
            strMot[n++]=strPhrase[i];
        }
        i++;

    }
    if (i)
    {
        if(m) n++;
        strMot[n]='\0';
        printf("Cratylation : %s\n", strMot);
        if(CratyleMot(strMot, strCratyleMot))  w++;
        sprintf(strCratylePhrase, "--%s%s%c", strCratylePhrase, strCratyleMot, strPhrase[i]);

        printf(strCratylePhrase);
    }

*/

    return ERROR_NO;
}



