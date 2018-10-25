#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2505;
const int P = 1e9 + 7;

int n, pos[maxn][maxn], m = 2500, con[maxn], ans;

bool vis[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
inline int pls(int x, int y, int z) {return pls(x, pls(y, z));}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int mul(int x, int y, int z) {return mul(x, mul(y, z));}
inline int dec(int x, int y) {x -= y; return x < 0 ? x + P : x;}

struct BIT {
	int C[maxn];
	inline void init() {memset(C, 0, sizeof(C));}
	inline void modify(int p, int x) {while(p <= m) {C[p] = pls(C[p], x); p += (-p & p);}}
	inline int query(int p) {int rnt = 0; while(p) {rnt = pls(rnt, C[p]); p -= (-p & p);} return rnt;}
	inline int sum(int l, int r) {return dec(query(r), query(l - 1));}
} T, S;

inline void update(int now) {
	if(vis[now]) return;
	vis[now] = true;
	T.modify(now, 1); S.modify(now, now);
}

inline int getit(int L0, int R0, int L1, int R1) {
	return dec(mul(S.sum(L1, R1), T.sum(L0, R0)), mul(S.sum(L0, R0), T.sum(L1, R1)));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("rectangle.in", "r", stdin);
	freopen("rectangle.out", "w", stdout);
#endif
	n = read();

	for(register int i = 1; i <= n; i++) {
		int x = read(), y = read();
		pos[x][++con[x]] = y;
	}

	for(register int i = 1; i <= m; i++)
		sort(pos[i] + 1, pos[i] + 1 + con[i]), pos[i][con[i] + 1] = m + 1;

	for(register int l = 1; l <= m; l++) if(con[l]) {
		T.init(); S.init();
		for(register int y = 1; y <= m; y++) vis[y] = false;
		for(register int i = 1; i <= con[l]; i++) update(pos[l][i]);
		for(register int r = l + 1; r <= m; r++) if(con[r]) {
			for(register int i = 1; i <= con[r]; i++) update(pos[r][i]);
			int Lt = 1, Rt = 1, cur = max(pos[l][1], pos[r][1]);

			while(pos[l][Lt + 1] <= cur) ++Lt;
			while(pos[r][Rt + 1] <= cur) ++Rt;

			while(Lt <= con[l] && Rt <= con[r]) {
				int nxt = min(pos[l][Lt + 1], pos[r][Rt + 1]), L = min(pos[l][Lt], pos[r][Rt]);
				ans = pls(ans, mul(getit(1, L, cur, nxt - 1), r - l));

				cur = nxt;
				if(pos[l][Lt + 1] <= cur) ++Lt;
				if(pos[r][Rt + 1] <= cur) ++Rt;
			}
		}
	}

	cout << ans;

	return 0;
}
/*
5
1 2
3 1
2 7
4 4
5 1
*/

