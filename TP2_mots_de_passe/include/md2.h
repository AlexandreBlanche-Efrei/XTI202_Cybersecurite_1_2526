#ifndef MD2_H
#define MD2_H

#define MAX_LENGTH 1024

// Cette fonction prend en entrée une chaîne de caractères s (de type char*) et un tableau output de unsigned char de taille 16,
// calcule le haché de s et l'écrit dans output.
void compute_md2 (char* s, unsigned char output[HASH_SIZE]);

#endif