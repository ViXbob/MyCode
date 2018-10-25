#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e3 + 5;

int n, q;

LL ans = 0, a[maxn][maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
	freopen("data.in", "r", stdin);
	freopen("std.out", "w", stdout);
	
	n = read(); q = read();
	
	while(q--) {
		int x = read(), y = read(), L = read(), s = read();
		for(register int i = x; i <= x + L - 1; i++)
			for(register int j = y; j <= i - x + y; j++)
				a[i][j] += s;
	}
	
	for(register int i = 1; i <= n; i++) {
		for(register int j = 1; j <= n; j++){
			//cout << a[i][j] << " ";
			ans ^= a[i][j];
		}
		//cout << endl;
	} cout << ans << endl;
	return 0;
}
