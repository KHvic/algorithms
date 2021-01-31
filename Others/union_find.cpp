#include <bits/stdc++.h>
using namespace std;

struct UF {
    int cnt;
    vector<int> p, rank, size;
    UF(int N): cnt{N} {
        p = rank = size = vector<int>(N, 1);
        for (int i = 0; i < N; i++) p[i] = i;
    }
    int find(int i) {
        return p[i] == i ? i : p[i] = find(p[i]);
    }
    bool connected(int i, int j) {
        return find(i) == find(j);
    }
    void join(int i, int j) {
        if (connected(i, j)) return;
        cnt--;
        int x = find(i), y = find(j);
        if (rank[x] > rank[y]) {
            p[y] = x;
            size[x] += size[y];
        } else {
            p[x] = y;
            size[y] += size[x];
            if (rank[x] == rank[y]) rank[y]++;
        }
    }
};
