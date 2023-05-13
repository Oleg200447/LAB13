#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"hash.h"

#define HASH_SIZE 20
#define INT_A_SYMB 65

#define KB 1024

long long findSumSymbols(const char* str)
{
	long long value_for_key = 0;
	for (int i = 0; i < strnlen_s(str,KB); i++)
	{
		value_for_key += (long long)(*(str + i));
	}

	return value_for_key;
}

char* makeHash(const char* str)
{
	if (str == NULL)
	{
		return NULL;
	}

	char* hash_key = (char*)calloc(HASH_SIZE, sizeof(char));
	if (hash_key == NULL)
	{
		return NULL;
	}

	long long value_for_key = findSumSymbols(str);
	
	for (int i = 1; i < HASH_SIZE; i++)
	{
		if (i % 5 != 0)
			*(hash_key + i - 1) = (char)(INT_A_SYMB + (int)(value_for_key % (i + 1)));
		else
			*(hash_key + i - 1) = '-';
	}

	return hash_key;
}