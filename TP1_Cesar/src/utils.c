#include "utils.h"

// Renvoie la longueur de la chaîne de caractères s
int length(char *s) {
    int l = 0;
    while (*s != '\0') {
        l++;
        s++;
    }
    return l;
}

// Renvoie r = a mod b, avec r entre 0 et b - 1
int positive_mod(int a, int b) {
    int r = a % b;
    return (a < 0) ? b + r : r;
}

// Renvoie l'indice du maximum du tableau t de taille n
int get_max_index(int t[], int n) {

    int i_max = 0;
    int val = t[0];
    for (int i = 1; i < n; i++) {
        if (t[i] > val) {
            i_max = i;
            val = t[i];
        }
    }
    return i_max;
}