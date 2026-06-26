#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int* arr = NULL;
int n = 0;
long long swapCount = 0;

void freeArray() {
    if (arr) {
        free(arr);
        arr = NULL;
        n = 0;
    }
}

void printArray(int a[], int size) {
    if (size == 0) {
        printf("Массив пуст.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d", a[i]);
        if (i < size - 1) printf(", ");
    }
    printf("\n");
}

// Сортировка пузырьком с выбором направления: ascending = 1 - по возрастанию, 0 - по убыванию
void bubbleSort(int a[], int size, long long* swaps, int ascending) {
    *swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            int needSwap = 0;
            if (ascending) {
                if (a[j] > a[j + 1]) needSwap = 1;
            }
            else {
                if (a[j] < a[j + 1]) needSwap = 1;
            }
            if (needSwap) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                (*swaps)++;
            }
        }
    }
}

int readNumber(FILE* f, int* num) {
    int c;
    do {
        c = fgetc(f);
        if (c == EOF) return 0;
    } while (!((c >= '0' && c <= '9') || c == '-'));
    ungetc(c, f);
    return fscanf(f, "%d", num) == 1;
}

int loadFromFile() {
    FILE* f = fopen("input.txt", "r");
    if (!f) {
        printf("Ошибка: файл input.txt не найден.\n");
        return 0;
    }
    int* temp = NULL;
    int count = 0, capacity = 10;
    temp = (int*)malloc(capacity * sizeof(int));
    if (!temp) {
        printf("Ошибка памяти.\n");
        fclose(f);
        return 0;
    }
    int num;
    while (readNumber(f, &num)) {
        if (count >= capacity) {
            capacity *= 2;
            int* newTemp = (int*)realloc(temp, capacity * sizeof(int));
            if (!newTemp) {
                printf("Ошибка памяти при чтении.\n");
                free(temp);
                fclose(f);
                return 0;
            }
            temp = newTemp;
        }
        temp[count++] = num;
    }
    fclose(f);
    if (count == 0) {
        printf("Файл пуст или не содержит чисел.\n");
        free(temp);
        return 0;
    }
    freeArray();
    arr = temp;
    n = count;
    printf("Загружено %d чисел из input.txt.\n", n);
    return 1;
}



void manualInput() {
    int size;
    printf("Введите размер: ");
    scanf("%d", &size);
    if (size <= 0) {
        printf("Размер должен быть положительным.\n");
        return;
    }
    int* temp = (int*)malloc(size * sizeof(int));
    if (!temp) {
        printf("Ошибка памяти.\n");
        return;
    }
    printf("Введите %d чисел через пробел: ", size);
    for (int i = 0; i < size; i++) scanf("%d", &temp[i]);
    freeArray();
    arr = temp;
    n = size;
    printf("Массив введён.\n");
}

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

void sortArray() {
    if (n == 0 || !arr) {
        printf("Массив пуст.\n");
        return;
    }
    int direction;
    printf("Выберите направление сортировки:\n");
    printf("1 - по возрастанию\n");
    printf("2 - по убыванию\n");
    printf("Ваш выбор: ");
    scanf("%d", &direction);
    int ascending = (direction == 1) ? 1 : 0; // по умолчанию убывание, если ввели не 1

    printf("Исходный массив:\n");
    printArray(arr, n);

    clock_t start = clock();
    bubbleSort(arr, n, &swapCount, ascending);
    clock_t end = clock();

    printf("Отсортированный массив (%s):\n", ascending ? "по возрастанию" : "по убыванию");
    printArray(arr, n);
    printf("Количество перестановок: %lld\n", swapCount);
    printf("Время выполнения: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void showMenu() {
    printf("\n=== МЕНЮ ===\n");
    printf("1. Ввести массив вручную\n");
    printf("2. Сгенерировать случайный массив\n");
    printf("3. Загрузить из input.txt\n");
    printf("4. Отсортировать массив\n");
    printf("5. Сохранить в output.txt\n");
    printf("6. Выход\n");
    printf("Выбор: ");
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