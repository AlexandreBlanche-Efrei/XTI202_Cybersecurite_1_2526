#ifndef CESAR_H
#define CESAR_H

// Renvoie le caractère c décalé de d positions
char shift(char c, int d);

// Renvoie une chaîne chiffrée avec le code de César, depuis la chaîne plain_text
char *caesar(char *plain_text);

// Renvoie une chaîne chiffrée avec le code par décalage, depuis la chaîne plain_text
// Chaque lettre de plain_text est décalée de d positions
char *shift_cipher(char *plain_text, int d);

// Place dans nb_occ[i] le nombre d'occurrences de la lettre i (0 = A, 1 = B, etc.)
// dans la chaîne text
void frequency(char *text, int nb_occ[]);

// Applique la stratégie d'analyse fréquentielle pour décrypter un texte cipher chiffré avec le code par décalage
char *decipher_caesar(char *cipher);

#endif