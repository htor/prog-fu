#include <stdio.h>

/* bubble sort */

int *arr_sort(int *arr, int len)
{
    int swap;
    while (len) {
        for (int i1 = 0, i2 = 1; i2 < len; i1++, i2++)
        {
            if (arr[i1] > arr[i2]) 
            {
                swap = arr[i1];
                arr[i1] = arr[i2];
                arr[i2] = swap;
            }

        }
        len--;
    }
    return 0;
}

void arr_print(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int arr[] = { 5, 3, 7, 'C', 9, 2, 'a', 1 };
    arr_sort(arr, sizeof(arr) / sizeof(*arr));
    arr_print(arr, sizeof(arr) / sizeof(*arr));
    return 0;
}
