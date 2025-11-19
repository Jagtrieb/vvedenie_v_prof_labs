#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    const int CHAR_N = 304;
    const int INT_N = 25;
    const int FLOAT_N = 25;

    const int a = 304;
    //Создание массивов с символами, целыми и вещественными числами
    char  charArr[CHAR_N];
    int intArr[INT_N];
    float floatArr[FLOAT_N];


    //Вывод массива символов
    printf("Вывод массива символов charArr:\n");
    for (int i = 0; i < CHAR_N; i++){
        printf("%3d - %c\t", i, charArr[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n\n");

    //Вывод массива целых чисел
    printf("Вывод массива символов intArr:\n");
    for (int i = 0; i < INT_N; i++) printf("%2d - %d\n", i, intArr[i]);
    printf("\n");

    //Вывод массива вещественных чисел
    printf("Вывод массива вещественных чисел floatArr:\n");
    for (int i = 0; i < FLOAT_N; i++) printf("%2d - %g\n", i, floatArr[i]);
    printf("\n");

    //Создание массивов с фамилиями
    char cyrillicSurname[] = "Боярских"; //3.1
    wchar_t charredCyrrilicSurname[] = {L'Б', L'о', L'я', L'р', L'с', L'к', L'и', L'х', L'\0'}; //3.2
    
    char latinSurname[] = "Boyarskikh"; //3.3
    char charredLatinSurname[] = {'B', 'o', 'y', 'a', 'r', 's', 'k', 'i', 'k', 'h', '\0'}; //3.4

    //3.5 Вывод длин строк
    printf("3.5 Длины массивов:\n");
    printf("Кириллица (непрерывная): %lu\n", strlen(cyrillicSurname));
    printf("Кириллица (посимвольно): %lu\n", wcslen(charredCyrrilicSurname));
    printf("Латиница (непрерывная): %lu\n", strlen(latinSurname));
    printf("Латиница (посимвольно): %lu\n", strlen(charredLatinSurname));
    printf("\n");

    //3.6 Вывод строк
    printf("3.6 Вывод строк:\nВывод строк через %%s:\n");
    printf("Кириллица: %s\n", cyrillicSurname);
    printf("Латиница: %s\n", latinSurname);
    
    printf("\nВывод строк через %%c и цикл:\n");
    printf("Кириллица: ");
    for (int i = 0; i < wcslen(charredCyrrilicSurname); i++) wprintf(L"%lc", charredCyrrilicSurname[i]);
    printf("\n");
    printf("Латиница: ");
    for (int i = 0; i < strlen(charredLatinSurname); i++) printf("%c", charredLatinSurname[i]);
    printf("\n\n");

    //3.7 Вывод фамилии латиницей 2 раза с разделением \0
    printf("3.7 Вывод фамилии на латинице 2 раза с разделением \\0: \n");
    printf("%s\0%s\n", latinSurname, latinSurname);

    //3.8 Вывод фамилии кириллицей и латиницей с разделением \r
    printf("\n\n3.8 Вывод фамилии на кириллице, затем на латинице с разделением \\r: \n");
    printf("%s\r%s\n", cyrillicSurname, latinSurname);

    //3.9 Вывод фамилии латиницей с двойными кавычками
    printf("\n3.9 Вывод фамилии на латинице с двойными кавычками: \n");
    printf("\"%s\"\n", latinSurname);

    //3.10 Вывод первых трёх букв фамилии (Пусть будет латиница) N раз (номер в группе - 4 -> N = 4)
    printf("\n3.10 Вывод первых трёх букв фамилии N = 4 раз:\n");
    for (int i; i < 4; i++){
        printf("%.3s\n", latinSurname);
    }
    return 0;
}