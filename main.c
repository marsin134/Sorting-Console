#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Сортировка пузырьком
void bubbleSort(int *arr, int size, int reverse)
{
   clock_t start = clock();
   int tmp;
   int numberOfPermutations;
   int numberOfExchanges;

   numberOfPermutations = 0;
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
      numberOfPermutations += numberOfExchanges;
   } while (numberOfExchanges > 0); // Если обменов не было, то массив отсортирован

   clock_t end = clock();
   double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
   printf("\nВремя сортировки: %.6f секунд\n", time_spent);
   printf("Количество перестановок: %d\n", numberOfPermutations);
}

// Чтение массива из файла
int *readFile(char *filename, int *size)
{
   FILE *file;
   int *arr = NULL;
   int number;
   char ch;
   int isValid = 1;

   file = fopen(filename, "r");
   if (file == NULL)
   {
      printf("Ошибка: файл '%s' не найден!\n", filename);
      return NULL;
   }

   // Проверяем, что файл содержит только числа и разделители
   while (fscanf(file, "%c", &ch) == 1)
   {
      // Разрешенные символы: цифры, пробелы, табуляция, перевод строки
      if (!isdigit(ch) && !isspace(ch))
      {
         printf("Ошибка: файл '%s' содержит недопустимый символ '%c'!\n", filename, ch);
         isValid = 0;
         break;
      }
   }

   if (!isValid)
   {
      fclose(file);
      return NULL;
   }

   rewind(file);

   // Подсчет количества чисел
   *size = 0;
   while (fscanf(file, "%d", &number) == 1)
   {
      (*size)++;
   }

   if (*size == 0)
   {
      printf("Ошибка: файл '%s' пуст или не содержит чисел!\n", filename);
      fclose(file);
      return NULL;
   }

   rewind(file);

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

// Генерация массива случайных чисел
int *generateRandomNumber(int size)
{
   if (size <= 0)
   {
      printf("Ошибка: размер должен быть > 0!\n");
      return NULL;
   }

   int *arr = (int *)malloc(size * sizeof(int));
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
   printf("Массив записан в файл %s\n", filename);
   return 0;
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

// Вывод меню
void printMenu()
{
   printf("\n╔═══════════════════════════════════════╗\n");
   printf("║       МЕНЮ СОРТИРОВКИ МАССИВА         ║\n");
   printf("╠═══════════════════════════════════════╣\n");
   printf("║  1. Сортировать массив из файла       ║\n");
   printf("║  2. Сгенерировать случайный массив    ║\n");
   printf("║  3. Сменить входной файл              ║\n");
   printf("║  4. Сменить выходной файл             ║\n");
   printf("║  5. Поменять сортировку               ║\n");
   printf("║  6. Показать текущие настройки        ║\n");
   printf("║  7. Выполнить тесты                   ║\n");
   printf("║  0. Выход                             ║\n");
   printf("╚═══════════════════════════════════════╝\n");
   printf("Ваш выбор: ");
}

// Очистка экрана
void clearScreen()
{
   system("cls");
}

// Ожидание нажатия Enter и очистка
void endMessage()
{
   printf("\nНажмите Enter для продолжения...");
   getchar();
   getchar();
   clearScreen();
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

      int *inputArr = readFile(inputPath, &size);
      int *outputArr = readFile(outputPath, &size);

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
            } else {
               printf("Test №%d: Неверный ответ\n", i);
               printf("Программа вернула: ");
               printArr(inputArr, size);
               printf("\nДолжно быть: ");
               printArr(outputArr, size);
               printf("\n\n");
               failed++;
            }

      } else {
         printf("Test №%d SKIP (файл не найден)\n", i);
      }
      free(inputArr);
      free(outputArr);

      flagReverse = (flagReverse + 1) % 2;
   }

   printf("\nВерно: %d\n", passed);
   printf("Не верно %d\n", failed);
}

int main(void)
{
   SetConsoleOutputCP(65001);
   srand(time(NULL));

   char inputFile[256] = "input.txt";
   char outputFile[256] = "output.txt";
   int *arr = NULL; // указатель на динамический массив
   int size = 0;    // текущий размер массива
   int choice;
   int running = 1;
   int reverse = 0;

   while (running)
   {
      printMenu();
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
      { // Сортировка из файла
         clearScreen();
         printf("═══════════ СОРТИРОВКА ИЗ ФАЙЛА ═══════════\n");

         // Освобождаем предыдущий массив перед загрузкой нового
         if (arr != NULL)
         {
            free(arr);
            arr = NULL;
         }

         arr = readFile(inputFile, &size);

         if (arr != NULL)
         {
            printf("\nИсходный массив (%d элементов):\n", size);
            printArr(arr, size);

            bubbleSort(arr, size, reverse);

            printf("\nОтсортированный массив:\n");
            printArr(arr, size);
            printf("\n");

            if (writeArr(outputFile, arr, size) == 0)
            {
               printf("Результат сохранен в '%s'\n", outputFile);
            }
         }
         else
         {
            printf("\nНе удалось прочитать файл '%s'\n", inputFile);
         }

         endMessage();
         break;
      }

      case 2:
      { // Генерация и сортировка случайного массива
         clearScreen();
         printf("═══════════ ГЕНЕРАЦИЯ МАССИВА ═══════════\n\n");

         if (arr != NULL)
         {
            free(arr);
            arr = NULL;
         }

         printf("Введите размер массива: ");
         scanf("%d", &size);

         if (size <= 0)
         {
            printf("Размер должен быть больше 0!\n");
         }
         else
         {
            arr = generateRandomNumber(size);

            if (arr != NULL)
            {
               printf("\nСгенерированный массив (%d элементов):\n", size);
               printArr(arr, size);

               bubbleSort(arr, size, reverse);

               printf("\nОтсортированный массив:\n");
               printArr(arr, size);
               printf("\n");

               if (writeArr(outputFile, arr, size) == 0)
               {
                  printf("Результат сохранен в '%s'\n", outputFile);
               }
            }
            else
            {
               printf("Ошибка!");
            }
         }

         endMessage();
         break;
      }

      case 3:
      { // Смена входного файла
         clearScreen();
         printf("═══════════ СМЕНА ВХОДНОГО ФАЙЛА ═══════════\n\n");
         printf("Текущий входной файл: %s\n", inputFile);
         printf("Введите новое имя файла: ");
         scanf("%s", inputFile);
         printf("Входной файл изменен на: %s\n", inputFile);

         endMessage();
         break;
      }

      case 4:
      { // Смена выходного файла
         clearScreen();
         printf("═══════════ СМЕНА ВЫХОДНОГО ФАЙЛА ═══════════\n\n");
         printf("Текущий выходной файл: %s\n", outputFile);
         printf("Введите новое имя файла: ");
         scanf("%s", outputFile);
         printf("Выходной файл изменен на: %s\n", outputFile);

         endMessage();
         break;
      }

      case 5:
      { // Смена сортировки по возрастанию или убыванию 
         clearScreen();
         printf("═══════════ СМЕНА СОРТИРОВКИ ═══════════\n\n");
         printf("Текущая сортировка по %s\n", reverse ? "возрастанию": "убыванию");
         printf("0 - сортировка по возрастанию, 1 - по убыванию\n");
         printf("Введите число соответствующее сортировке (0 или 1): ");
         scanf("%d", &reverse);
         printf("\nСортировка изменена по: %s\n", reverse ? "возрастанию": "убыванию");

         endMessage();
         break;
      }

      case 6:
      { // Отображение текущих настроек
         clearScreen();
         printf("═══════════ ТЕКУЩИЕ НАСТРОЙКИ ═══════════\n\n");
         printf("Входной файл:  %s\n", inputFile);
         printf("Выходной файл: %s\n", outputFile);
         printf("Текущая сортировка %s\n", reverse ? "по убыванию": "по возрастанию");

         if (arr != NULL && size > 0)
         {
            printf("Содержимое массива: ");
            printArr(arr, size);
         }

         endMessage();
         break;
      }

      case 7:
      {
         clearScreen();
         tests(10);
         endMessage();
         break;
      }

      case 0:
      { // Выход из программы
         clearScreen();
         running = 0;
         break;
      }

      default:
      {
         printf("Неверный выбор! Попробуйте снова.\n");
         endMessage();
         break;
      }
      }
   }

   // Освобождение памяти перед завершением
   if (arr != NULL)
   {
      free(arr);
   }

   return 0;
}