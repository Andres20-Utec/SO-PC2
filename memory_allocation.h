#ifndef __LIB_MEMORY_ALLOCATION_H
#define __LIB_MEMORY_ALLOCATION_H
#include "debug.h"
#include "list.h"
struct CM_Allocation{
  struct list list_procces;
  struct list list_holes;
};


void add_first_hole(struct list* list_holes, int begin, int end);
void init_cm_allocation(struct list* list_procces, struct list* list_holes);

// Methods
struct list_elem* first_fit(int n_bits, struct list* list_holes);
struct list_elem* best_fit(int n_bits, struct list* list_holes);
struct list_elem* worst_fit(int n_bits, struct list* list_holes);

bool request(int n_bits, char type, int id, struct list* list_procces, struct list* list_holes);
void destroy_cma(struct list *list_procces, struct list *list_holes);
void compact(struct list *list_process, struct list *list_holes);
bool release(int id, struct list *list_procces, struct list *list_holes);
void stat(struct list *list_procces, struct list *list_holes);

bool sort_by_begin(const struct list_elem *elem1,const struct list_elem *elem2, void *aux UNUSED);

#endif