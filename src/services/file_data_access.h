#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_current_path.h"
#include "id_verification.h"
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

  if (verify_id(new_contact->id))
  {
    fwrite(new_contact, sizeof(*new_contact), 1, fptr);
    printf("Novo contato criado!\n");
  }
  else
  {
    printf("Id já existente!\n");
  }

  fclose(fptr);

  free(path);
}

void list()
{
  char *database_path = "/src/database.bin";
  char *path = get_current_path();
  char full_path[256];
  FILE *fptr;
  Contact readed_contact;
  snprintf(full_path, sizeof(full_path), "%s%s", path, database_path);

  fptr = fopen(full_path, "rb");
  if (fptr == NULL)
  {
    printf("Error on opening database file located at: %s\n", full_path);
    return;
  }

  while (1)
  {
    fread(&readed_contact, sizeof(readed_contact), 1, fptr);

    if (feof(fptr))
    {
      break;
    }

    printf("Id: %d\n", readed_contact.id);
    printf("Nome: %s\n", readed_contact.name);
    printf("Email: %s\n", readed_contact.email);
    printf("Telefone: %s\n", readed_contact.phone);
  }

  fclose(fptr);

  free(path);
}

void update(int id)
{
  char *database_path = "/src/database.bin";
  char *path = get_current_path();
  char full_path[256];
  char new_name[30];
  char new_email[30];
  char new_phone[20];
  char temp;
  int c;
  FILE *fptr;
  Contact readed_contact;
  snprintf(full_path, sizeof(full_path), "%s%s", path, database_path);

  fptr = fopen(full_path, "rb+");
  if (fptr == NULL)
  {
    printf("Error on opening database file located at: %s\n", full_path);
    return;
  }

  while (1)
  {
    fread(&readed_contact, sizeof(readed_contact), 1, fptr);

    if (feof(fptr))
    {
      break;
    }

    if (id == readed_contact.id)
    {
      printf("Deixe em branco para manter.\n");
      printf("Digite o novo nome do contato: \n");
      scanf("%c", &temp);
      scanf("%[^\n]", new_name);
      printf("Digite o novo email do contato: \n");
      scanf("%c", &temp);
      scanf("%[^\n]", new_email);
      printf("Digite o novo telefone do contato: \n");
      scanf("%c", &temp);
      scanf("%[^\n]", new_phone);
      scanf("%c", &temp);

      if (strlen(new_name) > 0)
      {
        strcpy(readed_contact.name, new_name);
      }
      if (strlen(new_email) > 0)
      {
        strcpy(readed_contact.email, new_email);
      }
      if (strlen(new_phone) > 0)
      {
        strcpy(readed_contact.phone, new_phone);
      }
      fseek(fptr, -(long)sizeof(readed_contact), 1);
      // fputs(line, fptr);
      c = fwrite(&readed_contact, sizeof(readed_contact), 1, fptr);
      break;
    }
  }

  if (c == 1)
  {
    printf("Contato alterado\n");
  }
  else
  {
    printf("Contato nao alterado\n");
  }

  fclose(fptr);
}

void delete (int id)
{
  char *database_path = "/src/database.bin";
  char *database_path_temp = "/src/temp.bin";
  char *path = get_current_path();
  char full_path[256];
  char full_path_temp[256];
  int contact_removed;
  FILE *fptr;
  FILE *fptr_temp;
  Contact readed_contact;

  snprintf(full_path, sizeof(full_path), "%s%s", path, database_path);
  snprintf(full_path_temp, sizeof(full_path_temp), "%s%s", path, database_path_temp);

  fptr = fopen(full_path, "rb");
  fptr_temp = fopen(full_path_temp, "wb");
  if (fptr == NULL)
  {
    printf("Error on opening database file located at: %s\n", full_path);
    return;
  }

  while (1)
  {
    fread(&readed_contact, sizeof(readed_contact), 1, fptr);

    if (feof(fptr))
    {
      break;
    }

    if (id != readed_contact.id)
    {
      fwrite(&readed_contact, sizeof(readed_contact), 1, fptr_temp);
    }
    else
    {
      contact_removed = 1;
    }
  }

  fclose(fptr);
  fclose(fptr_temp);
  remove(full_path);
  rename(full_path_temp, full_path);
  if (contact_removed)
  {
    printf("Contato removido!\n");
  }
  else
  {
    printf("Contato nao encontrado.\n");
  }
}