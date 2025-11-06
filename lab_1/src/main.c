#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define CHAR_N 304
#define INT_N 25
#define FLOAT_N 25

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    FILE* fileptr;
    int8_t file_flag = 1;

    //Создание массивов с символами, целыми и вещественными числами
    char  charArr[CHAR_N];
    int intArr[INT_N];
    float floatArr[FLOAT_N];

    //Открытие файла output.txt для записи
    fileptr = fopen("output.txt", "w+");
    if (fileptr == NULL){
        printf("Ошибка открытия файла! Данные не будут записаны!\n");
        file_flag = 0;
    }
    else printf("Файл output.txt успешно открыт\n");

    //Вывод массива символов
    fprintf(fileptr, "Вывод массива символов charArr:\n");
    for (int i = 0; i < CHAR_N; i++){
        fprintf(fileptr, "%3d - %c\t", i, charArr[i]);
        if ((i + 1) % 10 == 0) fprintf(fileptr, "\n");
    }
    fprintf(fileptr, "\n\n");

    //Вывод массива целых чисел
    fprintf(fileptr, "Вывод массива символов intArr:\n");
    for (int i = 0; i < INT_N; i++) fprintf(fileptr, "%2d - %d\n", i, intArr[i]);
    fprintf(fileptr, "\n");

    //Вывод массива вещественных чисел
    fprintf(fileptr, "Вывод массива вещественных чисел floatArr:\n");
    for (int i = 0; i < FLOAT_N; i++) fprintf(fileptr, "%2d - %g\n", i, floatArr[i]);
    fprintf(fileptr, "\n");

    //Создание массивов с фамилиями
    char cyrillicSurname[] = "Боярских"; //3.1
    wchar_t charredCyrrilicSurname[] = {L'Б', L'о', L'я', L'р', L'с', L'к', L'и', L'х', L'\0'}; //3.2
    
    char latinSurname[] = "Boyarskikh"; //3.3
    char charredLatinSurname[] = {'B', 'o', 'y', 'a', 'r', 's', 'k', 'i', 'k', 'h', '\0'}; //3.4

    //3.5 Вывод длин строк
    fprintf(fileptr, "3.5 Длины массивов:\n");
    fprintf(fileptr, "Кириллица (непрерывная): %lu\n", strlen(cyrillicSurname));
    fprintf(fileptr, "Кириллица (посимвольно): %lu\n", wcslen(charredCyrrilicSurname));
    fprintf(fileptr, "Латиница (непрерывная): %lu\n", strlen(latinSurname));
    fprintf(fileptr, "Латиница (посимвольно): %lu\n", strlen(charredLatinSurname));
    fprintf(fileptr, "\n");

    //3.6 Вывод строк
    fprintf(fileptr, "3.6 Вывод строк:\nВывод строк через %%s:\n");
    fprintf(fileptr, "Кириллица: %s\n", cyrillicSurname);
    fprintf(fileptr, "Латиница: %s\n", latinSurname);
    
    fprintf(fileptr, "\nВывод строк через %%c и цикл:\n");
    fprintf(fileptr, "Кириллица: ");
    for (int i = 0; i < wcslen(charredCyrrilicSurname); i++) fwprintf(fileptr, L"%lc", charredCyrrilicSurname[i]);
    fprintf(fileptr, "\n");
    fprintf(fileptr, "Латиница: ");
    for (int i = 0; i < strlen(charredLatinSurname); i++) fprintf(fileptr, "%c", charredLatinSurname[i]);
    fprintf(fileptr, "\n\n");

    //3.7 Вывод фамилии латиницей 2 раза с разделением \0
    fprintf(fileptr, "3.7 Вывод фамилии на латинице 2 раза с разделением \\0: \n");
    fprintf(fileptr, "%s\0%s\n", latinSurname, latinSurname);

    //3.8 Вывод фамилии кириллицей и латиницей с разделением \r
    fprintf(fileptr, "\n\n3.8 Вывод фамилии на кириллице, затем на латинице с разделением \\r: \n");
    fprintf(fileptr, "%s\r%s\n", cyrillicSurname, latinSurname);

    //3.9 Вывод фамилии латиницей с двойными кавычками
    fprintf(fileptr, "\n3.9 Вывод фамилии на латинице с двойными кавычками: \n");
    fprintf(fileptr, "\"%s\"\n", latinSurname);

    //3.10 Вывод первых трёх букв фамилии (Пусть будет латиница) N раз (номер в группе - 4 -> N = 4)
    fprintf(fileptr, "\n3.10 Вывод первых трёх букв фамилии N = 4 раз:\n");
    for (int i; i < 4; i++){
        fprintf(fileptr, "%.3s\n", latinSurname);
    }
    
    //Закрытие файла, если он был открыт
    if (file_flag){
        printf("Все данные успешно записаны в файл output.txt\n");
        fclose(fileptr);
        printf("Файл output.txt закрыт\n");
    }
    return 0;
}