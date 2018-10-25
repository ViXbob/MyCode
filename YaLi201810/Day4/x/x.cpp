#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;
const int inf = 1e9 + 7;
const int P = 1e9 + 7;

int T, n[6], a[6][maxn], prime[maxn], flag[maxm], fa[maxm + maxn], tot, cal[maxn];
int num[maxm], fac[maxm][20];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int findx(int x) {return x == fa[x] ? fa[x] : fa[x] = findx(fa[x]);}

inline void merge(int x, int y) {fa[findx(x)] = findx(y);}

inline void init(int n) {
	//memset(prime, 0, sizeof(prime));
	//memset(flag, 0, sizeof(flag));
	for(register int i = 1; i <= n + maxm; i++) fa[i] = i;
}

inline int ksm(int x, int k) {
	int cnt = 1;
	while(k) {
		if(k & 1) cnt = 1ll * cnt * x % P;
		x = 1ll * x * x % P; k >>= 1;
	} return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("x.in", "r", stdin);
	freopen("x.out", "w", stdout);
#endif
	T = read();
	
	for(register int i = 2; i < maxm; i++) {
		if(!flag[i]) prime[++prime[0]] = i;
		for(register int j = 1; j <= prime[0] && i * prime[j] < maxm; j++){
			flag[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
	
	for(register int i = 1; i <= T; i++) {
		n[i] = read();
		for(register int j = 1; j <= n[i]; j++) {
			a[i][j] = read();
			num[a[i][j]] = 1;
		}
	}
	
	for(register int i = 1; i < maxm; i++)
		if(num[i]) {
			int x = i;
			if(!flag[i]) {fac[i][++fac[i][0]] = i; continue;}
			for(register int j = 1; j <= prime[0] && prime[j] * prime[j] <= x; j++) {
				if(x % prime[j] == 0) fac[i][++fac[i][0]] = prime[j];
				while(x % prime[j] == 0) x /= prime[j];
			}
			if(!flag[x]) fac[i][++fac[i][0]] = x;
		}
	
	for(register int k = 1; k <= T; k++) {
		init(n[k]);
		
		for(register int i = 1; i <= n[k]; i++) {
			int x = a[k][i];
			if(x == 1) continue;
			for(register int j = 1; j <= fac[x][0]; j++)
				merge(fac[x][j], i + maxm);
		}
		
		for(register int i = 1; i <= n[k]; i++)
			cal[i] = findx(fa[i + maxm]);
		
		sort(cal + 1, cal + 1 + n[k]);
		tot = unique(cal + 1, cal + 1 + n[k]) - cal - 1;
		
		printf("%d\n", (ksm(2, tot) - 2 + P) % P);
	}
	return 0;
}
