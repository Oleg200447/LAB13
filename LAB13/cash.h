#pragma once

struct CASH {
	char* id;
	struct CASH* next;
	struct CASH* prev;
}typedef cash;

struct HASH{
	 char* key;
	 struct CASH* id;
}typedef hash;

void menuCorrect(int* task);

int push(cash** head, cash** tail, char* id, char* domen);

unsigned int chechCashForId(char* domen, hash* mas_hash, unsigned int size);

void changePlaceOfElement(unsigned int place_in_masive, hash** mas_hash, cash** head, cash** tail, unsigned int size);

int delateElementFromCache(hash** mas_hash, cash** tail, unsigned int size);

int addElementInCash(hash** mas_hash, cash** head, cash** tail, unsigned int size, char* domen, char* id);

void freeCash(cash** head, hash** mas, int size);

void checkUserAnswer(char* symbol);

int findIdMenu(cash** head, cash** tail, hash** mas_hash, unsigned int *size);