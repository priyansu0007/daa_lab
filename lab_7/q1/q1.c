#include <stdio.h>

int min_moves_to_invert(int n) {
    return (n * (n + 1)) / 6;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    printf("Minimum moves for a triangle of base %d is: %d\n", n, min_moves_to_invert(n));
    return 0;
}