#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 5e3 + 5;

int n, P, f[2][maxn], U, ans;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

int main() {
	n = read(); P = read();

	f[1][1] = 1;

	for(register int i = 2; i <= n; i++) {
		int t = i & 1, t0 = t ^ 1;

		memset(f[t], 0, sizeof(f[t]));

		//cout << f[t0][i] << endl;
		//cout << f[t][0] << endl;

		for(register int j = 1; j <= i; j++)
			//for(register int k = 1; k <= j - 1; k++)
			//  f[t][j] = pls(f[t][j], f[t0][i - k]);
			//cout << (f[t][j] = pls(f[t][j - 1], f[t0][i - (j - 1)])) << " ";
			f[t][j] = pls(f[t][j - 1], f[t0][i - j + 1]);
			//cout << endl;
	}

	//cout << f[n & 1][1] << endl;

	for(register int i = 1; i <= n; i++)
		ans = pls(ans, f[n & 1][i]);

	//cout << f[n & 1][n] << endl;
	cout << mul(ans, 2);
	return 0;
}

