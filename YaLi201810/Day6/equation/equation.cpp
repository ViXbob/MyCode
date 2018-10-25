#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 5;

int n, m, k[maxn], b[maxn], head[maxn], cnt;
int dfn[maxn], pos[maxn], size[maxn], son[maxn], top[maxn], fa[maxn], deep[maxn], w[maxn];

struct Graph {int to, nt;} e[maxn << 1];

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

inline void dfs(int now, int f) {
	top[now] = f;
	pos[dfn[++dfn[0]] = now] = dfn[0];
	if(son[now] != now) dfs(son[now], f);
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == son[now] || v == fa[now]) continue;
		dfs(v, v);
	}
}

struct SegmentTree {
	struct node {int s[2];} t[maxn << 2];
	
	inline void pushup(int p) {
		t[p].s[0] = t[ls].s[0] + t[rs].s[0];
		t[p].s[1] = t[ls].s[1] + t[rs].s[1];
	}
	
	inline void build(int l, int r, int p) {
		if(l == r) {
			int id = dfn[r];
			t[p].s[deep[id] & 1] = w[id]; return;
		}
		build(l, mid, ls); build(mid + 1, r, rs);
		pushup(p);
	}
	
	inline void modify(int l, int r, int pos, int p, int x, int ty) {
		if(l == r) {
			t[p].s[ty] = x; return;
		}
		if(pos <= mid) modify(l, mid, pos, ls, x, ty);
		else modify(mid + 1, r, pos, rs, x, ty);
		pushup(p);
	}
	
	inline int query(int l, int r, int ql, int qr, int p, int ty) {
		if(ql == l && qr == r) return t[p].s[ty] - t[p].s[ty ^ 1];
		if(qr <= mid) return query(l, mid, ql, qr, ls, ty);
		else if(ql > mid) return query(mid + 1, r, ql, qr, rs, ty);
		else return (query(l, mid, ql, mid, ls, ty) + query(mid + 1, r, mid + 1, qr, rs, ty));
	}
} T;

inline int ChainQuery (int x, int y, int ty) {
	int ans = 0;
	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]]) swap(x, y);
		ans += T.query(1, n, pos[top[x]], pos[x], 1, ty);
		x = fa[top[x]];
	}
	if(deep[x] > deep[y]) swap(x, y);
	ans += T.query(1, n, pos[x], pos[y], 1, ty);
	return ans - T.query(1, n, 1, 1, 1, ty);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
#endif
	
	//freopen("data.in", "r", stdin);
	//freopen("my.out", "w", stdout);
	
	n = read(); m = read();
	
	for(register int i = 2; i <= n; i++) {
		int f = read(); w[i] = read();
		ini(i, f); ini(f, i);
	}
	
	deep[1] = fa[1] = 1;
	dfs(1); dfs(1, 1);
	
	T.build(1, n, 1);
	
	for(register int i = 1; i <= m; i++) {
		int opt = read(), u = read(), v = read(); LL s = 0;
		if(opt == 1) {
			s = read();
			LL su = ChainQuery(1, u, deep[u] & 1);
			LL sv = ChainQuery(1, v, deep[v] & 1);
			if((deep[u] & 1) ^ (deep[v] & 1)) {
				if(su + sv != s) puts("none");
				else puts("inf");
			}
			else {
				s -= (su + sv);
				if(abs(s) & 1) puts("none");
				else printf("%lld\n", s / (deep[u] & 1 ? 2 : -2));
			}
		}
		else T.modify(1, n, pos[u], 1, v, deep[u] & 1);
	}
	return 0;
}
