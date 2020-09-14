#include <stdio.h>
#include "get_current_path.h"
#include "../main.h"

int verify_id(int id) {
  char *database_path = "/src/database.bin";
  char *path = get_current_path();
  char full_path[256];
  int id_available = 1;
  FILE *fptr;
  Contact readed_contact;
  snprintf(full_path, sizeof(full_path), "%s%s", path, database_path);

  fptr = fopen(full_path, "rb");
  if (fptr == NULL)
  {
    printf("Error on opening database file located at: %s\n", full_path);
    return 0;
  }
    
  while (1) {
    fread(&readed_contact, sizeof(readed_contact), 1, fptr);

    if(feof(fptr)) {
      break;
    }

    if (id == readed_contact.id) {
      id_available = 0;
      break;
    }
  }

  fclose(fptr);

  free(path);

  return id_available;
}