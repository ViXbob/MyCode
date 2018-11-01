#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 3e2 + 5;
const int P = 1e9;

int n, f[maxn][maxn], ans;

char s[maxn];

inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int dfs(int l, int r) {
	if(l > r) return f[l][r] = 0;
	if(l == r) return f[l][r] = 1;
	if(f[l][r] != -1) return f[l][r];
	int rnt = 0;
	for(register int i = l + 2; i <= r; i++) {
		if(s[l + 1] != s[i - 1] || s[i] != s[r]) continue;
		rnt = pls(rnt, mul(dfs(l + 1, i - 1), dfs(i, r)));
	}
	return f[l][r] = rnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("prode.in", "r", stdin);
	freopen("prode.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);

	memset(f, 255, sizeof(f));

	dfs(1, n);
		
	cout << f[1][n];
	return 0;
}

