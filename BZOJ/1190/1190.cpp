#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;
const int maxv = 1e3;

int n, w, a, b, x, f[35][maxn], ans;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

int main() {
	while(true) {
		n = read(); w = read(); ans = 0;
		if(n == -1 || w == -1) break;
		memset(f, 0, sizeof(f));
		for(register int i = 1; i <= n; i++) {
			a = read(); x = read(); b = 0;
			while(!(a & 1)) b++, a >>= 1;
			for(register int j = maxv; j >= a; j--)
				f[b][j] = max(f[b][j], f[b][j - a] + x);
		}
		
		//for(register int i=1; i <= min(1000, w); i++)
		//	chkmax(ans, f[0][i]);
		
		for(register int i = 1; i <= 30; i++)
			for(register int j = min(maxv, w >> i); j >= 0; j--) 
				for(register int k = 0; k <= j; k++) 
                    chkmax(ans, f[i][j] = max(f[i][j], f[i][j - k] + f[i - 1][min((k << 1) + ((w >> (i - 1)) & 1), maxv)]));
		cout << ans << endl;
	}
	return 0;
}
