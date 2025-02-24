#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Uncomment this block to pass the first stage
  printf("$ ");

  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);
  size_t len = strlen(input);
  // change the last character of the input to \0 bc fgets puts new line by default
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

  printf("%s: command not found", input);
  return 0;
}
