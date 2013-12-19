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

#include "cratyle.h"
#include "libcratyle.h"
#include "libminitel.h"

//#include "testunitaire.h"

//#define DEBUG_FAKE_MINITEL2

#define CRATYLE_IMPRIME

#define DEBUG_MINITEL1
#define DEBUG_MINITEL2

// #define DEBUG_CRATYLE

volatile int STOP = FALSE;
const unsigned char PLATON[]="Platon";
const unsigned char SOCRATE[]="Socrate:";
const unsigned char CRATYLE[]="Cratyle:";
const unsigned char HERMOGENE[]="Hermogene:";



/**
 *  main
 *  @Return :
 */
int main()
{

//    char strTEst[CRATYLE_TEXTMAX];
/////////////////////////////////////////////BACASABLE
//    TestOuverture ();
//    TestGenre();
//    TestImprime ();

//    return ERROR_NO;


//    int iBaseGenreNombreIndex;
//    CratyleNombre ("futes", &iIndex);


//    Cratylation(" f coucou:fkj, - j'g h dff", strTEst);

//    sleep(10);

//    TestSalopeDeCigale();
//    char* strMotSingulier = NULL;

//        if ((CratyleNombre("fuItes", &iBaseGenreNombreIndex)) == pluriel)
//            strMotSingulier = CratyleMotSingulier(iBaseGenreNombreIndex);

//    char* strTemp;
//    strTemp = CratyleMotPluriel("fuite");
//    if(strTemp) free(strTemp);


    //return 1;
////////////////////////////////////////////////////////////////////////////////////////////
    CratyleInit();

    //Generation de l'aleatoire
	srand(time(NULL));

    pid_t pid_Minitel1, pid_Minitel2, pid_Minitel3;
    int fdMinitel1[2], fdMinitel2[2], fdMinitel3[2];
    int fdMinitel1Out[2], fdMinitel2Out[2], fdMinitel3Out[2];

// Ouverture de la communication inter processus
    if(pipe(fdMinitel1)==-1 || pipe(fdMinitel2)==-1 || pipe(fdMinitel3)==-1)
    {
        perror("pipe failed!");
        return 1;
    }
/*
Set the read non blocking
*/
    int flags = fcntl(fdMinitel1[0], F_GETFL, 0);
    if (fcntl (fdMinitel1[0], F_SETFL, flags | O_NONBLOCK) == -1)
    {
		perror("fnctl : fdMinitel1");
		return ERROR_GENERIC;
    }

    flags = fcntl(fdMinitel2[0], F_GETFL, 0);
    if (fcntl (fdMinitel2[0], F_SETFL, flags | O_NONBLOCK) == -1)
    {
		perror("fnctl : fdMinitel2");
		return ERROR_GENERIC;
    }

    flags = fcntl(fdMinitel3[0], F_GETFL, 0);
    if (fcntl (fdMinitel3[0], F_SETFL, flags | O_NONBLOCK) == -1)
    {
		perror("fnctl : fdMinitel3");
		return ERROR_GENERIC;
    }

// Ouverture de la communication inter processus OUT

    if(pipe(fdMinitel1Out)==-1 || pipe(fdMinitel2Out)==-1 || pipe(fdMinitel3Out)==-1)
    {
        perror("pipeOut failed!");
        return ERROR_GENERIC;
    }

/*
Set the read non blocking
*/
    flags = fcntl(fdMinitel1Out[0], F_GETFL, 0);
    if (fcntl (fdMinitel1Out[0], F_SETFL, flags | O_NONBLOCK) == -1)
    {
		perror("fnctl : fdMinitel1Out");
		return ERROR_GENERIC;
    }
    flags = fcntl(fdMinitel2Out[0], F_GETFL, 0);
    if (fcntl (fdMinitel2Out[0], F_SETFL, flags | O_NONBLOCK) == -1)
    {
		perror("fnctl : fdMinitel2Out");
		return ERROR_GENERIC;
    }
    flags = fcntl(fdMinitel3Out[0], F_GETFL, 0);
    if (fcntl (fdMinitel3Out[0], F_SETFL, flags | O_NONBLOCK) == -1)
    {
		perror("fnctl : fdMinitel3Out");
		return ERROR_GENERIC;
    }



    printf("Démarrage du programme\n");
    pid_Minitel1=fork();

    if(pid_Minitel1==-1)
    {
        perror("Minitel1 fork failed!");
        return ERROR_GENERIC;
    }

    if(pid_Minitel1==0)
    {
        pid_Minitel2=fork();
        if(pid_Minitel2==-1)
        {
            perror("Minitel2 fork failed!" );
            return ERROR_GENERIC;
        }

        if(pid_Minitel2==0)
        {
            pid_Minitel3=fork();
            if(pid_Minitel3==-1)
            {
                perror("Minitel3 fork failed!" );
                return ERROR_GENERIC;
            }

            if(pid_Minitel3==0)
            {
                printf("I am Minitel3\n");
                usleep(2500);//on attend 0.025 secondes
                printf("Minitel3, wait ok\n");

                int fdMinitel3Modem;
                struct termios oldtioMinitel3;

                if((fdMinitel3Modem = OuvrirConnectionMinitel(MINITEL3_MODEMDEVICE, &oldtioMinitel3)) == ERROR_GENERIC)
                {
                    perror("OuvrirConnectionMinitel 3 failed!");
                    return ERROR_GENERIC;
                }

                InitChat(fdMinitel3Modem);

                printf("Minitel3, ouvrir chat\n");

                OuvrirChat(fdMinitel3Modem, fdMinitel3, fdMinitel3Out, SOCRATE);

                FermerConnection(fdMinitel3Modem, &oldtioMinitel3);

                close(fdMinitel3[1]);  //close write side,
                close(fdMinitel3[0]);  //close read side

                printf("Minitel3 exit normal\n");
                return ERROR_NO; // actions grandson
            }
            else
            {
#ifdef DEBUG_FAKE_MINITEL2
                printf("I am (fAke) Minitel2\n");

                char bufferM1[1];

                printf("(fAke) Minitel2 : avant read");
                read(fdMinitel2Out[0],bufferM1,1);
                printf("(fAke) Minitel2 : apres read");
                while((int)bufferM1[0] != 10)
                {
                    printf("(fAke) Minitel2 : %c\n", bufferM1[0]);
                    usleep(250000);//on attend .025 secondes
                    read(fdMinitel2Out[0],bufferM1,1);
                }

#else
                printf("I am Minitel2\n");
                usleep(2500);//on attend 0.025 secondes
                printf("Minitel2, wait ok\n");

                int fdMinitel2Modem;
                struct termios oldtioMinitel2;

                if((fdMinitel2Modem = OuvrirConnectionMinitel(MINITEL2_MODEMDEVICE, &oldtioMinitel2)) == ERROR_GENERIC)
                {
                    perror("OuvrirConnectionMinitel 2 failed!");
                    return ERROR_GENERIC;
                }

                InitChat(fdMinitel2Modem);

                //MINITELBloquerClavier (fdMinitel2Modem, TRUE);

                OuvrirChat(fdMinitel2Modem, fdMinitel2, fdMinitel2Out, HERMOGENE);

                FermerConnection(fdMinitel2Modem, &oldtioMinitel2);

                close(fdMinitel2[1]);  //close write side,
                close(fdMinitel2[0]);  //close read side
#endif

                printf("Minitel2 exit normal\n");
                return ERROR_NO;/*actions grandson*/
            }
        }
        else
        {
#ifdef DEBUG_MINITEL2
        printf("pid Minitel2 %d\n", pid_Minitel2);
#endif
            printf("I am Minitel1\n");
            usleep(2500);//on attend 0.025 secondes
            printf("Minitel1, wait ok\n");

            int fdMinitel1Modem;
            struct termios oldtioMinitel1;

            if((fdMinitel1Modem = OuvrirConnectionMinitel(MINITEL1_MODEMDEVICE, &oldtioMinitel1)) == ERROR_GENERIC)
            {
                perror("OuvrirConnectionMinitel 1 failed!");
                return ERROR_GENERIC;
            }

            InitChat(fdMinitel1Modem);

            OuvrirChat(fdMinitel1Modem, fdMinitel1, fdMinitel1Out, CRATYLE);

            FermerConnection(fdMinitel1Modem, &oldtioMinitel1);

            write(fdMinitel1[1],CRATYLE_ESCAPE_SENTENCE,strlen(CRATYLE_ESCAPE_SENTENCE));

            close(fdMinitel1[1]);  //close write side
            close(fdMinitel1[0]);  //close read side

            ///////pipe2////
//            close(fdMinitel2[0]);  //close read side
//            dup2(fdMinitel2[1],1); //connect write with stdout/*it stops here -can't display "ok!"*/
//            printf("ok!\n");
//            close(fdMinitel2[1]);  //close write side

//            execlp("wc","wc",(char*)0);
            printf("Minitel1, finito!\n");
            return ERROR_NO;
        }
    }
    else
    {
#ifdef DEBUG_MINITEL1
/* infos : http://www.sourceware.org/gdb/onlinedocs/gdb/Forks.html*/
        printf("pid Minitel1 %d\n", pid_Minitel1);
        sleep(1);
#endif

        printf("I am the CRATYLE Serveur\n");
//        usleep(25000);//on attend 0.025 secondes
        printf("Cratyle,wait ok\n");

        char bufferM1[1], bufferM2[1], bufferM3[1];
        char strMinitel1[CRATYLE_TEXTMAX]= "", strMinitel2[CRATYLE_TEXTMAX]= "", strMinitel3[CRATYLE_TEXTMAX]= "";
//        char* strMinitelTok = NULL;
        char strMinitel1Cratyle[CRATYLE_TEXTMAX]= "", strMinitel2Cratyle[CRATYLE_TEXTMAX]= "", strMinitel3Cratyle[CRATYLE_TEXTMAX]= "";
        char strMinitel1CratyleAuteur[CRATYLE_TEXTMAX]= "", strMinitel2CratyleAuteur[CRATYLE_TEXTMAX]= "", strMinitel3CratyleAuteur[CRATYLE_TEXTMAX]= "";
        int iIndexMinitel1, iIndexMinitel2, iIndexMinitel3;
        int iNbCaracteresRecus;

        int iFdImprim1;
        iFdImprim1 = 0;
        struct termios oldtioImprim1;


#ifdef CRATYLE_IMPRIME

        if((iFdImprim1 = OuvrirConnectionImprimante(IMPRIM1_MODEMDEVICE, &oldtioImprim1)) == ERROR_GENERIC)
        {
            perror("OuvrirConnectionImprim 1 failed!");
            return ERROR_GENERIC;
        }
        // on efface ce qui pourrait etre dans le buffer du minitel
        MINITELEnvoyerCaractere(iFdImprim1, MINITEL_EFFACEMENT_DE_PAGE);

#endif

        iIndexMinitel1 = iIndexMinitel2 = iIndexMinitel3 = 0;


        while (STOP == FALSE)
        {
#ifdef DEBUG_CRATYLE
            printf("CRATYLE : avant lire\n");
            usleep(100000);//on attend
#endif
            //TODO propre : passer les trois code identique en boucle !

            iNbCaracteresRecus = read(fdMinitel1[0],bufferM1,1); //on lit ce qu'il y a dans l'entree du pipe du Minitel1
            if (iNbCaracteresRecus == -1 && errno == EAGAIN)
            {
#ifdef DEBUG_CRATYLE
                printf ("Rien a lire Minitel1\n");
#endif
//                sleep(1);//on attend 0.025 secondes
            }
            else
            {
                if((int)bufferM1[0] != 10 && (iIndexMinitel1 + 2) < CRATYLE_TEXTMAX)
                    strMinitel1[iIndexMinitel1++] = bufferM1[0];
                else
                {
                    // caractere de chaine pour printf&co
                    strMinitel1[iIndexMinitel1] = '\0';

                    printf("CRATYLE : strMinitel1 %s : %i : strlen %i\n", strMinitel1, iIndexMinitel1, strlen(strMinitel1));

                    if (strncmp (strMinitel1, CRATYLE_ESCAPE_SENTENCE, strlen(CRATYLE_ESCAPE_SENTENCE)) == 0) //
                    {
                        write(fdMinitel2Out[1], strMinitel1, strlen(strMinitel1)); //PRise direct sur m2
                        write(fdMinitel3Out[1], strMinitel1, strlen(strMinitel1)); //PRise direct sur m3

                        STOP = TRUE;
                        printf("CRATYLE : merci pour la conversation.\nà la prochaine.... ");
                    }
                    else
                    {
                        Cratylation(strMinitel1, strMinitel1Cratyle, iFdImprim1);

                        strcpy(strMinitel1CratyleAuteur, (const char*)CRATYLE);
                        strcat (strMinitel1CratyleAuteur, strMinitel1Cratyle );

                        write(fdMinitel2Out[1], strMinitel1CratyleAuteur, strlen(strMinitel1CratyleAuteur)); //PRise direct sur m2
                        write(fdMinitel3Out[1], strMinitel1CratyleAuteur, strlen(strMinitel1CratyleAuteur)); //PRise direct sur m3

                        //memset(strMinitel1, '\0', sizeof(strMinitel1));
                        //memset(strMinitel1Cratyle, '\0', sizeof(strMinitel1Cratyle));
                        iIndexMinitel1=0;
                    }
                }
            }
//            usleep(100000);//on attend
            iNbCaracteresRecus = read(fdMinitel2[0],bufferM2,1); //on lit ce qu'il y a dans l'entree du pipe du Minitel2
            if (iNbCaracteresRecus == -1 && errno == EAGAIN)
            {
    #ifdef DEBUG_CRATYLE
                printf ("Rien a lire Minitel2\n");
    #endif
//                sleep(1);//on attend 0.025 secondes
            }
            else
            {
                if((int)bufferM2[0] != 10 && (iIndexMinitel2 + 2) < CRATYLE_TEXTMAX)
                    strMinitel2[iIndexMinitel2++] = bufferM2[0];
                else
                {
                    strMinitel2[iIndexMinitel2] = '\0';

                printf("CRATYLE : strMinitel2 %s : %i : strlen %i\n", strMinitel2, iIndexMinitel2, strlen(strMinitel2));

                    if (strncmp (strMinitel2, CRATYLE_ESCAPE_SENTENCE, strlen(CRATYLE_ESCAPE_SENTENCE)) == 0) //
                    {
                        write(fdMinitel1Out[1], strMinitel2, strlen(strMinitel2)); //PRise direct sur m1
                        write(fdMinitel3Out[1], strMinitel2, strlen(strMinitel2)); //PRise direct sur m3

                        STOP = TRUE;
                        printf("CRATYLE : merci pour la conversation.\nà la prochaine.... ");

                    }
                    else
                    {
                        Cratylation(strMinitel2, strMinitel2Cratyle, iFdImprim1);

                        strcpy(strMinitel2CratyleAuteur, (const char*)HERMOGENE);
                        strcat (strMinitel2CratyleAuteur, strMinitel2Cratyle );

                        write(fdMinitel1Out[1], strMinitel2CratyleAuteur, strlen(strMinitel2CratyleAuteur)); //PRise direct sur m1
                        write(fdMinitel3Out[1], strMinitel2CratyleAuteur, strlen(strMinitel2CratyleAuteur)); //PRise direct sur m3

                        //memset(strMinitel2, '\0', sizeof(strMinitel2));
                        //memset(strMinitel2Cratyle, '\0', sizeof(strMinitel2Cratyle));
                        iIndexMinitel2=0;
                    }
                }
            }

            iNbCaracteresRecus = read(fdMinitel3[0],bufferM3,1); //on lit ce qu'il y a dans l'entree du pipe du Minitel3
            if (iNbCaracteresRecus == -1 && errno == EAGAIN)
            {
    #ifdef DEBUG_CRATYLE
                printf ("Rien a lire Minitel3\n");
    #endif
//                sleep(1);//on attend 0.025 secondes
            }
            else
            {
                if((int)bufferM3[0] != 10 && (iIndexMinitel3 + 2) < CRATYLE_TEXTMAX)
                    strMinitel3[iIndexMinitel3++] = bufferM3[0];
                else
                {
                    strMinitel3[iIndexMinitel3] = '\0';

                    printf("CRATYLE : strMinitel3 %s : %i : strlen %i\n", strMinitel3, iIndexMinitel3, strlen(strMinitel3));

                    if (strncmp (strMinitel3, CRATYLE_ESCAPE_SENTENCE, strlen(CRATYLE_ESCAPE_SENTENCE)) == 0) //
                    {
                        write(fdMinitel1Out[1], strMinitel3, strlen(strMinitel3)); //PRise direct sur m1
                        write(fdMinitel2Out[1], strMinitel3, strlen(strMinitel3)); //PRise direct sur m2

                        STOP = TRUE;
                        printf("CRATYLE : merci pour la conversation.\nà la prochaine.... ");

                    }
                    else
                    {
                        Cratylation(strMinitel3, strMinitel3Cratyle, iFdImprim1);

                        strcpy(strMinitel3CratyleAuteur, (const char*)SOCRATE);
                        strcat (strMinitel3CratyleAuteur, strMinitel3Cratyle );

                        write(fdMinitel1Out[1], strMinitel3CratyleAuteur, strlen(strMinitel3CratyleAuteur)); //PRise direct sur m1
                        write(fdMinitel2Out[1], strMinitel3CratyleAuteur, strlen(strMinitel3CratyleAuteur)); //PRise direct sur m2

                        //memset(strMinitel3, '\0', sizeof(strMinitel3));
                        //memset(strMinitel3Cratyle, '\0', sizeof(strMinitel3Cratyle));
                        iIndexMinitel3=0;
                    }
                }
            }

#ifdef DEBUG_CRATYLE
//            printf("CRATYLE : lire M1: %i , %c\n", bufferM1[0], bufferM1[0]);
//            printf("CRATYLE : lire M2: %i , %c\n", bufferM2[0], bufferM2[0]);
#endif
//            sleep(1);//on attend 1


//              if (memcmp(bufferM1[0], 'z', 1) == 0 ) STOP = TRUE;

        }

        if (iFdImprim1) FermerConnection(iFdImprim1, &oldtioImprim1 );


        printf("CRATYLE : Attente de le minitel.....\n");
        usleep(400000);//on attend
        printf("CRATYLE : Attente de le autre minitel.....\n");
        usleep(800000);//on attend

        printf("CRATYLE fin\n");


//        execlp("wc","wc",(char*)0);
    //    return 0;/*the parent*/
    }

    return ERROR_NO;

}
