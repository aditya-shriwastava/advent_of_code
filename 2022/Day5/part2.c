#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9

void move(char* from, char* to, int n){
  int from_len = strlen(from);
  int to_len = strlen(to);
  for(int i=0; i<n; i++){
    to[to_len] = from[from_len-n+i];
    from[from_len-n+i] = '\0';
    to_len++;
    /* from_len--; */
  }
}

void test(){
  char data1[100] = {0}, data2[100] = {0};
  strcat(data1, "abcdefghijklmnopqrstwxyz");
  strcat(data2, "ABCDEFGHIJKLMNOPQRSTUVWXYYZ");

  printf("data1: %s, data2: %s\n", data1, data2);
  move(data1, data2, 10);
  printf("data1: %s, data2: %s\n", data1, data2);
}

/*
        [M]     [B]             [N]
[T]     [H]     [V] [Q]         [H]
[Q]     [N]     [H] [W] [T]     [Q]
[V]     [P] [F] [Q] [P] [C]     [R]
[C]     [D] [T] [N] [N] [L] [S] [J]
[D] [V] [W] [R] [M] [G] [R] [N] [D]
[S] [F] [Q] [Q] [F] [F] [F] [Z] [S]
[N] [M] [F] [D] [R] [C] [W] [T] [M]
 1   2   3   4   5   6   7   8   9 
*/
int main(int argc, char** argv){
  /* test(); */
  /* return 0; */

  // 1. Init stack
  char stack[N][100] = {0};
  /* strcat(stack[0], "ZN"); */
  /* strcat(stack[1], "MCD"); */
  /* strcat(stack[2], "P"); */

  strcat(stack[0], "NSDCVQT");
  strcat(stack[1], "MFV");
  strcat(stack[2], "FQWDPNHM");
  strcat(stack[3], "DQRTF");
  strcat(stack[4], "RFMNQHVB");
  strcat(stack[5], "CFGNPWQ");
  strcat(stack[6], "WFRLCT");
  strcat(stack[7], "TZNS");
  strcat(stack[8], "MSDJRQHN");

  // 2. Read file
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Unable to open data.txt");
    return -1;
  }
  
  // 3. Perform all move operation
  char buf[100];
  while(fgets(buf, 100, fd)){
    char sfrom[5], sto[5], sn[5];
    int from, to, n;
    sscanf(buf, "move %5[0-9] from %5[0-9] to %5[0-9]", sn, sfrom, sto);
    n = atoi(sn);
    from = atoi(sfrom) - 1;
    to = atoi(sto) - 1;

    /* printf("n: %d, from: %d, to: %d\n", n, from, to); */
    /* for(int i=0; i<N; i++){ */
    /*   printf("%s\n", stack[i]); */
    /* } */
    /* printf("\n"); */
    move(stack[from], stack[to], n);
  }
  
  // 4. Print all top
  for(int i=0; i<N; i++){
    int len  = strlen(stack[i]);
    printf("%c", stack[i][len-1]);
  }
  printf("\n");

  fclose(fd);
  return 0;
}
