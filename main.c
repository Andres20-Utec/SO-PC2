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

struct C_M_Allocation
{
    struct list list_procces;
    struct list list_holes;
    struct list_elem* elem_next_fit;
};

struct C_M_Allocation cma;

void add_first_hole(struct list* list_holes, int begin, int end){
  struct list_elem* first_hole = (struct list_elem *)malloc(sizeof(struct list_elem));
  first_hole->id = 0;
  first_hole->begin = begin;
  first_hole->type = 'H';
  first_hole->end = end;
  list_push_front(list_holes, first_hole);
}

void init_cm_allocation(struct list* list_holes, struct list* list_procces){
  list_init(list_procces);
  list_init(list_holes);
  cma.elem_next_fit = NULL;
  add_first_hole(list_holes, 0, MAX);
}
void request(int n_bits, char type, int id){
  struct list_elem *new_procces = (struct list_elem *)malloc(sizeof(struct list_elem));
  new_procces->type = 'P';
  new_procces->id = id;
  new_procces->end = n_bits;
  switch(type){
    case 'F':{
      if(list_size(&cma.list_holes) > 1){
        struct list_elem *current_hole = list_begin(&cma.list_holes);
        struct list_elem *last_hole = list_back(&cma.list_holes);
        while (current_hole != list_end(&cma.list_holes)){
            if (current_hole->end >= n_bits){
                break;
            }
            current_hole = list_next(current_hole);
        }
        if(current_hole == list_back(&cma.list_procces)){
          struct list_elem *last_elemt = list_back(&cma.list_procces);
          new_procces->begin = last_elemt->begin + last_elemt->end;
          list_push_back(&cma.list_procces, new_procces);
          last_hole->begin += n_bits;
          last_hole->end -= n_bits;
        }else{
          int rest = current_hole->end - n_bits;
          new_procces->begin = current_hole->begin;
          // Update Hole
          current_hole->begin = current_hole->begin + n_bits;
          current_hole->end = current_hole->end - n_bits;
          if (rest == 0)
          {
            list_remove(current_hole);
          }
          list_insert_ordered(&cma.list_procces, new_procces, sort_by_begin, NULL);
        }  
      }else{
        if(list_empty(&cma.list_procces)){
          new_procces->begin = 0;
          list_push_back(&cma.list_procces, new_procces);
        }else{
          struct list_elem *last_elem = list_back(&cma.list_procces);
          new_procces->begin = last_elem->begin + last_elem->end;
          list_push_back(&cma.list_procces, new_procces);
        }
        struct list_elem *last_hole = list_back(&cma.list_holes);
        last_hole->begin += n_bits;
        last_hole->end -= n_bits;
      }
      break;
    }case 'B':{
      if(list_size(&cma.list_holes) > 1){
        struct list_elem *current_hole = list_begin(&cma.list_holes);
        struct list_elem *last_hole = list_back(&cma.list_holes);
        int min_space = last_hole->end;
        while (current_hole != list_end(&cma.list_holes)){
            if (current_hole->end >= n_bits && min_space > current_hole->end){
                min_space = current_hole->end;
                last_hole = current_hole;
            }
            current_hole = list_next(current_hole);
        }
        if(last_hole == list_back(&cma.list_holes)){
          struct list_elem *last_elemt = list_back(&cma.list_procces);
          new_procces->begin = last_elemt->begin + last_elemt->end;
          list_push_back(&cma.list_procces, new_procces);
          last_hole->begin += n_bits;
          last_hole->end -= n_bits;
          if(last_hole->end == 0){
            list_remove(last_hole);
          }
        }else{
          int rest = last_hole->end - n_bits;
          new_procces->begin = last_hole->begin;
          // Update Hole
          last_hole->begin = last_hole->begin + n_bits;
          last_hole->end = last_hole->end - n_bits;
          if (rest == 0){
            list_remove(last_hole);
          }
          list_insert_ordered(&cma.list_procces, new_procces, sort_by_begin, NULL);
        }
      }else{
        if(list_empty(&cma.list_procces)){
          new_procces->begin = 0;
          list_push_back(&cma.list_procces, new_procces);
        }else{
          struct list_elem *last_elem = list_back(&cma.list_procces);
          new_procces->begin = last_elem->begin + last_elem->end;
          list_push_back(&cma.list_procces, new_procces);
        }
        struct list_elem *last_hole = list_back(&cma.list_holes);
        last_hole->begin += n_bits;
        last_hole->end -= n_bits;
      }
      break;
    }case 'W':{
      if(list_size(&cma.list_holes) > 1){
        int position = cma.elem_next_fit->begin + cma.elem_next_fit->end;
        printf("%d\n", position);
        struct list_elem *current_hole = list_begin(&cma.list_holes);
        while (current_hole != list_end(&cma.list_holes)){
            if (current_hole->end >= n_bits && current_hole->begin >= position){
              break;
            }
            current_hole = list_next(current_hole);
        }
        if(current_hole == list_back(&cma.list_holes)){
          struct list_elem *last_elemt = list_back(&cma.list_procces);
          new_procces->begin = last_elemt->begin + last_elemt->end;
          list_push_back(&cma.list_procces, new_procces);
          current_hole->begin += n_bits;
          current_hole->end -= n_bits;
          if(current_hole->end == 0){
            list_remove(current_hole);
          }
        }else{
          int rest = current_hole->end - n_bits;
          new_procces->begin = current_hole->begin;
          current_hole->begin += n_bits;
          current_hole->end -= n_bits;
          if(rest == 0)
            list_remove(current_hole);
        }
        list_insert_ordered(&cma.list_procces, new_procces, sort_by_begin, NULL);
        cma.elem_next_fit = new_procces;
      }else{
        if(list_empty(&cma.list_procces)){
          new_procces->begin = 0;
          list_push_back(&cma.list_procces, new_procces);
        }else{
          struct list_elem *last_elem = list_back(&cma.list_procces);
          new_procces->begin = last_elem->begin + last_elem->end;
          list_push_back(&cma.list_procces, new_procces);
        }
        cma.elem_next_fit = new_procces;
        struct list_elem *last_hole = list_back(&cma.list_holes);
        last_hole->begin += n_bits;
        last_hole->end -= n_bits;
      }
      break;
    }
    default:
    printf("Doesn't work\n");
    break;
  }
}

void destroy_cma(struct list *list_procces, struct list *list_holes){
  while(!list_empty(list_procces)){
    list_pop_front(list_procces);
  }

  while (!list_empty(list_holes)){
      list_pop_front(list_holes);
  }
}

void compact(struct list *list_process, struct list *list_holes)
{
  struct list_elem *e = NULL;
  int last_begin = 0;
  for (e = list_begin(list_process); e != list_end(list_process); e = list_next(e)){
      if (last_begin == 0){
          last_begin = e->begin + e->end;
          e->begin = 0;
      }
      else{
          e->begin = last_begin + e->end;
          last_begin = e->begin + e->end;
      }
  }
  while (!list_empty(list_holes)){
    list_pop_front(list_holes);
  }
  add_first_hole(list_holes, last_begin, MAX - last_begin);
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

  struct list_elem* backUp = e;
  list_remove(e);
  backUp->type = H;

  // Insertamos en la lista de holes, el proceso eliminado
  list_insert_ordered(list_holes, backUp, sort_by_begin, NULL);
  return true;
}

void stat(struct list *list_procces, struct list *list_holes){

  if(list_empty(list_procces)){
    struct list_elem *last_hole = list_back(&cma.list_holes);
    printf("[%d:%d] Unused\n", last_hole->begin, last_hole->end);
    return;
  }
  struct list_elem *current_procces = list_begin(list_procces);
  struct list_elem *current_hole = list_begin(list_holes);
  while(current_procces!=list_end(list_procces) && current_hole!=list_end(list_holes)){
    if(current_procces->begin < current_hole->begin){
      printf("[%d:%d] Process%d\n", current_procces->begin, current_procces->end, current_procces->id);
      current_procces = list_next(current_procces);
    }else{
      printf("[%d:%d] Unused\n", current_hole->begin, current_hole->end);
      current_hole = list_next(current_hole);
    }
  }
  while(current_procces != list_end(list_procces)){  
      printf("[%d:%d] Process%d\n", current_procces->begin, current_procces->end, current_procces->id);
      current_procces = list_next(current_procces);
  }
  while(current_hole!=list_end(list_holes)){
    printf("[%d:%d] Unused\n", current_hole->begin, current_hole->end);
    current_hole = list_next(current_hole);

  } 
}


int main()
{
    char entry[40];
    init_cm_allocation(&cma.list_holes,&cma.list_procces);
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
            int space = atoi(char_space);
            char *method = strtok(NULL, " ");
            char type;
            if (strcmp(operation, "F") == 0)
                type = 'F';
            else if (strcmp(operation, "B") == 0)
                type = 'B';
            else if (strcmp(operation, "W") == 0)
                type = 'W';
            request(space, 'F', atoi(id));
        }
        else if (strcmp(operation, "RL") == 0)
        {
            printf("RL\n");
            char *id = strtok(NULL, " ");
            release(atoi(id), &cma.list_procces, &cma.list_holes);
        }
        else if (strcmp(operation, "C") == 0)
        {
            printf("C\n");
            compact(&cma.list_procces, &cma.list_holes);
        }
        else if (strcmp(operation, "STAT") == 0)
        {
            printf("STAT\n");
            stat(&cma.list_procces, &cma.list_holes);
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