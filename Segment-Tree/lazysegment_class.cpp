#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// sum segment tree
class ST {
    int n;
    const ll LAZY = 0, DEFAULT = 0;
    vector<ll> segment, lazy;
public:
    ST() {}

    ST(int n):n(n){
        segment.assign(4*n, DEFAULT);
        lazy.assign(4*n, LAZY);
    }

    ST(vector<ll>& vals): ST(vals.size()) {
        for(int i = 0; i < n; ++i) update(i, i, vals[i]);
    }

    void update(int qlow, int qhi, ll val) {
        update(0, 0, n-1, qlow, qhi, val);
    }

    ll query(int qlow, int qhi) {
        return query(0, 0, n-1, qlow, qhi);
    }

private:
    void updateLazy(int idx, int low, int high) {
        if(lazy[idx] != LAZY && low != high) {
            lazy[idx*2+1] += lazy[idx];
            lazy[idx*2+2] += lazy[idx];
        }
        // update logic
        if(lazy[idx] != LAZY) {
            segment[idx] += (high-low+1)*lazy[idx];
        }
        lazy[idx] = LAZY;
    }

    void update(int idx, int low, int hi, int qlow, int qhi, ll val) {
        updateLazy(idx, low, hi);
        if(low > qhi || hi < qlow) return;
        else if(low >= qlow && hi <= qhi) {
            lazy[idx] = val;
            updateLazy(idx, low, hi);
        } else {
            int mid = (low + hi) >> 1;
            update(idx*2+1, low, mid, qlow, qhi, val);
            update(idx*2+2, mid+1, hi, qlow, qhi, val);
            segment[idx] = operate(segment[idx*2+1], segment[idx*2+2]);
        }
    }

    ll query(int idx, int low, int hi, int qlow, int qhi) {
        updateLazy(idx, low, hi);
        if(low > qhi || hi < qlow) return DEFAULT;
        else if(low >= qlow && hi <= qhi) return segment[idx];
        int mid = (low+hi) >> 1;
        return operate(query(idx*2+1, low, mid, qlow, qhi), query(idx*2+2, mid+1, hi, qlow, qhi));
    }

    ll operate(ll a, ll b) {
        return a + b;
    }
};

int main(){
    vector<ll> test = {1, 2, 3, 4, 5, 10};
    ST st(test);
    printf("%lld\n", st.query(1, 2)); // 5
    printf("%lld\n", st.query(0, 5)); // 25
    st.update(0, 2, 2); // adjust all by +2
    printf("%lld\n", st.query(0, 3)); // 16 (3, 4, 5, 4)
}
