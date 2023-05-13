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

int push(cash** head, cash** tail, char* id);

unsigned int chechCashForId(const char* domen,const hash* mas_hash, unsigned int size);

void changePlaceOfElement(unsigned int place_in_masive, hash** mas_hash, cash** head, cash** tail, unsigned int size);

int delateElementFromCache(hash** mas_hash, cash** tail,int size);

int addElementInCash(hash** mas_hash, cash** head, cash** tail, unsigned int size,const char* domen, char* id);

void freeCash(hash** mas, int size);

void checkUserAnswer(char* symbol);

int findIdMenu(cash** head, cash** tail, hash** mas_hash, int *size);

void watchCash(cash* head);