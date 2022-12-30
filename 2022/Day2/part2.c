#include <stdio.h>

/*
B <- X <- C
C <- Y <- A
A <- Z <- B
*/

/*
X: lose
Y: draw
Z: win
*/

int main(int argc, char** argv){
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Cannot open file!");
    return -1;
  }

  char buf[5];
  int  total_score = 0;
  while(fgets(buf, 5, fd)){
    char u = buf[0];
    char v = buf[2];
    int p1 = 0, p2 = 0;
    if(v == 'X'){
      p2 = 0;
      if(u == 'A'){
        p1 = 3;
      }else if(u == 'B'){
        p1 = 1;
      }else if(u == 'C'){
        p1 = 2;
      }
    }else if(v == 'Y'){
      p2 = 3;
      if(u == 'A'){
        p1 = 1;
      }else if(u == 'B'){
        p1 = 2;
      }else if(u == 'C'){
        p1 = 3;
      }
    }else if (v == 'Z'){
      p2 = 6;
      if(u == 'A'){
        p1 = 2;
      }else if(u == 'B'){
        p1 = 3;
      }else if(u == 'C'){
        p1 = 1;
      }
    }
    total_score += p1 + p2;
  }
  printf("Total Score: %d\n", total_score);

  fclose(fd);
  return 0;
}
