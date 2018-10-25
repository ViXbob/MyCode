#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;
const int inf = 1e9 + 7;
const int P = 1e9 + 7;

int T, n, a[maxn], prime[maxn], flag[maxm], fa[maxm], cal[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int findx(int x) {return x == fa[x] ? fa[x] : fa[x] = findx(fa[x]);}

inline int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}

inline int ksm(int x, int k) {
	int cnt = 1;
	while(k) {
		if(k & 1) cnt = 1ll * cnt * x % P;
		x = 1ll * x * x % P; k >>= 1;
	} return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("data.in", "r", stdin);
	//freopen("std.out", "w", stdout);	
#endif
	T = read();
	
	while(T--) {
		n = read();
		
		for(register int i = 1; i <= n; i++) fa[i] = i;
		
		for(register int i = 1; i <= n; i++)
			a[i] = read();
			
		for(register int i = 1; i <= n; i++)
			for(register int j = 1; j <= n; j++) {
				if(i == j) continue;
				if(gcd(a[i], a[j]) != 1) fa[findx(j)] = findx(i);
			}
			
		for(register int i = 1; i <= n; i++)
			cal[i] = findx(fa[i]);
		
		sort(cal + 1, cal + 1 + n);
		cal[0] = unique(cal + 1, cal + 1 + n) - cal - 1;
		
		printf("%d %d\n", (ksm(2, cal[0]) - 2 + P) % P, cal[0]);
	}
	return 0;
}
