#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod = 1e9+7;
struct Binom {
    int n;
    vector<ll> fac, inv;
    Binom(int n): n(n) {
        fac = inv = vector<ll>(n+1, 1);
        for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i % mod;
        inv[n] = powe(fac[n], mod-2);
        for(int i=n-1;i>=0;i--) inv[i] = inv[i+1] * (i+1) % mod;
    }

    ll choose(int n, int r) {
        if(r>n || r<0) return 0;
        return fac[n] * inv[r] % mod * inv[n-r] % mod;
    }

    ll permute(int n, int r) {
        if(r>n || r<0) return 0;
        return fac[n] * inv[n-r] % mod;
    }

    ll powe(ll x, ll e) {
        ll r = 1;
        while (e) {
            if (e & 1) r = r * x % mod;
            x = x * x % mod;
            e >>= 1;
        }
        return r;
    }
};
