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


//#define DEBUG_FAKE_MINITEL2

#define DEBUG_MINITEL1
#define DEBUG_MINITEL2

// #define DEBUG_CRATYLE

volatile int STOP = FALSE;
const unsigned char PLATON[]="Platon";
const unsigned char SOCRATE[]="Socrate:";
const unsigned char CRATYLE[]="Cratyle:";
const unsigned char HERMOGENE[]="Hermogene:";

// extern const char* CratyleBaseGenreNombre[CRATYLE_DICO_INDEX][CRATYLE_DICO_SYNO];
extern char* CratyleDico[CRATYLE_DICO_INDEX][CRATYLE_DICO_SYNO];


int TestImprime()
{
        int iFdImprim1Test = 0;
    struct termios oldtioImprim1Test;
//    char *message2 = "message simple ";
//	char *message = "Socrate y combat deux thèses opposées sur la vérité du langage, celle d'Hermogène, qui soutient que les noms sont justes en \
//fonction d'une convention et celle de Cratyle, qui soutient que les noms sont justes par nature. Derrière ces deux thèses se  \
//cachent deux quêtes du sens. Il y a en filigrane de la pensée d'Hermogène la thèse protagoréenne de \"l'homme mesure de toute \
//chose\". Appliquée au langage, cette thèse affirme que c'est l'homme qui donne un sens à toute chose. La vérité du monde \
//appartient dès lors au monde social humain. À l'inverse, Cratyle, en affirmant la justesse naturelle des noms, propose une \
//nature qui a un sens, mais qui échappe aux hommes : tout est dans un flux perpétuel, un héraclitéisme poussé à l'absurde. Pour \
//récuser ces deux visions du monde, Socrate va faire exploser l'adéquation jusque-là idyllique entre mot et nom.\nContre \
//Hermogène, Socrate établit que les mots sont des instruments qui servent à nommer la réalité. Ils ont donc un lien avec elle :\
//les choses ont une existence qui ne dépend pas de nous et donc les actes qui s'y rapportent ne dépendent pas non plus de nous \
//(386e). Or, parler est un acte et nommer une partie de cet acte qui se rapporte aux choses. Nommer correspond donc à la \
//propriété des choses de pouvoir nommer ou être nommées (387d). Le nom est cet instrument qui permet de nommer (388 b, c). \
//C'est le législateur qui établit les noms et compose, à partir de syllabes, le nom qui correspond à une chose. Le dialecticien, \
//qui se sert de noms pour interroger et répondre pourra juger de l'ouvrage (390d). Cette justesse du nom est retrouvée grâce à \
//l'étymologie (393c et suivant), qui retrouve dans les noms le logos. Par exemple, les barbares admirant les astres du ciel \
//toujours en train de courir (thein) appelèrent les dieux theos. De mots en mots, l'étymologicien remonte aux \"noms primitifs\" \
//(421). Ces noms, par les lettres et les syllabes, imitent la nature d'un objet pour la nommer (423e). Par exemple, le ρ (rhô) \
//qui suggère l'expression du mouvement (426a), le δ (delta) ou le τ (tau) pour l'enchaînement ou l'arrêt (427b), etc. \nCratyle \
//approuve les propos de Socrate, mais refuse de considérer que des noms puissent être mal établis : si des noms sont mal \
//établis, ils ne sont plus que des éclats de voix (430a). Socrate corrige alors son paradigme. Les mots sont plus que des \
//instruments qui servent à nommer la réalité: ils sont comme des images qui renvoient à la réalité (430a). D'où des erreurs \
//d'attribution possibles. En effet, une image n'imite jamais parfaitement une chose (sinon ce n'est plus une image, mais une \
//copie, qui devient indépendante de son original). De même pour les noms, si le nom de Cratyle imitait parfaitement Cratyle, \
//il n'y aurait plus un mais deux Cratyle. Comme une icône, le nom doit conserver son statut d'image: il possède donc des \
//imperfections nécessaires pour ne pas redoubler les choses d'une autre réalité faites de mots (mythe des deux Cratyle). Le \
//nom ne doit pas être exactement la chose, mais simplement désigner les caractéristiques d'une chose(433c) ou la chose en soi.\
//\nDevant Cratyle, qui peine à l'admettre, Socrate montre dans les noms la part de convention qu'il y a: l'usage parfois se \
//substitue à la ressemblance pour désigner une chose. Alors que rhô exprime la dureté et sigma et lambda la douceur, les \
//Athéniens disent sklêrotês et les gens d'Érétrie sklêrotêr pour dire \"dureté\" (431c-435c).\nComment connaître dès lors les \
//choses à partir des noms comme le prétend Cratyle ? Le premier qui a établi les noms avait-il une idée juste des choses ? Mais \
//comment expliquer que les noms suggèrent avec équivocité tantôt le repos tantôt le mouvement ? Comment pouvait-il connaître \
//les choses, alors que leur nom n'existait pas encore si c'est leur nom qui les faisait connaître ? (435d-439b) ? Cratyle \
//répond en invoquant les dieux comme fondement des noms. Socrate refuse cela et demande d'aller aux choses directement, sans \
//les noms pour les connaître (438e) : les noms n'ont ni un sens naturel ni un sens conventionnel et pourtant, ils sont \
//traversés par une exigence de sens. Ce n'est donc pas sur le mot, mais sur le sens que doit porter la recherche. On passe \
//ainsi du Cratyle au Théétète.";


        if((iFdImprim1Test = OuvrirConnectionImprimante(IMPRIM1_MODEMDEVICE, &oldtioImprim1Test)) == ERROR_GENERIC)
        {
            perror("OuvrirConnectionImprim 1 failed!");
            return ERROR_GENERIC;
        }

        MINITELEnvoyerCaractere(iFdImprim1Test, MINITEL_EFFACEMENT_DE_PAGE);

        int i;

        for (i =0; i < 600 ; i++)
        {
          CratyleImprime(CratyleDico[i][0], iFdImprim1Test);
          usleep(25000);//on attend 0.25 secondes
        }


        //CratyleImprime(message, iFdImprim1Test);

        //int iScan;
        //scanf("%d", &iScan);

        //MINITELEnvoyerCaractere(iFdImprim1Test, MINITEL_EFFACEMENT_DE_PAGE);

        //CratyleImprime(message2, iFdImprim1Test);

        if (iFdImprim1Test) FermerConnection(iFdImprim1Test, &oldtioImprim1Test );

        return ERROR_NO;
}

int TestOuverture ()
{

            int fdMinitel1Modem;
            struct termios oldtioMinitel1;

            if((fdMinitel1Modem = OuvrirConnectionMinitel(MINITEL1_MODEMDEVICE, &oldtioMinitel1)) == ERROR_GENERIC)
            {
                perror("OuvrirConnectionMinitel 1 failed!");
                return ERROR_GENERIC;
            }

                                 int fdMinitel2Modem;
                struct termios oldtioMinitel2;

                if((fdMinitel2Modem = OuvrirConnectionMinitel(MINITEL2_MODEMDEVICE, &oldtioMinitel2)) == ERROR_GENERIC)
                {
                    perror("OuvrirConnectionMinitel 2 failed!");
                    return ERROR_GENERIC;
                }

/*
                int fdMinitel3Modem;
                struct termios oldtioMinitel3;
*/
/*TODOIMPRIM
                if((fdMinitel3Modem = OuvrirConnectionMinitel(MINITEL3_MODEMDEVICE, &oldtioMinitel3)) == ERROR_GENERIC)
                {
                    perror("OuvrirConnectionMinitel 3 failed!");
                    return ERROR_GENERIC;
                }
*/

    printf("TestOuverture chat 1 %i \n", fdMinitel1Modem);
    printf("TestOuverture chat 2 %i \n", fdMinitel2Modem);
//    printf("TestOuverture chat 3 %i \n", fdMinitel3Modem);


AfficherAttenteCratyle(fdMinitel1Modem);
AfficherAttenteCratyle(fdMinitel2Modem);
//AfficherAttenteCratyle(fdMinitel3Modem);


return ERROR_NO;
}

bool TestGenre()
{
    bool result = false;

    result = CratyleGenreIdentique("cession","apostasie"); // F & F
    result = CratyleGenreIdentique("cession","bradage"); // F & M
    result = CratyleGenreIdentique("bradage","voisinage"); // M & M

    result = CratyleGenreIdentique("bradage", "banlieue"); // M & F

    result = CratyleGenreIdentique("couramment", "banlieue"); // N & F

    result = CratyleGenreIdentique("defaillant", "largement"); // M & N

    return result;
}


bool TestNombre()
{
    bool result = false;



    return result;
}

void TestSalopeDeCigale ()
{
    char strSalopeDeCigale[CRATYLE_TEXTMAX]= "salope de cigale", strCratyle[CRATYLE_TEXTMAX]= "";
    int j;
    for (j = 0; j++ < 100;)
    {
        Cratylation(strSalopeDeCigale, strCratyle, 0);
        printf("%s ",strCratyle);
    }
}

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
