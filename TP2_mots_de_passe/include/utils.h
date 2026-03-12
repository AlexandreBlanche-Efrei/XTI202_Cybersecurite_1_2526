#ifndef UTILS_H
#define UTILS_H

#define HASH_SIZE 16

#include <stdbool.h>

// Renvoie la longueur de la chaîne de caractères s
int str_length(char *s);

// Renvoie true si les chaînes s1 et s2 sont égales
bool str_eq(char *s1, char *s2);

// Recopie la chaîne src sur la chaîne dest
void str_copy(char *dest, char *src);

// Renvoie true si deux hachés h1 et h2 sont égaux
bool hash_eq(unsigned char h1[HASH_SIZE], unsigned char h2[HASH_SIZE]);

// ------------------------------------------------
void copy_str_to_array(char *s, unsigned char t[]);
void print_array(unsigned char t[], int length);
unsigned char hex_to_dec(char *s);
void print_hex_repr(unsigned char n);
void print_hash(unsigned char hash[]);
void flush_buffer();

#endif