#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll> fenwick;
vector<ll> vec;
int n;

void init(int len) {
    n = len;
    fenwick.assign(n+1, 0);
    vec.assign(n+1, 0);
}

ll rsq(int a) {
    ll res = 0;
    a++;
    while(a) {
        res += fenwick[a];
        a -= (a&-a);
    }
    return res;
}

void adjust(int a, int v) {
    a++;
    while(a<=n) {
        fenwick[a] += v;
        a += (a&-a);
    }
}

void add(int a, int v) {
    int diff = v - vec[a];
    adjust(a, diff);
}

ll query(int a, int b) {
    return rsq(b) - rsq(a-1);
}

int main()
{
    init(5);
    add(0, 3);
    add(2, 1);
    cout << query(0, 2) << endl; // expect 4
    cout << query(0, 1) << endl; // expect 3
    add(1, 5);
    cout << query(0, 2) << endl; // expect 9
    add(0, -3);
    cout << query(0, 2) << endl; // expect 6
}
