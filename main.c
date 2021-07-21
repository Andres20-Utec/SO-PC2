#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#define MAX 1048576

bool sort_by_begin(struct list_elem *elem1, struct list_elem *elem2, void *aux)
{
    return elem1->begin < elem2->begin;
}

enum insertion_Type
{
    F,
    B,
    W
};

struct C_M_Allocation
{
    struct list list_process;
    struct list list_holes;
};

struct C_M_Allocation cma;

void init_C_M_Allocation()
{
    list_init(&cma.list_process);
    list_init(&cma.list_holes);
    struct list_elem *first_hole = (struct list_elem *)malloc(sizeof(struct list_elem *));
    first_hole->id = 0;
    first_hole->begin = 0;
    first_hole->type = H;
    first_hole->end = MAX;
    list_push_back(&cma.list_holes, first_hole);
};

void request(long int n_bits, enum insertion_Type type, int id)
{
    struct list_elem *new_process = (struct list_elem *)malloc(sizeof(struct list_elem *));
    new_process->type = P;
    new_process->id = id;
    new_process->end = n_bits;
    printf("HELLO1\n");
    switch (type)
    {
    default:
    {
        if (list_size(&cma.list_holes) > 1)
        {
            printf("HELLO2\n");
            struct list_elem *current_hole = list_front(&cma.list_holes);
            while (current_hole)
            {
                if (current_hole->end >= n_bits)
                {
                    break;
                }
                current_hole = list_next(current_hole);
            }
            if (current_hole)
            {
                struct list_elem *current_process = list_front(&cma.list_process);
                long int rest = current_hole->end - n_bits;
                current_process->begin = current_hole->begin;
                current_process->end = n_bits;
                current_hole->begin = current_hole->begin + n_bits;
                current_hole->end = current_hole->end + n_bits;
                if (!rest)
                {
                    list_remove(current_hole);
                }
                list_insert_ordered(&cma.list_process, new_process, &sort_by_begin, NULL);
            }
            else
            {
                struct list_elem *last_elemt = list_back(&cma.list_process);
                new_process->begin = last_elemt->begin + last_elemt->end;
                list_push_back(&cma.list_process, new_process);
                struct list_elem *last_hole = list_back(&cma.list_holes);
                last_hole->begin += n_bits;
                last_hole->end -= n_bits;
            }
        }
        else
        {
            printf("It's working\n");
            if (list_empty(&cma.list_process))
            {
                new_process->begin = 0;
                list_push_back(&cma.list_process, new_process);
            }
            else
            {
                struct list_elem *last_elemt = list_back(&cma.list_process);
                printf("%ld : %ld ", last_elemt->begin, last_elemt->end);
                new_process->begin = last_elemt->begin + last_elemt->end;
                printf("%ld : %ld", new_process->begin, new_process->end);
                list_push_back(&cma.list_process, new_process);
            }
            struct list_elem *last_hole = list_back(&cma.list_holes);
            last_hole->begin += n_bits;
            last_hole->end -= n_bits;
        }
        break;
    }
    case B:
    {
        if (!list_empty(&cma.list_holes))
        {
            struct list_elem *best_process = NULL;
            int m = MAX;
            struct list_elem *current_hole = list_front(&cma.list_holes);
            while (current_hole)
            {
                if (current_hole->end >= n_bits)
                {
                    best_process = current_hole;
                }
                current_hole = list_next(current_hole);
            }
        }
        else
        {
            if (list_empty(&cma.list_process))
            {
                new_process->begin = 0;
                list_push_back(&cma.list_process, new_process);
            }
            else
            {
                struct list_elem *last_elemt = list_back(&cma.list_process);
                new_process->begin = last_elemt->begin + last_elemt->end;
                list_push_back(&cma.list_process, new_process);
            }
        }
        break;
    }

    case W:
    {
        if (!list_empty(&cma.list_holes))
        {
        }
        else
        {
            if (list_empty(&cma.list_process))
            {
                new_process->begin = 0;
                list_push_back(&cma.list_process, new_process);
            }
            else
            {
                struct list_elem *last_elemt = list_back(&cma.list_process);
                new_process->begin = last_elemt->begin + last_elemt->end;
                list_push_back(&cma.list_process, new_process);
            }
        }
        break;
    }
    }
}
bool release(int id, struct list *list_process, struct list *list_holes)
{
    struct list_elem *e = NULL;
    int last_begin = 0;

    // Buscamos proceso por id
    for (e = list_begin(list_process); e != list_end(list_process); e = list_next(e))
    {
        if (e->id == id)
        {
            break;
        }
    }

    // En caso de que no exista tal proceso
    if (!e)
        return false;

    e = list_remove(e);
    e->type = H;

    // Insertamos en la lista de holes, el proceso eliminado
    list_insert_ordered(list_holes, e, &sort_by_begin, NULL);
    return true;
}

void compact(struct list *list_process, struct list *list_holes)
{
    struct list_elem *e = NULL;
    int last_begin = 0;
    for (e = list_begin(list_process); e != list_end(list_process); e = list_next(e))
    {
        if (last_begin == 0)
        {
            last_begin = e->begin + e->end;
            e->begin = 0;
        }
        else
        {
            e->begin = last_begin + e->end;
            last_begin = e->begin + e->end;
        }
    }
    while (!list_empty(list_holes))
    {
        list_pop_front(list_holes);
    }
}

void stat(struct list *list_process, struct list *list_holes)
{
    if (list_empty(list_process))
    {
        printf("No existen procesos.\n");
        return;
    }
    struct list_elem *current_proccess = list_front(list_process);
    struct list_elem *current_hole = list_front(list_holes);
    while (!is_the_last_(current_hole) && !is_the_last_(current_proccess)){
        if (current_proccess->begin < current_hole->begin){
            printf("[%ld:%ld] Process%d\n", current_proccess->begin, current_proccess->end, current_proccess->id);
            current_proccess = list_next(current_proccess);
        }
        else{
            printf("[%ld:%ld] Unused\n", current_hole->begin, current_hole->end);
            current_hole = list_next(current_hole);
        }
    }

    while (!is_the_last_(current_proccess)){
        printf("[%ld:%ld] Process%d\n", current_proccess->begin, current_proccess->end, current_proccess->id);
        current_proccess = list_next(current_proccess);
    }

    while (!is_the_last_(current_hole)){
        printf("[%ld:%ld] Unused\n", current_hole->begin, current_hole->end);
        current_hole = list_next(current_hole);
    }
}

int main()
{
    char entry[40];
    init_C_M_Allocation();
    while (true)
    {
        printf("\nallocator> ");
        fgets(entry, sizeof(entry), stdin);
        char *operation = strtok(entry, " ");
        if (strcmp(operation, "RQ") == 0)
        {
            printf("RQ\n");
            char *id = strtok(NULL, " ");
            char *char_space = strtok(NULL, " ");
            long long space = atol(char_space);
            char *method = strtok(NULL, " ");
            enum insertion_Type type;

            if (strcmp(operation, "F") == 0)
                type = F;
            else if (strcmp(operation, "B") == 0)
                type = B;
            else if (strcmp(operation, "W") == 0)
                type = W;
            request(space, type, atol(id));
        }
        else if (strcmp(operation, "RL") == 0)
        {
            printf("RL\n");
            char *id = strtok(NULL, " ");
            release(atol(id), &cma.list_process, &cma.list_holes);
        }
        else if (strcmp(operation, "C") == 0)
        {
            printf("C\n");
            compact(&cma.list_process, &cma.list_holes);
        }
        else if (strcmp(operation, "STAT") == 0)
        {
            printf("STAT\n");
            stat(&cma.list_process, &cma.list_holes);
        }
        else if (strcmp(operation, "X") == 0)
        {
            printf("X\n");
            exit(0);
        }
        else
            printf("Entry no valid\n");

        
    }

    return 0;
}