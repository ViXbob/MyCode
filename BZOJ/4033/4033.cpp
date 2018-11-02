#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e3 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, k, cnt, head[maxn], size[maxn];

LL f[maxn][maxn], tmp[maxn];

struct Graph{int to, nt, w;} e[maxn << 1];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline void ini(int x, int y, int w) {e[++cnt] = (Graph){y, head[x], w}; head[x] = cnt;}

inline void dfs(int now, int fr) {
	size[now] = 1;
	
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to; LL w = e[i].w;
		if(v == fr) continue;
		dfs(v, now);
		memset(tmp, 0, sizeof(tmp));
		for(register int j = min(size[now], k); j >= 0; j--)
			for(register int p = 0; p <= size[v] && p + j <= k; p++)
				if(n - k - size[v] + p >= 0)
					chkmax(tmp[j + p], f[v][p] + f[now][j] + w * ((k - p) * p + (size[v] - p) * (n - k - size[v] + p)));
		size[now] += size[v];
		for(register int j = 0; j <= min(size[now], k); j++) f[now][j] = tmp[j];
	}
}

int main() {
	n = read(); k = read();
	
	for(register int i = 1; i < n; i++) {
		int x = read(), y = read(), w = read();
		ini(x, y, w); ini(y, x, w);
	}
	
	dfs(1, 1);
	
	cout << f[1][k];
	return 0;
}
