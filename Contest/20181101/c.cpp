#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 4e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;
const int fx[4] = {0, 1, 0, -1};
const int fy[4] = {1, 0, -1, 0};
const int fx0[4] = {0, 0, 1, 1};
const int fy0[4] = {0, 1, 0, 1};

int n, m, cnt, head[maxn], vis[maxn], ID[105][105][105], tot;

int dis[maxn], mp[105][105][105];

struct Graph {int to, nt, w;} e[maxn << 4];

struct Node {
	int u, dis;
	Node (int U = 0, int DIS = 0) {u = U; dis = DIS;}
	bool operator < (const Node &t) const {return dis > t.dis;}
};
priority_queue<Node> q;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int pos(int p, int x, int y) {
	return ID[p][x][y];
}
// n * (n + 1) * (2 * n + 1)
inline void ini(int x, int y, int w) {e[++cnt] = {y, head[x], w}; head[x] = cnt;}

inline void Dij(int p, int i, int j) {
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	int s = pos(p, i, j);
	dis[s] = mp[p][i][j];
	q.push(Node(s, dis[s]));
	while(!q.empty()) {
		int now = q.top().u; q.pop();
		if(vis[now]) continue; vis[now] = 1;
		for(register int i = head[now]; i; i = e[i].nt) {
			int v = e[i].to;
			if(dis[v] > dis[now] + e[i].w) {
				dis[v] = dis[now] + e[i].w;
				q.push(Node(v, dis[v]));
			}
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	n = read(); m = read();
	
	for(register int p = 1; p <= n; p++) {
		for(register int i = 1; i <= n - p + 1; i++)	
			for(register int j = 1; j <= n - p + 1; j++)
				mp[p][i][j] = read(), ID[p][i][j] = ++tot; 
		for(register int i = 1; i <= n - p + 1; i++)	
			for(register int j = 1; j <= n - p + 1; j++)
				for(register int k = 0; k < 4; k++) {
					int dx = i + fx[k], dy = j + fy[k]; int id = n - p + 1;
					if(dx < 1 || dx > id || dy < 1 || dy > id) continue;
					ini(pos(p, i, j), pos(p, dx, dy), mp[p][dx][dy]);
				}
	}
	
	for(register int p = 2; p <= n; p++)
		for(register int i = 1; i <= n - p + 1; i++)	
			for(register int j = 1; j <= n - p + 1; j++) {
				int id1 = n - p + 1, id2 = id1 + 1;
				for(register int k = 0; k < 4; k++) {
					int dx = i + fx0[k], dy = j + fy0[k];
					if(dx < 1 || dx > id2 || dy < 1 || dy > id2) continue;
					ini(pos(p - 1, dx, dy), pos(p, i, j), mp[p][i][j]);
				}
			}
	
	for(register int i = 1; i <= m; i++) {
		int a1 = read(), b1 = read(), c1 = read(), a2 = read(), b2 = read(), c2 = read(), p1 = read();
		int id1 = n - a1 + 1, id2 = n - a2 + 1;
		ini(pos(a1, b1, c1), pos(a2, b2, c2), p1 + mp[a2][b2][c2]);
	}
	
	Dij(1, 1, 1);
	
	cout << dis[pos(n, 1, 1)];
	return 0;
}
/*
4 2
4 1 5 2
4 3 4 7
1 9 2 8
0 3 5 1
2 8 5
9 3 9
1 1 8
7 4
5 2
42
1 1 2 2 3 1 1
1 3 2 2 2 1 7

*/
