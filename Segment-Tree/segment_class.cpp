#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct ST{
public:
    vector<ll> segment;
    int len;
    const ll DEFAULT = 0;
    ST(int n): len(n){
        segment.assign(2*n, DEFAULT);
    }

    ST(vector<ll>& arr): ST(arr.size()) {
        for(int i=0;i<len;i++) segment[i+len] = arr[i];
        for(int i=len-1;i>0;i--) segment[i] = operate(segment[i*2], segment[i*2+1]);
    }

    void update(int i, ll val){
        segment[len+i] = val;
        for(i=(len+i)>>1;i>0;i>>=1) segment[i] = operate(segment[i*2], segment[i*2+1]);
    }

    ll query(int l, int r){
        ll res = 0;
        for(l+=len, r+=len; l<=r; l >>= 1, r >>= 1){
          if((l&1) == 1) res = operate(res, segment[l++]);
          if((r&1) == 0)  res = operate(res, segment[r--]);
        }
        return res;
    }

    ll operate(ll a, ll b) {
        return a+b;
    }
};

int main() {
    vector<ll> arr = {1,3,5};
    ST st(arr);
    printf("%lld\n", st.query(0, 1)); // 4
    st.update(1, 2);
    printf("%lld\n", st.query(0, 1)); // 3
    printf("%lld\n", st.query(0, 2)); // 8
}
