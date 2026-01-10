#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#define SIZE 5

typedef struct Employee {
    char lastName[50];
    char firstName[50];
    char patronymic[50];
    char position[50];
    float salary;
    char birthDate[11];
} employee_t;

/**
 * Заполнение массива сотрудников предустановленными (тестовыми) данными
 * @param employees массив структур сотрудников
 * @param size размер массива
 */
void fill_array(employee_t employees[], int size);

/**
 * Вывод информации об одном сотруднике в консоль
 * @param emp структура сотрудника для вывода
 */
void print_employee(employee_t emp);

/**
 * Вывод списка всех сотрудников из массива
 * @param employees массив структур сотрудников
 * @param size размер массива
 */
void print_array(employee_t employees[], int size);

/**
 * Поиск сотрудника в массиве по фамилии
 * @param employees указатель на массив сотрудников
 * @param size размер массива
 * @param lastname искомая фамилия
 * @return указатель на найденную структуру или NULL, если не найден
 */
employee_t* search_by_lastname(employee_t* employees, int size, char* lastname);

/**
 * Сортировка массива сотрудников по возрастанию зарплаты
 * @param employees массив сотрудников
 * @param size размер массива
 */
void sort_employees_by_salary(employee_t employees[], int size);

/**
 * Функция сравнения двух сотрудников по зарплате (для qsort)
 * @param a указатель на первый элемент
 * @param b указатель на второй элемент
 * @return -1 если a < b, 1 если a > b, 0 если равны
 */
int compare_by_salary(const void* a, const void* b);

/**
 * Запись массива сотрудников в текстовый файл
 * @param filename имя файла для записи
 * @param arr указатель на массив сотрудников
 * @param n количество элементов для записи
 * @return 1 - успешно, 0 - ошибка открытия файла
 */
int output_file(char* filename, employee_t* arr, int n);

/**
 * Чтение данных о сотрудниках из текстового файла в массив
 * @param filename имя файла для чтения
 * @param arr указатель на массив для заполнения
 * @return количество успешно считанных структур
 */
int input_file(char* filename, employee_t* arr);

#endif