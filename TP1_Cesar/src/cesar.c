#include "cesar.h"
#include "utils.h"

#include <stdlib.h>

// Renvoie le caractère c décalé de d positions
char shift(char c, int d) {
    if (c >= 'a' && c <= 'z') {
        return c; // TODO
    }
    else if (c >= 'A' && c <= 'Z') {
        return c; // TODO
    }
    else {
        return c;
    }
}

// Renvoie une chaîne chiffrée avec le code de César, depuis la chaîne plain_text
char *caesar(char *plain_text) {
    int l = length(plain_text);
    char *s = malloc((l + 1) * sizeof(char));
    s[l] = '\0';

    // TODO

    return s;
}

// Renvoie une chaîne chiffrée avec le code par décalage, depuis la chaîne plain_text
// Chaque lettre de plain_text est décalée de d positions
char *shift_cipher(char *plain_text, int d)  {

    int l = length(plain_text);
    char *s = malloc((l + 1) * sizeof(char));
    s[l] = '\0';

    // TODO

    return s;
}

// Place dans nb_occ[i] le nombre d'occurrences de la lettre i (0 = A, 1 = B, etc.)
// dans la chaîne text
void frequency(char *text, int nb_occ[]) {

    for (int i = 0; i < 26; i++) {
        nb_occ[i] = 0;
    }

    // TODO

}

// Applique la stratégie d'analyse fréquentielle pour décrypter un texte cipher chiffré avec le code par décalage
char *decipher_caesar(char *cipher) {
    
    int nb_occ[26] = { 0 };

    // TODO

    char *plain = ""; // TODO
    
    return plain;
}