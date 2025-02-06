#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "headlines.h"

// Прототипы функций и указатели на функции
void (*menu_ptr)() = menu;
void (*create_my_own_ptr)(int *) = create_my_own;
void (*creation_by_user_ptr)(int *) = creation_by_user;
void (*displayRecords_ptr)() = displayRecords;
void (*addRecord_ptr)(int *) = addRecord;
void (*deleteRecord_ptr)(int *) = deleteRecord;
void (*searchRecords_ptr)() = searchRecords;
void (*editBook_ptr)() = editBook;

int main() {
    // Установка кодировки для корректного отображения UTF-8 в консоли
    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Запрос у пользователя, использовать готовые данные или создать свои
    printf("С готовыми данными или создать свои? (1 - готовые, 2 - свои): ");
    int choice;
    scanf("%d", &choice);
    getchar(); // Удаление символа новой строки из буфера ввода
    int count;
    if (choice == 1) {
        // Создание готовых данных и отображение записей
        create_my_own_ptr(&count);
        displayRecords_ptr();
    } else {
        // Создание данных пользователем
        creation_by_user_ptr(&count);
        displayRecords_ptr();
    }

    // Основной цикл программы
    do {
        // Отображение меню
        menu_ptr();
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar(); // Удаление символа новой строки из буфера ввода

        // Выполнение действия в зависимости от выбора пользователя
        if (choice == 1) {
            // Добавление новой записи
            addRecord_ptr(&count);
            displayRecords_ptr();
        } else if (choice == 2) {
            // Удаление записи
            deleteRecord_ptr(&count);
            displayRecords_ptr();
        } else if (choice == 3) {
            // Поиск записей
            searchRecords_ptr();
        } else if (choice == 4) {
            // Редактирование записи
            editBook_ptr();
            displayRecords_ptr();
        } else if (choice == 5) {
            // Отображение всех записей
            displayRecords_ptr();
        }
    } while (choice != 6); // Завершение программы при выборе 6

    return 0;
}