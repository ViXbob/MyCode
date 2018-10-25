#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1

using namespace std;

typedef long long LL;

const int maxn = 95;
const int maxm = 1e4 + 5;
const int maxS = 1 << 11;
const int inf = 1e9 + 7;
const int P = 1e9 + 7;

int n, m, d, ans, head[maxn], cnt, d1, d2;
bitset<maxn> f[maxn][11][maxS], G0[maxn], G1[maxn], g[maxS];
struct Graph {int to, nt, w;} e[maxm << 2];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
};

inline void ini(int x, int y, int w) {e[++cnt] = (Graph) {y, head[x], w}; head[x] = cnt;}

int main() {
#ifndef ONLINE_JUDGE
	freopen("y.in", "r", stdin);
	freopen("y.out", "w", stdout);
#endif	
	n = read(); m = read(); d = read();
	
	for(register int i = 1; i <= m; i++) {
		int x = read(), y = read(), w = read();
		if(w) G1[x][y] = G1[y][x] = 1;
		else G0[x][y] = G0[y][x] = 1;
	}
	
	d1 = (d + 1) / 2; d2 = d - d1;
	
	for(register int u = 1; u <= n; u++) {
		f[u][1][1] |= G1[u]; f[u][1][0] |= G0[u];
		for(register int L = 2; L <= d1; L++)
			for(register int S = 0; S < (1 << L - 1); S++)
				for(register int v = 1; v <= n; v++)
					if(f[u][L - 1][S][v]) {
						f[u][L][S << 1] |= G0[v];
						f[u][L][S << 1 | 1] |= G1[v];
					}
		for(register int S = 0; S < 1 << d1; S++)
			g[S][u] = f[u][d1][S].any();
	}
	
	for(register int i = 0; i < 1 << d1; i++)
		for(register int j = 0; j < 1 << d2; j++)
			if((f[1][d2][j] & g[i]).any())
				ans++;
	
	cout << ans;
	return 0;
}
