#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 5

// Структура "Сотрудник"
typedef struct Employee {
    char lastName[50];
    char firstName[50];
    char patronymic[50];
    char position[50];
    float salary;
    char birthDate[11];
} employee_t;

void fill_array(employee_t employees[], int size); // Функция для заполнения массива константами
void print_employee(employee_t emp); // Функция для печати одной записи
void print_array(employee_t employees[], int size); // Функция для печати всего массива
employee_t* search_by_lastname(employee_t* employees, int size, char* lastname); // Функция для поиска по фамилии
void sort_employees_by_salary(employee_t employees[], int size); // Функция для сравнения для сортировки по зарплате
int compare_by_salary(const void* a, const void* b); // Функция сортировки массива qsort
int output_file(char* filename, employee_t* arr, int n); // Для записи файла
int input_file(char* filename, employee_t* arr); // Для чтения файла

int main() {
    setlocale(LC_ALL, "");
    system("chcp 1251");
    employee_t employees[SIZE];
    int num = 0;
    int is_filled = 0;
    char filename[50] = "database.txt";

    do {
        printf("\n====>>> МЕНЮ <<<===\n");
        printf("1 - Инициализация и вывод массива\n");
        printf("2 - Поиск\n");
        printf("3 - Сортировка по зарплате (qsort)\n");
        printf("4 - Запись массива в файл\n");
        printf("5 - Чтение массива из файла\n");
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
