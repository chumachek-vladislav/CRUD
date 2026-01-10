﻿#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char surname[50];
    char name[50];
    char patronymic[50];
    char position[50];
    double salary;
    int day, month, year;
} Employee;

int main() {
    setlocale(LC_CTYPE, "RUS");
    system("chcp 1251");
    puts("\nЗапись данных сотрудника");
    printf("(Полная структура: ФИО, должность, зарплата, дата рождения)\n");
    int n;
    printf("\nВведите количество сотрудников ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Ошибка: нужно минимум 1 сотрудник\n");
        return 1;
    }

    Employee emp[50];

    if (n > 50) {
        printf("Запись ограничена! Запись 50 сотрудников:\n");
    }
    for (int i = 0; i < n; i++) {
        printf("\n--- Сотрудник №%d ---\n", i + 1);

        printf("Фамилия: ");
        scanf("%s", emp[i].surname);

        printf("Имя: ");
        scanf("%s", emp[i].name);

        printf("Отчество: ");
        scanf("%s", emp[i].patronymic);

        printf("Должность: ");
        scanf("%s", emp[i].position);

        printf("Зарплата: ");
        scanf("%lf", &emp[i].salary);

        printf("Дата рождения (день месяц год через пробел): ");
        scanf("%d %d %d", &emp[i].day, &emp[i].month, &emp[i].year);
    }


    char filename[100];
    printf("\nВведите имя файла для сохранения (например: employees.txt): ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка! Не могу создать файл '%s'\n", filename);
        return 1;
    }


    fprintf(file, "ОТЧЕТ ПО СОТРУДНИКАМ\n");
    fprintf(file, "====================\n");
    fprintf(file, "Всего сотрудников: %d\n\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(file, "Сотрудник №%d\n", i + 1);
        fprintf(file, "  ФИО: %s %s %s\n", emp[i].surname, emp[i].name, emp[i].patronymic);
        fprintf(file, "  Должность: %s\n", emp[i].position);
        fprintf(file, "  Зарплата: %.2f\n", emp[i].salary);
        fprintf(file, "  Дата рождения: %02d.%02d.%04d\n\n",
            emp[i].day, emp[i].month, emp[i].year);
    }
    fclose(file);
    printf("\n!! - Данные успешно сохранены в файл '%s' - !!\n", filename);
    return 0;
}
