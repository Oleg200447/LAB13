#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"file.h"

#define KB 1024

#define MEMORY_ERROR 1
#define NEED_ADD 2
#define TYPE_DAMAGED 3

#define ERROR 1
#define SUCCESSFUL_WORK 0

#define STR_FINDED 0
#define NO_STR 1

#define FIRST_TYPE "IN A"
#define SECOND_TYPE "IN CNAME"

#define FIRST_TYPE_FIND 1
#define SECOND_TYPE_FIND 2
#define NO_TYPE 3

#define SPACE " "
#define TRANSFER "\n"

void checkForCorrectType(int* type)
{
	while ((scanf_s("%d",type)) != 1 || *type < 1 || *type>2 || getchar() != '\n')
	{
		printf("Make right choise(1/2):");
		rewind(stdin);
	}
}

void findNewDomen(char** domen, char* str)
{
	int i = 0;
	int j = (int)strlen(*domen) + (int)strlen(SECOND_TYPE)+2;

	while (*(str + j) != '\0')
	{
		*(*domen + i) = *(str + j);
		i++;
		j++;
	}

	*(*domen + i-1) = '\0';
}

int defineStrType(char* str, unsigned int domen_size)
{
	int first_type_cheker = 0;
	int second_type_cheker = 0;

	for (int i = domen_size + 1, j = 0; j < (int)strlen(SECOND_TYPE); j++, i++)
	{
		if (j < (int)strlen(FIRST_TYPE))
			if (*(str + i) == FIRST_TYPE[j])
				first_type_cheker++;

		if (*(str + i) == SECOND_TYPE[j])
			second_type_cheker++;
	}

	if (first_type_cheker == (int)strlen(FIRST_TYPE))
		return FIRST_TYPE_FIND;
	else if (second_type_cheker == (int)strlen(SECOND_TYPE))
		return SECOND_TYPE_FIND;
	else
		return NO_TYPE;
}

int findNeededString(char* domen, char** str,FILE* file)
{
	rewind(file);

	while (!feof(file))
	{
		fgets(*str, KB, file);

		if (strncmp(*str, domen, (int)strlen(domen)) == 0)
			return STR_FINDED;
	}
	return NO_STR;
}

int findId(FILE* file,char *domen,char **id)
{
	char* str = (char*)calloc(KB, sizeof(char));
	if (str == NULL)
	{
		return MEMORY_ERROR;
	}

	char* domen_storer = (char*)calloc(KB, sizeof(char));
	if (domen_storer == NULL)
	{
		free(str);
		return MEMORY_ERROR;
	}

	strcpy(domen_storer, domen);

	int flg = 1;
	int type = 0;

	while (flg)
	{
		if (findNeededString(domen_storer, &str, file) == NO_STR)
		{
			free(str);
			free(domen_storer);

			return NEED_ADD;
		}

		type = defineStrType(str, (int)strlen(domen_storer));

		if (type == FIRST_TYPE_FIND)
		{
			int i = 0;
			int j = (int)strlen(domen_storer) + (int)strlen(FIRST_TYPE)+2;

			while (*(str + j) != '\0')
			{
				*(*id + i) = *(str + j);
				i++;
				j++;
			}

			*(*id+ i) = '\0';
			break;
		}

		if (type == NO_TYPE)
		{
			free(str);
			free(domen_storer);

			return TYPE_DAMAGED;
		}

		if (type == SECOND_TYPE_FIND)
			findNewDomen(&domen_storer, str);		
	}

	free(domen_storer);
	free(str);
	return SUCCESSFUL_WORK;
}

int checkForIdInFile(FILE* file,char* id)
{
	rewind(file);

	char* str = (char*)calloc(KB, sizeof(char));
	if (str == NULL)
	{
		return ERROR;
	}

	while (!feof(file))
	{
		fgets(str, KB, file);

		int i = 0;

		while (*(str + i) != ' ')
		{
			i++;
		}	
		i += (int)strlen(FIRST_TYPE)+2;

		int size_id_str = (int)strlen(str)-i-1;
		int counter = 0;

		while (*(str + i) != '\n')
		{
			if (*(str + i) == *(id + counter))
			{
				counter++;
				i++;
			}
			else
				break;
		}
		if (counter == strlen(id))
		{
			free(str);
			return ERROR;
		}
	}
	free(str);
	return SUCCESSFUL_WORK;
}

int checkForDomenFile(FILE* file, char* domen)
{
	rewind(file);

	char* str = (char*)calloc(KB, sizeof(char));
	if (str == NULL)
	{
		return 1;
	}

	while (!feof(file))
	{
		fgets(str, KB, file);

		if (strncmp(domen, str, strlen(domen)) == 0)
		{
			free(str);
			return 1;
		}
	}

	free(str);
	return 0;
}

int addRecordInFileMenu()
{
	FILE* file;
	errno_t err_file = fopen_s(&file, "asd.txt", "a+");
	if (err_file != 0)
	{
		printf("Cant open file");

		return err_file;
	}

	char* domen = (char*)calloc(KB, sizeof(char));
	if (domen == NULL)
	{
		fclose(file);
		return 1;
	}

	int choise = 0;
	printf("Choose type of string(1/2):");
	checkForCorrectType(&choise);

	char *id= (char*)calloc(KB, sizeof(char));
	if (id == NULL)
	{
		free(domen);
		fclose(file);
		return ERROR;
	}

	printf("Input domen:");
	scanf_s("%s", domen, KB);

	if (checkForDomenFile(file,domen) == 1)
	{
		printf("There is this domen\n");
		free(id);
		free(domen);
		fclose(file);

		return SUCCESSFUL_WORK;
	}

	if (choise == 1)
		printf("Input id:");
	else
		printf("Input second domen:");
	scanf_s("%s", id, KB);

	if (checkForIdInFile(file,id) == 1)
	{
		printf("There is this id\n");
		free(id);
		free(domen);
		fclose(file);

		return SUCCESSFUL_WORK;
	}

	if (checkForValidation(id) == 1)
	{
		printf("Format id not correct.\n");
		free(id);
		free(domen);
		fclose(file);

		return SUCCESSFUL_WORK;
	}

	strcat(domen, SPACE);
	if(choise==1)
	strcat(domen, FIRST_TYPE);
	else
		strcat(domen, SECOND_TYPE);
	strcat(domen, SPACE);
	strcat(domen, id);
	strcat(domen, TRANSFER);

	fputs(domen, file);

	free(domen);
	free(id);
	fclose(file);

	return 0;
}

int findAllDomensForIdMenu()
{
	FILE* file;
	errno_t err_file = fopen_s(&file, "asd.txt", "r+");
	if (err_file != SUCCESSFUL_WORK)
	{
		printf("Cant open file");

		return err_file;
	}

	int size = 0;
	char** domen_mas = (char**)calloc(1, sizeof(char*));
	if (domen_mas == NULL)
	{
		fclose(file);
		return ERROR;
	}


	char* id = (char*)calloc(KB, sizeof(char));
	if (id == NULL)
	{
		free(domen_mas);
		fclose(file);
		return ERROR;
	}

	printf("Input id:");
	scanf_s("%s", id, KB);

	int flg = 1;

	char* str = (char*)calloc(KB, sizeof(char));
	if (str == NULL)
	{
		free(domen_mas);
		free(id);
		fclose(file);
		return ERROR;
	}

	while (flg)
	{
		flg = 0;

		while (!feof(file))
		{

			fgets(str, KB, file);

			int i = (int)strlen(str);

			while (*(str + i) != ' ')
				i--;
			i++;

			int counter=0;

			while (*(str + i) != '\0' && *(str + i) != '\n' &&(* (id + counter) == *(str + i)))
			{
				i++;
				counter++;
			}
			
			int k = i;
			i = 0;

			if ((counter ==(int) strlen(id)) && (*(str+k)=='\0' || *(str + k) == '\n'))
			{
				flg = 1;
				size++;

				char* domen = (char*)calloc(KB, sizeof(char));
				if (domen == NULL)
				{
					free(id);
					fclose(file);
					free(str);

					return ERROR;
				}

				while (*(str + i) != ' ')
				{
					*(domen + i) = *(str + i);
					i++;
				}

				*(domen + i) = '\0';

				id = domen;

				if (size != 1)
				{
					char** storer_mas = (char**)realloc(domen_mas, size * sizeof(char*));
					if (storer_mas != NULL)
						domen_mas = storer_mas;
				}
				*(domen_mas + size - 1) = domen;
			}
		}

		rewind(file);
	}

	for (int i = 0; i < size; i++)
		printf("%s\n", *(domen_mas + i));

	for (int i = 0; i < size; i++)
		free(*(domen_mas + i));
	
	fclose(file);

	return SUCCESSFUL_WORK;
}


int checkForValidation(char* id)
{
	int cheker_point = 0;
	int cheker_two_points = 0;

	for (int i = 0; i < strlen(id); i++)
	{
		if (*(id + i) == '.' && (*(id + i - 1) <= '9' && *(id + i - 1) >= '1') && (*(id + i + 1) <= '9' && *(id + i + 1) >= '1'))
		{
			cheker_point++;
		}		
	}

	if (cheker_point == 3 && chekerIPv4(id)==0)
	{
		return 0;
	}

	for (int i = 0; i < strlen(id); i++)
	{
		if (*(id + i) == ':' && ((* (id + i - 1) <= '9' && *(id + i - 1) >= '1') || (* (id + i - 1) <= 'Z' && *(id + i - 1) >= 'A') || (*(id + i - 1) <= 'z' && *(id + i - 1) >= 'a')) && ((*(id + i + 1) <= '9' && *(id + i + 1) >= '1') || (*(id + i + 1) <= 'Z' && *(id + i + 1) >= 'A') || (*(id + i + 1) <= 'z' && *(id + i + 1) >= 'a')))
		{
			cheker_two_points++;
		}
	}

	if (cheker_two_points == 7 && chekerIPv6(id) == 0)
	{
		return 0;
	}

	return 1;
}

int levelTen(int degree)
{
	int num = 1;
	for (int i = 1; i <= degree; i++)
	{
		num *= 10;
	}
	return num;
}

int chekerIPv4(char* id)
{
	for (int i = 0; i < strlen(id); i++)
	{
		if (*(id + i) != '.' || !(*(id + i) <= '9' && *(id + i) >= '1'))
			return 1;
	}

	int num = 0;

	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		char* storer = (char*)calloc(4, sizeof(char));
		if (storer == NULL)
			return 1;

		int j = 0;

		while (*(id + k) != '.')
		{
			*(storer + j) = *(id + k);
			j++;
			k++;
		}
		k++;

		for (int p = (int)strlen(storer),z=0; p >= 0; p--,z++)
		{
			num += (int)(*(storer + p) - (int)'0')*levelTen(z);
		}

		if (*(storer) == '0' && strlen(storer) == 1)
			return 1;

		if (!(num >= 0 && num <= 255))
			return 1;
	}

	
	return 0;
}

int chekerIPv6(char* id)
{
	for (int i = 0; i < strlen(id); i++)
	{
		if (*(id + i) != ':' && !(*(id + i) <= '9' && *(id + i) >= '1') && !(*(id + i) <= 'Z' && *(id + i) >= 'A') && !(*(id + i) <= 'z' && *(id + i) >= 'a'))
			return 1;
	}

	int cheker = 0;
	for (int i = 0; i < strlen(id); i++)
	{
		if (*(id + i) != ':')
			cheker++;
		
		if (*(id + i) == ':')
			cheker = 0;

		if (cheker == 5)
			return 1;
	}
	
	return 0;
}