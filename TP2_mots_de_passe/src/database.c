#include "database.h"

#include "utils.h"
#include "md2.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef HASH_IMPLEMENTATION

// Implémentation initiale
bool check_password(database *db, int index, char *pw) {
    // TODO
    return false;
}

#else

// Implémentation avec fonction de hachage
bool check_password(database *db, int index, char *pw) {
    // TODO
    return false;
}

#endif


// -----------------------------------------------------------

database create_database() {
    database db;
    db.nb_items = 0;
    return db;
}

#ifndef HASH_IMPLEMENTATION
// Implémentation initiale
item create_item(person *p, char *pw) {
    item it;
    it.person = *p;
    str_copy(it.password, pw);
    return it;
}

#else
// Implémentation avec fonction de hachage
item create_item(person *p, char *pw) {
    item it;
    it.person = *p;
    compute_md2(pw, it.hash_pw);
    return it;
}

item create_prehashed_item(person *p, unsigned char *hash) {
    item it;
    it.person = *p;
    for (int i = 0; i < HASH_SIZE; i++) {
        it.hash_pw[i] = hash[i];
    }
    return it;
}

#endif

#ifndef HASH_IMPLEMENTATION
void add_to_file(item *item) {

    person *p = &item->person;
    char *pw = item->password;
    
    FILE *file = fopen("../.data/.database_pt1.txt", "a");

    if (file == NULL) {
        printf("File not found\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\t\t%s\t\t%s\t\t%d\t%d\t%d\t%s\n",
        p->login, p->last_name, p->first_name,
        p->birthdate.day, p->birthdate.month, p->birthdate.year,
        pw);

    fclose(file);
}
#else
void add_to_file(item *item) {

    person *p = &item->person;
    unsigned char *h = item->hash_pw;

    FILE *file = fopen("../.data/.database_pt2.txt", "a");

    if (file == NULL) {
        printf("File not found\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\t\t%s\t\t%s\t\t%d\t%d\t%d\t",
        p->login, p->last_name, p->first_name,
        p->birthdate.day, p->birthdate.month, p->birthdate.year);

    // Writing the string representation of the hash (16 bytes)
    static char *hex_repr = "0123456789abcdef";
    for (int i = 0; i < HASH_SIZE; i++) {
        fprintf(file, "%c%c", hex_repr[h[i] / 16], hex_repr[h[i] % 16]);
    }
    fprintf(file, "\n");

    fclose(file);
}
#endif

void add_item(database *db, person *p, char *pw, bool user_defined) {
    
    if (db->nb_items >= MAX_NB_ITEMS) {
        printf("add_item: database full\n");
        exit(EXIT_FAILURE);
    }

    db->data[db->nb_items] = create_item(p, pw);
    db->nb_items++;

    if (user_defined) {
        add_to_file(&db->data[db->nb_items - 1]);
    }
}

#ifdef HASH_IMPLEMENTATION
void add_prehashed_item(database *db, person *p, unsigned char *hash) {
    
    if (db->nb_items >= MAX_NB_ITEMS) {
        printf("add_item: database full\n");
        exit(EXIT_FAILURE);
    }

    db->data[db->nb_items] = create_prehashed_item(p, hash);
    db->nb_items++;
}
#endif

void init_database(database *db) {

#ifndef HASH_IMPLEMENTATION
    srand(0);
    FILE *file = fopen("../.data/.database_pt1.txt", "rb");
#else
    srand(37);
    FILE *file = fopen("../.data/.database_pt2.txt", "rb");
#endif
    if (file == NULL) {
        printf("File not found\n");
        exit(EXIT_FAILURE);
    }
    int ret;
    int l = -1;
    bool keep = false;
    do {
        person p;
        p.last_purchase = rand() % NB_BOOKS;
#ifndef HASH_IMPLEMENTATION
        char pw[MAX_PASSWORD_SIZE] = { 0 };
        ret = fscanf(file, "%s %s %s %d %d %d %s",
            p.login, p.last_name, p.first_name,
            &p.birthdate.day, &p.birthdate.month, &p.birthdate.year,
            pw);
        l = str_length(pw);
        keep = (l != 0 && ret == 7);
        if (keep) {
            add_item(db, &p, pw, false);
        }
#else
        char hash_text[2 * HASH_SIZE + 1] = { 0 };
        ret = fscanf(file, "%s %s %s %d %d %d %s",
            p.login, p.last_name, p.first_name,
            &p.birthdate.day, &p.birthdate.month, &p.birthdate.year,
            hash_text);
        l = str_length(hash_text);
        keep = (l == 2 * HASH_SIZE && ret == 7);
        if (keep) {
            unsigned char hash[16];
            for (int i = 0; i < HASH_SIZE; i++) {
                hash[i] = hex_to_dec(hash_text + 2 * i);
            }
            add_prehashed_item(db, &p, hash);
        }
#endif
    } while (keep);
    fclose(file);
    return;
}

int get_index(database *db, char *login) {
    for (int i = 0; i < db->nb_items; i++) {
        if (str_eq(login, db->data[i].person.login)) {
            return i;
        }
    }
    return -1;
}