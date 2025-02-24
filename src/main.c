#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *builtin_functions[] = {"exit", "echo", "type"};
const int len = sizeof(builtin_functions) / sizeof(builtin_functions[0]);

// Function to check if a file exists and is executable
int is_executable(const char *path) { return access(path, X_OK) == 0; }

// Function to search for a command in the PATH
char *find_in_path(const char *command) {
  char *path_env = getenv("PATH");
  if (path_env == NULL) {
    return NULL;
  }

  char *path_copy = strdup(path_env);
  char *dir = strtok(path_copy, ":");
  static char full_path[1024];

  while (dir != NULL) {
    snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
    if (is_executable(full_path)) {
      free(path_copy);
      return full_path;
    }
    dir = strtok(NULL, ":");
  }

  free(path_copy);
  return NULL;

}

void trim_newline(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}
const int check_command_type(char * input) {
  trim_newline(input);
  for (int i = 0; i < len; i++) {
    if(strcmp(builtin_functions[i], input) == 0) {
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

    char *cmd = input + 5;

    if(!strcmp(input, "exit 0")) {
      exit(0);
    }       
    if(!strncmp(input, "echo ", 5)) {
      printf("%s\n", cmd);
      continue;
    }
    if(!strncmp(input, "type ", 5)) {
      if(check_command_type(cmd) == 0) {
        printf("%s is a shell builtin\n", cmd);
        continue;
      } else {
        char *path = find_in_path(cmd);
        if(path) {
          printf("%s is %s\n", cmd, path);
          continue;
        } else {
          printf("%s: not found\n", cmd);
          continue;
        }
      }
    }
    printf("%s: command not found\n", input);

    
  }
  return 0;
}
