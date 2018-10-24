#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 3e5 + 5;
const int inf = 0x3f3f3f3f;

int n, fa[maxn][21], cnt, head[maxn], deep[maxn], siz[maxn], ans[maxn];
int Tx0, Ty0, Tx1, Ty1, Sx, Sy, CurAns, tot, Ans[maxn];

struct Node {int d, x, y;} f[maxn];

struct Graph {int to, nt;} e[maxn << 1];
vector<pair<int, Node> > pre[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void ini(int x, int y) {e[++cnt] = (Graph) {y, head[x]}; head[x] = cnt;}

inline int Jump(int x, int d) {
	for(register int i = 0; d > 0; i++, d >>= 1)
		if(d & 1) x = fa[x][i];
	return x;
}

inline int LCA(int x, int y) {
	if(deep[x] < deep[y]) swap(x, y);
	x = Jump(x, deep[x] - deep[y]);
	if(x == y) return x;
	for(register int i = 20; ~i; i--)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

inline int getdis(int x, int y) {
	int lca = LCA(x, y);
	return deep[x] + deep[y] - 2 * deep[lca];
}

inline int getmid(int x, int y) {
	int lca = LCA(x, y), len = (deep[x] + deep[y] - 2 * deep[lca]) / 2;
	return deep[x] - deep[lca] >= len ? Jump(x, len) : Jump(y, len);
}

inline void merge(Node &a, Node b) {
	int len = a.d, x = a.x, y = a.y;
	if(chkmax(len, b.d)) a.x = b.x, a.y = b.y;
	if(chkmax(len, getdis(x, b.x))) a.x = x, a.y = b.x;
	if(chkmax(len, getdis(x, b.y))) a.x = x, a.y = b.y;
	if(chkmax(len, getdis(y, b.x))) a.x = y, a.y = b.x;
	if(chkmax(len, getdis(y, b.y))) a.x = y, a.y = b.y;
	a.d = len;
}

inline void dfs(int now) {
	for(register int i = 1; (1 << i) < deep[now]; i++)
		fa[now][i] = fa[fa[now][i - 1]][i - 1];

	f[now] = (Node) {0, now, now};

	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now][0]) continue;
		fa[v][0] = now; deep[v] = deep[now] + 1;
		dfs(v);
		merge(f[now], f[v]); siz[now]++;
	}
}

inline void dfs(int now, Node lst) {
	if(now != 1) {
		int len = max(max(f[now].d, lst.d), (f[now].d + 1) / 2 + (lst.d + 1) / 2 + 1);

		if(chkmin(CurAns, ans[now] = len)) {
			Sx = now; Sy = fa[now][0];
			Tx0 = lst.x; Ty0 = lst.y;
			Tx1 = f[now].x; Ty1 = f[now].y;
		}
	}

	int c = 0; pre[now][c++] = make_pair(-1, lst);

	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now][0]) continue;
		Node x = pre[now][c - 1].second;
		merge(x, f[v]); pre[now][c++] = make_pair(v, x);
	}

	Node tmp, Po = lst;
	merge(Po, (Node){0, now, now});

	for(register int i = c - 1; i > 0; i--) {
		int v = pre[now][i].first;
		if(v == fa[now][0]) continue;

		merge(tmp = Po, pre[now][i - 1].second);
		dfs(v, tmp);
		merge(Po, f[v]);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("league.in", "r", stdin);
	freopen("league.out", "w", stdout);
#endif
	n = read();

	for(register int i = 1; i < n; i++) {
		int x = read(), y = read();
		ini(x, y); ini(y, x);
	}

	deep[1] = 1; dfs(1); CurAns = inf;

	for(register int i = 1; i <= n; i++) pre[i].resize(siz[i] + 5);

	dfs(1, (Node) {0, 1, 1});
	for(register int i = 2; i <= n; i++)
		if(CurAns == ans[i]) Ans[++tot] = i - 1;

	printf("%d\n", CurAns);
	printf("%d ", tot);
	for(register int i = 1; i <= tot; i++)
		printf("%d ", Ans[i]);
	cout << endl;
	printf("%d %d %d %d", Sx, Sy, getmid(Tx0, Ty0), getmid(Tx1, Ty1));
	return 0;
}

