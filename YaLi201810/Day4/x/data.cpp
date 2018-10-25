#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;
const int inf = 1e9 + 7;

int T, n, a[maxn], prime[maxn], flag[maxm], fa[maxm];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int findx(int x) {return x == fa[x] ? fa[x] : fa[x] = findx(fa[x]);}

inline int getrand() {
	return rand() << 15 | rand();
}

int main() {
#ifndef ONLINE_JUDGE
	//freopen("data.in", "r", stdin);
	freopen("x.in", "w", stdout);	
#endif
	srand(time(NULL));

	T = 5; cout << T << endl;
	
	while(T--) {
		n = 100000; cout << n << endl;
		
		for(register int i = 1; i <= n; i++) {
			int x = getrand() % maxm + 1;
			if(x >= 1000000) x -= (10 + getrand() % maxn);
			cout << x << " ";
		} cout << endl;
	}
	return 0;
}
