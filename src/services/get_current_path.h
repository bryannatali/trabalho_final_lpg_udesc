#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PATH 1000

char* get_current_path() {
  char *cwd;
  cwd = (char*) malloc((MAX_PATH + 1) * sizeof(char));
  size_t size = sizeof(char) * (MAX_PATH + 1);
  if (getcwd(cwd, size) != NULL) {
      return cwd;
  } else {
      perror("getcwd() error");
      return cwd;
  }
}
