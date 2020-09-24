#include <bits/stdc++.h>
using namespace std;
#define ll long long

// template for mo's algorithm

const int MAXN = 1e6+50;
int vals[MAXN];
ll cnt[MAXN];
ll ans[MAXN];
ll res = 0;

const int blk_size = 500; // roughly sqrt(maxN)

struct Query {
    int l, r, idx;
    bool operator<(Query other) const {
        int v1 = l/blk_size, v2 = other.l/blk_size;
        if(v1 != v2) return v1 < v2;
        return v1&1 ? (r < other.r) : (r > other.r);
    }
}qs[MAXN];

void rmv(int idx) {
    // handle remove
    cnt[vals[idx]]--;
}

void add(int idx) {
    // handle add
    cnt[vals[idx]]++;
}



int main()
{
    int n, k;
    // init data structures & values here

    sort(qs, qs+k);
    int curL = 0, curR = -1;
    for(int i=0;i<t;i++) {
        Query q = qs[i];
        while(curL > q.l) add(--curL);
        while(curR < q.r) add(++curR);
        while(curL < q.l) rmv(curL++);
        while(curR > q.r) rmv(curR--);
        ans[q.idx] = res;
    }

    for(int i=0;i<t;i++) cout << ans[i] << "\n";
}
