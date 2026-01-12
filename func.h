#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>

#define SIZE 5 
#define MAX_EMPLOYEES 50 

typedef struct {
    char surname[50];      
    char name[50];         
    char patronymic[50];  
    char position[50];      
    double salary;        
    char birthDate[15];     
} Employee;

 /**
  * Заполнение массива сотрудников тестовыми данными
  * @param employees массив структур
  * @param size размер массива
  */
void fill_array(Employee employees[], int size);

/**
 * Вывод одного сотрудника в консоль
 */
void print_employee(Employee emp);

/**
 * Вывод таблицы сотрудников
 */
void print_array(Employee employees[], int size);

/**
 * Поиск по фамилии
 */
Employee* search_by_lastname(Employee* employees, int size, char* lastname);

/**
 * Сортировка по зарплате (qsort)
 */
void sort_employees_by_salary(Employee employees[], int size);

/**
 * Компаратор для qsort
 */
int compare_by_salary(const void* a, const void* b);

/**
 * Запись массива в файл
 */
int output_file(char* filename, Employee* arr, int n);

/**
 * Чтение из файла в массив
 */
int input_file(char* filename, Employee* arr);

/**
 * Читает входной файл посимвольно и переписывает его в выходной,
 * заменяя последнюю букву каждого слова на цифру '5'
 * @param input указатель на открытый файл для чтения
 * @param output указатель на открытый файл для записи
 */
void process_text(FILE* input, FILE* output);

/**
 * Открывает файлы по заданным именам и запускает процесс обработки текста
 * @param input_filename имя исходного файла
 * @param output_filename имя файла для сохранения результата
 * @return 0 - успешно, 1 - ошибка открытия файлов
 */
int read_and_process_file(char* input_filename, char* output_filename);

 /**
  * Ввод данных с клавиатуры.
  * Внутри конвертирует введенные день/месяц/год в строку birthDate.
  */
void fill_employees_manual(Employee* emp, int n);

/**
 * Сохранение отчета (форматированного)
 */
int save_report(char* filename, Employee* emp, int n);

#endif