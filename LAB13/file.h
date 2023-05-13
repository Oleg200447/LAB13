#pragma once

int findId(FILE* file, char* domen,char **id);

void checkForCorrectType(int* type);

void findNewDomen(char** domen, char* str);

int defineStrType(char* str, unsigned int domen_size);

int findNeededString(char* domen, char** str, FILE* file);

int checkForIdInFile(FILE* file, char* id);

int checkForDomenFile(FILE* file, char* domen);

int addRecordInFileMenu();

int findAllDomensForIdMenu();

int checkForValidation(char* id);

int levelTen(int degree);

int chekerIPv4(char* id);

int chekerIPv6(char* id);