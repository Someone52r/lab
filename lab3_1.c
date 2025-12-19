/* Вариант 25.
1. Найти минимальный эл-т А среди эл-тов лежащих на главной диагонали
2. Найти произведение А и мин. эл-тов каждого столбца матрицы
3. Заменить а[2][4] на полученное значение.
*/ 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("input file_name: ./matrix input.txt\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("error: file not opened\n");
        return 2;
    }
    // define matrix size
    int N = 0, M = 0;
    char buffer[1024], *ptr, *end;
    int temp;
    while (fgets(buffer, sizeof(buffer), file)) {
        ptr = buffer;
        int count = 0;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (*ptr == '\n' || *ptr == '\0') continue;
        while (1) {
            temp = (int)strtol(ptr, &end, 10);
            if (end == ptr) break;
            count++;
            ptr = end;
        }
        if (N == 0) M = count;
        else if (count != M) {
            printf("error: rows of matrix have different sizes\n");
            fclose(file);
            return 3;
        }
        N++;
    }
    if (N == 0 || M == 0) {
        printf("error: matrix is empty\n");
        fclose(file);
        return 4;
    }
    printf("matrix size: %d x %d\n", N, M);
    rewind(file);
    // mem crea
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
    // min on diag
    int min_diag = matrix[0][0];
    int min_length = (N < M) ? N : M;
    for (int i = 1; i < min_length; i++) {
        if (matrix[i][i] < min_diag) {
            min_diag = matrix[i][i];
        }
    }
    // min on colums
    int *min_col = (int *)malloc(M * sizeof(int));
    for (int j = 0; j < M; j++) {
        min_col[j] = matrix[0][j];
        for (int i = 1; i < N; i++) {
            if (matrix[i][j] < min_col[j]) {
                min_col[j] = matrix[i][j];
            }
        }
    }
    // mult
    long long mult = min_diag;
    for (int j = 0; j < M; j++) {
        mult *= min_col[j];
    }
    // 2;4 elem
    if (1 < N && 3 < M) {
        matrix[1][3] = (int)mult;
        printf("matrix[2][4] changed to %lld\n", mult);
    } else {
        printf("matrix[2][4] not exist\n");
    }
    // output
    printf("min on diag: %d\n", min_diag);
    printf("mult: %lld\n", mult);
    printf("changed matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    // mem free
    for (int i = 0; i < N; i++) free(matrix[i]);
    free(matrix);
    free(min_col);
    return 0;
}