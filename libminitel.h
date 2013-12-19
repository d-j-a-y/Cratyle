#ifndef LIBMINITEL_H_INCLUDED
#define LIBMINITEL_H_INCLUDED

#include <termios.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


/* baudrate settings are defined in <asm/termbits.h>, which is
included by <termios.h> */
#define BAUDRATE B1200 //300 4800

#define _POSIX_SOURCE 1 /* POSIX compliant source */


#define MINITEL_EFFACEMENT_DE_PAGE 0x0C

#define MINITEL_CURSEUR_ACTIVE 0x11

#define MINITEL_CURSEUR_DESACTIVE 0x14

#define MINITEL_ECHAPPEMENT 0x1B

#define MINITEL_POSITIONNEMENT_CURSEUR 0x1F

#define MINITEL_CARACTERE_ROUGE 0x41
#define MINITEL_CARACTERE_VERT 0x42
#define MINITEL_CARACTERE_BLANC 0x47
#define MINITEL_TAILLE_NORMALE 0x4C
#define MINITEL_DOUBLE_LARGEUR_DOUBLE_HAUTEUR 0x4F

#define MINITEL_FOND_NOIR 0x50
#define MINITEL_FOND_ROUGE 0x51

#define MINITEL_FOND_NORMAL 0x5C

#define MINITEL_TAILLE_X 40
#define MINITEL_TAILLE_Y 20

#define PENBOX_CARACTERE_MAX 1920

#define MISEENPAGE_HAUTEUR_DE_CHAT 18

#define MISEENPAGE_PIED_DE_CHAT 21
#define MISEENPAGE_PIED_DE_CHAT_INFO 22

#define PREFIXE_AUTEUR "-->"

extern const unsigned char PLATON[];
extern const unsigned char SOCRATE[];
extern const unsigned char CRATYLE[];
extern const unsigned char HERMOGENE[];

void OuvrirConnection (int iFileDescriptor, struct termios* oldtio);
void FermerConnection (int fd, struct termios* oldtio);

int OuvrirConnectionMinitel (char* strMinitelPort, struct termios* oldtio);
int OuvrirConnectionImprimante (char* strImprimPort, struct termios* oldtio);

void InitChat (int iFdMinitel);
int OuvrirChat (int iFdMinitel, int* fdPipeIn, int* fdPipeOut, const unsigned char* strPhilosophe) ;
void AfficherAttenteCratyle(int iFdMini);
void AfficherAurevoirCratyle(int iFdMini);

void MINITELEnvoyerCaractere(int Fichier, unsigned char Caractere);
void MINITELEnvoyerTexte(int Fichier, const unsigned char Texte[]);
void MINITELCurseurXY(int Fichier, unsigned char X, unsigned char Y);
void MINITELChangerAttribut(int Fichier, unsigned char Commande);
void MINITELBloquerClavier(int Fichier, int iBloque);

#endif
