#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, ans = 1;

pair<int, int> a[maxn];

struct BIT {
	int C[maxn + 5];
	inline void modify(int p, int x) {
		for(register int i = p; i <= n; i += (-i & i)) C[i] += x;
	}
	inline int sum(int p, int rnt = 0) {
		for(register int i = p; i; i -= (-i & i)) rnt += C[i];
		return rnt;
	}
} T;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

int main() {
#ifndef ONLINE_JUDGE
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	n = read();
	
	for(register int i = 1; i <= n; i++) 
		a[i] = make_pair(read(), i);
	
	sort(a + 1, a + 1 + n);
	
	for(register int i = 1; i <= n; i++) {
		T.modify(a[i].second, 1);
		ans = max(ans, i - T.sum(i));
	}
		
	cout << ans;
	return 0;
}
/*
5
5 2 8 3 1
*/
