#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Grid{
  int width;
  int height;
  int data[100000];
};

void populate_grid(FILE* fd, struct Grid* gd){
  int i=0;
  int j=0;
  while(true){
    char ch = fgetc(fd);
    if(ch == '\n'){
      gd->width = i;
      gd->height++;
      j++;
      i = 0;
    }else{
      gd->data[(j * gd->width) + i] = ch - 48;
      i++;
    }
    if(feof(fd)){
      printf("Width: %d, Height: %d\n", gd->width, gd->height);
      break;
    }
  }
}

void print_grid(struct Grid* gd){
  for(int j=0; j<gd->height; j++){
    for(int i=0; i<gd->width; i++){
      printf("%d", gd->data[i + (gd->width * j)]);
    }
    printf("\n");
  }
}

/*
    i   
  30373
  25512
j 65332
  33549
  35390
*/
int get_score(struct Grid* gd, int i, int j){
  // Score left
  int score_left = 0;
  for(int k=i-1; k>=0; k--){
    score_left++;
    if(gd->data[k + (j * gd->width)] >= gd->data[i + (j * gd->width)]){
      break;
    }
  }
  
  // Score right
  int score_right = 0;
  for(int k=i+1; k<gd->width; k++){
    score_right++;
    if(gd->data[k + (j * gd->width)] >= gd->data[i + (j * gd->width)]){
      break;
    }
  }
  
  // Score top
  int score_top = 0;
  for(int k=j-1; k>=0; k--){
    score_top++;
    if(gd->data[i + (k * gd->width)] >= gd->data[i + (j * gd->width)]){
      break;
    }
  }
  
  // Score bottom
  int score_bottom = 0;
  for(int k=j+1; k<gd->height; k++){
    score_bottom++;
    if(gd->data[i + (k * gd->width)] >= gd->data[i + (j * gd->width)]){
      break;
    }
  }

  return score_left * score_right * score_top * score_bottom;
}

int get_max_score(struct Grid* gd){
  int max_score = 0;
  for(int j=0; j<gd->height; j++){
    for(int i=0; i<gd->width; i++){
      int score = get_score(gd, i, j);
      if(score > max_score){
        max_score = score;
      }
    }
  }
  return max_score;
}

int main(int argc, char** argv){
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Unable to open data.txt");
    return -1;
  }

  struct Grid gd = {0, 0};
  populate_grid(fd, &gd);
  print_grid(&gd);

  printf("Max score: %d\n", get_max_score(&gd));

  fclose(fd);
  return 0;
}
