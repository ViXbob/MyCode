#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e3 + 5;
const int maxm = 21;
const int inf = 0x3f3f3f3f;

int n, m, c[maxm], id[maxn][maxm], tot, cnt, head[maxn * maxm], ans = inf;
int vis[maxn * maxm], dis[maxn * maxm], s;

struct Graph {int to, nt, w;} e[maxn * maxm * maxm * 2];

priority_queue<pair<int, int> > q;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void ini(int x, int y, int w) {e[++cnt] = (Graph){y, head[x], w}; head[x] = cnt;}

inline void Dij() {
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));

	q.push(make_pair(dis[id[1][s]] = 0, id[1][s]));

	while(!q.empty()) {
		int now = q.top().second; q.pop();
		if(vis[now]) continue; vis[now] = 1;
		for(register int i = head[now]; i; i = e[i].nt) {
			int v = e[i].to;
			if(dis[v] > dis[now] + e[i].w) {
				dis[v] = dis[now] + e[i].w;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("updown.in", "r", stdin);
	freopen("updown.out", "w", stdout);
#endif
	n = read(); m = read();

	for(register int i = 1; i <= m; i++) {
		c[i] = read();
		if(c[i] == 0) s = i;
	}

	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++) id[i][j] = ++tot;

	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++)
			for(register int k = 1; k <= m; k++) {
				int v = i + c[k];
				if(v < 1 || v > n) continue;
				int w = abs(c[k]) * 2 + abs(j - k);
				int x = id[i][j], y = id[v][k];
				ini(x, y, w);
			}

	Dij();

	for(register int i = 1; i <= m; i++) chkmin(ans, dis[id[n][i]]);

	cout << (ans == inf ? -1 : ans);
	return 0;
}

