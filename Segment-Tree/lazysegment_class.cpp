#include <bits/stdc++.h>
using namespace std;

// sum segment tree
struct ST {
    int n;
    vector<int> segment, lazy;
    ST(int n):n(n){
        segment.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    void updateLazy(int idx, int low, int high) {
        if(lazy[idx] && low != high) {
            lazy[idx*2+1] += lazy[idx];
            lazy[idx*2+2] += lazy[idx];
        }
        // update logic
        if(lazy[idx]) {
            segment[idx] += (high-low+1)*lazy[idx];
        }
        lazy[idx] = 0;
    }

    void update(int idx, int low, int hi, int qlow, int qhi, int val) {
        updateLazy(idx, low, hi);
        if(low>qhi || hi<qlow) return;
        else if(low>=qlow && hi<=qhi) {
            lazy[idx] = val;
            updateLazy(idx, low, hi);
        } else {
            int mid = (low+hi) >> 1;
            update(idx*2+1, low, mid, qlow, qhi, val);
            update(idx*2+2, mid+1, hi, qlow, qhi, val);
            segment[idx] = segment[idx*2+1] + segment[idx*2+2];
        }
    }

    void update(int qlow, int qhi, int val) {
        update(0, 0, n-1, qlow, qhi, val);
    }

    int query(int idx, int low, int hi, int qlow, int qhi) {
        updateLazy(idx, low, hi);
        if(low>qhi || hi<qlow) return 0;
        else if(low>=qlow && hi<=qhi) return segment[idx];
        int mid = (low+hi) >> 1;
        return query(idx*2+1, low, mid, qlow, qhi) + query(idx*2+2, mid+1, hi, qlow, qhi);
    }

    int query(int qlow, int qhi) {
        return query(0, 0, n-1, qlow, qhi);
    }
};

int main(){
    vector<int> test = {1, 2, 3, 4, 5, 10};
    ST st(test.size());
    for(int i=0;i<test.size();i++) st.update(i, i, test[i]);
    printf("%d\n", st.query(1, 2)); // 5
    printf("%d\n", st.query(0, 5)); // 25
    st.update(0, 2, 2); // adjust all by +2
    printf("%d\n", st.query(0, 3)); // 16 (3, 4, 5, 4)
}
