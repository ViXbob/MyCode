#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 4e2 + 5;
const int maxm = 5e4 + 5;

int n, m, u[maxm], v[maxm], ans, f[maxn];

bitset<maxn> g[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	n = read(); m = read();
	
	for(register int i = 1; i <= m; ++i) u[i] = read(), v[i] = read();
	
	for(register int i = 1; i <= n; ++i) {
		g[i][i] = 1;
		for(register int j = m; j >= 1; --j) {
			if(g[i][u[j]] && g[i][v[j]]) {f[i] = 1; break;}
			if(g[i][u[j]] || g[i][v[j]]) g[i][u[j]] = g[i][v[j]] = 1;
		}
	}
	
	for(register int i = 1; i <= n; i++)
		for(register int j = i + 1; j <= n && !f[i]; j++)
			if(!f[j] && (g[i] & g[j]).none()) ans++;
			
	cout << ans;
	return 0;
}
