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

int main(void) {
   SetConsoleOutputCP(65001);
   srand(time(NULL));

   int size = 10;
   int arr[] = {10, 8, 9, 5, 6, 7, 4, 3, 2, 1};

   bubbleSort(arr, size, 0);
   printArr(arr, size);
   
   bubbleSort(arr, size, 1);
   printArr(arr, size);
}