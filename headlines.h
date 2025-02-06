#ifndef HEADLINES_H
#define HEADLINES_H

#include <stdio.h>
#include <stdlib.h>

// Структура для хранения информации о книге
typedef struct {
    char author[50];
    char title[50];
    char year[50];
} Book;

// Объявления функций
void writeToFile(Book *books, int count);
void readFromFile();
void addRecord( int * count);
void deleteRecord( int * count);
void searchRecords();
void editBook();
void displayRecords();
void create_my_own(int * count);
void creation_by_user(int * AAAAAA);
int utf8_strlen(const char* str);
void printf_extend(const char* s, int length);
void safe_fgets(char* s, int size);
void menu();

#endif // HEADLINES_H