#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h"

int main() {
    setlocale(LC_CTYPE, "RUS");
    system("chcp 1251");

    puts("\nЗапись данных сотрудника");
    printf("(Полная структура: ФИО, должность, зарплата, дата рождения)\n");

    int n;
    printf("\nВведите количество сотрудников: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Ошибка ввода числа!\n");
        return 1;
    }

    if (n > MAX_EMPLOYEES) {
        printf("Лимит 50. Будет введено 50.\n");
        n = MAX_EMPLOYEES;
    }

    Employee emp[MAX_EMPLOYEES];

    fill_employees_manual(emp, n);

    char filename[100];
    printf("\nВведите имя файла для сохранения: ");
    scanf("%s", filename);

    if (save_report(filename, emp, n)) {
        printf("\nДанные сохранены в '%s'\n", filename);
    }
    else {
        printf("Ошибка создания файла!\n");
    }

    return 0;
}