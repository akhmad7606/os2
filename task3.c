#include <stdio.h>
#include <stdlib.h>

/* rows x cols o'lchamli int** matritsa yaratish (xato bo'lsa NULL) */
static int **create_matrix(int rows, int cols) {
    int **m = (int **)malloc(rows * sizeof(int *));
    if (m == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        m[i] = (int *)malloc(cols * sizeof(int));
        if (m[i] == NULL) {
            /* oldin ajratilgan satrlarni qaytarib, chiqamiz */
            for (int j = 0; j < i; j++) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }
    return m;
}

/* Avval har bir satr, so'ng satrlar massivi */
static void free_matrix(int **m, int rows) {
    if (m == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
}

static void print_matrix(int **m, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    const int ROWS = 3;
    const int COLS = 4;

    int **a = create_matrix(ROWS, COLS);
    if (a == NULL) {
        fprintf(stderr, "Xatolik: xotira ajratib bo'lmadi\n");
        return 1;
    }

    /* To'ldirish: 1, 2, 3, ... */
    int k = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            a[i][j] = k++;
        }
    }

    printf("Asl matritsa (%dx%d):\n", ROWS, COLS);
    print_matrix(a, ROWS, COLS);

    /* Transponirlash: natija COLS x ROWS (4x3) */
    int **t = create_matrix(COLS, ROWS);
    if (t == NULL) {
        fprintf(stderr, "Xatolik: xotira ajratib bo'lmadi\n");
        free_matrix(a, ROWS);
        return 1;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            t[j][i] = a[i][j];
        }
    }

    printf("\nTransponirlangan matritsa (%dx%d):\n", COLS, ROWS);
    print_matrix(t, COLS, ROWS);

    free_matrix(a, ROWS);
    free_matrix(t, COLS);
    return 0;
}
