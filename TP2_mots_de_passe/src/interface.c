#include "interface.h"

#include <stdio.h>
#include <string.h>

void account_menu(person *p, bool first_time) {
    if (first_time) {
        printf("\n\nBienvenue %s !\n\n", p->first_name);
    }
    else {
        printf("\n\nBonjour %s !\n\n", p->first_name);
    }
    print_person_long(p);
    printf("\n0- Revenir au menu\n");
    int n = -1;
    do {
        printf("Entrer option : ");
        fflush(stdout);
        scanf("%d", &n);
    }
    while (n != 0);
    printf("\nAu revoir !\n\n");
}

void connection(database *db) {

    int index;
    bool stop = false;
    bool go_back = false;
    do {
        printf("Entrez votre identifiant : ");
        fflush(stdout);

        char login[MAX_LOGIN_SIZE] = { 0 };
        fgets(login, MAX_LOGIN_SIZE - 1, stdin);

        // Replace the '\n' by '\0'
        int l = str_length(login);
        login[l - 1] = '\0';

        go_back = str_eq("0", login);
        index = get_index(db, login);
        stop = (index != -1) || go_back;

        if (index == -1) {
            printf("Utilisateur introuvable\n");
            printf("0- Retour au menu\n\n");
        }

    } while (!stop);

    if (go_back) {
        return;
    }

    bool success;
    do {
        printf("Entrez votre mot de passe : ");
        fflush(stdout);

        char pw[MAX_PASSWORD_SIZE] = { 0 };
        fgets(pw, MAX_PASSWORD_SIZE - 1, stdin);

        // Replace the '\n' by '\0'
        int lp = str_length(pw);
        pw[lp - 1] = '\0';

        go_back = str_eq("0", pw);
        success = check_password(db, index, pw);

        if (!success) {
            printf("Mauvais mot de passe\n");
            printf("0- Retour au menu\n\n");
        }
        
    } while (!(success || go_back));

    if (go_back) {
        return;
    }

    account_menu(&db->data[index].person, false);
    
    flush_buffer();
}

void main_menu(database *db) {
    while (true) {
        printf("\n------ Menu ------\n\n");
        printf("1- Se connecter\n");
        printf("2- S'inscrire\n");
        printf("\n0- Quitter\n");
        printf("------------------\n");
        int n = -1;
        do {
            printf("Entrer option : ");
            fflush(stdout);
            scanf("%d", &n);
            flush_buffer();
        } while (n < 0 || n > 2);

        switch (n) {
            case 1: { // Sign in
                connection(db);
                break;
            }

            case 2: { // Sign up
                
                bool keep;
                char login[MAX_LOGIN_SIZE] = { 0 };
                do {
                    keep = false;
                    printf("Identifiant : ");
                    fflush(stdout);
                    
                    fgets(login, MAX_LOGIN_SIZE, stdin);
                    int l = str_length(login);
                    login[l - 1] = '\0';
                    
                    if (get_index(db, login) != -1) {
                        keep = true;
                        printf("Cet identifiant existe déjà.\n\n");
                    }
                } while (keep);
                person p = enter_person_info(login);
                

                printf("Mot de passe : ");
                fflush(stdout);
                char pw[MAX_PASSWORD_SIZE] = { 0 };
                fgets(pw, MAX_NAME_SIZE, stdin);

                // Replace the '\n' by '\0'
                int lpw = str_length(pw);
                pw[lpw - 1] = '\0';

                add_item(db, &p, pw, true);
                account_menu(&db->data[db->nb_items - 1].person, true);
                break;
            }

            case 0: // Exit
                printf("\n\n");
                return;
            
            default:
                return;
        }
    }
}