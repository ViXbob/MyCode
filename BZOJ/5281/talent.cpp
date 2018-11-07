#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 255;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;
const int del = 1000;
const double eps = 1e-9;

int t[maxn], w[maxn], W, n;

double f[maxn][1500], ans, a[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

inline bool check(double mid) {
	for(register int i = 0; i <= n; i++)
		for(register int j = 0; j <= W; j++)
			f[i][j] = -inf;
	f[0][0] = 0;
	for(register int i = 1; i <= n; i++) a[i] = t[i] - mid * w[i];
	for(register int i = 1; i <= n; i++)
		for(register int j = 0; j <= W; j++) {
			f[i][j] = max(f[i][j], f[i - 1][j]);
			int p = min(W, j + w[i]);
			f[i][p] = max(f[i][p], f[i - 1][j] + a[i]);
		}
	return f[n][W] > eps;
}

inline double Biniry(double l, double r) {
	double mid = (l + r) / 2, ans = 0;
	while(r - l >= eps) {
		mid = (l + r) / 2;
		if(check(mid)) ans = mid, l = mid + eps;
		else r = mid - eps;
	} return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("talent.in", "r", stdin);
	freopen("talent.out", "w", stdout);
#endif
	n = read(); W = read();

	for(register int i = 1; i <= n; i++)
		w[i] = read(), t[i] = read();

	ans = Biniry(0, 1e3);

	printf("%d", int(ans * 1000));
	//cout << (ans * 1000);
	return 0;
}
/*
3 15
20 21
10 11
30 31

*/

