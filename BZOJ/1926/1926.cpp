#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 50 + 5;
const int maxm = 2500 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, m, T, s[2][maxn][maxn], f[maxm][maxn], g[maxn][maxn], h[maxn][maxn][2], ans;

char mp[maxn][maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

int main() {
	n = read(); m = read(); T = read();
	
	for(register int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
		
	for(register int i = 1; i <= n; i++) {
		memset(h, 0, sizeof(h));
		for(register int j = 1; j <= m; j++)
			for(register int k = 1; k <= min(m, T); k++) {
				h[j][k][0] = max(h[j - 1][k][0], h[j - 1][k - 1][1]) + (mp[i][j] == '0');
				h[j][k][1] = max(h[j - 1][k][1], h[j - 1][k - 1][0]) + (mp[i][j] == '1');
				g[i][k] = max(h[j][k][0], h[j][k][1]);
			}
		/*for(register int j = 1; j <= min(T, m); j++)
			cout << g[i][j] << " ";
		cout << endl;*/
	}
	
	for(register int i = 1; i <= T; i++)
		for(register int j = 1; j <= n; j++)
			for(register int k = 1; k <= min(i, m); k++)
				chkmax(ans, f[i][j] = max(f[i][j], f[i - k][j - 1] + g[j][k]));
	
	cout << ans;
	return 0;
}
