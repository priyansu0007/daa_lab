#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int rows;
    int cols;
    int total_cells;
    int num_islands;
    int *parent;
    int *rank;
} GridDSU;

// Initialize the grid DSU where all cells are water (-1)
GridDSU* grid_dsu_create(int rows, int cols) {
    GridDSU *grid = (GridDSU*)malloc(sizeof(GridDSU));
    grid->rows = rows;
    grid->cols = cols;
    grid->total_cells = rows * cols;
    grid->num_islands = 0;

    grid->parent = (int*)malloc(grid->total_cells * sizeof(int));
    grid->rank = (int*)calloc(grid->total_cells, sizeof(int));

    for (int i = 0; i < grid->total_cells; i++) {
        grid->parent[i] = -1; // -1 denotes water
    }

    return grid;
}

void grid_dsu_free(GridDSU *grid) {
    if (grid) {
        free(grid->parent);
        free(grid->rank);
        free(grid);
    }
}

// 2D to 1D index mapping
static inline int get_index(GridDSU *grid, int r, int c) {
    return r * grid->cols + c;
}

// Find with path compression
int dsu_find(GridDSU *grid, int i) {
    if (grid->parent[i] == i) {
        return i;
    }
    grid->parent[i] = dsu_find(grid, grid->parent[i]);
    return grid->parent[i];
}

// Union by rank; returns true if a merge occurred, false if already connected
bool dsu_union(GridDSU *grid, int i, int j) {
    int root_i = dsu_find(grid, i);
    int root_j = dsu_find(grid, j);

    if (root_i == root_j) {
        return false;
    }

    if (grid->rank[root_i] < grid->rank[root_j]) {
        grid->parent[root_i] = root_j;
    } else if (grid->rank[root_i] > grid->rank[root_j]) {
        grid->parent[root_j] = root_i;
    } else {
        grid->parent[root_j] = root_i;
        grid->rank[root_i]++;
    }

    return true;
}

// Process arrival of a land cell at (r, c)
int add_land(GridDSU *grid, int r, int c) {
    if (r < 0 || r >= grid->rows || c < 0 || c >= grid->cols) {
        return grid->num_islands;
    }

    int idx = get_index(grid, r, c);

    // If cell is already land, component count does not change
    if (grid->parent[idx] != -1) {
        return grid->num_islands;
    }

    // Initialize as a new independent island
    grid->parent[idx] = idx;
    grid->num_islands++;

    // Cardinal directions: Up, Down, Left, Right
    static const int dr[] = {-1, 1, 0, 0};
    static const int dc[] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k];
        int nc = c + dc[k];

        if (nr >= 0 && nr < grid->rows && nc >= 0 && nc < grid->cols) {
            int n_idx = get_index(grid, nr, nc);
            // Connect only to adjacent land cells
            if (grid->parent[n_idx] != -1) {
                if (dsu_union(grid, idx, n_idx)) {
                    grid->num_islands--;
                }
            }
        }
    }

    return grid->num_islands;
}

int main(void) {
    int R = 3, C = 3;
    GridDSU *grid = grid_dsu_create(R, C);

    // Stream of incoming land cells: (r, c)
    int stream[][2] = {
        {0, 0}, // New island -> 1
        {0, 1}, // Merges with (0,0) -> 1
        {1, 2}, // New island -> 2
        {2, 1}, // New island -> 3
        {0, 1}, // Duplicate entry -> 3
        {1, 1}, // Bridges (0,1), (1,2), and (2,1) -> 1
        {2, 2}  // Merges into main island -> 1
    };

    int num_operations = sizeof(stream) / sizeof(stream[0]);

    printf("Dynamic Connected Components on %dx%d Grid:\n", R, C);
    printf("-------------------------------------------------\n");

    for (int i = 0; i < num_operations; i++) {
        int r = stream[i][0];
        int c = stream[i][1];
        int islands = add_land(grid, r, c);
        printf("Operation %d: Added (%d, %d) -> Active Islands: %d\n", 
               i + 1, r, c, islands);
    }

    grid_dsu_free(grid);
    return 0;
}