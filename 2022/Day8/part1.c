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
bool is_visible(struct Grid* gd, int i, int j){
  // Is Visible from Left
  bool is_visible_from_left = true;
  for(int k=0; k<i; k++){
    if(gd->data[k + (gd->width * j)] >= gd->data[i + (gd->width * j)]){
      is_visible_from_left = false;
      break;
    }
  }
  if(is_visible_from_left){
    /* printf("Visible from left\n"); */
    return true;
  }

  // Is Visible from Right
  bool is_visible_from_right = true;
  for(int k=i+1; k<gd->width; k++){
    if(gd->data[k + (gd->width * j)] >= gd->data[i + (gd->width * j)]){
      is_visible_from_right = false;
      break;
    }
  }
  if(is_visible_from_right){
    /* printf("Visible from right\n"); */
    return true;
  }

  // Is Visible from Top
  bool is_visible_from_top = true;
  for(int k=0; k<j; k++){
    if(gd->data[i + (gd->width * k)] >= gd->data[i + (gd->width * j)]){
      is_visible_from_top = false;
      break;
    }
  }
  if(is_visible_from_top){
    /* printf("Visible from top\n"); */
    return true;
  }

  // Is Visible from Bottom
  bool is_visible_from_bottom = true;
  for(int k=j+1; k<gd->height; k++){
    if(gd->data[i + (gd->width * k)] >= gd->data[i + (gd->width * j)]){
      is_visible_from_bottom = false;
      break;
    }
  }
  if(is_visible_from_bottom){
    /* printf("Visible from bottom\n"); */
    return true;
  }

  return false;
}

int count_visible(struct Grid* gd){
  int total = 0;
  for(int j=0; j<gd->height; j++){
    for(int i=0; i<gd->width; i++){
      if(is_visible(gd, i, j)){
        total++;
      }
    }
  }
  return total;
}

void test(){
  char ch = '0';
  printf("%d\n", ch);
}

int main(int argc, char** argv){
  /* test(); */
  /* return 0; */

  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Unable to open data.txt");
    return -1;
  }

  struct Grid gd = {0, 0};
  populate_grid(fd, &gd);
  print_grid(&gd);
  printf("Visible: %d\n", count_visible(&gd));

  fclose(fd);
  return 0;
}
