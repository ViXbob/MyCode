#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;

int n, m, a[maxn][maxn], P, f[maxn], c[maxn], s[maxn][maxn], ans = -inf;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int lst(int x) { return x <= 1 ? n : x - 1; }

inline int calc(int x, int i, int p) {
	return s[lst((x + p - 1) % n + 1)][i + p] - s[lst(x)][i];
}

int main() {
	n = read(); m = read(); P = read();

	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++)
			a[i][j] = read();

	for(register int i = 1; i <= n; i++) c[i] = read();

	for(register int j = 1; j <= m; j++)
		for(register int i = 1; i <= n; i++)
			s[i][j] = s[lst(i)][j - 1] + a[i][j];

	memset(f, ~0x3f, sizeof(f)); f[0] = 0;

	for(register int i = 0; i <= m; i++)
		for(register int x = 1; x <= n; x++)
			for(register int p = 1; p <= P && i + p <= m; p++)
				f[i + p] = max(f[i + p], f[i] - c[x] + calc(x, i, p));
				//f[i + p] = max(f[i] - c[x] + s[lst((x + p - 1) % n + 1)][i + p] - s[lst(x)][i]);
				//f[i + p] = f[i] + max(- s[lst(x)][i] - c[x] + s[lst(x + p - 1)][i + p]);

	cout << f[m];
	return 0;
}

