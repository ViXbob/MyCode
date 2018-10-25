#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e3 + 5;

int n, q;

LL ans = 0;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

struct SegmentTree {
	struct node {LL tag;} t[maxn << 2];
	
	inline void pushdown(int l, int r, int p) {
		if(t[p].tag != 0) {
			LL o = t[p].tag;
			t[ls].tag += o;
			t[rs].tag += o;
			t[p].tag = 0;
		}
	}
	
	inline void modify(int l, int r, int ql, int qr, int p, int x) {
		if(ql == l && qr == r) {
			t[p].tag += x; return;
		} pushdown(l, r, p);
		if(qr <= mid) modify(l, mid, ql, qr, ls, x);
		else if(ql > mid) modify(mid + 1, r, ql, qr, rs, x);
		else modify(l, mid, ql, mid, ls, x), modify(mid + 1, r, mid + 1, qr, rs, x);
	}
	
	inline LL query(int l, int r, int ql, int qr, int p) {
		if(ql == l && qr == r) return t[p].tag;
		pushdown(l, r, p);
		if(qr <= mid) return query(l, mid, ql, qr, ls);
		else if(ql > mid) return query(mid + 1, r, ql, qr, rs);
		else return (query(l, mid, ql, mid, ls) + query(mid + 1, r, mid + 1, qr, rs));
	}
} TR[maxn], TSlope[maxn * 2];

int main() {
	freopen("u.in", "r", stdin);
	freopen("u.out", "w", stdout);
	
	n = read(); q = read();
	
	while(q--) {
		int x = read(), y = read(), L = read(), s = read();
		TR[y].modify(1, n, x, min(x + L - 1, n), 1, s);
		if(y < n)
			TSlope[x - (y + 1) + n].modify(1, n, y + 1, min(y + L, n), 1, -s);
	}
	
	for(register int x = 1; x <= n; x++) {
		LL S = 0;
		for(register int y = 1; y <= n; y++) {
			S += TR[y].query(1, n, x, x, 1);
			S += TSlope[x - y + n].query(1, n, y, y, 1);
			ans ^= S;
		}
	} cout << ans << endl;
	return 0;
}
