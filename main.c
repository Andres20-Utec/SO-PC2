#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#define MAX 1048576 - 1



struct C_M_Allocation{
    char *stack;
    struct list p_h_list;
};

struct C_M_Allocation cma;

void init_C_M_Allocation(){
    cma.stack = (char *) malloc(MAX);
    list_init(&cma.p_h_list);
    //struct list_elemt *elem = 
};

void request();
void release();
void compact();
void stat();


int main(){
    char operation[30];

    while(true)
    {
        fgets(operation, sizeof(operation), stdin);
        /*
            1. Separar el string.
            2. Verificar la primera palabra de operation, para verificar qué operación hacer.
            3. Realizar operación dependiendo del tipo de operación.
        */
    }


    return 0;
}