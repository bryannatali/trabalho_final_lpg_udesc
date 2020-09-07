#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_current_path.h"
#include "../main.h"

void insert(Contact *new_contact)
{
  char *database_path = "/src/database.bin";
  char *path = get_current_path();
  FILE *fptr;
  char full_path[256];
  snprintf(full_path, sizeof(full_path), "%s%s", path, database_path);

  fptr = fopen(full_path, "ab");
  if (fptr == NULL)
  {
    printf("Error on opening database file located at: %s\n", full_path);
    return;
  }

  fwrite(new_contact, sizeof(*new_contact), 1, fptr);
  fclose(fptr);

  free(path);
}

void list()
{
  char *database_path = "/src/database.bin";
  char *path = get_current_path();
  char full_path[256];
  int count = 0;
  FILE *fptr;
  Contact readed_contact;
  snprintf(full_path, sizeof(full_path), "%s%s", path, database_path);

  fptr = fopen(full_path, "rb");
  if (fptr == NULL)
  {
    printf("Error on opening database file located at: %s\n", full_path);
    return;
  }
    
  while (1) {
    fread(&readed_contact, sizeof(readed_contact), 1, fptr);

    if(feof(fptr)) {
      break;
    }

    printf("id: %d\n", readed_contact.id);
    printf("name: %s\n", readed_contact.name);
    printf("email: %s\n", readed_contact.email);
    printf("phone: %s\n", readed_contact.phone);
  }

  fclose(fptr);

  free(path);
}
