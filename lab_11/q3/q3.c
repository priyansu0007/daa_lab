#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_WORDS 100000
#define MAX_LEN 12

typedef struct {
    char word[MAX_LEN];
    int dist;
} QueueItem;

// Global to avoid Stack Overflow. Kept to maximum size but only populated as needed.
char dictionary[MAX_WORDS][MAX_LEN];
int dict_size = 0;

int compareStrings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int findWordIndex(char* word) {
    void* found = bsearch(word, dictionary, dict_size, MAX_LEN, compareStrings);
    if (found != NULL) {
        // Safe pointer arithmetic to find the index in the 2D array
        ptrdiff_t offset = (char*)found - (char*)dictionary;
        return (int)(offset / MAX_LEN);
    }
    return -1;
}

bool isValidWord(char* word) {
    return findWordIndex(word) != -1;
}

int bidirectionalBFS(char* start, char* end) {
    if (strcmp(start, end) == 0) return 0;
    if (!isValidWord(end)) return -1;

    // OPTIMIZATION: Allocate ONLY what is needed for the current test case.
    // The queue can never exceed the number of words in the dictionary + 1 (the start word).
    int max_q_size = dict_size + 2;

    QueueItem* qA = (QueueItem*)malloc(max_q_size * sizeof(QueueItem));
    QueueItem* qB = (QueueItem*)malloc(max_q_size * sizeof(QueueItem));
    int* visitedA = (int*)calloc(max_q_size, sizeof(int));
    int* visitedB = (int*)calloc(max_q_size, sizeof(int));

    if (!qA || !qB || !visitedA || !visitedB) {
        printf("System memory limit reached.\n");
        if(qA) free(qA); if(qB) free(qB);
        if(visitedA) free(visitedA); if(visitedB) free(visitedB);
        return -1;
    }

    int frontA = 0, rearA = 0, frontB = 0, rearB = 0;

    strcpy(qA[rearA].word, start);
    qA[rearA].dist = 0;
    rearA++;

    int startIdx = findWordIndex(start);
    if (startIdx != -1) visitedA[startIdx] = 1;

    strcpy(qB[rearB].word, end);
    qB[rearB].dist = 0;
    rearB++;

    int endIdx = findWordIndex(end);
    visitedB[endIdx] = 1;

    while (frontA < rearA && frontB < rearB) {

        // Expand Queue A (Forward direction)
        int levelSizeA = rearA - frontA;
        while (levelSizeA-- > 0) {
            QueueItem currA = qA[frontA++];
            int wordLen = strlen(currA.word);

            for (int i = 0; i < wordLen; i++) {
                char tempWord[MAX_LEN];
                strcpy(tempWord, currA.word);

                for (char c = 'a'; c <= 'z'; c++) {
                    if (tempWord[i] == c) continue;
                    tempWord[i] = c;

                    int idx = findWordIndex(tempWord);
                    if (idx != -1) {
                        if (visitedB[idx]) {
                            int total_dist = currA.dist + visitedB[idx];
                            free(qA); free(qB); free(visitedA); free(visitedB);
                            return total_dist;
                        }
                        if (!visitedA[idx]) {
                            visitedA[idx] = currA.dist + 2;
                            strcpy(qA[rearA].word, tempWord);
                            qA[rearA].dist = currA.dist + 1;
                            rearA++;
                        }
                    }
                }
            }
        }

        // Expand Queue B (Backward direction)
        int levelSizeB = rearB - frontB;
        while (levelSizeB-- > 0) {
            QueueItem currB = qB[frontB++];
            int wordLen = strlen(currB.word);

            for (int i = 0; i < wordLen; i++) {
                char tempWord[MAX_LEN];
                strcpy(tempWord, currB.word);

                for (char c = 'a'; c <= 'z'; c++) {
                    if (tempWord[i] == c) continue;
                    tempWord[i] = c;

                    int idx = findWordIndex(tempWord);
                    if (idx != -1) {
                        if (visitedA[idx]) {
                            int total_dist = currB.dist + visitedA[idx];
                            free(qA); free(qB); free(visitedA); free(visitedB);
                            return total_dist;
                        }
                        if (!visitedB[idx]) {
                            visitedB[idx] = currB.dist + 2;
                            strcpy(qB[rearB].word, tempWord);
                            qB[rearB].dist = currB.dist + 1;
                            rearB++;
                        }
                    }
                }
            }
        }
    }

    // Cleanup on failure to find path
    free(qA); free(qB); free(visitedA); free(visitedB);
    return -1;
}

int main() {
    const char* words[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    dict_size = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < dict_size; i++) {
        strcpy(dictionary[i], words[i]);
    }

    // Requirement for bsearch: The dictionary MUST be sorted alphabetically
    qsort(dictionary, dict_size, MAX_LEN, compareStrings);

    char startWord[MAX_LEN] = "hit";
    char targetWord[MAX_LEN] = "cog";

    int result = bidirectionalBFS(startWord, targetWord);

    printf("--- Bidirectional BFS Word Transformation ---\n");
    if (result != -1) {
        printf("Minimum mutations from '%s' to '%s': %d\n", startWord, targetWord, result);
    } else {
        printf("No valid transformation sequence found.\n");
    }

    return 0;
}
