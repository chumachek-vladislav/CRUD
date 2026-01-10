#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h" 

void fill_array(employee_t employees[], int size) {
    employee_t const_data[SIZE] = {
        {"Иванов", "Иван", "Иванович", "Инженер", 50000, "15.05.1985"},
        {"Петрова", "Мария", "Сергеевна", "Бухгалтер", 45000, "22.11.1990"},
        {"Сидоров", "Алексей", "Петрович", "Менеджер", 60000, "03.08.1988"},
        {"Кузнецова", "Елена", "Викторовна", "Дизайнер", 55000, "17.09.1992"},
        {"Смирнов", "Дмитрий", "Алексеевич", "Директор", 80000, "30.01.1987"}
    };

    for (int i = 0; i < size; i++) {
        employees[i] = const_data[i];
    }
}

void print_employee(employee_t emp) {
    printf("| %-10s | %-10s | %-12s | %-10s | %8.2f | %10s |\n",
        emp.lastName, emp.firstName, emp.patronymic,
        emp.position, emp.salary, emp.birthDate);
}

void print_array(employee_t employees[], int size) {
    printf("=== Вывод массива сотрудников ===\n");
    for (int i = 0; i < size; i++) {
        printf("Запись %d: ", i + 1);
        print_employee(employees[i]);
    }
}

employee_t* search_by_lastname(employee_t* employees, int size, char* lastname) {
    for (int i = 0; i < size; i++) {
        if (strcmp(employees[i].lastName, lastname) == 0)
            return (employees + i);
    }
    return NULL;
}

int compare_by_salary(const void* a, const void* b) {
    const employee_t* employeeA = (const employee_t*)a;
    const employee_t* employeeB = (const employee_t*)b;

    if (employeeA->salary < employeeB->salary) {
        return -1;
    }
    else if (employeeA->salary > employeeB->salary) {
        return 1;
    }
    return 0;
}

void sort_employees_by_salary(employee_t employees[], int size) {
    qsort(employees, size, sizeof(employee_t), compare_by_salary);
}

int output_file(char* filename, employee_t* arr, int n) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s %s %s %.2f %s\n",
            arr[i].lastName,
            arr[i].firstName,
            arr[i].patronymic,
            arr[i].position,
            arr[i].salary,
            arr[i].birthDate);
    }

    fclose(fp);
    return 1;
}

int input_file(char* filename, employee_t* arr) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0;
    }

    int i = 0;
    while (i < SIZE && fscanf(fp, "%s %s %s %s %f %s",
        arr[i].lastName,
        arr[i].firstName,
        arr[i].patronymic,
        arr[i].position,
        &arr[i].salary,
        arr[i].birthDate) == 6) {
        i++;
    }

    fclose(fp);
    return i;
}