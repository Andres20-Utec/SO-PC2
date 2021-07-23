#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "memory_allocation.h"
#include "debug.h"
#include "list.h"
#define MAX_bits 1048576


bool sort_by_begin(const struct list_elem *elem1,const struct list_elem *elem2, void *aux UNUSED)
{
    return elem1->begin < elem2->begin;
}

bool max_space_elem(const struct list_elem *elem1,const struct list_elem *elem2, void *aux UNUSED){
    int e1 = elem1->end - elem1->begin;
    int e2 = elem2->end - elem2->begin;
    return e1 < e2;
}

void add_first_hole(struct list* list_holes, int begin, int end){
    struct list_elem* first_hole = (struct list_elem *)malloc(sizeof(struct list_elem));
    first_hole->id = 0;
    first_hole->begin = begin;
    first_hole->type = 'H';
    first_hole->end = end;
    list_push_front(list_holes, first_hole);
}


void init_cm_allocation(struct list* list_procces, struct list* list_holes){
    list_init(list_procces);
    list_init(list_holes);
    add_first_hole(list_holes, 0, MAX_bits);
}

struct list_elem* first_fit(int n_bits, struct list* list_holes){
    struct list_elem *current_hole = list_begin(list_holes);
    while (current_hole != list_end(list_holes)){
        if ((current_hole->end - current_hole->begin) >= n_bits){
            break;
        }
        current_hole = list_next(current_hole);
    }
    return current_hole;
}

struct list_elem* best_fit(int n_bits, struct list* list_holes){
    struct list_elem *current_hole = list_begin(list_holes);
    struct list_elem *last_hole = NULL;
    struct list_elem *bigger_space = list_max(list_holes, max_space_elem, NULL);
    int min_space = MAX_bits;
    while (current_hole != list_end(list_holes)){
        if ((current_hole->end - current_hole->begin) >= n_bits && min_space >= (current_hole->end - current_hole->begin)){
            printf("%d\n",min_space);
            min_space = current_hole->end - current_hole->begin;
            last_hole = current_hole;
        }
        printf("%d\n",min_space);
        current_hole = list_next(current_hole);
    }
    return last_hole;
}

struct list_elem* worst_fit(int n_bits, struct list* list_holes){
    struct list_elem *current_hole = list_begin(list_holes);
    struct list_elem *save_hole = NULL;
    int bigger_space = n_bits;
    while (current_hole != list_end(list_holes)){
        if ((current_hole->end - current_hole->begin) >= n_bits && (current_hole->end - current_hole->begin) >= bigger_space){
        save_hole = current_hole;
        bigger_space = (current_hole->end - current_hole->begin);
        }
        current_hole = list_next(current_hole);
    }
    return save_hole;
}

bool request(int n_bits, char type, int id, struct list* list_procces, struct list* list_holes){
    struct list_elem *new_procces = (struct list_elem *)malloc(sizeof(struct list_elem));
    new_procces->type = 'P';
    new_procces->id = id;

    if(list_size(list_holes) > 1){
    struct list_elem* current_hole = NULL;
    if(type == 'F'){
        current_hole = first_fit(n_bits, list_holes);
    }else if(type == 'B'){
        current_hole = best_fit(n_bits, list_holes);
    }else if(type == 'W'){
        current_hole = worst_fit(n_bits, list_holes);
    }
    if(current_hole != list_end(list_holes)){
        int rest = current_hole->end - n_bits;
        new_procces->begin = current_hole->begin;
        new_procces->end = new_procces->begin + n_bits;
        // Update Hole
        current_hole->begin = new_procces->end;
        //current_hole->end = current_hole->end - n_bits;
        if (rest == 0){
            list_remove(current_hole);
        }
        list_insert_ordered(list_procces, new_procces, sort_by_begin, NULL);
    }else{
        printf("There isn't enough space to %d\n", n_bits);
        return false;
        } 
    }else{
        struct list_elem* last_hole = list_back(list_holes);
        if(n_bits > last_hole->end){
            printf("There isn't enough space to %d bits. \n", n_bits);
            return false;
        }
        if(list_empty(list_procces)){
            new_procces->begin = 0;
            new_procces->end = n_bits;
            list_push_back(list_procces, new_procces);
        }else{
            struct list_elem *last_elem = list_back(list_procces);
            new_procces->begin = last_elem->end;
            new_procces->end = new_procces->begin + n_bits;
            list_push_back(list_procces, new_procces);
        }
        last_hole->begin += n_bits;
        last_hole->end -= n_bits;
    }
    return true;
}

void destroy_cma(struct list *list_procces, struct list *list_holes){
  while(!list_empty(list_procces)){
    list_pop_front(list_procces);
  }

  while (!list_empty(list_holes)){
      list_pop_front(list_holes);
  }
}

void compact(struct list *list_process, struct list *list_holes){
    struct list_elem *e = NULL;
    int last_begin = 0;
    for (e = list_begin(list_process); e != list_end(list_process); e = list_next(e)){
        if (last_begin == 0){
            e->end = e->end - e->begin;
            e->begin = 0;
            last_begin = e->end;
        }else{
            int n_bits = e->end - e->begin;
            e->begin = last_begin;
            e->end = e->begin + n_bits;
            last_begin = e->end;
        }
    }
    while (!list_empty(list_holes)){
        list_pop_front(list_holes);
    }
    add_first_hole(list_holes, last_begin, MAX_bits - last_begin);
}


bool release(int id, struct list *list_procces, struct list *list_holes){
  struct list_elem *e = NULL;

  // Buscamos proceso por id
    for (e = list_begin(list_procces); e != list_end(list_procces); e = list_next(e)){
        if (e->id == id){
            break;
        }
    }

    // En caso de que no exista tal proceso
    if (e == list_end(list_procces))
        return false;

    struct list_elem* save_node = e;
    list_remove(e);
    save_node->type = 'H';

    // Insertamos en la lista de holes, el proceso eliminado
    list_insert_ordered(list_holes, save_node, sort_by_begin, NULL);
    return true;
}

void stat(struct list *list_procces, struct list *list_holes){

    if(list_empty(list_procces)){
        struct list_elem *last_hole = list_back(list_holes);
        printf("Addresesses [%d:%d] Unused\n", last_hole->begin, last_hole->end);
        return;
    }
    struct list_elem *current_procces = list_begin(list_procces);
    struct list_elem *current_hole = list_begin(list_holes);
    while(current_procces!=list_end(list_procces) && current_hole!=list_end(list_holes)){
        if(current_procces->begin < current_hole->begin){
            printf("Addresesses [%d:%d] Process%d\n", current_procces->begin, current_procces->end, current_procces->id);
            current_procces = list_next(current_procces);
        }else{
            printf("Addresesses [%d:%d] Unused\n", current_hole->begin, current_hole->end);
            current_hole = list_next(current_hole);
        }
    }
    while(current_procces != list_end(list_procces)){  
        printf("Addresesses [%d:%d] Process%d\n", current_procces->begin + 1, current_procces->end, current_procces->id);
        current_procces = list_next(current_procces);
    }
    while(current_hole!=list_end(list_holes)){
        printf("Addresesses [%d:%d] Unused\n", current_hole->begin, current_hole->end);
        current_hole = list_next(current_hole);
    }
}