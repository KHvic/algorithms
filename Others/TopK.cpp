#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Data structure to maintain TopK online query, useful for finding X percentile
struct cmp {
    bool operator()(const ll a, const ll b) const {
        return a < b;
    }
};

struct TopK {
    int k;
    multiset<ll, cmp> high, low;
    vector<ll> sum = {0, 0};
    TopK(int k=0):k(k) {}

    void adjust() {
        while(high.size() > k) {
            auto rmv = high.begin();
            low.insert(*rmv);
            high.erase(rmv);
            sum[0] -= *rmv;
            sum[1] += *rmv;
        }
        while(high.size() < k && !low.empty()) {
            auto rmv = low.rbegin();
            ll val = *rmv;
            high.insert(*rmv);
            low.erase(next(rmv).base());
            sum[1] -= val;
            sum[0] += val;
        }
    }

    void add(ll x) {
        high.insert(x);
        sum[0] += x;
        adjust();
    }

    void del(ll x) {
        if(high.count(x)) high.erase(high.find(x)), sum[0] -= x;
        else low.erase(low.find(x)), sum[1] -= x;
        adjust();
    }

    void setK(int k) {
        this->k = k;
        adjust();
    }

    int size() {
        return high.size() + low.size();
    }
};
