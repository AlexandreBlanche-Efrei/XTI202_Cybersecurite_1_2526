#include "person.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

void print_date(date *d) {
    printf("(%.2d / %.2d / %d)", d->day, d->month, d->year);
}

void print_person(person *p) {
    printf("%s - %s %s ", p->login, p->first_name, p->last_name);
    print_date(&p->birthdate);
}

void print_person_long(person *p) {
    printf("Identifiant : %s\nNom : %s %s\nDate de naissance : ", p->login, p->first_name, p->last_name);
    print_date(&p->birthdate);
    printf("\n");
    printf("Dernier achat : ");
    if (p->last_purchase == -1) {
        printf("aucun achat pour le moment.\n");
    }
    else {
        printf("%s\n", books[p->last_purchase]);
    }
}

person enter_person_info(char *login) {

    person p;
    memset(p.first_name, 0, MAX_NAME_SIZE * sizeof(char));
    memset(p.last_name, 0, MAX_NAME_SIZE * sizeof(char));

    str_copy(p.login, login);

    printf("Prénom : ");
    fflush(stdout);
    fgets(p.first_name, MAX_NAME_SIZE, stdin);
    
    printf("Nom de famille : ");
    fflush(stdout);
    fgets(p.last_name, MAX_NAME_SIZE, stdin);
    
    printf("Date de naissance (jour mois année) : ");
    fflush(stdout);
    scanf("%d %d %d", &p.birthdate.day, &p.birthdate.month, &p.birthdate.year);
    flush_buffer();

    // Deletion of the '\n'
    p.first_name[str_length(p.first_name) - 1] = '\0';
    p.last_name [str_length(p.last_name)  - 1] = '\0';

    p.last_purchase = -1;

    return p;
}