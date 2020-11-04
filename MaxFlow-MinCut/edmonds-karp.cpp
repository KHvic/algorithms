#include <bits/stdc++.h>
using namespace std;

int n,u,v,w;
int s=0,t=1; // source, sink target index
int f;
const int INF = 1e8;
vector<int> pars;
vector<map<int,int>> graph;

void augment(int u, int mn) {
    if(u==s) {
        f = mn;
    } else if(pars[u] != -1) {
        int p = pars[u];
        augment(p, min(mn, graph[p][u]));
        graph[p][u] -= f;
        graph[u][p] += f;
    }
}

// O(V*E^2)
int maxFlow() {
    int mf = 0;
    while(1) {
        vector<bool> vis(n);
        pars.assign(n, -1);
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            u = q.front(); q.pop();
            if(u==t) break;
            for(auto& edge : graph[u]) {
                tie(v, w) = edge;
                if(!vis[v] && w>0) {
                    vis[v] = 1;
                    pars[v] = u;
                    q.push(v);
                }
            }
        }
        f = 0;
        augment(t, INF);
        if(f==0) break;
        mf += f;
    }
    return mf;
}

int main()
{
    n = 4;
    graph.assign(n, map<int, int>());
    auto add = [&](int u, int v, int w) {
        graph[u][v] = w;
    };
    add(s,2,3);
    add(s,3,2);
    add(2,t,1);
    add(3,t,2);
    cout << maxFlow(); // 3
}
