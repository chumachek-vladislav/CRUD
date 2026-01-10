#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void process_text(FILE* input, FILE* output);
int read_and_process_file(char* input_filename, char* output_filename);

int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");

    char input_filename[] = "winter.txt";
    char output_filename[100];

    printf("Введите имя файла для записи результата: ");
    scanf("%s", output_filename);

    if (read_and_process_file(input_filename, output_filename) == 0) {
        printf("Результат записан в файл %s\n", output_filename);
    }
    else {
        printf("Ошибка при обработке файлов!\n");
        return 1;
    }

    return 0;
}

// Заменить все последние буквы слов цифрой 5
void process_text(FILE* input, FILE* output) {
    int ch;
    int stored_ch = -1; 

    while ((ch = fgetc(input)) != EOF) {

        if (isalpha((unsigned char)ch)) {

            if (stored_ch != -1) {
                fputc(stored_ch, output);
            }

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

    if (stored_ch != -1) {
        fputc('5', output);
    }
}

int read_and_process_file(char* input_filename, char* output_filename) {
    FILE* input_file, * output_file;

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", input_filename);
        return 1;
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", output_filename);
        fclose(input_file);
        return 1;
    }

    process_text(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    return 0;
}