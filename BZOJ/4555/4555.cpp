#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 4e5 + 5;
const int P = 998244353;
const int G = 3;

int n, a[maxn], b[maxn], fac[maxn], ifac[maxn], ans;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int mul(int x, int y, int z) {return mul(x, mul(y, z));}

inline int ksm(int x, int k) {
	int cnt = 1;
	while(k) {
		if(k & 1) cnt = mul(cnt, x);
		x = mul(x, x); k >>= 1;
	} return cnt;
}

inline int inv(int x) {return ksm(x, P - 2);}

namespace NTT {
	int F[maxn], H[maxn], rev[maxn], s, l;
	
	inline void dft(int *a, int n, int f) {
		for(register int i = 0; i < n; i++)
			if(i < rev[i]) swap(a[i], a[rev[i]]);
		for(register int i = 1; i < n; i <<= 1) {
			int Wn = ksm(f, (P - 1) / (i << 1));
			for(register int j = 0; j < n; j += (i << 1)) {
				int w = 1;
				for(register int k = 0; k < i; k++, w = mul(w, Wn)) {
					int A1 = a[j + k], A2 = mul(a[i + j + k], w);
					a[j + k] = pls(A1, A2); a[i + j + k] = pls(A1, -A2);
				}
			}
		}
	}
	
	inline void conv(int *a, int *b, int n, int m, int *h) {
		s = 2; l = 1;
		while(s <= n + m) s <<= 1, l++;
		for(register int i = 0; i < s; i++)
			rev[i] = rev[i >> 1] >> 1 | (i & 1) << (l - 1);
		memset(F, 0, sizeof(F));
		memset(H, 0, sizeof(H));
		for(register int i = 0; i <= n; i++) F[i] = a[i];
		for(register int i = 0; i <= m; i++) H[i] = b[i];
		dft(F, s, G); dft(H, s, G);
		for(register int i = 0; i < s; i++) h[i] = mul(F[i], H[i]);
		dft(h, s, ksm(G, P - 2)); int inv = ksm(s, P - 2);
		for(register int i = 0; i < s; i++) h[i] = mul(h[i], inv);
	}
}

int main() {
	n = read();

	fac[0] = ifac[0] = 1;
	for(register int i = 1; i <= n; i++)
		fac[i] = mul(fac[i - 1], i), ifac[i] = inv(fac[i]);	
	
	a[0] = b[0] = 1; a[1] = P - 1; b[1] = n + 1;
	for(register int i = 2; i <= n; i++) a[i] = ((i & 1 ? -1 : 1) * ifac[i] + P) % P;
	for(register int i = 2; i <= n; i++) b[i] = mul(pls(ksm(i, n + 1), -1), ifac[i], inv(i - 1));
	
	NTT :: conv(a, b, n, n, a);
	
	for(register int i = 0, w = 1; i <= n; i++, w = pls(w, w))
		ans = pls(ans, mul(fac[i], w, a[i]));
		
	cout << ans;
	return 0;
}
