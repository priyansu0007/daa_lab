#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int type; // 1 for birth, -1 for death
} Event;

int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->year == e2->year) {
        return e1->type - e2->type; // -1 (death) comes before 1 (birth)
    }
    return e1->year - e2->year;
}

void find_best_year(int births[], int deaths[], int n) {
    Event events[2 * n];
    for (int i = 0; i < n; i++) {
        events[2 * i] = (Event){births[i], 1};
        events[2 * i + 1] = (Event){deaths[i], -1};
    }

    qsort(events, 2 * n, sizeof(Event), compare);

    int current_alive = 0, max_alive = 0, best_year = 0;
    for (int i = 0; i < 2 * n; i++) {
        current_alive += events[i].type;
        if (current_alive > max_alive) {
            max_alive = current_alive;
            best_year = events[i].year;
        }
    }
    printf("Best year to be alive: %d with %d scientists.\n", best_year, max_alive);
}

int main() {
    int births[] = {1879, 1642, 1831, 1564};
    int deaths[] = {1955, 1727, 1879, 1642};
    int n = sizeof(births) / sizeof(births[0]);
    find_best_year(births, deaths, n);
    return 0;
}