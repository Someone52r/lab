#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void bubble_sort(int *arr, int n);
void selection_sort(int *arr, int n);
void quick_sort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}
void copy_array(int *src, int *dst, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}
int main() {
    int sizes[] = {10, 1000, 10000, 100000};
    int num_sizes = 4;
    printf("+------------+------------------+------------------+------------------+\n");
    printf("| size  N    | bubble (sec)     | selection (sec)  | quicksort (sec)  |\n");
    printf("+------------+------------------+------------------+------------------+\n");
    srand(time(NULL));
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        // mem crea
        int *arr = (int *)malloc(n * sizeof(int));
        int *arr_b = (int *)malloc(n * sizeof(int));
        int *arr_s = (int *)malloc(n * sizeof(int));
        int *arr_q = (int *)malloc(n * sizeof(int));
        if (!arr || !arr_b || !arr_s || !arr_q) {
            printf("Error: mem_crea\n");
            return 1;
        }
        fill_random(arr, n);
        copy_array(arr, arr_b, n);
        copy_array(arr, arr_s, n);
        copy_array(arr, arr_q, n);
        double time_bubble = 0.0, time_selection = 0.0, time_quick = 0.0;
        clock_t start = clock();
        bubble_sort(arr_b, n);
        clock_t end = clock();
        time_bubble = (double)(end - start) / CLOCKS_PER_SEC;
        start = clock();
        selection_sort(arr_s, n);
        end = clock();
        time_selection = (double)(end - start) / CLOCKS_PER_SEC;
        start = clock();
        quick_sort(arr_q, 0, n - 1);
        end = clock();
        time_quick = (double)(end - start) / CLOCKS_PER_SEC;
        printf("| %-10d | %-16f | %-16f | %-16f |\n", n, time_bubble, time_selection, time_quick);
        // mem free
        free(arr);
        free(arr_b);
        free(arr_s);
        free(arr_q);
    }
    printf("+------------+------------------+------------------+------------------+\n");
    return 0;
}
void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void selection_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}