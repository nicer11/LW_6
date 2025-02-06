#include "headlines.h"
#include <string.h>
#include <io.h>


/*

void printf_extend(const char* s, int length)
{
    int i = (true_str_len - 1)-1;
    
    while (i>=0 && s[i]!=' ')
    {
        i--;
        
    }
    printf("%s", s);
    for (int j=0; j< (length - 1) - i ; j++)
    {
        printf(" ");
    }
}
*/




// Функция для подсчета количества символов в строке UTF-8
int utf8_strlen(const char* str) {
    int len = 0;

    // Проверяем, дошли ли мы до конца строки
    while (* str != '\0') {

        // Побитовое И с маской 0xc0 = 11000000. В кодировке UTF-8 байты, начинающиеся с 10xxxxxx (0x80 до 0xBF), являются продолжением многобайтового символа. А именно, 2 байта:( 110xxxxx 10xxxxxx ), 3 байта: (1110xxxx 10xxxxxx )
        // 4 байта:( 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx) -  каждый из них обозначает один объект в кодировке UTF-8. Выходит, число занятых char не равно числу объектов
        if ((*str & 0xC0) != 0x80) { 
            len++;
        }
        str++; // Важный момент, константой является не указатель, а содержимое, на которое str указывает. Ошибки не будет
    }
    return len;
}

// Функция для выравнивания строки с символами UTF-8
void printf_extend(const char* s, int length) {
    int utf8_len = utf8_strlen(s);
    printf("%s", s);
    for (int i = utf8_len  ; i < length; i++) { 
        printf(" ");
    }
}

void safe_fgets(char* s, int size) {
    fgets(s, size, stdin);
    int len = strlen(s);
    if (s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}


void menu() {
    printf("Меню:\n");
    printf("1. Добавить запись\n");
    printf("2. Удалить запись\n");
    printf("3. Поиск записей\n");
    printf("4. Редактировать запись\n");
    printf("5. Показать все записи\n");
    printf("6. Выход\n");
}


void create_my_own(int * count) {
    FILE* file = fopen("books.bin", "wb");
    if (file != NULL) {
         Book books[] = {
            {"Александр Пушкин", "Евгений Онегин", "1823"},
            {"Лев Толстой", "Война и мир", "1869"},
            {"Федор Достоевский", "Преступление и наказание", "1866"},
            {"Николай Гоголь", "Мертвые души", "1842"},
            {"Иван Тургенев", "Отцы и дети", "1862"},
            {"Антон Чехов", "Вишневый сад", "1904"},
            {"Михаил Булгаков", "Мастер и Маргарита", "1967"},
            {"Александр Солженицын", "Архипелаг ГУЛАГ", "1973"},
            {"Александр Пушкин", "Капитанская дочка", "1836"},
            {"Александр Пушкин", "Борис Годунов", "1825"},
            {"Лев Толстой", "Анна Каренина", "1877"},
            {"Лев Толстой", "Детство", "1852"},
            {"Федор Достоевский", "Идиот", "1869"},
            {"Федор Достоевский", "Братья Карамазовы", "1880"},
            {"Николай Гоголь", "Ревизор", "1836"},
            {"Николай Гоголь", "Тарас Бульба", "1835"},
            {"Иван Тургенев", "Дворянское гнездо", "1859"},
            {"Иван Тургенев", "Записки охотника", "1852"},
            {"Антон Чехов", "Чайка", "1896"},
            {"Антон Чехов", "Дядя Ваня", "1899"},
            {"Михаил Булгаков", "Белая гвардия", "1925"},
            {"Михаил Булгаков", "Собачье сердце", "1925"},
            {"Александр Солженицын", "Раковый корпус", "1968"},
            {"Александр Солженицын", "Один день Ивана Денисовича", "1962"},
            {"Александр Пушкин", "Руслан и Людмила", "1820"},
            {"Лев Толстой", "Крейцерова соната", "1889"},
            {"Федор Достоевский", "Бесы", "1872"},
            {"Николай Гоголь", "Майская ночь", "1832"},
            {"Иван Тургенев", "Ася", "1858"},
            {"Антон Чехов", "Толстый и тонкий", "1883"},
            {"Михаил Булгаков", "Дьяволиада", "1925"},
            {"Александр Солженицын", "Октябрьская трилогия", "1974"},
            {"Александр Пушкин", "Пиковая дама", "1834"},
            {"Лев Толстой", "Смерть Ивана Ильича", "1886"},
            {"Федор Достоевский", "Игрок", "1866"},
            {"Николай Гоголь", "Вий", "1835"},
            {"Иван Тургенев", "Накануне", "1860"},
            {"Антон Чехов", "В овраге", "1900"},
            {"Михаил Булгаков", "Багровый остров", "1927"},
            {"Александр Солженицын", "Канцлер", "2000"},
            {"Александр Пушкин", "Медный всадник", "1837"},
            {"Лев Толстой", "Хаджи-Мурат", "1912"},
            {"Федор Достоевский", "Белые ночи", "1848"},
            {"Николай Гоголь", "Шинель", "1842"}
            
            };
            *count = sizeof(books) / sizeof(Book);

            fwrite(books, 1, sizeof(books), file);

        fclose(file);
    } else {
        printf("Ошибка при открытии файла.\n");
    }
}

// Функция для создания массива книг с вводом данных пользователем
void creation_by_user(int *count) {
    FILE* file = fopen("books.bin", "wb");
    printf("Введите количество книг: ");
        
        scanf("%d", count);
        getchar();
        for(int i=0; i<(* count);i++)
        {
            Book book;
            printf("Введите автора %d: ",i+1);
            safe_fgets( book.author, sizeof(book.author));
            printf("Введите название %d: ",i+1);
            safe_fgets( book.title, sizeof(book.title));
            printf("Введите год %d: ", i+1);
            safe_fgets( book.year, sizeof(book.year));
            fwrite(&book, sizeof(Book), 1, file);
        }
        fclose(file);
}



// Функция для записи массива книг в бинарный файл
void writeToFile(Book *books, int count) {
    FILE *file = fopen("books.bin", "wb");
    if (file != NULL) {
        fwrite(books, sizeof(Book), count, file);
        fclose(file);
    } else {
        printf("Ошибка при открытии файла.\n");
    }
}

// Функция для чтения массива книг из бинарного файла
void readFromFile() {
    FILE *file = fopen("books.bin", "rb");
    if (file != NULL) {
        Book book;
        int index = 0;
        while (fread(&book, sizeof(Book), 1, file)) {
            printf("Индекс: %d, Автор: %s, Название: %s, Год: %s\n", index++, book.author, book.title, book.year);
        }
        fclose(file);
    } else {
        printf("Ошибка при открытии файла.\n");
    }
}

// Функция для редактирования информации о книге по индексу
void editBook() {
    FILE *file = fopen("books.bin", "rb+"); // Открытие файла "books.bin" для чтения и записи в бинарном режиме
    if (file != NULL) {
        int index;
        printf("Введите индекс записи для редактирования: ");
        scanf("%d", &index);
        getchar();
        fseek(file, (index-1) * sizeof(Book), SEEK_SET); // Перемещение указателя файла на нужную позицию

        Book book;
        // Ввод новой информации о книге
        printf("Введите нового автора книги: ");
        safe_fgets( book.author, sizeof(book.author));
        printf("Введите новое название книги: ");
        safe_fgets( book.title, sizeof(book.title));
        printf("Введите новый год издания книги: ");
        safe_fgets( book.year, sizeof(book.year));
        
        fwrite(&book, sizeof(Book), 1, file); // Запись новой информации о книге в файл
        fclose(file); // Закрытие файла
    } else {
        printf("Ошибка при открытии файла.\n"); // Сообщение об ошибке при открытии файла
    }
}



// Функция для добавления записи в файл
void addRecord( int * count) {
    FILE *file = fopen("books.bin", "ab");
    if (file != NULL) {
        Book book;
        printf("Введите автора: ");
        safe_fgets( book.author, sizeof(book.author));
        printf("Введите название: ");
        safe_fgets( book.title, sizeof(book.title));
        printf("Введите год: ");
        safe_fgets( book.year, sizeof(book.year));
        fwrite(&book, sizeof(Book), 1, file);
        fclose(file);
    } else {
        printf("Ошибка при открытии файла.\n");
    }
    (*count)++;
}

// Функция для удаления записи из файла по индексу
void deleteRecord( int * count) {
    FILE *file = fopen("books.bin", "rb+"); // Открытие файла для чтения и записи
    if (file != NULL) {
        
        int index;
        printf("Введите индекс записи для удаления: ");
        scanf("%d", &index);
        getchar();
        index--;

        if (index < 0 || index >= (* count)) {
            printf("Неверный индекс.\n");
            fclose(file);
            return;
        }
        Book book;
        for (int i = index + 1; i < (* count); i++) {
            fseek(file, i * sizeof(Book), SEEK_SET); // Перемещение указателя на следующую запись
            fread(&book, sizeof(Book), 1, file); // Чтение следующей записи
            fseek(file, (i - 1) * sizeof(Book), SEEK_SET); // Перемещение указателя на предыдущую позицию
            fwrite(&book, sizeof(Book), 1, file); // Запись следующей записи на предыдущую позицию
        }

        // Обрезка файла до нового размера
        _chsize_s(_fileno(file), ((* count) - 1) * sizeof(Book));// _fileno возвращает файловый дескриптор - число, определяющее открытый файл в операционной системе
        (* count)--; // Уменьшение количества записей

        fclose(file); // Закрытие файла
    } else {
        printf("Ошибка при открытии файла.\n");
    }
}

// Функция для поиска записей по заданному полю
void searchRecords() {
    FILE *file = fopen("books.bin", "rb");
    if (file != NULL) {
        char value[50];
        int field;
        printf("Введите критерий для поиска (число 1 = автор, число 2 = назавание, число 3 = год): ");
        scanf("%d", &field);
        getchar();
        printf("Введите значение для поиска: ");
        safe_fgets(value, sizeof(value));
        Book book;
        int found = 0;
        int num = 1;
        printf("Индекс\tАвтор\t\t\tНазвание\t\t   Год\n");
        printf("-------------------------------------------------------------\n");
        if (field ==1)
        {
        while (fread(&book, sizeof(Book), 1, file)) {  // Читаем, пока читается
            // printf("%s, %s, %d\n", book.author, value, strcmp(book.author, value) );
            if (strcmp(book.author, value) == 0)  {
                printf("%d\t", num);
                printf_extend(book.author, 24);
                printf_extend(book.title, 27);
                printf("%s\n", book.year);
                found = 1;
            }
            num++;
        }

        } else if (field == 2) {
            while (fread(&book, sizeof(Book), 1, file)) {
                if (strcmp(book.title, value) == 0) {
                    printf("%d\t", num);
                    printf_extend(book.author, 24);
                    printf_extend(book.title, 26);
                    printf("%s\n", book.year);
                    found = 1;
                }
                num++;
            }
        } else if (field == 3) {
            while (fread(&book, sizeof(Book), 1, file)) {
                if (strcmp(book.year, value) == 0) {
                    printf("%d\t", num);
                    printf_extend(book.author, 24);
                    printf_extend(book.title, 26);
                    printf("%s\n", book.year);
                    found = 1;
                }
                num++;
            }
        } else {
            printf("Неверное поле для поиска.\n");
        }

        if (!found) {
            printf("Записи не найдены (нет точного совпадения).\n");
        }
        fclose(file);
    } else {
        printf("Ошибка при открытии файла.\n");
    }
}



// Функция для вывода содержимого файла в табличном виде
void displayRecords() {
    FILE *file = fopen("books.bin", "rb");
    if (file != NULL) {
        Book book;
        printf("Индекс\tАвтор\t\t\tНазвание\t\t   Год\n");
        printf("-------------------------------------------------------------\n");
        int index = 0;
        while (fread(&book, sizeof(Book), 1, file)) {
            printf("%d\t", ++index);
            printf_extend(book.author, 24);
            printf_extend(book.title, 27);
            printf("%s\n", book.year);
            
        }
        fclose(file);
    } else {
        printf("Ошибка при открытии файла.\n");
    }
}