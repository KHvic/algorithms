#include <bits/stdc++.h>
using namespace std;

struct AP {
    vector<vector<int>> graph, bridges;
    vector<bool> ap;
    vector<int> low, idx;
    int n, cur;

    AP(int N): n(N), cur(0) {
        graph = vector<vector<int>>(n);
        ap = vector<bool>(n);
        low = idx = vector<int>(n);
    }

    int dfs(int x, int par) {
        idx[x] = low[x] = ++cur;
        int child_cnt = 0;
        for(int y : graph[x]) {
            if(y == par) continue;
            if(low[y] == 0) {
                dfs(y, x);
                child_cnt++;
                if(low[y] >= idx[x]) ap[x] = true;
                if(low[y] > idx[x]) bridges.push_back({x, y});

                low[x] = min(low[x], low[y]);
            } else low[x] = min(low[x], idx[y]);
        }
        return child_cnt;
    }

    void start() {
        for(int i=0;i<n;i++)
        if(idx[i] == 0) {
            if(dfs(i, i) > 1) ap[i] = true;
        }
    }

    void add(int a, int b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
};

int main(){
    vector<vector<int>> edges = {{0,1},{0,5},{0,3},{0,2},{3,4}};
    AP ap(6);
    for(auto& edge : edges) ap.add(edge[0], edge[1]);
    ap.start();

    cout << count(ap.ap.begin(), ap.ap.end(), true) << endl;
    cout << ap.bridges.size() << endl; // 3
}
