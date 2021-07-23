#include "memory_allocation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void test_first_fit(){
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
  request(50000, 'F', 10, &cma.list_procces, &cma.list_holes);
  request(30000, 'F', 11, &cma.list_procces, &cma.list_holes);
  /*for(int i = 10;i < 15; i++){
    request(6000, 'W', i);
  }*/
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
  printf("\n\n");
  request(50000, 'F', 10, &cma.list_procces, &cma.list_holes);
  request(30000, 'F', 11, &cma.list_procces, &cma.list_holes);
  /*for(int i = 10;i < 15; i++){
    request(6000, 'W', i);
  }*/
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
  request(50000, 'F', 10, &cma.list_procces, &cma.list_holes);
  request(30000, 'F', 11, &cma.list_procces, &cma.list_holes);
  /*for(int i = 10;i < 15; i++){
    request(6000, 'W', i);
  }*/
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  compact(&cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);
}