#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<ll> segment;
int n;
void build(vector<ll> arr) {
    n = arr.size();
    segment.assign(2*n,0);
    for(int i=0;i<n;i++) segment[i+n] = arr[i];
    for(int i=n-1;i>0;i--) segment[i] = segment[i*2]+segment[i*2+1];
}

void update(int i, ll val){
    segment[n+i] = val;
    for(i=(n+i)>>1;i>0;i>>=1) segment[i] = segment[i*2]+segment[i*2+1];
}

ll query(int l, int r){
    ll res = 0;
    for(l+=n, r+=n; l<=r; l >>= 1, r >>= 1){
      // l is odd, is right child of parent
      if((l&1) == 1) res += segment[l++];
      // r is left child, include it
      if((r&1) == 0)  res += segment[r--];
    }
    return res;
}
