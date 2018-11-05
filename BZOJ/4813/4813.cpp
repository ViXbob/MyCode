#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e2 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, S, head[maxn], cnt, f[maxn][maxn], g[maxn][maxn], fa[maxn], ans;

struct Graph {int to, nt;} e[maxn << 1];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline void ini(int x, int y) {e[++cnt] = (Graph){y, head[x]}; head[x] = cnt;}

inline void dfs(int now) {
	f[now][0] = 1; g[now][0] = 1;
	//f[now][0] = 1;
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now]) continue;
		fa[v] = now; dfs(v);
		for(register int k = S; k >= 0; k--)
			for(register int j = S; j >= 0; j--) {
				if(k + j < S)
					g[now][j + k + 1] = max(g[now][j + k + 1], f[now][k] + g[v][j]);
				if(k + j + 1 < S) {
					g[now][j + k + 2] = max(g[now][j + k + 2], g[now][k] + f[v][j]);
					f[now][j + k + 2] = max(f[now][j + k + 2], f[now][k] + f[v][j]);
				}
			}
	}
	for(register int i = 1; i <= S; i++)
		f[now][i] = max(f[now][i], f[now][i - 1]), g[now][i] = max(g[now][i], g[now][i - 1]);
	//ans = max(ans, f[now][S]);
}

int main() {
	n = read(); S = read();

	for(register int i = 1; i < n; i++) {
		int x = read() + 1, y = read() + 1;
		ini(x, y); ini(y, x);
	}

	dfs(1);

	cout << g[1][S];
	return 0;
}

