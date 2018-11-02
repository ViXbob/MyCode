#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, D, ans = inf, L, R, pos, maxv;

pair<int, int> a[maxn];
deque<int> Mxq, Mnq;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

inline bool cmp(int x, int y, bool is) {
	return is ? (x >= y) : (x <= y);
}

inline void push(deque<int> &q, int x, bool is) {
	while(!q.empty() && cmp(a[x].second, a[q.back()].second, is))
		q.pop_back();
	q.push_back(x);
}

inline void pop(deque<int> &q, int Lim) {
	while(!q.empty() && q.front() < Lim)
		q.pop_front();
}

inline void Add(int pos) {
	//while(pos <= n && a[pos].first <= Lim)
	push(Mxq, pos, true); push(Mnq, pos, false);
}

int main() {
	n = read(); D = read();

	for(register int i = 1; i <= n; i++) {
		int x = read(), y = read();
		a[i] = make_pair(x, y); maxv = max(x, maxv);
	}

	sort(a + 1, a + 1 + n);

	L = 1; R = 1; pos = 1;
	Add(R);

	while(R <= n) {
		while((Mxq.empty() || a[Mxq.front()].second - a[Mnq.front()].second < D) && R <= n)
			R++, Add(R);
		if(R > n) break;
		while(!Mxq.empty() && a[Mxq.front()].second - a[Mnq.front()].second >= D)
			ans = min(ans, a[R].first - a[L].first), L++, pop(Mxq, L), pop(Mnq, L);
	}

	cout << (ans == inf ? -1 : ans);
	return 0;
}

