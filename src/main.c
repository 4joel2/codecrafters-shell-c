#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const *builtin_functions[] = {"exit ", "echo ", "type "};

const int check_command_type(char * input) {
  int len = sizeof(builtin_functions) / sizeof(builtin_functions[0]);
  for (int i = 0; i < len; i++) {
    if(!strcmp(builtin_functions[i], input)) {
      return 0;
    }
  }
  return -1;
}

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
    if(!strncmp(input, "echo ", 5)) {
      printf("%s\n", input + 5);
      continue;
    }
    if(!strncmp(input, "type ", 5)) {
      if(check_command_type(input + 5) == 0) {
        printf("%s is a shell builtin\n", input + 5);
      } else {
        printf("%s: not found\n", input + 5);
      }
    }
    printf("%s: command not found\n", input);

    
  }
  return 0;
}
