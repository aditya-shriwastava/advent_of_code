#include <stdio.h>
#include <stdlib.h>

void insert(int* max, int index, int data){
  for(int i=2; i>index; i--){
    max[i] = max[i-1];
  }
  max[index] = data;
}

int main(int argc, char** argv){
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Failed to open file data.txt");
    return -1;
  }

  char buf[10]; // Temp buffer on stack
  int max[3] = {0, 0, 0}; // Top 3 calories
  int curr = 0; // Current Elve calory
  while(fgets(buf, 10, fd) != NULL){
    if(buf[0] == '\n'){ // CASE: Newline reached
      for(int i=0; i<3; i++){
        if(curr > max[i]){
          insert(max, i, curr);
          break;
        }
      }
      curr = 0;
    }else{
      curr += atoi(buf);
    }
  }

  fclose(fd);
  printf("Max: %d + %d + %d = %d\n", max[0], max[1], max[2], max[0] + max[1] + max[2]);
  return 0;
}
