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


/**
 *
 *  @Param[in,out]
 *  @Return
 */



/**
 *   OuvrirConnection
 *   @Param[in] iFileDescriptor , Descripteur de fichier
 *   @Param[out] *oldtio , structure pour acceuillir ancienne valeur port
 *   @Return void
 */
void OuvrirConnection (int iFileDescriptor, struct termios* oldtio)
{
    struct termios newtio;

    tcgetattr(iFileDescriptor,oldtio); /* save current serial port settings */
    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

    //newtio.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits

    /*
    BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
    CRTSCTS : output hardware flow control (only used if the cable has
            all necessary lines. See sect. 7 of Serial-HOWTO)
    CS8     : 8n1 (8bit,no parity,1 stopbit)
    CS7     : 7n1 (7bit,no parity,1 stopbit)
    CLOCAL  : local connection, no modem contol
    CREAD   : enable receiving characters
    */
    newtio.c_cflag = BAUDRATE | CS7 | CLOCAL | CREAD;

    /*
    IGNPAR  : ignore bytes with parity errors
    ICRNL   : map CR to NL (otherwise a CR input on the other computer
            will not terminate input)
    otherwise make device raw (no other input processing)
    */
    newtio.c_iflag = INPCK | ICRNL;



	/* Parité paire. */
	newtio.c_cflag |= PARENB;



	/* newtio.c_cflag &= CSTOPB; */



	/* 2 bits de stop. */
	newtio.c_cflag |= CSTOPB;



    /*
     Raw output.
    */
     newtio.c_oflag = 0;

    /*
      ICANON  : enable canonical input
      disable all echo functionality, and don't send signals to calling program
    */
     newtio.c_lflag = ICANON;

    /*
      initialize all control characters
      default values can be found in /usr/include/termios.h, and are given
      in the comments, but we don't need them here
    */
     newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
     newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
     newtio.c_cc[VERASE]   = 0;     /* del */
     newtio.c_cc[VKILL]    = 0;     /* @ */
     newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
     newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
     newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
     newtio.c_cc[VSWTC]    = 0;     /* '\0' */
     newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
     newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
     newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
     newtio.c_cc[VEOL]     = 0;     /* '\0' */
     newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
     newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
     newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
     newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
     newtio.c_cc[VEOL2]    = 0;     /* '\0' */

    /*
    now clean the modem line and activate the settings for the port
    */
    tcflush(iFileDescriptor, TCIFLUSH);
    tcsetattr(iFileDescriptor,TCSANOW,&newtio);
}

/**
 *   OuvrirConnectionMinitel
 *   @Param : strMinitelPort , port de /tty/USBx
 *   @Param : *oldtio , structure pour acceuillir ancienne valeur port
 *   @Return : Descripteur de fichier vers Minitel sinon ERROR_GENERIC
 */
int OuvrirConnectionMinitel (char* strMinitelPort, struct termios* oldtio)
{
    int fd;

/*
Open modem device for reading and writing and not as controlling tty
because we don't want to get killed if linenoise sends CTRL-C.
*/
    fd = open(strMinitelPort, O_RDWR | O_NOCTTY );
    if(fd < 0)
	{
		perror("OuvrirConnectionMinitel : strMinitelPort");
		return ERROR_GENERIC;
	}

    OuvrirConnection(fd, oldtio);

    return fd;
}

/**
 *   OuvrirConnectionImprimante
 *   @Param : strImprimantePort , port de /tty/USBx
 *   @Param : *oldtio , structure pour acceuillir ancienne valeur port
 *   @Return : Descripteur de fichier vers Imprimante sinon ERROR_GENERIC
 */
int OuvrirConnectionImprimante (char* strImprimantePort, struct termios* oldtio)
{
    int fd;

/*
Open modem device for reading and writing and not as controlling tty
because we don't want to get killed if linenoise sends CTRL-C.
*/
    fd = open(strImprimantePort, O_WRONLY  | O_NOCTTY );
    if(fd < 0)
	{
		perror("OuvrirConnectionImprimante : strImprimantePort");
		return ERROR_GENERIC;
	}

    OuvrirConnection(fd, oldtio);

    return fd;
}

/**
 *  FermerConnection
 *  @Param : fd, Descripteur de fichier de la connexion
 *  @Return :
 */
void FermerConnection (int fd, struct termios* oldtio)
{
    /* restore the old port settings */
    tcsetattr(fd,TCSANOW,oldtio);
}


/**
 *  InitChat
 *  @Param : iFdMinitel, Descripteur de fichier du minitel
 *  @Return : void
 */
void InitChat (int iFdMinitel)
{
	printf ("Vidage de l'écran...\n");
	MINITELEnvoyerCaractere(iFdMinitel, MINITEL_EFFACEMENT_DE_PAGE);
	printf (" -\n");
	printf ("Intro...\n");
	MINITELCurseurXY(iFdMinitel, 1, 1);
	int k =0;
/*    for(k = 0; k < 40; k++)
    {
        MINITELEnvoyerCaractere(fd, '_');
    }

*/	MINITELCurseurXY(iFdMinitel, 2, 1);
	MINITELChangerAttribut(iFdMinitel, MINITEL_DOUBLE_LARGEUR_DOUBLE_HAUTEUR);
	MINITELEnvoyerTexte(iFdMinitel, (unsigned char*)CRATYLE_VERSION_TEXTE);
	MINITELChangerAttribut(iFdMinitel, MINITEL_TAILLE_NORMALE);
	MINITELCurseurXY(iFdMinitel, 3, 1);
    for(k = 0; k < MINITEL_TAILLE_X; k++)
    {
        MINITELEnvoyerCaractere(iFdMinitel, '_');
    }
}

/**
 *  OuvrirChat
 *  @Param[in] le descripteur de fichier du minitel
 *  @Param[in] le pipe d'ecriture, bouche vers serveur
 *  @Param[in] le pipe de lecture, oreille sur serveur
 *  @Param[in] le philosophe
 *  @Return :
 */
int OuvrirChat (int iFdMinitel, int* fdPipeOut, int* fdPipeIn, const unsigned char* strPhilosophe)
{
    int STOP;
    int k;
    unsigned char LigneEnCours = 1;
    int iLignesTexteMinitel = 0;
    int iLongueurPhilosophe, iLongueurPrefixe;

    int iNbCaracteresRecus, iCalculLignes;
    char bufMinitel[CRATYLE_TEXTMAX];
//    char bufOreille[CRATYLE_TEXTMAX];

    iLongueurPhilosophe = strlen((const char*)strPhilosophe);
    iLongueurPrefixe = strlen (PREFIXE_AUTEUR);

    STOP = FALSE;
    printf("ouvrir chat %i \n", iFdMinitel);

    AfficherAttenteCratyle(iFdMinitel);

    unsigned char strServeur[CRATYLE_TEXTMAX];
    int iLnMessage = 0;
/* save fd flags*/
    int flags = fcntl(iFdMinitel, F_GETFL, 0);

/* on tourne tant que l'on reste : CRATYLE_ESCAPE_SENTENCE */
     while (STOP == FALSE)
     {

/* ici traitement de l'oreille minitel */

#ifdef DEBUG_CRATYLE
        printf (" Attente lecture M : %i\n",iFdMinitel );
#endif
/* set NONBLOCK flag afin que la lecture soit non bloquante*/
        fcntl (iFdMinitel, F_SETFL, flags | O_NONBLOCK);
        iNbCaracteresRecus = read(iFdMinitel,bufMinitel,CRATYLE_TEXTMAX);
/* restore fd flags*/
        fcntl (iFdMinitel, F_SETFL, flags);


        if (iNbCaracteresRecus == -1 && errno == EAGAIN)
        {
#ifdef DEBUG_CRATYLE
            printf ("Rien a lire sur le minitel\n");
#endif
            usleep(25000);
        }
        else
        {

            MINITELEnvoyerCaractere(iFdMinitel, MINITEL_CURSEUR_DESACTIVE);
            if(((iNbCaracteresRecus == 2) && (bufMinitel[0] != 0x20)) || ((iNbCaracteresRecus >= 3) && (bufMinitel[0] >= 0x20)))
            {
                // caractere de chaine pour printf&co
                bufMinitel[iNbCaracteresRecus] = '\0';

                //calcul nombre de ligne du texte
                iLignesTexteMinitel = 1;
                iCalculLignes = iNbCaracteresRecus-1 + iLongueurPhilosophe;

                while(iCalculLignes-MINITEL_TAILLE_X >= 0)
                {
                    iCalculLignes = MINITEL_TAILLE_X - iCalculLignes;
                    printf("LOCAL:CalculLignes : %d\n", iCalculLignes);

                    iLignesTexteMinitel++;
                }

                printf("LOCAL:LignesTexteMinitel : %d -- CalculLignes %d\n", iLignesTexteMinitel, iCalculLignes);

                MINITELCurseurXY(iFdMinitel, MISEENPAGE_PIED_DE_CHAT_INFO, 3);
                MINITELEnvoyerTexte(iFdMinitel, (const unsigned char*)"Envoi...              ");
/*
                for(k = 7; k < iNbCaracteresRecus; k++)
                {
                    MINITELEnvoyerCaractere(iFdMinitel, ' ');
                }
*/
                //test du bas de la piece du chat
                LigneEnCours++;
                if(LigneEnCours > MISEENPAGE_HAUTEUR_DE_CHAT)
                {
                    LigneEnCours = 2;
                }
                MINITELCurseurXY(iFdMinitel, (LigneEnCours + 2), 1);

                //affichage du philosophe
                MINITELEnvoyerTexte(iFdMinitel, strPhilosophe);
                //MINITELEnvoyerCaractere(iFdMinitel, ' ');

                // On affiche le texte saisie dans la piece du chat
                MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_VERT);
                printf("LigneEnCours : %d\n", LigneEnCours) ;
                for(k = 0; k < (iNbCaracteresRecus - 1); k++)
                {
                    //le texte saisie fait deux lignes, retour en haut a la fin de la premiere
                    if(iLignesTexteMinitel >= 2 && LigneEnCours+2 >= MISEENPAGE_HAUTEUR_DE_CHAT && k+iLongueurPhilosophe == MINITEL_TAILLE_X)
                    {
                        LigneEnCours = 2;
                        MINITELCurseurXY(iFdMinitel, (LigneEnCours + 2), 1);
                        MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_VERT);
                        iLignesTexteMinitel = 1;
                    }

                    if(bufMinitel[k] >= 0x20)
                    {
                        MINITELEnvoyerCaractere(iFdMinitel, bufMinitel[k]);
                    }
                    else
                    {
                        MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_ROUGE);
                        MINITELEnvoyerCaractere(iFdMinitel, '!');
                        MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_VERT);
                    }
                }

                MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_BLANC);

                //On efface la fin de la ligne
                for(k = 0 ; k < MINITEL_TAILLE_X+iCalculLignes ; k++)
                    MINITELEnvoyerCaractere(iFdMinitel, ' ');

//                if(iNbCaracteresRecus >= 32)
//                {
//                    LigneEnCours++;
//                }

                // On efface la ligne suivante pour separer le nouveau texte de l'ancien (si pas en bas)
                LigneEnCours += iLignesTexteMinitel-1;
                if(LigneEnCours+3 < MISEENPAGE_HAUTEUR_DE_CHAT)
                {
                    MINITELCurseurXY(iFdMinitel, (LigneEnCours + 3), 1);
                    for(k = 0; k < MINITEL_TAILLE_X; k++)
                    {
                        MINITELEnvoyerCaractere(iFdMinitel, ' ');
                    }
                }

                AfficherAttenteCratyle(iFdMinitel);

                printf("bufMinitel:%s:%d\n", bufMinitel, iNbCaracteresRecus);

                //Test sur phrase specials et envoi dans le tuyau
                // todo plus propre : swicth ou variable envoi_message
                if (strncmp (bufMinitel, CRATYLE_CLEAR_SENTENCE, strlen(CRATYLE_CLEAR_SENTENCE)) == 0) //
                {
//Petit clean de l'interface
                    printf ("CRATYLE_CLEAR_SENTENCE \n");
                    MINITELCurseurXY(iFdMinitel, 2, 1);
                    MINITELChangerAttribut(iFdMinitel, MINITEL_DOUBLE_LARGEUR_DOUBLE_HAUTEUR);
                    MINITELEnvoyerTexte(iFdMinitel, (unsigned char*)CRATYLE_VERSION_TEXTE);
                    MINITELChangerAttribut(iFdMinitel, MINITEL_TAILLE_NORMALE);
                    MINITELCurseurXY(iFdMinitel, 3, 1);
                    for(k = 0; k < MINITEL_TAILLE_X; k++)
                    {
                        MINITELEnvoyerCaractere(iFdMinitel, '_');
                    }
                    AfficherAttenteCratyle(iFdMinitel);
                }
                else
                {
                    if (strncmp (bufMinitel, CRATYLE_PROPRE_SENTENCE, strlen(CRATYLE_PROPRE_SENTENCE)) == 0)
                    {
//Gros nettoyage du chat
                        InitChat(iFdMinitel);
                        AfficherAttenteCratyle(iFdMinitel);
                        LigneEnCours = 1;
                    }
                    else
                    {
                        write (fdPipeOut[1], bufMinitel, iNbCaracteresRecus);
                    }

                }

                if (strncmp (bufMinitel, CRATYLE_ESCAPE_SENTENCE, strlen(CRATYLE_ESCAPE_SENTENCE)) == 0)
                {
//Message de aurevoir
                    printf ("CRATYLE_ESCAPE_SENTENCE \n");

                    AfficherAurevoirCratyle(iFdMinitel);

                    STOP = TRUE;
                }

                memset(bufMinitel, '\0', sizeof(bufMinitel));

            }
        }

/*
oreille sur le serveur
*/
        char buffer[1];
        iNbCaracteresRecus = read(fdPipeIn[0],buffer,1);
        if (iNbCaracteresRecus == -1 && errno == EAGAIN)
        {
#ifdef DEBUG_CRATYLE
            printf ("Rien a lire sur le serveur\n");
#endif
            if(iLnMessage != 0)
            {
                // caractere de chaine pour printf&co
                strServeur[iLnMessage] = '\0';
                printf("MinitelxDansRien : strServeur %s \n", strServeur);
/* restore fd flags*/
                fcntl (iFdMinitel, F_SETFL, flags);
//                if(memcmp(strServeur,CRATYLE_ESCAPE_SENTENCE,iLnMessage) == 0) //
                if (strcmp ((const char*)strServeur, CRATYLE_ESCAPE_SENTENCE) == 0)
                {
//Petit message de aurevoir
                    printf ("On me dit aurevoir dans l'oreille....\n");
                    AfficherAurevoirCratyle(iFdMinitel);

                    STOP = TRUE;
                }
                else
                {
                    //calcul nombre de ligne du texte

                    iLignesTexteMinitel = 1;
                    iCalculLignes = iLnMessage-1 + iLongueurPrefixe;
                    while(iCalculLignes-MINITEL_TAILLE_X >= 0)
                    {
                        iCalculLignes = MINITEL_TAILLE_X - iCalculLignes;
                        printf("DISTANT:CalculLignes : %d\n", iCalculLignes);

                        iLignesTexteMinitel++;
                    }
                    printf("LOCAL:LignesTexteMinitel : %d -- CalculLignes %d\n", iLignesTexteMinitel, iCalculLignes);

                    LigneEnCours++;

                    //test du bas de la piece du chat
                    if(LigneEnCours > MISEENPAGE_HAUTEUR_DE_CHAT)
                    {
                        LigneEnCours = 2;
                    }

                    MINITELCurseurXY(iFdMinitel, (LigneEnCours + 2), 1);
                    MINITELEnvoyerTexte(iFdMinitel, (const unsigned char*)PREFIXE_AUTEUR);
                    //MINITELEnvoyerCaractere(iFdMinitel, ' ');
                    MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_VERT);
                    for(k = 0; k < iLnMessage; k++)
                    {
                        //le texte saisie fait deux lignes, retour en haut a la fin de la premiere
                        if(iLignesTexteMinitel >= 2 && LigneEnCours+2 >= MISEENPAGE_HAUTEUR_DE_CHAT && k+iLongueurPrefixe == MINITEL_TAILLE_X)
                        {
                            LigneEnCours = 2;
                            MINITELCurseurXY(iFdMinitel, (LigneEnCours + 2), 1);
                            MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_VERT);
                            iLignesTexteMinitel = 1;
                        }
                        MINITELEnvoyerCaractere(iFdMinitel, strServeur[k]);
                    }
                    MINITELChangerAttribut(iFdMinitel, MINITEL_CARACTERE_BLANC);


                    //On efface la fin de la ligne
                    for(k = 0 ; k < MINITEL_TAILLE_X+iCalculLignes ; k++)
                        MINITELEnvoyerCaractere(iFdMinitel, ' ');

                    /*
                    if(iLnMessage >= 36)
                    {
                        for(k = 0 ; k < (iLnMessage % 36) ; k++)
                            MINITELEnvoyerCaractere(iFdMinitel, ' ');
                        LigneEnCours++;
                    }
                    else
                    {
                        for(k = 0 ; k+iLnMessage < 36 ; k++)
                            MINITELEnvoyerCaractere(iFdMinitel, ' ');
                    }
                    */

                    // On efface la ligne suivante pour separer le nouveau texte de l'ancien (si pas en bas)
                    LigneEnCours += iLignesTexteMinitel-1;
                    if(LigneEnCours+3 < MISEENPAGE_HAUTEUR_DE_CHAT)
                    {
                        MINITELCurseurXY(iFdMinitel, (LigneEnCours + 3), 1);
                        for(k = 0; k < MINITEL_TAILLE_X; k++)
                        {
                            MINITELEnvoyerCaractere(iFdMinitel, ' ');
                        }
                    }

/*
                    MINITELCurseurXY(iFdMinitel, (LigneEnCours + 3), 1);
                    for(k = 0; k < MINITEL_TAILLE_X; k++)
                    {
                        MINITELEnvoyerCaractere(iFdMinitel, ' ');
                    }
*/
                    AfficherAttenteCratyle(iFdMinitel);

                }
                iLnMessage = 0;
            }

// ici           usleep(250000);

        }
        else
        {
#ifdef CRATYLE_DEBUG_BUFFER
            printf("Minitelx : buffer[0] %c \n", buffer[0]);
#endif
            strServeur[iLnMessage++] = buffer[0];
/*
            if(buffer[0] == '\0')
            {
                printf("Minitelx : strServeur %s \n", strServeur);
                fcntl (iFdMinitel, F_SETFL, flags);
                MINITELEnvoyerTexte(iFdMinitel, strServeur);
                iLnMessage = 0;
            }
*/
        }

     }

    return ERROR_NO;
}

/**
 *  MINITELEnvoyerCaractere
 *  @Param
 *  @Return
 */
void MINITELEnvoyerCaractere(int Fichier, unsigned char Caractere)
{
	if(write(Fichier, &Caractere, 1) < 0)
	{
		perror ("write");
	}
}

/**
 *  MINITELEnvoyerTexte
 *  @Param
 *  @Return
 */
void MINITELEnvoyerTexte(int Fichier, const unsigned char Texte[])
{
	int k = 0;
	while(Texte[k] != '\0')
	{
		MINITELEnvoyerCaractere(Fichier, Texte[k]);
		k++;
	}
}

/**
 *  MINITELCurseurXY
 *  @Param , un entier pour descripteur du fichier
 *  @Param
 *  @Param
 *  @Return
 */
void MINITELCurseurXY(int Fichier, unsigned char X, unsigned char Y)
{
	MINITELEnvoyerCaractere(Fichier, MINITEL_POSITIONNEMENT_CURSEUR);
	MINITELEnvoyerCaractere(Fichier, (0x40 + X));
	MINITELEnvoyerCaractere(Fichier, (0x40 + Y));
}

/**
 *  MINITELBloquerClavier
 *  @Param , un entier pour descripteur du fichier
 *  @Param , TRUE ou FALSE pour bloquer ou debloquer
 *  @Return
 */
void MINITELBloquerClavier(int Fichier, int iBloque)
{
    printf("MINITELBloquerClavier\n");


	MINITELEnvoyerCaractere(Fichier, MINITEL_ECHAPPEMENT);
	MINITELEnvoyerCaractere(Fichier, 0x5b);
	MINITELEnvoyerCaractere(Fichier, 0x32);
    if (iBloque == TRUE)
        MINITELEnvoyerCaractere(Fichier, 0x68);
    else
        MINITELEnvoyerCaractere(Fichier, 0x6c);
}

/**
 *  MINITELChangerAttribut
 *  @Param
 *  @Return
 */
void MINITELChangerAttribut(int Fichier, unsigned char Commande)
{
	MINITELEnvoyerCaractere(Fichier, MINITEL_ECHAPPEMENT);
	MINITELEnvoyerCaractere(Fichier, Commande);
}


/**
 *  AfficherAttenteCratyle : Reinitialisation de l'ecran d'attente
 *  @Param
 *  @Return
 */
void AfficherAttenteCratyle(int iFdMini)
{
    int k;

    printf("AfficherAttenteCratyle\n");

    MINITELCurseurXY(iFdMini, MISEENPAGE_PIED_DE_CHAT, 1);
    for(k = 0; k < MINITEL_TAILLE_X; k++)
    {
        //MINITELEnvoyerCaractere(iFdMini, '-'); MINITELEnvoyerCaractere(iFdMini, '-'); MINITELEnvoyerCaractere(iFdMini, '*'); MINITELEnvoyerCaractere(iFdMini, '-');
        MINITELEnvoyerCaractere(iFdMini, '_');
    }
    MINITELCurseurXY(iFdMini, MISEENPAGE_PIED_DE_CHAT_INFO, 1);

    MINITELEnvoyerTexte(iFdMini, (const unsigned char*)"  Entrez votre message :          ");

    MINITELCurseurXY(iFdMini, 23, 1);
    for(k = 0; k < MINITEL_TAILLE_X; k++)
    {
        MINITELEnvoyerCaractere(iFdMini, ' ');
    }
//    MINITELEnvoyerTexte(iFdMini, (const unsigned char*)"          ");
    MINITELCurseurXY(iFdMini, 24, 1);
    for(k = 0; k < MINITEL_TAILLE_X; k++)
    {
        MINITELEnvoyerCaractere(iFdMini, ' ');
    }


    MINITELCurseurXY(iFdMini, 23, 3);
    MINITELEnvoyerCaractere(iFdMini, '>');
    MINITELEnvoyerCaractere(iFdMini, ' ');
    MINITELEnvoyerCaractere(iFdMini, MINITEL_CURSEUR_ACTIVE);
}


/**
 *  AfficherAurevoirCratyle
 *  @Param
 *  @Return
 */
void AfficherAurevoirCratyle(int iFdMini)
{
    printf ("AfficherAurevoirCratyle : %i\n", iFdMini);

    MINITELEnvoyerCaractere(iFdMini, MINITEL_EFFACEMENT_DE_PAGE);
    MINITELCurseurXY(iFdMini, 1, 1);

    int k=0;

    for(k = 0; k < MINITEL_TAILLE_X; k++)
    {
        MINITELEnvoyerCaractere(iFdMini, '_');
    }
    MINITELChangerAttribut(iFdMini, MINITEL_DOUBLE_LARGEUR_DOUBLE_HAUTEUR);
    MINITELEnvoyerTexte(iFdMini, (unsigned char*) "*CratYle StOP*");
    for(k = 0; k < 45; k++)
    {
        MINITELEnvoyerCaractere(iFdMini, '_');
    }
}
