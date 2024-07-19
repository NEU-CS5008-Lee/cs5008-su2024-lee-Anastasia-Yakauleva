// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu

#include <stdio.h>
#include <stdlib.h>        // for qsort
#define VSIZE 9
#define INF 99999

typedef struct Fedge {        // F: edge set
    int key;        // weight
    int u;
    int v;
} Fedge;

// Utility function to compare
int compare(const void *a, const void *b) {
    Fedge *m = (Fedge *)a;
    Fedge *n = (Fedge *)b;
    if (m->key < n->key) return -1;    // -1 when a < b
    if (m->key > n->key) return 1;        //  1 when a > b
    return 0;                //  0 when a = b
}

int parent[VSIZE];
int edge_num = 0;

// Initializing to create a set
void make_set(int n) {
    parent[n] = -1;
}

// Returning a set including v
int find_set(int v) {
    while (parent[v] >= 0) {
        v = parent[v];
    }
    return v;
}

// Merging 2 sets
void union_set(int n1, int n2) {
    int root1 = find_set(n1);
    int root2 = find_set(n2);

    if (root1 != root2) {
        if (parent[root1] <= parent[root2]) { // root1 has more members
            parent[root1] += parent[root2];
            parent[root2] = root1;
        } else {                             // root2 has more members
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }

        printf("Union edge %d and edge %d. parent --> ", n1, n2);

        for (int i = 0; i < VSIZE; ++i)
            printf("%3d", parent[i]);
        printf("\n");
    }
}

// Kruskal Algorithm
int kruskal(Fedge e[], int n) {
    int i, u, v;
    int mst_e = 0;                    // min cost
    int mst_e_n = 0;                 // # of edges for mst

    qsort(e, edge_num, sizeof(Fedge), compare); // sort edges using qsort

    for (i = 0; i < edge_num; i++) {
        u = find_set(e[i].u);
        v = find_set(e[i].v);
        if (u != v) {
            union_set(e[i].u, e[i].v);
            mst_e += e[i].key;
            mst_e_n++;
            if (mst_e_n == n - 1) break;
        } else {
            printf("Edge %d and edge %d cause Cycle!!\n", e[i].u, e[i].v);
        }
    }

    return mst_e;
}

int main() {
    int mst;
    int graph[VSIZE][VSIZE] = { // input_graph
    {   0,  4,INF,INF,INF,INF,INF,  8,INF},
    {   4,  0,  8,INF,INF,INF,INF, 11,INF},
    { INF,  8,  0,  7,INF,  4,INF,INF,  2},
    { INF,INF,  7,  0,  9, 14,INF,INF,INF},
    { INF,INF,INF,  9,  0, 10,INF,INF,INF},
    { INF,INF,  4, 14, 10,  0,  2,INF,INF},
    { INF,INF,INF,INF,INF,  2,  0,  1,  6},
    {   8, 11,INF,INF,INF,INF,  1,  0,  7},
    { INF,INF,  2,INF,INF,INF,  6,  7,  0 }};

    Fedge edge_set[INF];

    int i, j;

    // Add your code here to create edge_set
    for (i = 0; i < VSIZE; i++) {
        for (j = i + 1; j < VSIZE; j++) {
            if (graph[i][j] != 0 && graph[i][j] != INF) {
                edge_set[edge_num].u = i;
                edge_set[edge_num].v = j;
                edge_set[edge_num].key = graph[i][j];
                edge_num++;
            }
        }
    }

    for (i = 0; i < VSIZE; i++) {
        make_set(i);
    }

    mst = kruskal(edge_set, VSIZE);
    printf("Min cost is %d.\n", mst);
}