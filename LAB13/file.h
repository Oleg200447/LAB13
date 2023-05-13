#pragma once

int findId(FILE* file,const char* domen,char **id);

void checkForCorrectType(int* type);

void findNewDomen(char** domen,const char* str);

int defineStrType(const char* str, unsigned int domen_size);

int findNeededString(const char* domen, char** str, FILE* file);

int checkForIdInFile(FILE* file,const char* id);

int checkForDomenFile(FILE* file,const char* domen);

int addRecordInFileMenu();

int findAllDomensForIdMenu();

int checkForValidation(char* id);

int levelTen(int degree);

int chekerIPv4(const char* id);

int chekerIPv6(const char* id);