#include <stdio.h>

void print_shot_sequence(int n) {
    if (n <= 1) {
        printf("No valid sequence for n <= 1\n");
        return;
    }
    printf("Shoot sequence: ");
    for (int i = 2; i <= n - 1; i++) {
        printf("%d ", i);
    }
    for (int i = n - 1; i >= 2; i--) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int n = 5; // Number of hiding spots
    print_shot_sequence(n);
    return 0;
}