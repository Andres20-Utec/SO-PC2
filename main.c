#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#define MAX 1048576 - 1

enum insertion_Type{
  F,
  B,
  W
};

struct C_M_Allocation{
    struct list list_procces;
    struct list list_holes;
};

struct C_M_Allocation cma;

void init_C_M_Allocation(){
    list_init(&cma.list_procces);
    list_init(&cma.list_holes);
    //struct list_elemt *elem = 
};

void request(size_t n_bits, enum insertion_Type type, int id){
    struct list_elem *current_hole = list_head(&cma.list_holes);
    struct list_elem *current_process = list_head(&cma.list_procces);
    switch (type){
        case F:
            if(current_hole){
                while(current_hole){
                    if(current_hole->end >= n_bits){
                        break;
                    }
                    current_hole = list_next(current_hole);
                }
                if(current_hole){
                    if(current_hole->prev == NULL){

                    }else{

                    }
                }else{
                    struct list_elem *new_process = (struct list_elem*)malloc(sizeof(struct list_elem*));
                    new_process->id = id;
                    new_process->end = n_bits;     
                }
            }else{
                
            }
            break;
        case B:
            if(current_hole){

            }else{

            }
            break;

        case W:
            if(current_hole){

            }else{

            }
            break;
    }
}
void release();
void merge_holes();
void compact();
void stat(){
    struct list_elem *current_proccess = list_head(&cma.list_procces);
    struct list_elem *current_hole = list_head(&cma.list_holes);
    while(current_proccess && current_hole){
        if(current_proccess->begin < current_hole->begin){
            printf("[%d:%d] Process%d",current_proccess->begin, current_proccess->end, current_proccess->id);
            current_proccess = list_next(current_proccess);
        }else{
            printf("[%d:%d] Unused",current_hole->begin, current_hole->end);
            current_hole = list_next(current_hole);
        }
    }

    while(current_proccess){
        printf("[%d:%d] Process%d",current_proccess->begin, current_proccess->end, current_proccess->id);
        current_proccess = list_next(current_proccess);
    }

    while(current_hole){
        printf("[%d:%d] Unused",current_hole->begin, current_hole->end);
        current_hole = list_next(current_hole);
    }
}


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