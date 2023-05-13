#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"cash.h"
#include"hash.h"
#include"file.h"

#define MAX_CASH_SIZE 2
#define KB 1024

#define MEMORY_MISTAKE -1
#define MEMORY_MISTAKE_ADD 0

#define SECCUES_PUSH 0

#define HACHE_SIZE 19

#define FIRST_TASK 1
#define LAST_TASK 4

#define SUCCESSFUL_WORK 0
#define ERROR 1

#define MEMORY_ERROR 1
#define NEED_ADD 2
#define TYPE_DAMAGED 3

#define NOT_IN_CASH 0

void menuCorrect(int* task)
{
	while ((scanf_s("%d", task)) != 1 || *task < FIRST_TASK || *task>LAST_TASK || getchar() != '\n')
	{
		printf("Make right choise(1-6):");
		rewind(stdin);
	}
}

int push(cash** head,cash**tail, char* id,char *domen) 
{
	cash* storer = malloc(sizeof(cash));
	if (storer == NULL)
		return MEMORY_MISTAKE;
	
	storer->id = id;

	if (*tail == NULL)
	{
		*tail = storer;
		*head = storer;
		storer->next = NULL;
		storer->prev = NULL;
	}
	else
	{
		storer->prev = *head;
		storer->next = NULL;
		(*head)->next = storer;
		*head = storer;
	}

	return SECCUES_PUSH;
}

int addElementInCash(hash** mas_hash, cash** head,cash **tail,unsigned int size,char *domen,char* id)
{
	unsigned int new_size = size + 1;

	hash* storer = (hash*)realloc(*mas_hash, new_size * sizeof(hash));
	if (storer == NULL)
		return MEMORY_MISTAKE_ADD;
	else
		*mas_hash = storer;

	(*mas_hash)[new_size - 1].key = makeHash(domen);
	if (push(head, tail, id, domen) == MEMORY_MISTAKE)
		return MEMORY_MISTAKE_ADD;
	(*mas_hash)[new_size - 1].id = *head;
	
	return new_size;
}

unsigned int chechCashForId(char* domen, hash* mas_hash,unsigned int size)
{
	char* key = (char*)calloc(KB, sizeof(char));
	if (key == NULL)
		return MEMORY_MISTAKE;
	key = makeHash(domen);

	for (int i = 0; i <(int) size; i++)
	{
		if (strncmp(key, (*(mas_hash + i)).key, HACHE_SIZE) == 0)
			return i + 1;
	}
	
	return 0;
}

void changePlaceOfElement(unsigned int place_in_masive, hash** mas_hash, cash** head, cash** tail, unsigned int size)
{
	if (place_in_masive == size)
		return;

	hash storer_hash = *(*mas_hash + place_in_masive - 1);
	cash* storer_cash = storer_hash.id;

	for (int i = place_in_masive - 1; i <(int) size - 1; i++)
		*(*mas_hash + i) = *(*mas_hash + i + 1);
	*(*mas_hash + size - 1) = storer_hash;

	if (storer_cash == *tail)
	{
		*tail = storer_cash->next;
		(*tail)->prev = NULL;
		storer_cash->next = NULL;

		(*head)->next = storer_cash;
		storer_cash->prev = *head;
		*head = storer_cash;
	}
	else 
	{
		storer_cash->next->prev = storer_cash->prev;
		storer_cash->prev->next = storer_cash->next;

		(*head)->next = storer_cash;
		storer_cash->prev = *head;
		storer_cash->next = NULL;
		*head = storer_cash;
	}
}

int delateElementFromCache(hash** mas_hash, cash** tail, unsigned int size)
{
	int new_size = size - 1;

	for (int i = 0; i < new_size; i++)
	{
		*(*mas_hash + i) = *(*mas_hash + i + 1);
	}

	hash* storer = (hash*)realloc(*mas_hash, new_size * sizeof(hash));
	if (storer == NULL)
		return MEMORY_MISTAKE;
	else
		*mas_hash = storer;

	cash* storer_cach = *tail;
	(*tail) = (*tail)->next;
	(*tail)->prev = NULL;
	free(storer_cach->id);
	free(storer_cach);

	return size - 1;
}

void freeCash(cash** head, hash** mas,int size)
{
	for (int i = 0; i < size; i++)
	{
		free((*(*mas + i)).id->id);
		free((*(*mas + i)).id);
		free((*(*mas + i)).key);
	}
}

void checkUserAnswer(char* symbol)
{
	while ((scanf_s("%c", symbol, 1)) != 1 || getchar() != '\n' || (*symbol != 'Y' && *symbol != 'N'))
	{
		printf("(Y/N):");
		rewind(stdin);
	}
}

int findIdMenu(cash **head,cash**tail,hash **mas_hash,unsigned int *size)
{
	FILE* file;
	errno_t err_file = fopen_s(&file, "asd.txt", "r+");
	if (err_file != SUCCESSFUL_WORK)
	{
		printf("Cant open file");

		return err_file;
	}

	char* domen = (char*)calloc(KB, sizeof(char));
	if (domen == NULL)
	{
		fclose(file);

		return MEMORY_ERROR;
	}

	int place_in_masive = NOT_IN_CASH;

	char* id = (char*)calloc(KB, sizeof(char));
	if (id == NULL)
	{
		free(domen);
		fclose(file);

		return MEMORY_ERROR;
	}

	printf("Input domen:");
	scanf_s("%s", domen, KB);

	place_in_masive = chechCashForId(domen, *mas_hash, *size);

	if (place_in_masive == NOT_IN_CASH)
	{
		int err = findId(file, domen, &id);
		if (err == MEMORY_ERROR|| err == TYPE_DAMAGED)
		{
			free(domen);
			fclose(file);

			return ERROR;
		}

		if (err == NEED_ADD)
		{
			free(domen);
			fclose(file);

			printf("Not enough info in file\n");

			return SUCCESSFUL_WORK;
		}

	}

	if (*size < MAX_CASH_SIZE && place_in_masive == NOT_IN_CASH)
	{
		*size = addElementInCash(mas_hash, head, tail, *size, domen, id);
		if (*size == 0)
		{
			free(domen);
			fclose(file);

			return ERROR;
		}
	}
	else
	{
		if (place_in_masive == NOT_IN_CASH)
		{
			*size = delateElementFromCache(mas_hash, tail, *size);
			if (*size < 0)
			{
				free(domen);
				fclose(file);

				return ERROR;
			}

			*size = addElementInCash(mas_hash, head, tail, *size, domen, id);
			if (*size == 0)
			{
				free(domen);
				fclose(file);

				return ERROR;
			}
		}
		else
		{
			changePlaceOfElement(place_in_masive, mas_hash, head, tail, *size);
		}
	}
	printf("id:%s", (*(*mas_hash + *size - 1)).id->id);

	fclose(file);
	free(domen);

	return SUCCESSFUL_WORK;
}