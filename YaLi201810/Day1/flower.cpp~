#include <bits/stdc++.h>
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 15;
const int B = 1e3;
const int Lim = 1e5;

int n, m, f[maxn], a[maxn], be[maxn];
int ans[105][maxn], Mbe, L[maxn], R[maxn], M;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("flower.in", "r", stdin);
	freopen("flower.out", "w", stdout);
#endif
	n = read(); m = read(); Mbe = (n - 1) / B + 1;

	for(register int i = 1; i <= n; i++) 
		M = max(M, a[i] = read()), be[i] = (i - 1) / B + 1;
		

	for(register int i = 1; i <= Mbe; i++) {
		memset(f, 0, sizeof(f));
		L[i] = (i - 1) * B + 1; R[i] = min(i * B, n);
		for(register int j = L[i]; j <= R[i]; j++) f[a[j]] = a[j];

		for(register int j = 1; j <= Lim; j++) f[j] = max(f[j], f[j - 1]);

		for(register int j = 1; j <= Lim; j++)
			for(register int k = 0; k <= Lim; k += j)
				ans[i][j] = max(ans[i][j], f[min(k + j - 1, Lim)] - k);
	}

	/*for(register int j = 1; j <= Mbe; j++) {
		for(register int k = 1; k <= M + 1; k++)
			cerr << ans[j][k] << " ";
		cerr << endl;
	}*/


	for(register int i = 1; i <= m; i++) {
		int l = read(), r = read(), k = read(), Ans = 0;

		//cerr << k << " " << M << endl;

		for(register int j = l; be[j] == be[l] && j <= r; j++) Ans = max(Ans, a[j] % k);
		for(register int j = be[l] + 1; j <= be[r] - 1; j++) Ans = max(Ans, ans[j][k]);
		for(register int j = r; be[j] == be[r] && j >= l; j--) Ans = max(Ans, a[j] % k);

		printf("%d\n", Ans);
	}

	return 0;
}

