#ifndef VIGENERE_H
#define VIGENERE_H

char *vigenere(char* plain, char* key);

char *inverse_vigenere(char* cipher, char* key);



/// Bonus : Cryptanalyse du code de Vigenère

// Affiche les chaînes décryptées possibles pour une taille de clé qui varie entre 1 et max_size inclus
void decipher_vigenere(char *cipher, int max_size);

#endif