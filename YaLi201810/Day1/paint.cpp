#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 55;
const int inf = 0x3f3f3f3f;
const int fx[4] = {0, 1, 0, -1};
const int fy[4] = {1, 0, -1, 0};

int dis[maxn][maxn], n, m, ans;
deque<pair<int, int> > q;

char mp[maxn][maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int calc(int sx, int sy) {
	memset(dis, -1, sizeof(dis));
	while(!q.empty()) q.pop_back();
	
	q.push_back(make_pair(sx, sy)); dis[sx][sy] = 0;
	int rnt = -1, M = -1;
	
	while(!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop_front();
		
		if(mp[x][y] == '1') rnt = max(rnt, dis[x][y]);
				
		for(register int i = 0; i < 4; i++) {
			int nx = x + fx[i], ny = y + fy[i];
			if(~dis[nx][ny] || nx < 1 || nx > n || ny < 1 || ny > m) continue; 
			if(mp[x][y] == mp[nx][ny]) {
				dis[nx][ny] = dis[x][y];
				q.push_front(make_pair(nx, ny));
			} else {
				dis[nx][ny] = dis[x][y] + 1;
				q.push_back(make_pair(nx, ny));
			}
		}
	} return rnt + 1;
}

inline void getans() {
	for(register int i = 1; i <= n; i++) 
		for(register int j = 1; j <= m; j++)
			ans = min(ans, calc(i, j));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
#endif
	n = read(); m = read(); ans = inf;
	
	for(register int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
	
	getans();

	printf("%d", ans);
	return 0;
}
/*
9 9
000010000
011101110
010010010
010101010
101010101
010101010
010010010
011101110
000010000
*/
