#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int N = 101;
ll pascal[N][N]; // n choose k
void initPascal() {
	for(int i=0;i<N;i++) {
		pascal[i][0] = 1;
		for(int j=1;j<=i;j++) {
			pascal[i][j] = pascal[i-1][j] + pascal[i-1][j-1];
		}
	}
}

int main() {
    initPascal();
    cout << pascal[16][8]; // 12870
}
