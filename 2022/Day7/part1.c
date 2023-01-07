#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int get_word(char* buf, char* word){
  int i;
  for(i=0; i<100; i++){
    if(buf[i] == '\0'){
      break;
    }else if(buf[i] == ' '){
      break;
    }else{
      word[i] = buf[i];
    }
  }
  word[i] = '\0';
  return i;
}


struct File{
  char name[50]; // File name
  int size; // File size in bytes
};

struct Dir{
  int n_files; // Number of files
  int n_dirs; // Number of dirs
  char name[50]; // Name of dir
  struct Dir* parent; // Parent dir (NULL if root)
  struct File* files[1000]; // List of files in this dir
  struct Dir* dirs[1000]; // List of dirs in this dir
};

struct Dir* cd(struct Dir* curr_dir, char* dir_name){
  if(strcmp(dir_name, "..") == 0){
    if(curr_dir->parent == NULL){ // Already in root dir. Cannot go up
      return curr_dir;
    }
    return curr_dir->parent;
  }

  if(strcmp(dir_name, ".") == 0){
    return curr_dir;
  }

  for(int i=0; i<curr_dir->n_dirs; i++){
    if(strcmp(curr_dir->dirs[i]->name, dir_name) == 0){
      return curr_dir->dirs[i];
    }
  }
  return curr_dir;
}

void mkdir(struct Dir* curr_dir, char* dir_name){
  int n = ++curr_dir->n_dirs;
  curr_dir->dirs[n - 1] = calloc(1, sizeof(struct Dir));
  curr_dir->dirs[n - 1]->n_files = 0;
  curr_dir->dirs[n - 1]->n_dirs = 0;
  strcpy(curr_dir->dirs[n - 1]->name, dir_name);
  curr_dir->dirs[n - 1]->parent = curr_dir;
}

void touch(struct Dir* curr_dir, char* file_name, int file_size){
  int n = ++curr_dir->n_files;
  curr_dir->files[n - 1] = calloc(1, sizeof(struct File));
  strcpy(curr_dir->files[n - 1]->name, file_name);
  curr_dir->files[n - 1]->size = file_size;
}

void print_tree(struct Dir* curr_dir, int indent){
 for(int j=0; j<indent; j++){
   printf("  ");
 }
 printf("%s\n", curr_dir->name);
 indent++;
 for(int i=0; i<curr_dir->n_files; i++){
   for(int j=0; j<indent; j++){
     printf("  ");
   }
   printf("%d %s\n", curr_dir->files[i]->size, curr_dir->files[i]->name);
 }
 for(int i=0; i<curr_dir->n_dirs; i++){
   print_tree(curr_dir->dirs[i], indent);
 }
}

void test_dir_tree(){
  struct Dir root = {0, 0, "/", NULL};
  struct Dir* curr_dir = &root;
  
  touch(curr_dir, "a.txt", 100);
  touch(curr_dir, "b.txt", 200);
  mkdir(curr_dir, "dir1");
  curr_dir = cd(curr_dir, "dir1");
  touch(curr_dir, "c.txt", 300);
  touch(curr_dir, "d.txt", 400);
  curr_dir = cd(curr_dir, "..");
  mkdir(curr_dir, "dir2");
  curr_dir = cd(curr_dir, "dir2");
  touch(curr_dir, "e.txt", 500);
  touch(curr_dir, "f.txt", 600);
  curr_dir = cd(curr_dir, "..");

  print_tree(curr_dir, 0);
}

void test_get_word(){
  char data[100] = {0};
  strcpy(data, "My name is aditya");
  char* data_ptr = data;
  char word[20] = {0};
  while(true){
    int n = get_word(data_ptr, word);
    if(n == 0){
      break;
    }
    data_ptr += n+1;
    printf("%s\n", word);
  }
}

void populate_dir(struct Dir* dir, FILE* fd){
  char line[100];
  char word[100];
  struct Dir* curr_dir = NULL;
  while(fgets(line, 100, fd)){
    int n = 0;
    int l = strlen(line);
    line[l-1] = '\0';
    char* line_ptr = line;
    n = get_word(line_ptr, word);
    if(n == 0){continue;}else{line_ptr += n+1;}
    if (strcmp(word, "$") == 0) { // Is cmd
      n = get_word(line_ptr, word);
      if(n == 0){continue;}else{line_ptr += n+1;}
      if(strcmp(word, "ls") == 0){ // cmd = ls
        // DO NOTHING
      }else if(strcmp(word, "cd") == 0){ // cmd = cd
        n = get_word(line_ptr, word);
        if(n == 0){continue;}else{line_ptr += n+1;}
        if(strcmp(word, "/") == 0){ // dir = /
          curr_dir = dir;
        }else{
          if(curr_dir == NULL){
            continue;
          }
          curr_dir = cd(curr_dir, word);
        }
      }
    }else{ // Is not cmd
      if(curr_dir == NULL){continue;}
      /* n = get_word(line_ptr, word); */
      /* if(n == 0){continue;}else{line_ptr += n+1;} */
      if(strcmp(word, "dir") == 0){ // Is dir
        n = get_word(line_ptr, word);
        if(n == 0){continue;}else{line_ptr += n+1;}
        mkdir(curr_dir, word);
      }else{ // Is file
        char size[20];
        strcpy(size, word);
        n = get_word(line_ptr, word);
        if(n == 0){continue;}else{line_ptr += n+1;}
        touch(curr_dir, word, atoi(size));
      }
    }
  }
}

int sum_dir_size(struct Dir* curr_dir, int* sum_ptr){
  int dir_size = 0;

  for(int i=0; i<curr_dir->n_files; i++){
    dir_size += curr_dir->files[i]->size;
  }

  for(int i=0; i<curr_dir->n_dirs; i++){
    int size = sum_dir_size(curr_dir->dirs[i], sum_ptr);
    if(size <= 100000){
      printf("Dir: %s of size: %d is less that 100000\n", curr_dir->dirs[i]->name, size);
      *sum_ptr += size;
    }
    dir_size += size;
  }

  return dir_size;
}

int main(int argc, char** argv){
  /* test_dir_tree(); */
  /* return 0; */

  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Unable to open data.txt");
    return -1;
  }

  struct Dir root = {0, 0, "/", NULL};
  populate_dir(&root, fd);
  print_tree(&root, 0);

  int sum = 0;
  sum_dir_size(&root, &sum);
  printf("Sum: %d\n", sum);
  
  fclose(fd);
  return 0;
}
