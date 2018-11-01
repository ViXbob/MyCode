#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 5e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, vis[maxn];

LL v[maxn], ans, cnt, a[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

int main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	n = read();
	
	for(register int i = 1; i <= n; i++) 
		a[i] = (v[i] = read()) - v[i - 1];
		
	a[n + 1] = -v[n];
	
	sort(a + 1, a + 2 + n);
	
	for(register int i = n + 1; i >= 1; i--)
		a[i] += a[i + 1], ans += a[i];
	//cerr << " " << cnt;
	
	cout << ans;
	return 0;
}
