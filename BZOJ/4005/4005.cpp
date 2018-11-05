#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 3e6 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int fac[maxn], ifac[maxn], n, m, M, ans, x, y;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

inline int ksm(int x, int k) {
	int cnt = 1;
	while(k) {
		if(k & 1) cnt = mul(cnt, x);
		x = mul(x, x); k >>= 1;
	} return cnt;
}

inline int calc(int x, int y) {return (x < 0 || y < 0) ? 0 : mul(fac[x + y], mul(ifac[x], ifac[y]));}
inline void TurnOver1(int &x, int &y) {swap(x, y); x--; y++;}
inline void TurnOver2(int &x, int &y) {swap(x, y); x += (m + 2); y -= (m + 2);}

int main() {
	n = read(); m = read(); M = 3 * max(n, m) + 1;
	
	fac[0] = 1; //ifac[0] = 1;
	for(register int i = 1; i <= M; i++) fac[i] = mul(fac[i - 1], i);
	ifac[M] = ksm(fac[M], P - 2);
	for(register int i = M - 1; i >= 0; i--) ifac[i] = mul(ifac[i + 1], i + 1);
	
	x = n + m + 1; y = n;
	ans = calc(x, y);
	while(x >= 0 && y >= 0) {
		TurnOver1(x, y); ans = pls(ans, -calc(x, y));
		TurnOver2(x, y); ans = pls(ans, calc(x, y));
	}
	x = n + m + 1; y = n;
	while(x >= 0 && y >= 0) {
		TurnOver2(x, y); ans = pls(ans, -calc(x, y));
		TurnOver1(x, y); ans = pls(ans, calc(x, y));
	}
	cout << ans;
	return 0;
}
