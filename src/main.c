#include <stdio.h>
#include <string.h>
#include "services/file_data_access.h"
#include "main.h"

void add_contact();
void list_contacts();
void update_contact();
void delete_contact();

int main()
{
  int broker = 1;

  while (broker)
  {
    printf("============================\n");
    printf("1. Criar novo contato\n");
    printf("2. Excluir contato\n");
    printf("3. Alterar contato\n");
    printf("4. Listar contatos\n");
    printf("0. Sair\n");
    printf("============================\n");
    scanf("%d", &broker);

    switch (broker)
    {
    case 1:
      add_contact();
      break;
    case 2:
      delete_contact();
      break;
    case 3:
      update_contact();
      break;
    case 4:
      list_contacts();
      break;
    }
  }

  return 0;
}

void add_contact()
{
  Contact new_contact;
  char temp;

  printf("Id: ");
  scanf("%d", &new_contact.id);
  printf("Nome: ");
  scanf("%c", &temp);
  scanf("%[^\n]", new_contact.name);
  printf("Email: ");
  scanf("%c", &temp);
  scanf("%[^\n]", new_contact.email);
  printf("Telefone: ");
  scanf("%c", &temp);
  scanf("%[^\n]", new_contact.phone);
  scanf("%c", &temp);

  insert(&new_contact);
}

void list_contacts() {
  list();
}

void update_contact() {
  int id = 0;
  printf("Informe o Id do contato a ser alterado: \n");
  scanf("%d", &id);
  update(id);
}

void delete_contact() {
  int id = 0;
  printf("Informe o Id do contato a ser removido: \n");
  scanf("%d", &id);
  delete(id);
}