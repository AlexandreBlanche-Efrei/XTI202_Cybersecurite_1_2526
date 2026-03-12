#include "utils.h"

#include <stdio.h>

// Renvoie la longueur de la chaîne de caractères s
int str_length(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

// Renvoie true si les chaînes s1 et s2 sont égales
bool str_eq(char *s1, char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 == '\0' && *s2 == '\0';
}

// Recopie la chaîne src sur la chaîne dest
void str_copy(char *dest, char *src) {
    while (*src != '\0') {
        *dest = *src;
        src++;
        dest++;
    }
    *dest = '\0';
}

// Renvoie true si deux hachés h1 et h2 sont égaux
bool hash_eq(unsigned char h1[HASH_SIZE], unsigned char h2[HASH_SIZE]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (h1[i] != h2[i])
            return false;
    }
    return true;
}


// ------------------------------------------------

void copy_str_to_array(char *s, unsigned char t[]) {

    int i = 0;
    while (*s != '\0') {
        t[i] = *s;
        s++;
        i++;
    }
}

void print_array(unsigned char t[], int length) {

    printf("{ ");
    for (int i = 0; i < length - 1; i++) {
        printf("%u, ", t[i]);
    }
    printf("%u }\n", t[length - 1]);
}

// s[0]s[1] should be two characters in 0123456789abcdef
unsigned char hex_to_dec(char *s) {
    int val0 = (s[0] >= '0' && s[0] <= '9') ? s[0] - '0' : s[0] - 'a' + 10;
    int val1 = (s[1] >= '0' && s[1] <= '9') ? s[1] - '0' : s[1] - 'a' + 10;
    return 16 * val0 + val1;
}

void print_hex_repr(unsigned char n) {
    static char *hex_repr = "0123456789abcdef";
    printf("%c%c", hex_repr[n / 16], hex_repr[n % 16]);
}

void print_hash(unsigned char hash[]) {

    for (int i = 0; i < HASH_SIZE; i++)
        print_hex_repr(hash[i]);
}

void flush_buffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}