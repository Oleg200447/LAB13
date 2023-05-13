#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"hash.h"
#include"cash.h"
#include"file.h"

#define EXIT 5

#define SUCCESSFUL_WORK 0
#define ERROR 1

#define FIRST_TASK 1
#define SECOND_TASK 2
#define THIRD_TASK 3
#define FOURTH_TASK 4

int main()
{
	hash* mas_hash = (hash*)calloc(1, sizeof(hash));	
	if (mas_hash == NULL)	
		return ERROR;

	cash *head = NULL;
	cash* tail = NULL;

	int size = 0;
	char answer = 'Y';
	int task_choise = 0;

	do {
		printf("  Menu:\n1.Find id.\n2.Add record.\n3.Find all domens for id.\n4.Watch cash.\n5.Exit.\nYour choise:");
		menuCorrect(&task_choise);
		system("cls");

		if (task_choise == EXIT )
		{
			freeCash(&mas_hash, size);
			return 0;
		}

		if (task_choise==FIRST_TASK && findIdMenu(&head, &tail, &mas_hash, &size) != SUCCESSFUL_WORK)
		{
			freeCash (&mas_hash, size);
			return ERROR;
		}

		if (task_choise == SECOND_TASK && addRecordInFileMenu() != SUCCESSFUL_WORK)
		{
			freeCash(&mas_hash, size);
			return ERROR;
		}

		if (task_choise == THIRD_TASK && findAllDomensForIdMenu() != SUCCESSFUL_WORK)
		{
			freeCash(&mas_hash, size);
			return ERROR;
		}

		if (task_choise == FOURTH_TASK)
		{
			watchCash(head);
		}

		printf("Do you want to continue?(Y/N):");
		rewind(stdin);
		checkUserAnswer(&answer);

		system("cls");
	} while (answer == 'Y');

	freeCash(&mas_hash, size);

	return 0;
}