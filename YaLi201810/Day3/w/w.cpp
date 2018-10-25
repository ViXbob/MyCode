#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

int n, head[maxn], cnt = 1, judge = 1;

LL ans = 0;

struct Graph {int to, nt, is;} e[maxn << 1];
struct Node {
	int odd, len;
	Node (int O = 0, int L = 0) {odd = O; len = L;}
	Node operator + (const Node &t) const {return Node(odd + t.odd, len + t.len);}
	bool operator < (const Node &t) const {return odd < t.odd || (odd == t.odd && len < t.len);}
} f[maxn][2];

const Node deltaO = (Node) {1, 0};
const Node deltaL = (Node) {0, 1};
const Node oo = (Node) {inf, inf};

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void ini(int x, int y, int is) {e[++cnt] = (Graph){y, head[x], is}; head[x] = cnt;}

inline void dfs(int now, int fa, int Ty) {
	Node f0 = Node(0, 0), f1 = oo;
	for(register int i = head[now]; i; i = e[i].nt) {
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v, now, e[i].is);
		Node tmp0, tmp1;
		tmp0 = min(f0 + f[v][0], f1 + f[v][1]);
		tmp1 = min(f0 + f[v][1], f1 + f[v][0]);
		f0 = tmp0; f1 = tmp1;
	}
	
	if(Ty == 2 || Ty == 1)
		f[now][1] = min(f0 + deltaO + deltaL, f1 + deltaL);
	else f[now][1] = oo;
	if(Ty == 2 || Ty == 0)
		f[now][0] = min(f0, f1 + deltaO);
	else f[now][0] = oo;
}

int main() {
#ifndef ONLINE_JUDGE
	//freopen("w.in", "r", stdin);
	//freopen("w.out", "w", stdout);
#endif
	n = read();
	
	for(register int i = 1; i < n; i++) {
		int x = read(), y = read(), c = read(), d = read(), is = 0;
		if(d != 2) is = c != d;
		else is = d;
		ini(x, y, is); ini(y, x, is);
	}
	
	dfs(1, 0, 0);
	
	cout << f[1][0].odd / 2 << " " << f[1][0].len;
	return 0;
}
/*
7
1 2 0 1
2 3 0 0
3 4 1 2
4 5 0 0
5 6 0 1
6 7 0 1
*/
