#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 5;
const int inf = 1e9 + 7;
const int P = 1e9 + 7;

int n, q, a[maxn], l, s[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("z.in", "r", stdin);
	freopen("z.out", "w", stdout);
#endif
	n = read(); q = read();
	
	for(register int i = 1; i <= n; i++) a[i] = read();
	
	for(register int i = 1; i <= q; i++)
		l = read();
		
		
	
	return 0;
}
