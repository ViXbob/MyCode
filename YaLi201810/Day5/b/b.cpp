#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 2e5 + 5;
const int LOG = 85;
const int inf = 1e9 + 7;

int n, m, k, A, B, a[maxn], b[maxn], w[maxn], vis[maxn], pos[maxn];
int S0[maxn], S1[maxn], S2[maxn], S3[maxn];

LL s0[maxn], s1[maxn], s2[maxn];

LL ans = 1ll << 60;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

struct SegmentTree {
	struct node {int size; LL s;} t[maxn << 2];

	inline void pushup(int p) {
		t[p].size = t[ls].size + t[rs].size;
		t[p].s = t[ls].s + t[rs].s;
	}

	inline void insert(int l, int r, int now, int p, int s, int x) {
		if(l == r) {
			t[p].size += s;
			t[p].s += x; return;
		}
		if(now <= mid) insert(l, mid, now, ls, s, x);
		else insert(mid + 1, r, now, rs, s, x);
		pushup(p);
	}

	inline LL query(int l, int r, int k, int p) {
        if(k <= 0) return 0;
		if(l == r) return t[p].s / t[p].size * k;
		//if(k == t[p].size) return t[p].s;
		if(k <= t[ls].size) return query(l, mid, k, ls);
		else return t[ls].s + query(mid + 1, r, k - t[ls].size, rs);
	}
} T;

int main() {
#ifndef ONLINE_JUDGE
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	n = read(); m = read(); k = read();

	for(register int i = 1; i <= n; i++) w[i] = pos[i] = read();

	A = read();
	for(register int i = 1; i <= A; i++) vis[a[i] = read()] += 1;

	B = read();
	for(register int i = 1; i <= B; i++) vis[b[i] = read()] += 2;

	if(A < k || B < k) {cout << -1; return 0;}

	for(register int i = 1; i <= n; i++)
		if(vis[i] == 3) S0[++S0[0]] = w[i];
		else if(vis[i] == 1) S1[++S1[0]] = w[i];
		else if(vis[i] == 2) S2[++S2[0]] = w[i];
		else S3[++S3[0]] = w[i];

	sort(pos + 1, pos + 1 + n);
	pos[0] = unique(pos + 1, pos + 1 + n) - pos - 1;
	sort(S0 + 1, S0 + 1 + S0[0]);
	sort(S1 + 1, S1 + 1 + S1[0]);
	sort(S2 + 1, S2 + 1 + S2[0]);

	for(register int i = 1; i <= n; i++) {
		if(i <= S0[0]) s0[i] = s0[i - 1] + S0[i];
		if(i <= S1[0]) s1[i] = s1[i - 1] + S1[i];
		if(i <= S2[0]) s2[i] = s2[i - 1] + S2[i];
	}

	int L0 = 0, R1 = k, R2 = k;

	if(S1[0] < R1) {
		L0 += (R1 - S1[0]);
		R2 -= (R1 - S1[0]);
		R1 -= (R1 - S1[0]);
	}

	if(S2[0] < R2) {
		L0 += (R2 - S2[0]);
		R1 -= (R2 - S2[0]);
		R2 -= (R2 - S2[0]);
	}

	for(register int i = L0 + 1; i <= S0[0]; i++) {
		int o = lower_bound(pos + 1, pos + 1 + pos[0], S0[i]) - pos;
		T.insert(1, pos[0], o, 1, 1, pos[o]);
	}

	for(register int i = R1 + 1; i <= S1[0]; i++) {
		int o = lower_bound(pos + 1, pos + 1 + pos[0], S1[i]) - pos;
		T.insert(1, pos[0], o, 1, 1, pos[o]);
	}

	for(register int i = R2 + 1; i <= S2[0]; i++) {
		int o = lower_bound(pos + 1, pos + 1 + pos[0], S2[i]) - pos;
		T.insert(1, pos[0], o, 1, 1, pos[o]);
	}

	for(register int i = 1; i <= S3[0]; i++) {
		int o = lower_bound(pos + 1, pos + 1 + pos[0], S3[i]) - pos;
		T.insert(1, pos[0], o, 1, 1, pos[o]);
	}
	
	//cout << n << " " << S0[0] << " " << m << endl;
	
	//cout << T.t[1].size << " " << T.t[1].s << endl;

	while(L0 <= S0[0] && L0 <= m) {
		int res = m - 2 * k + L0, o = 0;
		if(L0 >= k) ans = min(ans, s0[L0] + T.query(1, pos[0], m - L0, 1));
		else if(res >= 0)
			ans = min(ans, s0[L0] + s1[k - L0] + s2[k - L0] + T.query(1, pos[0], res, 1));
		if(L0 < S0[0]) {
			o = lower_bound(pos + 1, pos + 1 + pos[0], S0[++L0]) - pos;
			T.insert(1, pos[0], o, 1, -1, -pos[o]);
		} else L0++;
		if(R1 > 0) {
			o = lower_bound(pos + 1, pos + 1 + pos[0], S1[R1--]) - pos;
			T.insert(1, pos[0], o, 1, 1, pos[o]);
		}
		if(R2 > 0) {
			o = lower_bound(pos + 1, pos + 1 + pos[0], S2[R2--]) - pos;
			T.insert(1, pos[0], o, 1, 1, pos[o]);
		}
	}

	//cout << ans << " " << T.t[1].size;

	cout << ((ans == (1ll << 60)) ? -1 : ans);

	//cout << ans;

	return 0;
}
/*
4 3 2
3 2 2 1
2
1 2
2
1 3
*/

