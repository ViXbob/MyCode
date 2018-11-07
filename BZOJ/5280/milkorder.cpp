#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, m, in[maxn], con, p, ans[maxn], tot;

vector<int> e[maxn], G[maxn];
queue<int> q;
priority_queue <int,vector<int>,greater<int> > Gq;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline void ini(int x, int y) {G[x].push_back(y);}

inline void build(int p) {
	memset(in, 0, sizeof(in));

	for(register int i = 1; i <= n; i++) G[i].clear();

	for(register int i = 1; i <= p; i++) {
		for(register int j = 0; j + 1 < e[i].size(); j++) {
			int now = e[i][j], v = e[i][j + 1];
			G[now].push_back(v); in[v]++;
		}
	}
}

inline bool check(int mid) {
    build(mid);

	for(register int i = 1; i <= n; i++)
		if(!in[i]) q.push(i);

	while(!q.empty()) {
		int now = q.front(); q.pop();
		for(register int i = 0; i < G[now].size(); i++) {
			int v = G[now][i];
			in[v]--; if(in[v] == 0) q.push(v);
		}
	}

	for(register int i = 1; i <= n; i++)
		if(in[i] > 0) return false;
	return true;
}

inline void Topsort() {
	for(register int i = 1; i <= n; i++)
		if(!in[i]) Gq.push(i);

	while(!Gq.empty()) {
		int now = Gq.top(); ans[++tot] = now; Gq.pop();
		for(register int i = 0; i < G[now].size(); i++) {
			int v = G[now][i];
			in[v]--; if(in[v] == 0) Gq.push(v);
		}
	}

	for(register int i = 1; i <= tot; i++)
		printf("%d ", ans[i]);
}

inline int Biniry(int l, int r) {
	int mid = (l + r) / 2, ans = 0;
	while(l <= r) {
		mid = (l + r) / 2;
		if(check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	} return ans;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("milkorder.in", "r", stdin);
	freopen("milkorder.out", "w", stdout);
#endif	
	n = read(); m = read();

	for(register int i = 1; i <= m; i++) {
		int All = read();
		for(register int j = 1; j <= All; j++) e[i].push_back(read());
	}

	int p = Biniry(1, m);

	build(p);

	Topsort();
	return 0;
}
/*
4 3
3 1 2 3
2 4 2
3 3 4 1
*/

