#ifndef DATA_H
#define DATA_H

#include "products.h"

#define MAX_LOGIN_SIZE 16
#define MAX_NAME_SIZE 128
#define MAX_PASSWORD_SIZE 32

typedef struct {
    int day;
    int month;
    int year;
} date;

void print_date(date *d);

typedef struct {
    
    char login[MAX_LOGIN_SIZE];
    char last_name[MAX_NAME_SIZE];
    char first_name[MAX_NAME_SIZE];
    date birthdate;
    int last_purchase;

} person;

void print_person(person *p);
void print_person_long(person *p);

person enter_person_info(char *login);

#endif