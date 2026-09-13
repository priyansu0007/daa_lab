#include <stdio.h>

void turnOn(int n);
void turnOff(int n);

void turnOff(int n) {
    if (n <= 0) return;
    if (n == 1) { 
        printf("Toggle 1\n"); 
        return; 
    }
    if (n == 2) { 
        printf("Toggle 2\nToggle 1\n"); 
        return; 
    }
    turnOff(n - 2);
    printf("Toggle %d\n", n);
    turnOn(n - 2);
    turnOff(n - 1);
}

void turnOn(int n) {
    if (n <= 0) return;
    if (n == 1) { 
        printf("Toggle 1\n"); 
        return; 
    }
    if (n == 2) { 
        printf("Toggle 1\nToggle 2\n"); 
        return; 
    }
    turnOn(n - 1);
    turnOff(n - 2);
    printf("Toggle %d\n", n);
    turnOn(n - 2);
}

int main() {
    int n = 4; // Number of switches
    printf("Sequence to turn off %d switches:\n", n);
    turnOff(n);
    return 0;
}