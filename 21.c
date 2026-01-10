#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h" 

int main() {
    setlocale(LC_ALL, "");
    system("chcp 1251");
    employee_t employees[SIZE];
    int num = 0;
    char filename[50] = "database.txt";

    do {
        printf("\n====>>> МЕНЮ <<<===\n");
        printf("1 - Инициализация и вывод массива\n");
        printf("2 - Поиск\n");
        printf("3 - Сортировка по зарплате (qsort)\n");
        printf("4 - Запись в файл\n");
        printf("5 - Чтение из файла\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &num) != 1) {
            while (getchar() != '\n');
            num = 0;
        }

        switch (num) {
        case 1: {
            printf("\n");
            fill_array(employees, SIZE);
            print_array(employees, SIZE);
            break;
        }

        case 2: {
            printf("\n");
            char search_name[50];
            printf("Введите фамилию для поиска: ");
            scanf("%s", search_name);

            employee_t* found = search_by_lastname(employees, SIZE, search_name);
            if (found != NULL) {
                printf("Найден сотрудник:\n");
                print_employee(*found);
            }
            else {
                printf("Сотрудник с фамилией '%s' не найден.\n", search_name);
            }
            break;
        }

        case 3: {
            printf("\n");
            sort_employees_by_salary(employees, SIZE);
            printf("Массив отсортирован по зарплате:\n");
            print_array(employees, SIZE);
            break;
        }

        case 4: {
            printf("\nВведите имя файла для записи (например, data.txt): ");
            scanf("%s", filename);
            if (output_file(filename, employees, SIZE)) {
                printf("Данные успешно записаны в %s\n", filename);
            }
            else {
                printf("Ошибка записи файла!\n");
            }
            break;
        }

        case 5: {
            printf("\nВведите имя файла для чтения: ");
            scanf("%s", filename);
            int count = input_file(filename, employees);
            if (count > 0) {
                printf("Успешно прочитано %d записей.\n", count);
                print_array(employees, SIZE);
            }
            else {
                printf("Ошибка чтения или файл пуст/не найден.\n");
            }
            break;
        }
        case 0:
            printf("Выход из программы\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (num != 0);

    return 0;
}