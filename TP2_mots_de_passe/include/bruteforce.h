#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "database.h"

char * bruteforce(database *db, unsigned char *hash);

void launch_bruteforce(database *db);

#endif