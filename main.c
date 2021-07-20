#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#define MAX 1048576

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
    struct list_elem *current_hole = list_front(&cma.list_holes);
    struct list_elem *current_process = list_front(&cma.list_procces);
    switch (type){
        case F:          
            struct list_elem *new_process = (struct list_elem*)malloc(sizeof(struct list_elem*));
            new_process->type = P;
            new_process->id = id;
            new_process->end = n_bits;
            struct list_elem *last_elemt = list_back(&cma.list_procces);
            if(current_hole){
                while(current_hole){
                    if(current_hole->end >= n_bits){
                        break;
                    }
                    current_hole = list_next(current_hole);
                }
                if(current_hole){
                    int rest = current_hole->end - n_bits;
                    if(!rest){
                        
                    }
                    else if(current_hole->prev == NULL){
                        
                    }else{
                        current_process->begin = current_hole->begin;
                        current_process->end = n_bits;
                        current_hole->begin = current_hole->begin + n_bits;
                        current_hole->end = current_hole->end + n_bits;
                    }
                }else{
                    new_process->begin = last_elemt->begin + last_elemt->end;
                    list_push_back(&cma.list_procces, new_process);
                }
            }else{
                if(!last_elemt){
                    new_process->begin = 0;
                    list_push_back(&cma.list_procces, new_process);
                }else{
                    new_process->begin = last_elemt->begin + last_elemt->end;
                    list_push_back(&cma.list_procces, new_process);
                }
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
void release(){

}

void merge_holes(struct list_elem* first, struct list_elem* second){
    
}
void compact(){
}

void stat(){
    struct list_elem *current_proccess = list_front(&cma.list_procces);
    struct list_elem *current_hole = list_front(&cma.list_holes);
    while(current_proccess && current_hole){
        if(current_proccess->begin < current_hole->begin){
            printf("[%d:%d] Process%d\n",current_proccess->begin, current_proccess->end, current_proccess->id);
            current_proccess = list_next(current_proccess);
        }else{
            printf("[%d:%d] Unused\n",current_hole->begin, current_hole->end);
            current_hole = list_next(current_hole);
        }
    }

    while(current_proccess){
        printf("[%d:%d] Process%d\n",current_proccess->begin, current_proccess->end, current_proccess->id);
        current_proccess = list_next(current_proccess);
    }

    while(current_hole){
        printf("[%d:%d] Unused\n",current_hole->begin, current_hole->end);
        current_hole = list_next(current_hole);
    }
}


int main(){
    char entry[30];

    while(true)
    {
        printf("\nallocator> ");
        fgets(entry, sizeof(entry), stdin);
        char *operation = strtok(entry, " ");
        if(strcmp(operation, "RQ") == 0) 
        {
           char *id = strtok(NULL, " ");
           char *char_space = strtok(NULL, " ");
           int space = atoi(char_space);
           char *method = strtok(NULL, " ");
           printf("%s \n", id);
           printf("%s \n", char_space);
           printf("%s \n", method);
        }
        else if(strcmp(operation, "RL") == 0) 
        {
           char* id = strtok(NULL, " ");
           printf("RL\n"); 
        }
        else if(strcmp(operation, "C") == 0) 
        {
           printf("C\n"); 
        }
        else if(strcmp(operation, "STAT") == 0) 
            stat();
        else if(strcmp(operation, "X") == 0) 
        {
           exit(0);
        }
        else 
            printf("Entry no valid\n");
    }


    return 0;
}