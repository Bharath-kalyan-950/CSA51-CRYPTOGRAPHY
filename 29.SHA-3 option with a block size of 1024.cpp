#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#define MATRIX_SIZE 5
#define LANE_BITS 64
bool allCapacityLanesNonzero(uint64_t state[MATRIX_SIZE][MATRIX_SIZE], int capacityLanes[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (capacityLanes[i][j] == 1 && state[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}
int main() {
    uint64_t state[MATRIX_SIZE][MATRIX_SIZE] = {0};  
    int capacityLanes[MATRIX_SIZE][MATRIX_SIZE] = {0}; 
    state[0][0] = 1;  
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            capacityLanes[i][j] = 1;  
        }
    }
    int steps = 0;
    while (!allCapacityLanesNonzero(state, capacityLanes)) {
        steps++;
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                if (i > 0 && state[i-1][j] != 0) {
                    state[i][j] = 1;
                }
                if (i < MATRIX_SIZE - 1 && state[i+1][j] != 0) {
                    state[i][j] = 1;
                }
                if (j > 0 && state[i][j-1] != 0) {
                    state[i][j] = 1;
                }
                if (j < MATRIX_SIZE - 1 && state[i][j+1] != 0) {
                    state[i][j] = 1;
                }
            }
        }
    }
    printf("All capacity lanes are nonzero after %d steps.\n", steps);
    return 0;
}
