#include "memory_allocation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void test_first_fit(){
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);
  printf("Request\n");
  request(100000, 'F', 1, &cma.list_procces, &cma.list_holes);
  request(70000, 'F', 2, &cma.list_procces, &cma.list_holes);
  request(60000, 'F', 3, &cma.list_procces, &cma.list_holes);
  request(80000, 'F', 4, &cma.list_procces, &cma.list_holes);
  request(40000, 'F', 5, &cma.list_procces, &cma.list_holes);
  request(90000, 'F', 6, &cma.list_procces, &cma.list_holes);
  request(10000, 'F', 7, &cma.list_procces, &cma.list_holes);
  request(50000, 'F', 8, &cma.list_procces, &cma.list_holes);
  request(55000, 'F', 9, &cma.list_procces, &cma.list_holes);
  request(50000, 'F', 10, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Release\n");
  release(1, &cma.list_procces, &cma.list_holes);
  release(6, &cma.list_procces, &cma.list_holes);
  release(8, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("ADD SOME PROCCESESS\n");
  request(50000, 'F', 11, &cma.list_procces, &cma.list_holes);
  request(30000, 'F', 12, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  compact(&cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);

}

void test_best_fit(){
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);
  printf("Request\n");
  request(100000, 'B', 1, &cma.list_procces, &cma.list_holes);
  request(70000, 'B', 2, &cma.list_procces, &cma.list_holes);
  request(60000, 'B', 3, &cma.list_procces, &cma.list_holes);
  request(80000, 'B', 4, &cma.list_procces, &cma.list_holes);
  request(40000, 'B', 5, &cma.list_procces, &cma.list_holes);
  request(90000, 'B', 6, &cma.list_procces, &cma.list_holes);
  request(10000, 'B', 7, &cma.list_procces, &cma.list_holes);
  request(50000, 'B', 8, &cma.list_procces, &cma.list_holes);
  request(55000, 'B', 9, &cma.list_procces, &cma.list_holes);
  request(50000, 'B', 10, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Release\n");
  release(1, &cma.list_procces, &cma.list_holes);
  release(6, &cma.list_procces, &cma.list_holes);
  release(8, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("ADD SOME PROCCESESS\n");
  request(50000, 'B', 11, &cma.list_procces, &cma.list_holes);
  request(30000, 'B', 12, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  compact(&cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);


}

void test_worst_fit(){
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);

  printf("Request\n");
  request(100000, 'W', 1, &cma.list_procces, &cma.list_holes);
  request(70000, 'W', 2, &cma.list_procces, &cma.list_holes);
  request(60000, 'W', 3, &cma.list_procces, &cma.list_holes);
  request(80000, 'W', 4, &cma.list_procces, &cma.list_holes);
  request(40000, 'W', 5, &cma.list_procces, &cma.list_holes);
  request(90000, 'W', 6, &cma.list_procces, &cma.list_holes);
  request(10000, 'W', 7, &cma.list_procces, &cma.list_holes);
  request(50000, 'W', 8, &cma.list_procces, &cma.list_holes);
  request(55000, 'W', 9, &cma.list_procces, &cma.list_holes);
  request(50000, 'W', 10, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Release\n");
  release(1, &cma.list_procces, &cma.list_holes);
  release(6, &cma.list_procces, &cma.list_holes);
  release(8, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("ADD SOME PROCCESESS\n");
  request(50000, 'W', 11, &cma.list_procces, &cma.list_holes);
  request(30000, 'W', 12, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  compact(&cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);
}

void test_user(){
  char entry[30];
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);
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
          request(space, *operation , atoi(id), &cma.list_procces ,&cma.list_holes);
      }
      else if (strcmp(operation, "RL") == 0)
      {
          printf("RL\n");
          char *id = strtok(NULL, " ");
          release(atoi(id), &cma.list_procces ,&cma.list_holes);
      }
      else if (strcmp(operation, "C") == 0)
      {
          printf("C\n");
          compact(&cma.list_procces ,&cma.list_holes);
      }
      else if (strcmp(operation, "STAT") == 0)
      {
          printf("STAT\n");
          stat(&cma.list_procces ,&cma.list_holes);
      }
      else if (strcmp(operation, "X") == 0)
      {
          printf("X\n");
          exit(0);
      }
      else
          printf("Entry no valid\n");
  }
}