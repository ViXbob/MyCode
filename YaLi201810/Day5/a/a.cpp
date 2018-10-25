#include <bits/stdc++.h>
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 2e5 + 5;
const int LOG = 85;

int m;

LL maxr, opt[maxn], l[maxn], r[maxn];

struct SegmentTree {
	int tot, root;
	struct node {int ls, rs; bool rev; char s, tag;} t[maxn * LOG];
	
	inline void pushup(int p) {
		if(t[t[p].ls].s == 2 && t[t[p].rs].s == 2) t[p].s = 2;
		else if(t[t[p].ls].s != 0 || t[t[p].rs].s != 0) t[p].s = 1;
		else t[p].s = 0;
	}
	
	inline void rever(int p) {
		if(t[p].s == 2) t[p].s = 0;
		else if(t[p].s == 0) t[p].s = 2;
		if(t[p].tag != -1) t[p].tag ^= 1;
		else t[p].rev ^= 1;
	}
	
	inline void pushdown(int p, LL l, LL r) {
		if(t[p].tag != -1) {
			char o = t[p].tag;
			if(!t[p].ls) t[p].ls = ++tot;
			t[t[p].ls].s = o ? 2 : 0;
			t[t[p].ls].tag = o; t[t[p].ls].rev = 0;
			if(!t[p].rs) t[p].rs = ++tot;
			t[t[p].rs].s = o ? 2 : 0;
			t[t[p].rs].tag = o; t[t[p].rs].rev = 0;
			t[p].tag = -1;
		}
		if(t[p].rev) {
			if(!t[p].ls) t[p].ls = ++tot;
			rever(t[p].ls);
			if(!t[p].rs) t[p].rs = ++tot;
			rever(t[p].rs);
			t[p].rev = 0;
		}
	}
	
	inline void modify(LL l, LL r, LL ql, LL qr, int &p, int x, int T) {
		if(!p) t[p = ++tot].tag = - 1;
		if(ql == l && qr == r) {
			if(T) t[p].tag = x, t[p].s = x ? 2 : 0, t[p].rev = 0;
			else rever(p); return;
		} pushdown(p, l, r);
		if(qr <= mid) modify(l, mid, ql, qr, t[p].ls, x, T);
		else if(ql > mid) modify(mid + 1, r, ql, qr, t[p].rs, x, T);
		else modify(l, mid, ql, mid, t[p].ls, x, T), modify(mid + 1, r, mid + 1, qr, t[p].rs, x, T);
		pushup(p);
	}
	
	inline bool check() {return t[root].s == 2;}
	
	inline LL query(LL l, LL r, int &p) {
		if(!p) t[p = ++tot].tag = -1;
		if(t[p].s == 0) return l;
		pushdown(p, l, r);
		if(t[t[p].ls].s != 2) return query(l, mid, t[p].ls);
		else return query(mid + 1, r, t[p].rs);
		pushup(p);
	}
} T;

inline LL read() {
	char ch = getchar(); LL u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	
	m = read();
	
	for(register int i = 1; i <= m; i++) {
		opt[i] = read(); l[i] = read(); r[i] = read();
		maxr = max(maxr, r[i]);
	}
	
	for(int i = 1; i <= m; i++) {
		if(opt[i] == 1) T.modify(1, maxr, l[i], r[i], T.root, 1, 1);
		else if(opt[i] == 2) T.modify(1, maxr, l[i], r[i], T.root, 0, 1);
		else T.modify(1, maxr, l[i], r[i], T.root, 1, 0);
		
		if(T.check()) printf("%lld\n", maxr + 1);
		else printf("%lld\n", T.query(1, maxr, T.root));
	}
	
	//cerr << T.tot;
	return 0;
}
