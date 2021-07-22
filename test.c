#include "memory_allocation.h"

void test_first_fit(){
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);
  printf("Request\n");

  for(int i = 0; i < 10; i++){
    if(i % 2 == 0)
      request(100000, 'F', i, &cma.list_procces, &cma.list_holes);
    else
      request(50000, 'F', i, &cma.list_procces, &cma.list_holes);
  }
  stat(&cma.list_procces, &cma.list_holes);
  printf("Release\n");
  release(1, &cma.list_procces, &cma.list_holes);
  release(6, &cma.list_procces, &cma.list_holes);
  release(8, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  //compact(&cma.list_procces, list_holes);
  //stat(&cma.list_procces, list_holes);
  request(200000, 'F', 10, &cma.list_procces, &cma.list_holes);
  request(40000, 'F', 11, &cma.list_procces, &cma.list_holes);
  /*for(int i = 10;i < 15; i++){
    request(6000, 'W', i);
  }*/
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);
  return 0;
}

void test_best_fit(){
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);
  printf("Request\n");

  for(int i = 0; i < 10; i++){
    if(i % 2 == 0)
      request(100000, 'F', i, &cma.list_procces, &cma.list_holes);
    else
      request(50000, 'F', i, &cma.list_procces, &cma.list_holes);
  }
  stat(&cma.list_procces, &cma.list_holes);
  printf("Release\n");
  release(1, &cma.list_procces, &cma.list_holes);
  release(6, &cma.list_procces, &cma.list_holes);
  release(8, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  //compact(&cma.list_procces, list_holes);
  //stat(&cma.list_procces, list_holes);
  request(200000, 'F', 10, &cma.list_procces, &cma.list_holes);
  request(40000, 'F', 11, &cma.list_procces, &cma.list_holes);
  /*for(int i = 10;i < 15; i++){
    request(6000, 'W', i);
  }*/
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);
  return 0;

}

void test_worst_fit(){
  struct CM_Allocation cma;
  init_cm_allocation(&cma.list_procces, &cma.list_holes);
  printf("Request\n");

  for(int i = 0; i < 10; i++){
    if(i % 2 == 0)
      request(100000, 'F', i, &cma.list_procces, &cma.list_holes);
    else
      request(50000, 'F', i, &cma.list_procces, &cma.list_holes);
  }
  stat(&cma.list_procces, &cma.list_holes);
  printf("Release\n");
  release(1, &cma.list_procces, &cma.list_holes);
  release(6, &cma.list_procces, &cma.list_holes);
  release(8, &cma.list_procces, &cma.list_holes);
  stat(&cma.list_procces, &cma.list_holes);
  printf("Compact\n");
  //compact(&cma.list_procces, list_holes);
  //stat(&cma.list_procces, list_holes);
  request(200000, 'F', 10, &cma.list_procces, &cma.list_holes);
  request(40000, 'F', 11, &cma.list_procces, &cma.list_holes);
  /*for(int i = 10;i < 15; i++){
    request(6000, 'W', i);
  }*/
  stat(&cma.list_procces, &cma.list_holes);
  destroy_cma(&cma.list_procces, &cma.list_holes);
  return 0;  
}