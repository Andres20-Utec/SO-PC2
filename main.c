#include "memory_allocation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "test.h"
int main()
{   
    printf("FIRST FIT\n");
    printf("---------------\n");
    test_first_fit();
    printf("---------------\n");
    printf("BEST FIT\n");
    printf("---------------\n");
    test_best_fit();
    printf("---------------\n");
    printf("WORST FIT\n");
    printf("---------------\n");
    test_worst_fit();
    //test_user();
    return 0;
}