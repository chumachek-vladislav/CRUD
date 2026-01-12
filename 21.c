#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h" 

int main() {
    setlocale(LC_ALL, "");
    system("chcp 1251");

    Employee employees[SIZE]; 
    int num = 0;
    char filename[50] = "database.txt";

    do {
        printf("\n====>>> МЕНЮ <<<===\n");
        printf("1 - Инициализация и вывод\n");
        printf("2 - Поиск\n");
        printf("3 - Сортировка по зарплате\n");
        printf("4 - Запись в файл\n");
        printf("5 - Чтение из файла\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &num) != 1) {
            while (getchar() != '\n'); num = 0;
        }

        switch (num) {
        case 1:
            fill_array(employees, SIZE);
            print_array(employees, SIZE);
            break;
        case 2: {
            char search_name[50];
            printf("Введите фамилию: ");
            scanf("%s", search_name);
            Employee* found = search_by_lastname(employees, SIZE, search_name);
            if (found) {
                printf("Найден:\n");
                print_employee(*found);
            }
            else printf("Не найдено\n");
            break;
        }
        case 3:
            sort_employees_by_salary(employees, SIZE);
            printf("Отсортировано.\n");
            print_array(employees, SIZE);
            break;
        case 4:
            printf("Файл для записи: "); scanf("%s", filename);
            output_file(filename, employees, SIZE);
            break;
        case 5:
            printf("Файл для чтения: "); scanf("%s", filename);
            if (input_file(filename, employees) > 0) print_array(employees, SIZE);
            else printf("Ошибка чтения\n");
            break;
        case 0: break;
        default: printf("Неверно\n");
        }
    } while (num != 0);

    return 0;
}