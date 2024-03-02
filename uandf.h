// uandf.h
#ifndef UANDF_H
#define UANDF_H

#include <vector>

class uandf {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int count;

public:
    uandf(int n);
    void make_set(int i);
    int find_set(int i);
    void union_sets(int i, int j);
    void final_sets();
    int finalSetsCount();
};

#endif // UANDF_H
