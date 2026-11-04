#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n = 10;

    int *p = (int *)malloc(n * sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "Xatolik: xotira ajratib bo'lmadi\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    /* [-50; 50] oraliqdagi tasodifiy sonlar bilan to'ldirish */
    for (int i = 0; i < n; i++) {
        *(p + i) = rand() % 101 - 50;
    }

    printf("Massiv: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(p + i));
    }
    printf("\n");

    /* Juft indeksdagi elementlar yig'indisi: 0, 2, 4, 6, 8 */
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        sum += *(p + i);
    }
    printf("Juft indeksdagi elementlar yig'indisi: %d\n", sum);

    free(p);
    p = NULL;
    return 0;
}
