#ifndef DATABASE_H
#define DATABASE_H

#include "person.h"
#include "utils.h"

//#define HASH_IMPLEMENTATION

#define MAX_NB_ITEMS 100

#ifndef HASH_IMPLEMENTATION

typedef struct {
    char password[MAX_PASSWORD_SIZE];
    person person;
} item;

#else

typedef struct {
    unsigned char hash_pw[HASH_SIZE];
    person person;
} item;

#endif

typedef struct {
    item data[MAX_NB_ITEMS];
    int nb_items;
} database;

database create_database();
item create_item(person *p, char *pw);
void add_item(database *db, person *p, char *pw, bool user_defined);
void init_database(database *db);

int get_index(database *db, char *login);
bool check_password(database *db, int index, char *pw);

#endif