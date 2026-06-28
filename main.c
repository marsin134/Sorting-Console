#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Сортировка пузырьком
void bubbleSort(int *arr, int size, int reverse)
{
   clock_t start = clock();
   int tmp;
   unsigned numberOfExchanges;

   do
   {
      numberOfExchanges = 0;
      for (int i = 0; i < size - 1; i++)
      {
         if (!reverse && arr[i] > arr[i + 1])
         {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
            numberOfExchanges++;
         } else if (reverse && arr[i] < arr[i + 1]) {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
            numberOfExchanges++;
         }
      }
      size--;
   } while (numberOfExchanges > 0); // Если обменов не было, то массив отсортирован

   clock_t end = clock();
   double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
   printf("\nВремя сортировки: %.6f секунд\n", time_spent);
}

 // Чтение массива из файла
int *readFile(char *filename, int *size)
{
   FILE *file;
   int *arr = NULL;
   int number;

   file = fopen(filename, "r");
   if (file == NULL)
   {
      printf("Ошибка: файл '%s' не найден!\n", filename);
      return NULL;
   }

   // Подсчет количества чисел
   *size = 0;
   while (fscanf(file, "%d", &number) == 1)
   {
      (*size)++;
   }

   rewind(file); // Возвращаем указатель в начало файла

   // Выделяем память под массив
   arr = (int *)malloc(*size * sizeof(int));
   if (arr == NULL)
   {
      printf("Ошибка памяти!\n");
      fclose(file);
      return NULL;
   }

   // Чтение чисел в массив
   for (int i = 0; i < *size; i++)
   {
      fscanf(file, "%d", &arr[i]);
   }

   fclose(file);
   return arr;
}

// Вывод массива в консоль
void printArr(int *arr, int size)
{
   for (int i = 0; i < size; i++)
   {
      printf("%d", arr[i]);
      if (i < size - 1)
      {
         printf(", ");
      };
   }
}
// Запись массива в файл
int writeArr(char *filename, int *arr, int size)
{
   if (arr == NULL || size <= 0)
   {
      printf("Ошибка: массив пуст!\n");
      return 1;
   }

   FILE *file;

   file = fopen(filename, "w");
   if (file == NULL)
   {
      printf("Ошибка: не удалось создать файл!\n");
      return 1;
   }

   for (int i = 0; i < size; i++)
   {
      fprintf(file, "%d ", arr[i]);
   }

   fprintf(file, "\n");

   fclose(file);
   printf("\nМассив записан в файл %s\n", filename);
   return 0;
}


// Генерация массива случайных чисел
int* generateRandomNumber(int size)
{
    if (size == NULL)
    {
        printf("Ошибка: передан NULL указатель!\n");
        return NULL;
    }
    if (size <= 0)
    {
        printf("Ошибка: размер должен быть > 0!\n");
        return NULL;
    }
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Ошибка памяти!\n");
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
    return arr;
}

int tests(int count) {
    char inputPath[256];
    char outputPath[256];
    int passed = 0;
    int failed = 0;
    int flagReverse = 0;

    for (int i = 1; i <= count; i++) {
        int size = 0;

        sprintf(inputPath, "tests/input%d.txt", i);
        sprintf(outputPath, "tests/output%d.txt", i);

        int* inputArr = readFile(inputPath, &size);
        int* outputArr = readFile(outputPath, &size);

        if (inputArr != NULL && outputArr != NULL) {
            bubbleSort(inputArr, size, flagReverse);
            // Сравниваем массивы, а не указатели
            int equal = 1;
            for (int j = 0; j < size; j++) {
                if (inputArr[j] != outputArr[j]) {
                    equal = 0;
                    break;
                }
            }
            if (equal) {
                printf("Test №%d: Ок\n", i);
                passed++;
            }
            else {
                printf("Test №%d: Неверный ответ\n", i);
                printf("Программа вернула: ");
                printArr(inputArr, size);
                printf("\nДолжно быть: ");
                printArr(outputArr, size);
                printf("\n\n");
                failed++;
            }
        }
        else {
            printf("Test №%d SKIP (файл не найден)\n", i);
        }
        free(inputArr);
        free(outputArr);

        flagReverse = (flagReverse + 1) % 2;
    }
    printf("\nВерно: %d\n", passed);
    printf("Не верно %d\n", failed);
}


int main(void) {
    SetConsoleOutputCP(65001);
    srand(time(NULL));

    tests(10);
}