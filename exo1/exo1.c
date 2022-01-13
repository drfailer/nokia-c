/*
 * REMPLACER LES NOMS DES FONCTIONS PAR LES VOTRES
 * DANS LES FICHIERS VOTRECODE.H et VOTRECODE.C
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "code.h"
#include "../teZZt.h"


// DEBUT DES FONCTIONS DE TESTS
BEGIN_TEST_GROUP(exo1)


TEST(MAJ, "") {
	char s[50];

    strcpy(s, "");
    majuscules(s);
    CHECK(0 == strcmp(s, ""));

    strcpy(s, "PROMO 2023");
    majuscules(s);
    CHECK(0 == strcmp(s, "PROMO 2023"));

    strcpy(s, "zz1");
    majuscules(s);
    CHECK(0 == strcmp(s, "ZZ1"));

    strcpy(s, "langage c");
    majuscules(s);
    CHECK(0 == strcmp(s, "LANGAGE C"));
}

TEST(MULTI1, "") {
    char s[50];
    char d[50];

    strcpy(s, "EXAMEN");
    multitap1(d, s);
    CHECK(0 == strcmp(d, "33 99 2 6 33 66"));

    strcpy(s, "BONJOUR");
    multitap1(d, s);
    CHECK(0 == strcmp(d, "22 666 66 5 666 88 777"));
}

TEST(MULTI2, "") {
    char s[50];

    strcpy(s, "EXAMEN");
    multitap2(s);
    CHECK(0 == strcmp(s, "2*32*9262*32*6"));

    strcpy(s, "BONJOUR");
    multitap2(s);
    CHECK(0 == strcmp(s, "2*23*62*653*62*83*7"));
}

TEST(MULTI3, "") {
    char s[50];
    char d[50];

    strcpy(s, "33 99 2 6 33 66");
    antitap1(d, s);
    CHECK(0 == strcmp(d, "EXAMEN"));

    strcpy(s, "22 666 66 5 666 88 777");
    antitap1(d, s);
    CHECK(0 == strcmp(d, "BONJOUR"));
}

TEST(MULTI4, "") {
    char s[50];

    strcpy(s, "2*32*9262*32*6");
    antitap2(s);
    CHECK(0 == strcmp(s, "EXAMEN"));

    strcpy(s, "2*23*62*653*62*83*7");
    antitap2(s);
    CHECK(0 == strcmp(s, "BONJOUR"));
}

TEST(BONUS, "") {
    char s[50];
    char d[50];

    strcpy(s, "5 33 3 33 8 33 7777 8 33 555 33 222");
    antitap1(d, s);
    CHECK(0 == strcmp(d, devinette));

    strcpy(s, "52*332*382*34*782*33*52*33*2");
    antitap2(s);
    CHECK(0 == strcmp(s, devinette));
}

TEST(LECTUREFAUSSE, "") {
   char * s = sms("inconnu.txt");

   CHECK(NULL == s);
}

TEST(LECTURE, "") {
   char * s = sms("texte.txt");

   char resultat[] = "333 444 66\n7 777 33 6 444 33 777\n33 99 33 777 222 444 222 33";

   REQUIRE(NULL != s);
   CHECK(0 == strcmp(s, resultat));

   free(s);
}


END_TEST_GROUP(exo1)


int main() {
    char d[50] =  "5 33 3 33 8 33 7777 8 33 555 33 222";
    char s[50];
    antitap1(s, d);
    printf("%s\n", s);
    RUN_TEST_GROUP(exo1);

   return 0;
}

