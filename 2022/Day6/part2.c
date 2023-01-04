#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_first_n_different(const char* data, int n){
  for(int j=0; j<n; j++){
    for(int k=j+1; k<n; k++){
      if(data[j] == data[k]){
        return false;
      }
    }
  }
  return true;
}

int first_marker(const char* data){
  for(int i=0; true; i++){
    if(is_first_n_different(data + i, 14)){
      return i + 14;
    }
  }
  return 0;
}

void test(){
  char test_data[100] = {0};
  strcat(test_data, "mjqjpqmgbljsphdztnvjfqwrcgsmlb");
  printf("First Marker: %d\n", first_marker(test_data));
}

int main(int argc, char** argv){
  /* test(); */
  /* return 0; */

  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Inable to open data.txt");
    return -1;
  }

  char data[5000];
  fgets(data, 5000, fd);
  printf("First Marker: %d\n", first_marker(data));

  fclose(fd);
  return 0;
}
