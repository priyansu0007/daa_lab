#include <stdio.h>

// Recursive function to simulate Towers of Hanoi and count moves
void hanoi(int n, char from_rod, char to_rod, char aux_rod, unsigned long long *moves) {
    if (n == 0) {
        return;
    }
    // Move n-1 disks from source to auxiliary
    hanoi(n - 1, from_rod, aux_rod, to_rod, moves);
    
    // Simulate moving the current nth disk (increment counter)
    (*moves)++;
    
    // Move the n-1 disks from auxiliary to target
    hanoi(n - 1, aux_rod, to_rod, from_rod, moves);
}

int main() {
    FILE *fp = fopen("toh_data.dat", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "# Discs(N) Total_Moves\n");
    
    int max_discs = 25;
    
    printf("Simulating Towers of Hanoi up to %d discs...\n", max_discs);

    for (int n = 1; n <= max_discs; n++) {
        unsigned long long moves = 0;
        
        // Simulating with rods 'A', 'C' (target), and 'B' (auxiliary)
        hanoi(n, 'A', 'C', 'B', &moves);
        
        fprintf(fp, "%d %llu\n", n, moves);
        printf("N = %2d  |  Moves = %llu\n", n, moves);
    }

    fclose(fp);
    printf("Simulation complete. Data saved to 'toh_data.dat'\n");

    return 0;
}