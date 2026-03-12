#include "bruteforce.h"

#include "database.h"
#include "md2.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void next(char *s) {
    for (int i = 0; ; i++) {
        switch (s[i]) {
            case 'z':
                // TODO
                break;

            case '\0':
                // TODO
                break;
            
            default:
                // TODO
                break;
        }
    }
}

// Renvoie une chaîne de caractères dont le haché MD2 est égal à hash
char * bruteforce(database *db, unsigned char *hash) {

    // Mot de passe que l'on va tester
    char pw[MAX_PASSWORD_SIZE] = { 0 };

    // Tableau dans lequel on calcule le haché du mot de passe
    unsigned char h[HASH_SIZE];
    
    unsigned int cpt = 1;

    while (true) {
        
        if (cpt % 10000 == 0) {
            printf("\rPasswords tested: %u (password = %s)", cpt, pw);
            fflush(stdout);
        }
        /* ----------------------------- */
        // TODO



        /* ----------------------------- */
        cpt++;
    }

    // Copie du mot de passe obtenu
    char *output = calloc(MAX_PASSWORD_SIZE, sizeof(char));
    str_copy(output, pw);

    return output;
}

/* ----------------------------------------------------------------- */

void launch_bruteforce(database *db) {
    printf("Entrer le haché du mot de passe : ");
    char s[2 * HASH_SIZE + 2] = { 0 };
    fgets(s, 2 * HASH_SIZE + 1, stdin);
    unsigned char h[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        h[i] = hex_to_dec(s + 2 * i);
    }

    char *pw = bruteforce(db, h);
    printf("\n==> Mot de passe obtenu: %s\n", pw);
    free(pw);
}