#include <stdio.h>

#define TABLE_SIZE 11
#define N 8

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void displayTable(int table[]) {
    int i;
    printf("Index : ");
    for (i = 0; i < TABLE_SIZE; i++)
        printf("%4d", i);
    printf("\nValue : ");
    for (i = 0; i < TABLE_SIZE; i++) {
        if (table[i] == -1)
            printf("%4s", "-");
        else
            printf("%4d", table[i]);
    }
    printf("\n");
}

/* Hashing search using the same linear-probing collision resolution
   used during insertion. Each examined slot counts as one operation. */
int hashSearch(int table[], int key, int *operations) {
    int start = hashFunction(key);
    int index = start;
    *operations = 0;

    do {
        (*operations)++;

        if (table[index] == -1)
            return -1;

        if (table[index] == key)
            return index;

        index = (index + 1) % TABLE_SIZE;
    } while (index != start);

    return -1;
}

/* Linear search. Each element comparison counts as one comparison. */
int linearSearch(int arr[], int n, int key, int *comparisons) {
    int i;
    *comparisons = 0;

    for (i = 0; i < n; i++) {
        (*comparisons)++;
        if (arr[i] == key)
            return i;
    }

    return -1;
}

int main(void) {
    int songIDs[N] = {105, 210, 315, 420, 525, 630, 735, 840};
    int searchIDs[] = {105, 420, 735, 840, 999};
    int searchCount = sizeof(searchIDs) / sizeof(searchIDs[0]);
    int table[TABLE_SIZE];
    int i, key, hashIndex, index, collisions;
    int hashOps, linearComps;

    for (i = 0; i < TABLE_SIZE; i++)
        table[i] = -1;

    printf("MUSIC APPLICATION - HASHING ASSIGNMENT\n");
    printf("Hash function: h(k) = k %% %d\n", TABLE_SIZE);
    printf("Collision resolution: Linear Probing\n\n");

    printf("INSERTION TRACE\n");
    for (i = 0; i < N; i++) {
        key = songIDs[i];
        hashIndex = hashFunction(key);
        index = hashIndex;
        collisions = 0;

        while (table[index] != -1) {
            collisions++;
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = key;

        printf("Insert %d: hash=%d, final_slot=%d, collisions=%d\n",
               key, hashIndex, index, collisions);
        displayTable(table);
        printf("\n");
    }

    printf("FINAL HASH TABLE\n");
    displayTable(table);

    printf("\nSEARCH COMPARISON\n");
    printf("%-10s %-15s %-15s %-15s\n",
           "ID", "Hash Result", "Hash Ops", "Linear Comparisons");

    for (i = 0; i < searchCount; i++) {
        int hpos = hashSearch(table, searchIDs[i], &hashOps);
        int lpos = linearSearch(songIDs, N, searchIDs[i], &linearComps);

        printf("%-10d %-15s %-15d %-15d\n",
               searchIDs[i],
               hpos == -1 ? "Not Found" : "Found",
               hashOps,
               linearComps);
    }

    return 0;
}
