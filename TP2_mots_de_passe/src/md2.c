// MD2

#include "utils.h"
#include "md2.h"

#include <assert.h>

static unsigned char pi_subst[256] = {
    41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6, 19,
    98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188, 76, 130, 202,
    30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24, 138, 23, 229, 18,
    190, 78, 196, 214, 218, 158, 222, 73, 160, 251, 245, 142, 187, 47, 238, 122,
    169, 104, 121, 145, 21, 178, 7, 63, 148, 194, 16, 137, 11, 34, 95, 33,
    128, 127, 93, 154, 90, 144, 50, 39, 53, 62, 204, 231, 191, 247, 151, 3,
    255, 25, 48, 179, 72, 165, 181, 209, 215, 94, 146, 42, 172, 86, 170, 198,
    79, 184, 56, 210, 150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241,
    69, 157, 112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2,
    27, 96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
    85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197, 234, 38,
    44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65, 129, 77, 82,
    106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123, 8, 12, 189, 177, 74,
    120, 136, 149, 139, 227, 99, 232, 109, 233, 203, 213, 254, 59, 0, 29, 57,
    242, 239, 183, 14, 102, 88, 208, 228, 166, 119, 114, 248, 235, 117, 75, 10,
    49, 68, 80, 180, 143, 237, 31, 26, 219, 153, 141, 51, 159, 17, 131, 20
};

// ------------------------------------------------------------

// La fonction que nous allons utiliser est la fonction MD2, pour "Message Digest 2", créée par Ronald Rivest en 1989.

// Les entrées que nous considérons seront des séquences d'octets, sous forme de tableaux de unsigned char.
// La première étape est d'ajouter du bourrage (padding) à la séquence pour que sa longueur soit un multiple de 16. Les octets de bourrage ont tous pour valeur le nombre d'octets de bourrage à ajouter.

// Adds the padding and returns the new length of the array
int pad(unsigned char t[], int length) {

    int pad_length = 16 - (length % 16);
    int new_length = length + pad_length;
    for (int i = length; i < new_length; i++) {
        t[i] = pad_length;
    }

    return new_length;
}

// La deuxième étape consiste à calculer une somme de contrôle (checksum) à partir du message, et de l'ajouter à la fin du message, après les octets de bourrage que l'on vient d'ajouter.
// Cette somme de contrôle est une séquence de 16 octets, que l'on représentera par un tableau de unsigned char de taille 16.
// L'algorithme de calcul repose sur un tableau de 256 valeurs "rien dans la manche" (choisies de manière naturelle afin d'éviter toute suspicion de manipulation) générées à partir des décimales de pi et de l'algorithme de mélange de Durstenfeld. Elles sont données dans le tableau pi_subst.

// L'algorithme de calcul du haché MD2 est décrit dans la RFC 1319 : https://www.ietf.org/rfc/rfc1319.txt
// Attention, celle-ci contient une erreur dans la description du calcul de la somme de contrôle : https://www.rfc-editor.org/errata_search.php?rfc=1319

// Pour calculer la somme de contrôle, on initialise les 16 unsigned char d'un tableau checksum avec la valeur 0.
// On initialise une variable l à 0.
// On itère ensuite sur les 16 blocs avec l'opération suivante :
// Pour chaque octet c du bloc, à la position i (entre 0 et 15) dans le bloc, la valeur pi_subst[c XOR l] XOR checksum[i] est placée dans la variable l et dans checksum[i].

void compute_checksum (unsigned char checksum[16], unsigned char t[], int length) {

    int nb_blocks = length / 16; // length is a multiple of 16
    for (int i = 0; i < 16; i++)
        checksum[i] = 0;
    unsigned char l = 0;

    for (int block = 0; block < nb_blocks; block++) {
        for (int i = 0; i < 16; i++) {
            int index = block * 16 + i;
            l = pi_subst[t[index] ^ l] ^ checksum[i];
            checksum[i] = l;
        }
    }
}
// Appends t2 to t1 and returns the new length of t1
int append_array (unsigned char t1[], unsigned char t2[], int length_t1, int length_t2) {

    for (int i = 0; i < length_t2; i++) {
        t1[length_t1 + i] = t2[i];
    }
    
    return length_t1 + length_t2;
}

// L'étape suivante consiste à calculer un buffer de 48 octets, qui sera utilisé pour calculer le haché final.
// On suppose que l'on dispose d'un tableau buffer de unsigned char de taille 48, que l'on commence par initialiser avec des 0.
// Ce tableau est divisé en trois parties de 16 octets, que l'on peut définir par :
// unsigned char* buffer0 = buffer;
// unsigned char* buffer1 = &buffer[16];
// unsigned char* buffer2 = &buffer[2 * 16];

// Pour chaque bloc de 16 octets du tableau d'entrée t, on applique les opérations suivantes :
// - le bloc est recopié sur buffer1
// - buffer2 reçoit buffer1 XOR buffer0 (élément par élément)
// - une variable l de type unsigned char est initialisée à 0
// - L'opération suivante est réalisée 18 fois de suite (indexées par p allant de 0 à 17):
//      * pour chaque élément c de buffer (de l'indice 0 à 47), la valeur (c XOR pi_subst[l]) est placée dans c et dans l
//      * une fois les 48 éléments traités, l reçoit la valeur l + p, où p est le numéro de la passe actuelle (entre 0 et 17)

void compute_buffer (unsigned char buffer[48], unsigned char t[], int length) {

    for (int i = 0; i < 48; i++)
        buffer[i] = 0;
    
    int nb_blocks = length / 16;

    unsigned char* buffer0 = buffer;
    unsigned char* buffer1 = &buffer[16];
    unsigned char* buffer2 = &buffer[2 * 16];

    for (int i = 0; i < nb_blocks; i++) {

        for (int j = 0; j < 16; j++) {

            int index = i * 16 + j;
            buffer1[j] = t[index]; // block 1 = current block
            buffer2[j] = buffer1[j] ^ buffer0[j]; // block 2 = block 0 XOR block 1
        }

        unsigned char l = 0;

        // 18 passes
        for (unsigned char pass = 0; pass < 18; pass++) {
            for (int k = 0; k < 48; k++) {
                l = buffer[k] ^ pi_subst[l];
                buffer[k] = l;
            }
            l = l + pass;
        }
    }
}

// Les 16 premiers éléments de buffer constituent le haché final.

// L'algorithme MD2, en partant du tableau t de taille suffisante :
// - Ajouter le bourrage à t
// - Calculer la somme de contrôle et la concaténer à t
// - Calculer le buffer à partir de t
// - Extraire les 16 premiers octets du buffer

// Cette fonction prend en entrée une chaîne de caractères s (de type char*) et un tableau output de unsigned char de taille 16,
// calcule le haché de s et l'écrit dans output.
void compute_md2 (char* s, unsigned char output[HASH_SIZE]) {

    static_assert(HASH_SIZE == 16, "Wrong HASH_SIZE");

    int l = str_length(s);
    unsigned char t[MAX_LENGTH];
    copy_str_to_array(s, t);

    l = pad(t, l);

    unsigned char checksum[16];
    compute_checksum(checksum, t, l);

    l = append_array(t, checksum, l, 16);

    unsigned char buffer[48];
    compute_buffer(buffer, t, l);

    for (int i = 0; i < HASH_SIZE; i++)
        output[i] = buffer[i];
}