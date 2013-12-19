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
#include "testunitaire.h"

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
