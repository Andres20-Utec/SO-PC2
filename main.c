#include "memory_allocation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "test.h"
int main()
{
    // test_first_fit();
    test_best_fit();
    // char entry[40];
    // struct CM_Allocation cma;
    // init_cm_allocation(&cma.list_procces, &cma.list_holes);
    // while (true)
    // {
    //     printf("\nallocator> ");
    //     fgets(entry, sizeof(entry), stdin);
    //     char *operation = strtok(entry, " ");
    //     if (strcmp(operation, "RQ") == 0)
    //     {
    //         printf("RQ\n");
    //         char *id = strtok(NULL, " ");
    //         char *char_space = strtok(NULL, " ");
    //         int space = atoi(char_space);
    //         char *method = strtok(NULL, " ");
    //         char type;
    //         if (strcmp(operation, "F") == 0)
    //             type = 'F';
    //         else if (strcmp(operation, "B") == 0)
    //             type = 'B';
    //         else if (strcmp(operation, "W") == 0)
    //             type = 'W';
    //         request(space, 'F', atoi(id), &cma.list_procces ,&cma.list_holes);
    //     }
    //     else if (strcmp(operation, "RL") == 0)
    //     {
    //         printf("RL\n");
    //         char *id = strtok(NULL, " ");
    //         release(atoi(id), &cma.list_procces ,&cma.list_holes);
    //     }
    //     else if (strcmp(operation, "C") == 0)
    //     {
    //         printf("C\n");
    //         compact(&cma.list_procces ,&cma.list_holes);
    //     }
    //     else if (strcmp(operation, "STAT") == 0)
    //     {
    //         printf("STAT\n");
    //         stat(&cma.list_procces ,&cma.list_holes);
    //     }
    //     else if (strcmp(operation, "X") == 0)
    //     {
    //         printf("X\n");
    //         exit(0);
    //     }
    //     else
    //         printf("Entry no valid\n");
    // }

    return 0;
}