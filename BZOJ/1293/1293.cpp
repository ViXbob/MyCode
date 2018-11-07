#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, cnt[100], num, tot, L, R, ans = inf, k;

pair<int, int> a[maxn * 10];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline void add(int col) {num += (++cnt[col] == 1);}
inline void del(int col) {num -= (--cnt[col] == 0);}

int main() {
	n = read(); k = read();
	
	for(register int i = 1; i <= k; i++) {
		int T = read();
		for(register int j = 1; j <= T; j++) {
			int x = read();
			a[++tot] = make_pair(x, i);
		}
	}
	
	sort(a + 1, a + 1 + n);
	
	L = 1; R = 1; add(a[R].second);

	while(R <= n) {
		while(num < k && R <= n) add(a[++R].second);
		if(R > n) break;
		while(num >= k && L <= R) ans = min(ans, a[R].first - a[L].first), del(a[L++].second);
	}

	cout << ans;
	return 0;
}
