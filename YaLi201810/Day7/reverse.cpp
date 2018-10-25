#include <bits/stdc++.h>
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int n, S, m, k, dis[maxn], ban[maxn], pos, tot, vis[maxn];
deque<int> q;
vector<pair<int, int> > G[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void BFS(int S) {
	memset(dis, 0x3f, sizeof(dis));
	q.push_back(S); dis[S] = 0;
	
	while(!q.empty()) {
		int now = q.front(); q.pop_front();
		for(register int i = 0; i < G[now].size(); i++) {
			int v = G[now][i].first, w = G[now][i].second;
			if(dis[v] == inf) {
				dis[v] = dis[now] + w;
				if(w) q.push_back(v);
				else q.push_front(v);
			}
		}
	}
}

struct Segment {
	int root;
	struct node {int ls, rs;} t[maxn];
	
	inline void Prep(int l, int r, int &p, int ty) {
		p = ++tot;
		if(l == r) {
			if(ban[r]) return;
			if((r & 1) == ty) {
				G[p].push_back(make_pair(r, 1));
			} return;
		}
		Prep(l, mid, t[p].ls, ty); Prep(mid + 1, r, t[p].rs, ty);
		G[p].push_back(make_pair(t[p].ls, 0));
		G[p].push_back(make_pair(t[p].rs, 0));
	}
	
	inline void Link(int l, int r, int ql, int qr, int p, int x) {
		if(ql == l && qr == r) {G[x].push_back(make_pair(p, 0)); return;}
		if(qr <= mid) Link(l, mid, ql, qr, t[p].ls, x);
		else if(ql > mid) Link(mid + 1, r, ql, qr, t[p].rs, x);
		else Link(l, mid, ql, mid, t[p].ls, x), Link(mid + 1, r, mid + 1, qr, t[p].rs, x);
	}
} odd, even;

int main() {
#ifndef ONLINE_JUDGE
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
#endif
	n = read(); k = read(); m = read(); S = read();
	
	for(register int i = 1; i <= m; i++) ban[read()] = 1;
	
	tot = n;
	odd.Prep(1, n, odd.root, 1); even.Prep(1, n, even.root, 0);
	
	for(register int i = 1; i <= n; i++) {
		int posl = max(1, i - k + 1);
		int posr = min(n, i + k - 1);
		
		int L = (posl + k - 1) - (i - posl);
		int R = (posr - k + 1) + (posr - i);
		
		if(L > R) swap(L, R);
				
		if((i + k - 1) & 1) odd.Link(1, n, L, R, odd.root, i);
		else even.Link(1, n, L, R, even.root, i);
	}
	
	BFS(S);
	
	for(register int i = 1; i <= n; i++)
		printf("%d ", dis[i] == inf ? -1 : dis[i]);
	
	return 0;
}
