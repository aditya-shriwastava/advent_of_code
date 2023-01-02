#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*
-----a---------b----------
-------x-----y------------

        or

--------a---b-------------
-------x-----y------------
*/ 
bool fully_contains(int a, int b, int x, int y){
  if( (x>=a && b>=y) || (a>=x && y>=b) ){
    return true;
  }else{
    return false;
  }
}

int main(int argc, char** argv){
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Unable to open data.txt");
    return -1;
  }

  char buf[50] = {0};
  int total = 0;
  while(fgets(buf, 50, fd)){
    int a, b, x, y;
    char aa[6] = {0}, bb[6] = {0}, xx[6] = {0}, yy[6] = {0};
    sscanf(buf, "%5[0-9]-%5[0-9],%5[0-9]-%5[0-9]", aa, bb, xx, yy);
    a = atoi(aa);
    b = atoi(bb); assert(b>=a);
    x = atoi(xx);
    y = atoi(yy); assert(y >= x);

    if(fully_contains(a, b, x, y)){
      total += 1;
    }
  }
  printf("total: %d\n", total);

  fclose(fd);
  return 0;
}

