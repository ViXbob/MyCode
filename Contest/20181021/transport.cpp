#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 20;
const int maxs = 1 << 19;
const int inf = 0x3f3f3f3f;

int n, m, G[maxn][maxn], nxt[maxs], U, w[maxs], ans = inf;
int minU[maxn], dis[maxs][maxn], vis[maxs][maxn];
int t;

//priority_queue<pair<int, pair<int, int> > > q;

queue<pair<int, int> > q;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void Dij(int s) {
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	
	/*q.push(make_pair(dis[1 << s - 1][1] = 0, make_pair(1 << s - 1, s)));
	
	while(!q.empty()) {
		int S = q.top().second.first, u = q.top().second.second; q.pop();
		if(vis[S][u]) continue; vis[S][u] = 1;
		for(register int i = 1; i <= n; i++) {
			//if(S & (1 << i - 1)) continue;
			int S0 = S | (1 << i - 1);
			if(dis[S0][i] > dis[S][u] + G[u][i]) {
				dis[S0][i] = dis[S][u] + G[u][i];
				q.push(make_pair(-dis[S0][i], make_pair(S0, i)));
			}
		}
	}*/
	
	q.push(make_pair(1 << s - 1, s)); dis[1 << s - 1][s] = 0; vis[1 << s - 1][s] = 1;
	
	while(!q.empty()) {
		int S = q.front().first, u = q.front().second; q.pop();
		vis[S][u] = 0;
		for(register int i = 1; i <= n; i++) {
			int S0 = S | (1 << i - 1);
			if(dis[S0][i] > dis[S][u] + G[u][i]) {
				dis[S0][i] = dis[S][u] + G[u][i];
				if(!vis[S0][i]) q.push(make_pair(S0, i)), vis[S0][i] = 1;
			}
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
#endif
	t = clock();
	n = read(); m = read(); U = (1 << n) - 1;
	
	memset(G, 0x3f, sizeof(G));
	memset(w, 0x3f, sizeof(w));
	
	for(register int i = 1; i <= m; i++) {
		int x = read(), y = read(), w = read();
		G[x][y] = G[y][x] = w;
	}
	
	Dij(1);
	
	for(register int S = 0; S < U; S++) 
		for(register int i = 1; i <= n; i++) 
			w[S] = min(w[S], dis[S][i]);
	
	for(register int S = 0; S < U; S++) {
		//if(!(S & 1)) continue;
		for(register int S0 = S; S0; S0 = (S0 - 1) & S) {
			ans = min(ans, max(w[S], w[~S0 & U]));
		}
		//ans = min(ans, max(w[S], w[(U - S) | 1]));
	}
	
	cout << ans;
	return 0;
}
/*
6 6
1 2 10
2 3 10
3 4 5
4 5 10
5 6 20
2 5 10

*/
