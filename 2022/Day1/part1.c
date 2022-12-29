#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Failed to open file data.txt");
    return -1;
  }

  char buf[10]; // Temp buffer on stack
  int max = 0; // Max calories
  int curr = 0; // Current Elve calory
  while(fgets(buf, 10, fd) != NULL){
    if(buf[0] == '\n'){ // CASE: Newline reached
      if(curr>max){
        max = curr;
      }
      curr = 0;
    }else{ // CASE: Has calory
      curr += atoi(buf);
    }
  }

  fclose(fd);
  printf("Max: %d\n", max);
  return 0;
}
