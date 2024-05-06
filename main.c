#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *a;             // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;      // highest power 10
    unsigned int size;   // size of allocated dynamic memory in a
} Decimal;

void elong_add(const Decimal *a, const Decimal *b, Decimal *res) {
    int carry = 0;
    int max_size = (a->size > b->size) ? a->size : b->size;

    res->size = max_size + 1; // +1 to accommodate possible carry in the highest position
    res->a = (char *)malloc(res->size * sizeof(char));

    int i = 0;
    while (i < max_size || carry) {
        int sum = carry;
        if (i < a->size) {
            sum += a->a[a->size - 1 - i] - '0'; // Read digits from the end of the string
        }
        if (i < b->size) {
            sum += b->a[b->size - 1 - i] - '0'; // Read digits from the end of the string
        }
        res->a[i] = (sum % 10) + '0';
        carry = sum / 10;
        i++;
    }

    res->n = i - 1; // highest power 10
}

int main() {
    Decimal a, b, res;

    printf("Enter Decimal a: ");
    char input_a[100];
    scanf("%s", input_a);
    a.size = strlen(input_a);
    a.a = strdup(input_a); // Allocate memory for a and copy input

    printf("Enter Decimal b: ");
    char input_b[100];
    scanf("%s", input_b);
    b.size = strlen(input_b);
    b.a = strdup(input_b); // Allocate memory for b and copy input

    elong_add(&a, &b, &res);

    printf("Result of adding a and b: ");
    for (int i = res.n; i >= 0; i--) {
        printf("%c", res.a[i]);
    }
    printf("\n");

    free(a.a); // Free dynamically allocated memory for a
    free(b.a); // Free dynamically allocated memory for b
    free(res.a); // Free dynamically allocated memory for result

    return 0;
}
