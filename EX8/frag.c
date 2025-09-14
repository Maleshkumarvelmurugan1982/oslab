#include <stdio.h>

// ---------- FIFO ----------
void fifo(int rs[], int n, int f) {
    int i, j, k, m[10], pf = 0, count = 0;
    for (i = 0; i < f; i++) m[i] = -1; // init frames empty

    printf("\nFIFO Page Replacement:\n");
    for (i = 0; i < n; i++) {
        // check if page already in frame
        for (k = 0; k < f; k++) if (m[k] == rs[i]) break;

        if (k == f) { // page fault
            m[count++] = rs[i]; // replace oldest
            pf++;
        }
        for (j = 0; j < f; j++) printf("%d\t", m[j]);
        if (k == f) printf("PF No. %d", pf);
        printf("\n");

        if (count == f) count = 0; // cycle for FIFO
    }
    printf("Total Page Faults (FIFO): %d\n", pf);
}

// ---------- LRU ---------- 
void lru(int rs[], int n, int f) {
    int i, j, k, min, m[10], count[10], flag, pf = 0, next = 0;
    for (i = 0; i < f; i++) { m[i] = -1; count[i] = 0; }

    printf("\nLRU Page Replacement:\n");
    for (i = 0; i < n; i++) {
        flag = 0;
        // check if page present
        for (j = 0; j < f; j++) {
            if (m[j] == rs[i]) {
                flag = 1; // hit
                count[j] = next++;
            }
        }
        if (flag == 0) { // page fault
            if (i < f) { // fill empty frames first
                m[i] = rs[i];
                count[i] = next++;
            } else {
                // find least recently used
                min = 0;
                for (j = 1; j < f; j++)
                    if (count[j] < count[min]) min = j;
                m[min] = rs[i];
                count[min] = next++;
            }
            pf++;
        }
        for (j = 0; j < f; j++) printf("%d\t", m[j]);
        if (flag == 0) printf("PF No. %d", pf);
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", pf);
}

// ---------- OPTIMAL ----------
void optimal(int rs[], int n, int f) {
    int i, j, k, m[10], pf = 0, flag, pos, farthest, index;
    for (i = 0; i < f; i++) m[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (i = 0; i < n; i++) {
        flag = 0;
        // check if page present
        for (j = 0; j < f; j++) if (m[j] == rs[i]) { flag = 1; break; }

        if (flag == 0) { // page fault
            if (i < f) {
                m[i] = rs[i]; // fill empty
            } else {
                // predict future use
                farthest = i + 1; pos = -1;
                for (j = 0; j < f; j++) {
                    index = -1;
                    for (k = i + 1; k < n; k++)
                        if (m[j] == rs[k]) { index = k; break; }
                    if (index == -1) { pos = j; break; } // never used again
                    if (index > farthest) { farthest = index; pos = j; }
                }
                if (pos == -1) pos = 0;
                m[pos] = rs[i];
            }
            pf++;
        }
        for (j = 0; j < f; j++) printf("%d\t", m[j ]);
        if (flag == 0) printf("PF No. %d", pf);
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", pf);
}

// ---------- MAIN ----------
int main() {
    int n, f, i, rs[25], choice;
    printf("Enter length of reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) scanf("%d", &rs[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\nChoose Algorithm:\n1. FIFO\n2. LRU\n3. Optimal\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1: fifo(rs, n, f); break;
        case 2: lru(rs, n, f); break;
        case 3: optimal(rs, n, f); break;
        default: printf("Invalid choice!\n");
    }
    return 0;
}
