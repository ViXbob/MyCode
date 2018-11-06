#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return b < a ? a = b, 1 : 0;}

const int maxn = 4e3 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, S, head[maxn], cnt, dfn[maxn << 1], st[maxn << 1][16], coc, fa[maxn], pos[maxn], Time[maxn << 1];
int Len[maxn << 1], size[maxn], ans, dis[maxn];

struct Node {
	int x, y, d, dp;
	bool operator < (const Node &t) const {
		return dp - d < t.dp - t.d;
	}
} f[maxn][maxn];

struct Graph {int to, nt, w;} e[maxn << 1];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline void ini(int x, int y, int w) {e[++cnt] = (Graph) {y, head[x], w}; head[x] = cnt;}

inline void Pre(int now) {
	dfn[pos[now] = ++coc] = now;
	Time[coc] = pos[now];

	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now]) continue;
		fa[v] = now; dis[v] = dis[now] + e[i].w;
		Pre(v);
		dfn[++coc] = now;
		Time[coc] = pos[now];
	}
}

inline void SetST() {
	for(register int i = 0; i <= coc; i++) Len[i] = log2(i);
	for(register int i = 1; i <= coc; i++) st[i][0] = Time[i];
	for(register int i = 1; (1 << i) <= coc; i++)
		for(register int j = 1; j + (1 << i) - 1 <= coc; j++)
			st[j][i] = min(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
}

inline int LCA(int x, int y) {
	if(pos[x] > pos[y]) swap(x, y);
	int k = Len[pos[y] - pos[x]];
	return dfn[min(st[pos[x]][k], st[pos[y] - (1 << k) + 1][k])];
}

inline int getdis(int x, int y) {
	return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
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
	size[now] = 1; f[now][1] = (Node){now, now, 0, 0};
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa[now]) continue;
		dfs(v);
		for(register int k = min(size[now], S); k >= 0; k--)
			for(register int j = min(size[v], S - k); j >= 0; j--) {
				Node tmp0 = f[now][k], tmp1 = f[v][j];
				merge(tmp0, tmp1);
				tmp0.dp = tmp0.dp + tmp1.dp + e[i].w * 2;
				//if(tmp0 < f[now][j + k])
				chkmin(f[now][j + k], tmp0);
			}
		size[now] += size[v];
	}
	ans = min(ans, f[now][S].dp - f[now][S].d);
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("my.out", "w", stdout);
	n = read(); S = read();

	for(register int i = 1; i < n; i++) {
		int x = read(), y = read(), w = read();
		ini(x, y, w); ini(y, x, w);
	}

	Pre(1); SetST();

	for(register int i = 1; i <= n; i++)
		for(register int j = 0; j <= S; j++)
			f[i][j] = (Node) {i, i, 0, inf};

	ans = inf;
	dfs(1);

	cout << (S == 1 ? 0 : ans);
	return 0;
}
// this solution is dead
