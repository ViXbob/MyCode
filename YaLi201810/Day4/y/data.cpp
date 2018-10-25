#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;
const int inf = 1e9 + 7;

int T, n, m, a[maxn], prime[maxn], flag[maxm], fa[maxm], G[90][90];

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
	freopen("data.in", "w", stdout);	
#endif
	srand(time(NULL));

	n = 90; m = 4000; T = 20;
	cout << n << " " << m << " " << T << endl;
	
	for(register int i = 1; i <= m; i++) {
		int x = rand() % n + 1, y = rand() % n + 1, w = rand() % 2;
		
		while(G[x][y]) x = rand() % n + 1, y = rand() % n + 1, w = rand() % 2;
		
		G[x][y] = G[y][x] = 1;
		cout << x << " " << y << " " << w << endl;
	}
	return 0;
}
