#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 2e2 + 5;
const int inf = 0x3f3f3f3f;

int n, m, Q, G[maxn][maxn], a[maxn][maxn], pos[maxn * maxn], be[maxn][maxn], Bn, Bm, Id[maxn][maxn];
int X0, Y0, X, Y;

LL ans[(int)1e5 + 5], cnt[maxn * maxn], CurAns;

struct Query {
	int id, x0, y0, x, y;
	
	bool operator < (const Query &t) const {
		return be[x0][y0] == be[t.x0][t.y0] ? Id[x][y] < Id[t.x][t.y] : be[x][y] < be[t.x][t.y];
	}
} q[(int)1e5 + 5];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void add(int x, int y) {
	CurAns += cnt[a[x][y]] * 2 + 1;
	cnt[a[x][y]]++;
}

inline void del(int x, int y) {
	CurAns += 1 - cnt[a[x][y]] * 2;
	cnt[a[x][y]]--;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("vegetable.in", "r", stdin);
	freopen("vegetable.out", "w", stdout);
#endif
	
	n = read(); m = read(); Q = read();
	Bn = sqrt(n); Bm = sqrt(m);
	
	//Bn = Bm = n / pow(m, 1.0 / 4.0);
	
	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++) {
			pos[++pos[0]] = G[i][j] = read();
			be[i][j] = i / Bn * Bm + j / Bm;
		}
					
	sort(pos + 1, pos + 1 + pos[0]);
	pos[0] = unique(pos + 1, pos + 1 + pos[0]) - pos - 1;
	
	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++)
			a[i][j] = lower_bound(pos + 1, pos + 1 + pos[0], G[i][j]) - pos;

	for(register int i = 1; i <= Q; i++) {
		int x0 = read(), y0 = read(), x = read(), y = read();
		q[i] = (Query) {i, x0, y0, x, y};
	}
	
	sort(q + 1, q + 1 + Q);

	X0 = Y0 = 1; X = Y = 0;
		// Empty Martix or Empty Segment
	
	for(register int i = 1; i <= Q; i++) {
		while(X0 > q[i].x0) {
			X0--;
			for(register int y = Y0; y <= Y; y++) add(X0, y);
		}
		while(X < q[i].x) {
			X++;
			for(register int y = Y0; y <= Y; y++) add(X, y);
		}
		while(Y0 > q[i].y0) {
			Y0--;
			for(register int x = X0; x <= X; x++) add(x, Y0);
		}
		while(Y < q[i].y) {
			Y++;
			for(register int x = X0; x <= X; x++) add(x, Y);
		}
		
		while(X0 < q[i].x0) {
			for(register int y = Y0; y <= Y; y++) del(X0, y);
			X0++;
		}
		while(X > q[i].x) {
			for(register int y = Y0; y <= Y; y++) del(X, y);
			X--;
		}
		while(Y0 < q[i].y0) {
			for(register int x = X0; x <= X; x++) del(x, Y0);
			Y0++;
		}
		while(Y > q[i].y) {
			for(register int x = X0; x <= X; x++) del(x, Y);
			Y--;
		} ans[q[i].id] = CurAns;
	}

	for(register int i = 1; i <= Q; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
/*
3 4 8
1 3 2 1
1 3 2 4
1 2 3 4
1 1 2 2
1 1 2 1
1 1 3 4
1 1 1 1
2 2 3 3
2 2 3 4
1 1 3 3
2 4 3 4
*/
