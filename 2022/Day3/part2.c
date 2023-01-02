#include <stdio.h>
#include <string.h>

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

  char buf[3][100];
  bool item[3][52]; // Present or not
  int sum = 0;

  while(fgets(buf[0], 100, fd)){
    // 1. Get items
    fgets(buf[1], 100, fd);
    fgets(buf[2], 100, fd);

    // 1. Clear item
    for(int i=0; i<3; i++){
      for(int j=0; j<52; j++){
        item[i][j] = false;
      }
    }

    // 2. Get length of buf
    int len[3];
    for(int i=0; i<3; i++){
      len[i] = strlen(buf[i]) - 1;
      buf[i][len[i]] = '\0';
    }

    // 3. Fill item
    for(int i=0; i<3; i++){
      for(int j=0; j<len[i]; j++){
        item[i][get_priority(buf[i][j]) - 1] = true;
      }
    }

    // 4. Find common
    for(int i=0; i<52; i++){
      if(item[0][i] && item[1][i] && item[2][i]){
        printf("%d\n", i + 1);
        sum += i + 1;
        break;
      }
    }
  }
  printf("sum: %d\n", sum);

  fclose(fd);
  return 0;
}
