#ifndef UTILS_H
#define UTILS_H

// Renvoie la longueur de la chaîne de caractères s
int length(char* s);

// Renvoie r = a mod b, avec r entre 0 et b - 1
int positive_mod(int a, int b);

// Renvoie l'indice du maximum du tableau t de taille n
int get_max_index(int t[], int n);

#endif