#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* ASCII
A --> Z : 65 --> 90
a --> z : 97 --> 122
*/
/* Priority
A --> Z : 27 --> 52
a --> z : 1 --> 26
*/

int get_priority(const char ch){
  if(ch >= 65 && ch <= 90){
    return ch - 65 + 26 + 1;
  }else if(ch >= 97 && ch <= 122){
    return ch - 97 + 1;
  }else{
    printf("Invalid ch: %u\n", ch);
    return 0;
  }
}

int main(int argc, char** argv){
  FILE* fd = fopen("./data.txt", "r");
  if(fd == NULL){
    printf("Unable to read data.txt");
    return -1;
  }

  char buf[100];
  bool part1[52];
  int sum = 0;

  while(fgets(buf, 100, fd)){
    // 1. Clear part1 (i.e. set to false)
    for(int i=0; i<52; i++){
      part1[i] = false;
    }

    // 2. Get length of buf
    int len = strlen(buf) - 1;
    buf[len] = '\0';

    // 3. Fill part1
    for(int i=0; i<len/2; i++){
      part1[get_priority(buf[i]) - 1] = true;
    }

    for(int i=0; i<52; i++){
      printf("%d", part1[i]);
    }
    printf(" || ");

    // 4. Check if part2 matches with part1
    for(int i=len/2; i<len; i++){
      if(part1[get_priority(buf[i]) - 1] == true){
        printf("%c at %d(%d): %d\n", buf[i], i+1, len, get_priority(buf[i]));
        sum += get_priority(buf[i]);
        break;
      }
    }
  }
  printf("sum: %d\n", sum);

  fclose(fd);
  return 0;
}
