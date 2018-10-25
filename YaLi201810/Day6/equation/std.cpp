#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 5;

int n, m, k[maxn], b[maxn], head[maxn], cnt;
int dfn[maxn], pos[maxn], size[maxn], son[maxn], top[maxn], fa[maxn], deep[maxn], w[maxn];

struct Graph {int to, nt;} e[maxn << 2];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void ini(int x, int y) {e[++cnt] = (Graph) {y, head[x]}; head[x] = cnt;}

inline void dfs(int now) {
	int maxs = -1; size[now] = 1;
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now]) continue;
		fa[v] = now; deep[v] = deep[now] + 1;
		dfs(v);
		size[now] += size[v];
		if(size[v] > maxs) {son[now] = v; maxs = size[v];}
	}
	if(maxs == -1) son[now] = now;
}

inline int ChainQuery(int x, int y, int ty) {
	int ans = 0;
	while(y != x) {
		ans += (ty == (deep[y] & 1)) * w[y];
		y = fa[y];
	} return ans;
}

int main() {
	freopen("data.in", "r", stdin);
	freopen("std.out", "w", stdout);
	
	n = read(); m = read();
	
	for(register int i = 2; i <= n; i++) {
		int f = read(); w[i] = read();
		ini(i, f); ini(f, i);
	}
	deep[1] = fa[1] = 1;
	dfs(1);
	
	for(register int i = 1; i <= m; i++) {
		int opt = read(), u = read(), v = read(), s = 0;
		if(opt == 1) {
			s = read();
			int su = ChainQuery(1, u, deep[u] & 1) - ChainQuery(1, u, (deep[u] & 1) ^ 1);
			int sv = ChainQuery(1, v, deep[v] & 1) - ChainQuery(1, v, (deep[v] & 1) ^ 1);
			if((deep[u] & 1) ^ (deep[v] & 1)) {
				if(su + sv != s) puts("none");
				else puts("inf");
			}
			else {
				s -= (su + sv);
				if(abs(s) & 1) puts("none");
				else printf("%d\n", s / (deep[u] & 1 ? 2 : -2));
			}
		}
		else w[u] = v;
	}
	return 0;
}
