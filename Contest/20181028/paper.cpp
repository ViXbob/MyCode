#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 3e6 + 5;
const int inf = 0x3f3f3f3f;

int n, s, cur, lst[maxn], nxt[maxn], a[maxn];
int dex[maxn], idex[maxn << 3];

LL ans, cnt;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

namespace SegmentTree {
	struct Node {
		int l, r;
		Node (int L = 0, int R = 0) {l = L; r = R;}
		Node operator & (const Node &t) const {
			return Node(max(l, t.l), min(r, t.r));
		}
		bool operator & (const int &t) const {
			return t >= l && t <= r;
		}
	} T[maxn << 3];
	
	inline Node calc(int p1, int p2) {
		if(p1 < p2) return Node(p1 + p2 + 2 >> 1, inf);
		if(p1 > p2) return Node(0, p1 + p2 - 1 >> 1);
		return Node(inf, 0);
	}
	
	inline void build(int l, int r, int p) {
		if(l == r) {
			int pos = (r - 1) % n + 1;
			if(r == pos) dex[pos] = p;
			idex[p] = pos;
			T[p] = calc(a[pos], a[nxt[pos]]); return;
		}
		build(l, mid, ls); build(mid + 1, r, rs);
		T[p] = T[ls] & T[rs];
	}
	
	inline void remove(int l, int r, int pos, int p) {
		if(l == r) {T[p] = Node(0, inf); return;}
		if(pos <= mid) remove(l, mid, pos, ls);
		else remove(mid + 1, r, pos, rs);
		T[p] = T[ls] & T[rs];
	}
	
	inline void modify(int l, int r, int pos, int p) {
		if(l == r) {
			int pos = (r - 1) % n + 1;
			T[p] = calc(a[pos], a[nxt[pos]]);
			return;
		}
		if(pos <= mid) modify(l, mid, pos, ls);
		else modify(mid + 1, r, pos, rs);
		T[p] = T[ls] & T[rs];
	}
	
	inline int bound(int cur, int pos) {
		cur = dex[cur];
		
		Node now = T[cur];
		while(now & pos) {
			if(!(cur & 1))
				now = now & T[cur ^ 1];
			cur >>= 1;
		}
		
		if(idex[cur]) return idex[cur];
		
		cur = cur << 1 | 1;
		
		while(!idex[cur]) {
			if(T[cur << 1] & pos)
				cur = cur << 1 | 1;
			else cur = cur << 1;
		} return idex[cur];
	}
}

using namespace SegmentTree;

int main() {
#ifndef ONLEIN_JDUGE
	freopen("paper.in", "r", stdin);
	freopen("paper.out", "w", stdout);
#endif
	n = read(); s = read(); cur = 1;
	
	for(register int i = 1; i <= n; i++) a[i] = read();
	for(register int i = 1; i <= n; i++) nxt[i] = i % n + 1;
	for(register int i = 1; i <= n; i++) lst[nxt[i]] = i;
	
	build(1, n << 1, 1);
	
	for(register int i = 1; i <= n; i++) {
		int pos = bound(cur, s);
		
		remove(1, n << 1, pos, 1);
		remove(1, n << 1, pos + n, 1);
		
		nxt[lst[pos]] = nxt[pos];
		lst[nxt[pos]] = lst[pos];
		
		modify(1, n << 1, lst[pos], 1);
		modify(1, n << 1, lst[pos] + n, 1);
		
		ans += abs(s - a[pos]);
		s = a[pos]; cur = pos;
	}
	
	cout << ans;
	return 0;
}
/*
5 1
2 3 1 4 5
*/
