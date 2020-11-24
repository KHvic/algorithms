#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct RK {
    ll mod = 1000000007;
    ll P = 37;
    vector<ll> prefix, pinv;
    RK(string s) {
        prefix = {0};
        pinv = {1};
        ll Pinv = powe(P, mod-2);
        ll ha = 0;
        ll pwr = 1, pwrinv = 1;
        for(int i=0;i<s.size();i++) {
            int v = s[i]-'a';
            ha = (ha + v * pwr % mod) % mod;
            pwr = pwr * P % mod;
            pwrinv = pwrinv * Pinv % mod;
            prefix.push_back(ha);
            pinv.push_back(pwrinv);
        }
    }

    ll query(int low, int high) {
        ll res = (prefix[high+1] - prefix[low]) * pinv[low] % mod;
        if(res<0) res += mod;
        return res;
    }

    ll powe(ll x, ll e) {
        ll res = 1;
        while(e) {
            if(e&1) res = res*x%mod;
            e >>= 1;
            x = x*x%mod;
        }
        return res;
    }
};

int main(){
    RK rk("abccabcc");
    cout << rk.query(0, 1) << ":" << rk.query(4, 5) << "\n";
    cout << rk.query(0, 2) << ":" << rk.query(4, 6) << "\n";
    cout << rk.query(2, 3) << ":" << rk.query(6, 7) << "\n";
}
