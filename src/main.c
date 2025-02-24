#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);


  while(1) {
    printf("$ ");
    // Wait for user input
    char input[100];
    fgets(input, 100, stdin);
    size_t len = strlen(input);
    // change the last character of the input to \0 bc fgets puts new line by default
    if (len > 0 && input[len - 1] == '\n') {
      input[len - 1] = '\0';
    }
    if(!strcmp(input, "exit 0")) {
      exit(0);
    }       
    if(!strncmp(input, "echo", 4)) {
      printf("%s\n", input);
    }
    printf("%s: command not found\n", input);

    
  }
  return 0;
}
