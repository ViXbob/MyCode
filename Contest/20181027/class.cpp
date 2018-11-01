#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 4e4 + 5;
const int P = 998244353;
const int G = 3;

int n, m, a[maxn], rfac[maxn], fac[maxn], ifac[maxn], sum[maxn];
int cnt[maxn], ans[maxn], tmp[maxn], rev[maxn], s, l, I[maxn], F[maxn], H[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int mul(int x, int y, int z) {return mul(x, mul(y, z));}
inline int dec(int x, int y) {x -= y; return x < 0 ? x + P : x;}

inline int pow(int x, int k) {
	int cnt = 1;
	while(k) {
		if(k & 1) cnt = mul(cnt, x);
		x = mul(x, x); k >>= 1;
	} return cnt;
}

inline void dft(int *a, int n, int f) {
	for(register int i = 0; i < n; i++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(register int i = 1; i < n; i <<= 1) {
		int Wn = pow(f, (P - 1) / (i << 1));
		for(register int j = 0; j < n; j += (i << 1)) {
			int w = 1;
			for(register int k = 0; k < i; k++, w = mul(w, Wn)) {
				int A1 = a[j + k], A2 = mul(a[i + j + k], w);
				a[j + k] = pls(A1, A2); a[i + j + k] = dec(A1, A2);
			}
		}
	}
}

inline void conv(int *a, int *b, int *adj) {
	memset(F, 0, sizeof(int) * s);
	memset(H, 0, sizeof(int) * s);
	for(register int i = 0; i <= n; i++) F[i] = a[i];
	for(register int i = 0; i <= n; i++) H[i] = b[i];
	dft(F, s, G); dft(H, s, G);
	for(register int i = 0; i < s; i++)
		F[i] = mul(F[i], H[i]);
	dft(F, s, pow(G, P - 2)); int inv = pow(s, P - 2);
	for(register int i = 0; i <= 2 * n; i++)
		adj[i] = mul(F[i], inv);
}

inline void ksm(int *a, int k, int n) {
	for(register int i = 0; i <= n; i++) I[i] = 0;
	I[0] = 1;
	while(k) {
		if(k & 1) conv(I, a, I);
		conv(a, a, a); k >>= 1;
	}
	for(register int i = 0; i <= n; i++) a[i] = I[i];
}

int main() {
#ifndef ONLINE_JUDGE
	//freopen("class.in", "r", stdin);
	//freopen("class.out", "w", stdout);
#endif
	fac[0] = 1; ifac[0] = 1;
	for(register int i = 1; i < maxn; i++)
		fac[i] = mul(fac[i - 1], i), ifac[i] = pow(fac[i], P - 2);

	n = read(); m = read();

	s = 2; l = 1; while(s <= 2 * n) s <<= 1, l++;
	for(register int i = 0; i < s; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));

	for(register int i = 1; i <= m; i++)
		cnt[a[i] = read()]++, sum[i] = sum[i - 1] + a[i];

	/*
	for(register int i = 0; i <= n; i++) a[i] = read();
	for(register int i = 0; i <= m; i++) tmp[i] = read();

	conv(a, tmp, a);

	for(register int i = 0; i <= 2 * n; i++)
		cout << a[i] << " ";
	return 0;
	*/

	sort(a + 1, a + 1 + m);
	m = unique(a + 1, a + 1 + m) - a - 1;

	ans[0] = 1;

	if(sum[m] > n) cout << 0;
	else {
		//for(register int i = a[1]; i <= n; i++)
		for(register int i = 1; i <= m; i++) {
			memset(tmp, 0, sizeof(tmp));
			//for(register int j = 0; j < a[i]; j++) tmp[j] = 0;
			for(register int j = a[i]; j <= n; j++) tmp[j] = ifac[j];
			//tmp[0] = 1;
			ksm(tmp, cnt[a[i]], n);
			conv(ans, tmp, ans);
		} cout << mul(ans[n], fac[n]);
	}

	//cout << C(20, 13) << endl;
	//cout << com[21][14];

	return 0;
}

