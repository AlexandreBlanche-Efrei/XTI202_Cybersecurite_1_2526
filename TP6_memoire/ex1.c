#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char name[10];
    int ssn;        // social security number
} user;

int main() {
  
    user users[] = {
        {                       .ssn = 0x33e1b327 },
        { .name = "Bob",        .ssn = 0x5e3c4a22 },
        { .name = "Charlie",    .ssn = 0xe487396a }
    };
    user * p1 = &users[0];
    user * p2 = &users[1];
    user * p3 = &users[2];
    
    printf("Entrez votre nom : \n");

    char arg[MAX_SIZE];
    scanf("%s", arg);

    strncpy(p1->name, arg, strlen(arg));

    printf("Bonjour %s !\n", p1->name);
  
    return 0;
}
