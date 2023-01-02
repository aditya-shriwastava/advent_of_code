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

  char buf0[100];
  char buf1[100];
  char buf2[100];
  bool item[52][3]; // Present or not
  int sum = 0;

  while(fgets(buf0, 100, fd)){
    // 1. Get items
    fgets(buf1, 100, fd);
    fgets(buf2, 100, fd);

    // 1. Clear item
    for(int i=0; i<3; i++){
      for(int j=0; j<52; j++){
        item[j][i] = false;
      }
    }

    // 2. Get length of buf
    int len0 = strlen(buf0) - 1;
    buf0[len0] = '\0';
    int len1 = strlen(buf1) - 1;
    buf1[len1] = '\0';
    int len2 = strlen(buf2) - 1;
    buf2[len2] = '\0';

    // 3. Fill item
    for(int i=0; i<len0; i++){
      item[get_priority(buf0[i]) - 1][0] = true;
    }
    for(int i=0; i<len1; i++){
      item[get_priority(buf1[i]) - 1][1] = true;
    }
    for(int i=0; i<len2; i++){
      item[get_priority(buf2[i]) - 1][2] = true;
    }

    // 4. Find common
    for(int i=0; i<52; i++){
      if(item[i][0] && item[i][1] && item[i][2]){
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
