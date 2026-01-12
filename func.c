#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "func.h" 

void fill_array(Employee employees[], int size) {
    Employee const_data[SIZE] = {
        {"Иванов", "Иван", "Иванович", "Инженер", 50000.0, "15.05.1985"},
        {"Петрова", "Мария", "Сергеевна", "Бухгалтер", 45000.0, "22.11.1990"},
        {"Сидоров", "Алексей", "Петрович", "Менеджер", 60000.0, "03.08.1988"},
        {"Кузнецова", "Елена", "Викторовна", "Дизайнер", 55000.0, "17.09.1992"},
        {"Смирнов", "Дмитрий", "Алексеевич", "Директор", 80000.0, "30.01.1987"}
    };
    for (int i = 0; i < size; i++) {
        employees[i] = const_data[i];
    }
}

void print_employee(Employee emp) {
    printf("| %-10s | %-10s | %-12s | %-10s | %8.2f | %10s |\n",
        emp.surname, emp.name, emp.patronymic,
        emp.position, emp.salary, emp.birthDate);
}

void print_array(Employee employees[], int size) {
    printf("=== Вывод массива сотрудников ===\n");
    for (int i = 0; i < size; i++) {
        printf("Запись %d: ", i + 1);
        print_employee(employees[i]);
    }
}

Employee* search_by_lastname(Employee* employees, int size, char* lastname) {
    for (int i = 0; i < size; i++) {
        if (strcmp(employees[i].surname, lastname) == 0)
            return (employees + i);
    }
    return NULL;
}

int compare_by_salary(const void* a, const void* b) {
    const Employee* employeeA = (const Employee*)a;
    const Employee* employeeB = (const Employee*)b;
    if (employeeA->salary < employeeB->salary) return -1;
    else if (employeeA->salary > employeeB->salary) return 1;
    return 0;
}

void sort_employees_by_salary(Employee employees[], int size) {
    qsort(employees, size, sizeof(Employee), compare_by_salary);
}

int output_file(char* filename, Employee* arr, int n) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) return 0;

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s %s %s %.2f %s\n",
            arr[i].surname, arr[i].name, arr[i].patronymic,
            arr[i].position, arr[i].salary, arr[i].birthDate);
    }
    fclose(fp);
    return 1;
}

int input_file(char* filename, Employee* arr) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) return 0;

    int i = 0;
    while (i < SIZE && fscanf(fp, "%s %s %s %s %lf %s",
        arr[i].surname, arr[i].name, arr[i].patronymic,
        arr[i].position, &arr[i].salary, arr[i].birthDate) == 6) {
        i++;
    }
    fclose(fp);
    return i;
}

void process_text(FILE* input, FILE* output) {
    int ch;
    int stored_ch = -1;
    while ((ch = fgetc(input)) != EOF) {
        if (isalpha((unsigned char)ch)) {
            if (stored_ch != -1) fputc(stored_ch, output);
            stored_ch = ch;
        }
        else {
            if (stored_ch != -1) {
                fputc('5', output);
                stored_ch = -1;
            }
            fputc(ch, output);
        }
    }
    if (stored_ch != -1) fputc('5', output);
}

int read_and_process_file(char* input_filename, char* output_filename) {
    FILE* input_file = fopen(input_filename, "r");
    if (!input_file) {
        printf("Ошибка: не удалось открыть файл %s\n", input_filename);
        return 1;
    }
    FILE* output_file = fopen(output_filename, "w");
    if (!output_file) {
        printf("Ошибка: не удалось создать файл %s\n", output_filename);
        fclose(input_file);
        return 1;
    }
    process_text(input_file, output_file);
    fclose(input_file);
    fclose(output_file);
    return 0;
}

void fill_employees_manual(Employee* emp, int n) {
    int d, m, y; 
    for (int i = 0; i < n; i++) {
        printf("\n--- Сотрудник №%d ---\n", i + 1);
        printf("Фамилия: "); scanf("%s", emp[i].surname);
        printf("Имя: "); scanf("%s", emp[i].name);
        printf("Отчество: "); scanf("%s", emp[i].patronymic);
        printf("Должность: "); scanf("%s", emp[i].position);
        printf("Зарплата: "); scanf("%lf", &emp[i].salary);

        printf("Дата рождения (день месяц год через пробел): ");
        scanf("%d %d %d", &d, &m, &y);

        sprintf(emp[i].birthDate, "%02d.%02d.%04d", d, m, y);
    }
}

int save_report(char* filename, Employee* emp, int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    fprintf(file, "ОТЧЕТ ПО СОТРУДНИКАМ\n");
    fprintf(file, "====================\n");
    fprintf(file, "Всего сотрудников: %d\n\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(file, "Сотрудник №%d\n", i + 1);
        fprintf(file, "  ФИО: %s %s %s\n", emp[i].surname, emp[i].name, emp[i].patronymic);
        fprintf(file, "  Должность: %s\n", emp[i].position);
        fprintf(file, "  Зарплата: %.2f\n", emp[i].salary);
        fprintf(file, "  Дата рождения: %s\n\n", emp[i].birthDate);
    }
    fclose(file);
    return 1;
}