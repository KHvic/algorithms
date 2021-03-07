#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 998244353; // mod has to be a prime
const int n = 200002;
ll fac[n+1], fin[n+1];

// power with mod
ll powe(ll x, ll e) {
	ll r = 1;
	while (e) {
		if (e & 1) r = r * x % mod;
		x = x * x % mod;
		e >>= 1;
	}
	return r;
}

// find inverse modular I of 1/a
// fermat little theorem => a^(p-1) congruent 1 (mod p) if p is prime
// then a^(p-2) congruent to 1/a (mod p)
ll inv(ll x) {
	return powe(x, mod - 2);
}

// combination formula
ll choose(int a, int b) {
	if (b < 0 || b > a) return 0;
	return fac[a] * fin[b] % mod * fin[a - b] % mod;
}

// permutation formula
ll permute(int a, int b) {
	return fac[a] * fin[a - b] % mod;
}

int main()
{
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
	fin[n - 1] = inv(fac[n - 1]);
	for (int i = n - 2; i >= 0; --i) fin[i] = fin[i + 1] * (i + 1) % mod;
}
