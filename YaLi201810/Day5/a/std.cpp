#include <bits/stdc++.h>
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 2e5 + 5;
const int LOG = 50;

int m, a[maxn];

LL maxr;

inline LL read() {
	char ch = getchar(); LL u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
	freopen("data.in", "r", stdin);
	freopen("std.out", "w", stdout);
	
	m = read();
	
	for(register int i = 1; i <= m; i++) {
		LL opt = read(), l = read(), r = read();
		for(register int j = l; j <= r; j++)
			if(opt == 1) a[j] = 1;
			else if(opt == 2) a[j] = 0;
			else a[j] ^= 1;
		int pos = 1;
		while(a[pos]) pos++;
		printf("%d\n", pos);
	}
	return 0;
}
