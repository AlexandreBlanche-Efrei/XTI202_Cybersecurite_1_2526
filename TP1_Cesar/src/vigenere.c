#include "vigenere.h"
#include "cesar.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

char *vigenere(char *plain, char *key) {

    int l = length(plain);
    int n = length(key);

    char *cipher = malloc((l + 1) * sizeof(char));
    cipher[l] = '\0';
    
    // TODO

    return cipher;
}

char *inverse_vigenere(char *cipher, char *key) {

    int l = length(cipher);
    int n = length(key);
    char *plain = malloc((l + 1) * sizeof(char));
    plain[l] = '\0';
    
    // TODO

    return plain;
}



/// Bonus : Cryptanalyse du code de Vigenère

int frequency_analysis_step_k(int nb_occ[], char *s, int length, int i, int k) {
    
    // Réinitialise le tableau freq
    for (int j = 0; j < 26; j++) {
        nb_occ[j] = 0;
    }


    // TODO
    
    int d = 0; // TODO

    return d;
}

// Affiche la chaîne déchiffrée possible depuis cipher, en supposant que la clé de chiffrement est de longueur k
void decipher_vigenere_fixed_size(char *cipher, int k) {
    int nb_occ[26];
    int l = length(cipher);
    char *key = malloc((k + 1) * sizeof(char));

    // Calcul de la clé
    for (int i = 0; i < k; i++) {
        // Calcul du caractère i de la clé

        // TODO

        key[i] = 'A'; // TODO
    }

    // Affichage et libération de la mémoire
    printf("Key: %s\n", key);
    char *plain = inverse_vigenere(cipher, key);
    printf("%s\n\n", plain);
    free(plain);
    plain = NULL;
    free(key);
    key = NULL;
}

// Affiche les chaînes décryptées possibles pour une taille de clé qui varie entre 1 et max_size inclus
void decipher_vigenere(char *cipher, int max_size) {
    // TODO
}