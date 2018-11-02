#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e3 + 5;
const int inf = 0x3f3f3f3f;

int f[2][maxn][maxn], n, a[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
	while(cin >> n) {
		memset(f, 0x3f, sizeof(f));
		//memset(g, 0x3f, sizeof(g));
		for(register int i = 1; i <= n; i++) a[i] = read();

		f[0][1][1] = 0;
		f[1][1][1] = 0;

		for(register int i = 1; i <= n; i++)
			for(register int j = 1; j <= min(i, n / 2); j++) {
				if(f[0][i][j] != inf) {
					if(a[i + 1] > a[i]) 
						f[0][i + 1][j + 1] = min(f[0][i + 1][j + 1], f[0][i][j]);
					if(a[i + 1] > f[0][i][j]) 
						f[1][i + 1][i - j + 1] = min(f[1][i + 1][i - j + 1], a[i]);
				}
				
				if(f[1][i][j] != inf) {
					if(a[i + 1] > a[i]) 
						f[1][i + 1][j + 1] = min(f[1][i + 1][j + 1], f[1][i][j]);
					if(a[i + 1] > f[1][i][j])
						f[0][i + 1][i - j + 1] = min(f[0][i + 1][i - j + 1], a[i]);
				}
			}

		if(f[0][n][n / 2] != inf || f[1][n][n / 2] != inf) puts("Yes!");
		else puts("No!");
	}
	return 0;
}

