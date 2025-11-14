#include <stdio.h>
#include <stdlib.h>
unsigned long long a(unsigned int m, unsigned int n) {
    if (m == 0) {return n + 1;} 
    else if (m > 0 && n == 0) {return a(m - 1, 1);}
    else {return a(m - 1, a(m, n - 1));}}
int ok_input(const char *msg, unsigned int *value) {
    int compare;
    printf("%s", msg);
    compare = scanf("%u", value);
    if (compare != 1) {
        while (getchar() != '\n');
        return 0;}
    return 1; }
int main() {
    unsigned int m, n;
    printf("calculating Accerman number (m,n)\n");
    while (!ok_input("Enter a natural number m: ", &m)) {
        printf("Enter a NATURAL number.\n");}
    while (!ok_input("Enter a natural number n: ", &n)) {
        printf("Enter a NATURAL number\n");}
    if (m > 3) {
        printf("Warn: m > 3 may cause err in calculating.\n");
        printf("Continue? (y/n): ");
        char c;
        scanf(" %c", &c);
        if (c != 'y' && c != 'Y') {
            printf("Denied calculating.\n");
            return 0;}}
    unsigned long long result = a(m, n);
    printf("Result: A(%u, %u) = %llu\n", m, n, result);
    return 0;}
