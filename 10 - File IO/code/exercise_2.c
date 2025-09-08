#include <stdio.h>

static void number_lines(FILE *in) {
      char buf[1024];
      int line = 0;
      while (fgets(buf, sizeof buf, in)) {
          printf("%d: %s", ++line, buf);
      }
   
}

int main(void) {
    number_lines(stdin);
    return 0;
}