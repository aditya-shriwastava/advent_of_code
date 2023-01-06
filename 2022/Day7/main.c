#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
  buf += i+1;
  return i;
}

void test(){
  // TODO
}

struct File{
	char name[20];
	int size;
};

struct Dir{
	struct File* files;
	struct Dir** dirs;
};

int main(int argc, char** argv){
  test();
  return 0;

  FILE* fd = fopen("./test.txt", "r");
  if(fd == NULL){
    printf("Unable to open data.txt");
    return -1;
  }

  char buf[100];
  while(fgets(buf, 100, fd)){
    char* buf_ptr = buf;
    if(buf_ptr[0] == '$'){ // Is cmd
      buf_ptr += 2;
      if(buf_ptr[0] == 'c' && buf_ptr[1] == 'd'){ // cmd: cd
        buf_ptr += 3;
        // TODO
        printf("%s", buf);
      }else if(buf_ptr[0] == 'l' && buf_ptr[1] == 's'){ // cmd: ls
        buf_ptr += 3;
        // TODO
        printf("%s", buf);
      }
    }
  }

  fclose(fd);
  return 0;
}
