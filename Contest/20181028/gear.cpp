#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e5 + 5;

int fa[maxn], n, m, x, y;

LL R[maxn];

char opt[maxn];

inline LL read() {
	char ch = getchar(); LL u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int findx(int x) {return fa[x] == x ? fa[x] : fa[x] = findx(fa[x]);}

inline LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}

int main() {
#ifndef ONLINE_JUDGE
	freopen("gear.in", "r", stdin);
	freopen("gear.out", "w", stdout);
#endif
	n = read(); m =read();
	
	for(register int i = 1; i <= n; i++) {
		R[i] = read(); fa[i] = i;
	}
	
	for(register int i = 1; i <= m; i++) {
		scanf("%s", opt + 1); x = read(); y = read();
		int rtx = findx(x), rty = findx(y);
		if(opt[1] == 'l') fa[rtx] = rty;
		else if(opt[1] == 'q') {
			if(rtx != rty) puts("-/-");
			else {
				LL d = gcd(R[x], R[y]);
				printf("%lld/%lld\n", R[y] / d, R[x] / d);
			}
		}
	}
	
	return 0;
}
/*
2 3
2 3
query 1 2
link 1 2
query 1 2
*/
