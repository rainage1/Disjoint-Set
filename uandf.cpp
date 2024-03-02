// uandf.cpp
#include "uandf.h"

uandf::uandf(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    count = n;
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

void uandf::make_set(int i) {
    if (parent[i] == i) {
        return; // The set already exists as a single element set.
    }
    parent[i] = i;
    rank[i] = 0;
    count++; // Increase the count of disjoint sets
}

int uandf::find_set(int i) {
    if (i != parent[i]) {
        parent[i] = find_set(parent[i]); // Path compression
    }
    return parent[i];
}

void uandf::union_sets(int i, int j) {
    int iRoot = find_set(i);
    int jRoot = find_set(j);

    // Check if they're in the same set
    if (iRoot == jRoot) {
        return;
    }

    // Union by rank
    if (rank[iRoot] < rank[jRoot]) {
        parent[iRoot] = jRoot;
    } else if (rank[iRoot] > rank[jRoot]) {
        parent[jRoot] = iRoot;
    } else {
        parent[jRoot] = iRoot;
        rank[iRoot]++; // Increase the rank if both have the same rank
    }

    count--; // Decrease the count of disjoint sets since they are merged into 1
}

void uandf::final_sets() {
    int representative = 1;
    for (int i = 0; i < parent.size(); ++i) {
        if (i == find_set(i)) {
            parent[i] = representative - 1; // Resetting representatives
            representative++;
        } else {
            parent[i] = find_set(parent[i]); // Ensure all nodes point to their new representative
        }
    }
}

int uandf::finalSetsCount() {
    return count;
}
