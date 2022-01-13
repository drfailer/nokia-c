#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char devinette[255] = "JEDETESTELEC";

/* clavier du telephone */
char CLAVIER[8][5] = {{  'A', 'B', 'C', '2',  0  }, // touche 2
                       { 'D', 'E', 'F', '4',  0  }, // touche 3
                       { 'G', 'H', 'I', '4',  0  },
                       { 'J', 'K', 'L', '5',  0  }, // ...
                       { 'M', 'N', 'O', '6',  0  },
                       { 'P', 'Q', 'R', 'S', '7' },
                       { 'T', 'U', 'V',  0 , '8' },
                       { 'W', 'X', 'Y', 'Z', '9' }}; // touche 9


void majuscules(char * s) {
   int i = 0;
   while (s[i]) {
      if (s[i] >= 'a' && s[i] <= 'z') {
         s[i] -= 'a' - 'A';
      }
      ++i;
   }
}


void multitap1(char * d, char * s) {
   int i, j, k;
   int id = 0, is = 0;

   majuscules(s);
   // parcour de s
   while (s[is] != 0) {
      // espace => touche 0
      if (s[is] == ' ') {
         d[id] = '0';
         d[id+1] = ' ';
         id += 2;
      } else if (s[is] >= 'A' && s[is] <= 'Z') { // caratère classique => touche 2-9
         // recherche du caractère dans le tableau
         for (i = 0; i < 8; ++i) {
            for (j = 0; j < 4; ++j) {
               // On met à jour d quand on trouve le la touche
               if (CLAVIER[i][j] == s[is]) {
                  // i contient la ligne du tableau clavier (ie: une touche de
                  // 2 à 9) et j contient la répétition de la touche, donc on
                  // écrit j fois la touche qui correspond
                  for (k = 0; k <= j; ++k) {
                     d[id] = '2' + i;
                     ++id;
                  }
                  // on ajoute un espace quand on a fini si il nous reste des
                  // caratères à traduire:
                  if (s[is+1] >= 'A' && s[is+1] <= 'Z') {
                     d[id] = ' ';
                     ++id;
                  }
               }
            }
         }
      } else {
         d[id] = s[is];
         ++id;
      }
      ++is;
   }
   // ajout de la fin du mot:
   d[id] = 0;
}

void multitap2(char * s) {
   char d[500];
   int i, j;
   int id = 0, is = 0;

   majuscules(s);
   while (s[is]) {
      // espace => touche 0
      if (s[is] == ' ') {
         d[id] = '0';
         ++id;
      } else  if (s[is] >= 'A' && s[is] <= 'Z') {
         // caratère classique => touche 2-9
         for (i = 0; i < 8; ++i) {
            for (j = 0; j < 4; ++j) {
               if (CLAVIER[i][j] == s[is]) {
                  // ajoute le multiplicateur si il est supérieur à 1 (ie: j >
                  // 0) puis le *
                  if (j > 0) {
                     d[id] = '1' + j;
                     d[id+1] = '*';
                     id+=2;
                  }
                  // on ajoute la touche préssée
                  d[id] = '2' + i;
                  ++id;
               }
            }
         }
      } else {
         d[id] = s[is];
         ++id;
      }
      ++is;
   }
   d[id] = 0;
   strcpy(s, d);
}

void antitap1(char *d, char * s) {
   int id = 0, is = 0;
   int rep;
   // bug bizarre chez moi, il y a un caractère espaced dans s donc on test si
   // s est bien > '0'
   while (s[is] >= '0') {
      rep = 0;
      while (s[is] >= '0' && s[is] != ' ') {
         ++rep;
         ++is;
      }
      d[id] = CLAVIER[s[is-1] - '2'][rep-1];
      ++id;
      ++is;
   }
   d[id] = 0;
}

void antitap2(char * s) {
   int id = 0, is = 0;
   int rep;
   char d[500];

   while (s[is]) {
      rep = s[is] - '0';
      if (s[is+1] == '*') {
         d[id] = CLAVIER[s[is+2] - '2'][rep - 1];
         is+=3;
      } else {
         // dans ce cas rep contient le chiffre et non la repetition
         d[id] = CLAVIER[rep-2][0];
         is+=1;
      }
      ++id;
   }
   d[id] = 0;
   strcpy(s, d);
}

char * sms(char * nom) {
   char content[1000];
   char *result = NULL;
   char buff[500];
   FILE *f = fopen(nom, "r+");

   // test ouverture du fichier
   if (f == NULL) {
      fprintf(stderr, "error: can't open file\n");
   } else {
      result = (char*) malloc(2000*sizeof(char));
      if (result != NULL) {
         // on récupère toutes les lignes et on les traduit
         while (fgets(buff, 500, f)) {
            multitap1(content, buff);
            strcat(result, content);
         }
      } else {
         fprintf(stderr, "error: alloc failed\n");
      }
   }

   return result;
}
