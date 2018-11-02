#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;

int a, b, n, mx[maxn][maxn], mn[maxn][maxn], mp[maxn][maxn], ans = inf;

inline bool cmp(int x, int y, int is) {return is ? (x >= y) : (x <= y);}

struct Deque {
	deque<int> q; int id;

	inline void push(int x, bool is) {
		while(!q.empty() && cmp(mp[id][x], mp[id][q.back()], is))
            q.pop_back();
		q.push_back(x);
	}

	inline void pop(int Lim) {
		while(!q.empty() && q.front() <= Lim)
            q.pop_front();
	}

	inline int Front() {return q.front();}
	inline int Back() {return q.back();}
	inline int Wget() {return mp[id][q.front()];}
	inline void clear() {while(!q.empty()) q.pop_back();}
} Q[maxn], zQ;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void init(bool is) {
	for(register int i = 1; i <= a; i++) Q[i].clear();

	for(register int i = 1; i <= a; i++)
		for(register int j = 1; j <= n; j++) Q[i].push(j, is);
}

inline void pushit(int x, int is) {
	while(!zQ.q.empty() && cmp(Q[x].Wget(), Q[zQ.Back()].Wget(), is))
		zQ.q.pop_back();
	zQ.q.push_back(x);
}

inline int getans(int id, bool is) {
    zQ.clear();
	for(register int i = 1; i <= n; i++)
		pushit(i, is);

	if(is) mx[1][id] = max(mx[1][id], Q[zQ.Front()].Wget());
	else mn[1][id] = min(mn[1][id], Q[zQ.Front()].Wget());

	for(register int i = 1; i + n - 1 < a; i++) {
		zQ.pop(i); pushit(i + n, is);
		if(is) mx[i + 1][id] = max(mx[i + 1][id], Q[zQ.Front()].Wget());
		else mn[i + 1][id] = min(mn[i + 1][id], Q[zQ.Front()].Wget());
	}
}

int main() {
	a = read(); b = read(); n = read();

	memset(mx, ~0x3f, sizeof(mx));
	memset(mn,  0x3f, sizeof(mn));

	for(register int i = 1; i <= a; i++) {
		for(register int j = 1; j <= b; j++) mp[i][j] = read();
		Q[i].id = i;
	}

	init(true); getans(1, true);
	for(register int j = 1; j + n - 1 < b; j++) {
		for(register int k = 1; k <= a; k++) {
			Q[k].pop(j); Q[k].push(j + n, true);
		} getans(j + 1, true);
	}

	init(false); getans(1, false);
	for(register int j = 1; j + n - 1 < b; j++) {
		for(register int k = 1; k <= a; k++) {
			Q[k].pop(j); Q[k].push(j + n, false);
		} getans(j + 1, false);
	}

	for(register int i = 1; i + n - 1 <= a; i++)
		for(register int j = 1; j + n - 1 <= b; j++)
			ans = min(ans, mx[i][j] - mn[i][j]);

	cout << ans;
	return 0;
}
/*
5 4 2
1 2 5 6
0 17 16 0
16 17 2 1
2 10 2 1
1 2 2 2
*/

