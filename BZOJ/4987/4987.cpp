#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 3e3 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, head[maxn], cnt, f[maxn][maxn][3], fa[maxn], size[maxn], ans, S;

struct Graph {int to, nt, w;} e[maxn << 2];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}


inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline void ini(int x, int y, int w) {e[++cnt] = (Graph){y, head[x], w}; head[x] = cnt;}

inline void dfs(int now) {
	size[now] = 1; f[now][1][0] = f[now][1][1] = 0;
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now]) continue;
		fa[v] = now; dfs(v);
		for(register int k = min(size[now], S); k >= 0; k--)
			for(register int j = min(size[v], S - k); j >= 0; j--) {
				chkmin(f[now][k + j][0], f[now][k][0] + f[v][j][0] + e[i].w * 2);
				chkmin(f[now][k + j][1], f[now][k][1] + f[v][j][0] + e[i].w * 2);
				chkmin(f[now][k + j][1], f[now][k][0] + f[v][j][1] + e[i].w);
				chkmin(f[now][k + j][2], f[now][k][1] + f[v][j][1] + e[i].w);
				chkmin(f[now][k + j][2], f[now][k][2] + f[v][j][0] + e[i].w * 2);
				chkmin(f[now][k + j][2], f[now][k][0] + f[v][j][2] + e[i].w * 2);
			}
		size[now] += size[v];
	}
	chkmin(ans, min(f[now][S][1], f[now][S][2]));
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("std.out", "w", stdout);
	n = read(); S = read();

	for(register int i = 1; i < n; i++) {
		int x = read(), y = read(), w = read();
		ini(x, y, w); ini(y, x, w);
	}

	ans = inf;
	memset(f, 0x3f, sizeof(f));

	dfs(1);

	cout << (S == 1 ? 0 : ans);
	return 0;
}

