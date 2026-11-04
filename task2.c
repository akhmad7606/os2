#include <stdio.h>
#include <stdlib.h>

/* strlen o'rniga: pointer yordamida uzunlikni hisoblash */
static size_t str_len(const char *s) {
    const char *e = s;
    while (*e != '\0') {
        e++;
    }
    return (size_t)(e - s);
}

/* fgets + realloc: istalgan uzunlikdagi satrni dinamik xotiraga o'qiydi */
static char *read_line(void) {
    size_t cap = 16;
    size_t len = 0;

    char *buf = (char *)malloc(cap);
    if (buf == NULL) {
        return NULL;
    }
    *buf = '\0';

    while (fgets(buf + len, (int)(cap - len), stdin) != NULL) {
        len += str_len(buf + len);

        /* satr oxiridagi '\n' ni olib tashlash va tugatish */
        if (len > 0 && *(buf + len - 1) == '\n') {
            *(buf + len - 1) = '\0';
            len--;
            break;
        }

        /* bufer to'lgan bo'lsa, kengaytiramiz */
        if (len + 1 == cap) {
            size_t new_cap = cap * 2;
            char *tmp = (char *)realloc(buf, new_cap);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
            cap = new_cap;
        }
    }
    return buf;
}

/* Satrni joyida teskari qilish: faqat pointerlar, string.h siz */
static void reverse_string(char *s) {
    char *left = s;
    char *right = s;

    while (*right != '\0') {
        right++;
    }
    if (right == s) {
        return; /* bo'sh satr */
    }
    right--; /* oxirgi belgiga */

    while (left < right) {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}

int main(void) {
    printf("Satrni kiriting: ");

    char *str = read_line();
    if (str == NULL) {
        fprintf(stderr, "Xatolik: xotira ajratib bo'lmadi\n");
        return 1;
    }

    printf("Asl satr:        %s\n", str);
    reverse_string(str);
    printf("Teskari satr:    %s\n", str);

    free(str);
    str = NULL;
    return 0;
}
