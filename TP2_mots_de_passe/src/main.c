#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "interface.h"

#include "bruteforce.h"
#include "md2.h"

int main() {

    database db = create_database();
    init_database(&db);

    main_menu(&db);

    return EXIT_SUCCESS;
}