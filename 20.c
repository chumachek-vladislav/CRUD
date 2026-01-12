#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h"

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");

    char input_filename[] = "winter.txt";
    char output_filename[100];

    printf("Введите имя файла для записи результата: ");
    if (scanf("%99s", output_filename) != 1) { 
        printf("Ошибка ввода имени файла.\n");
        return 1;
    }

    if (read_and_process_file(input_filename, output_filename) == 0) {
        printf("Результат записан в файл %s\n", output_filename);
    }
    else {
        printf("Ошибка при обработке файлов!\n");
        return 1;
    }

    return 0;
}