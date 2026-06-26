#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int* arr = NULL;
int n = 0;
long long swapCount = 0;


void generateRandom() {
    int size, minVal, maxVal;
    printf("Размер: "); scanf("%d", &size);
    if (size <= 0) {
        printf("Размер должен быть положительным.\n");
        return;
    }
    printf("Минимум: "); scanf("%d", &minVal);
    printf("Максимум: "); scanf("%d", &maxVal);
    if (minVal > maxVal) {
        printf("Минимум не может быть больше максимума.\n");
        return;
    }
    int* temp = (int*)malloc(size * sizeof(int));
    if (!temp) {
        printf("Ошибка памяти.\n");
        return;
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
        temp[i] = minVal + rand() % (maxVal - minVal + 1);
    freeArray();
    arr = temp;
    n = size;
    printf("Сгенерировано %d чисел в диапазоне [%d, %d].\n", n, minVal, maxVal);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
        case 1: manualInput(); break;
        case 2: generateRandom(); break;
        case 3: loadFromFile(); break;
        case 4: sortArray(); break;
        case 5: saveToFile(); break;
        case 6: printf("Выход.\n"); break;
        default: printf("Неверный выбор.\n");
        }
    } while (choice != 6);
    freeArray();
    printf("Нажмите любую клавишу...");
    _getch();
    return 0;
}