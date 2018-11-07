#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2500;
const int inf = 0x3f3f3f3f;
const int P = 2333;

int T, f[maxn][maxn], fac[maxn], ifac[maxn];

LL n, k;

inline LL read() {
	char ch = getchar(); LL u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int mul(int a, int b, int c) {return mul(a, mul(b, c));}

inline int ksm(int x, int k) {
	int cnt = 1;
	while(k) {
		if(k & 1) cnt = mul(cnt, x);
		x = mul(x, x); k >>= 1;
	} return cnt;
}

inline int C(int n, int m) {return n < m ? 0 : mul(fac[n], ifac[n - m], ifac[m]);}

inline int Lucas(LL n, LL m) {
	if(m == 0) return 1;
	return mul(C(n % P, m % P), Lucas(n / P, m / P));
}

inline int F(LL n, LL k) {
	if(k < 0) return 0;
	if(n < P && k < P) return f[n][k];
	return pls(mul(F(n % P, P - 1), F(n / P, k / P - 1)), mul(f[n % P][k % P], Lucas(n / P, k / P)));
}

int main() {
	T = read();

	fac[0] = ifac[0] = 1;
	for(register int i = 1; i < P; i++) fac[i] = mul(fac[i - 1], i);
	ifac[P - 1] = ksm(fac[P - 1], P - 2);
	for(register int i = P - 2; i >= 1; i--) ifac[i] = mul(ifac[i + 1], i + 1);

	for(register int i = 0; i < P; i++) {
		f[i][0] = 1;
		for(register int k = 1; k < P; k++)
			f[i][k] = pls(f[i][k - 1], C(i, k));
	}

	//cout << f[5][5];

	//cout << endl << fac[5] << " " << ifac[P - 1];

	//cout << endl << C(10, 2);

	while(T--) {
		n = read(); k = read();
		printf("%d\n", F(n, k));
	}
	return 0;
}

