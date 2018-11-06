#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n, k, fa[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int findx(int x) {return fa[x] == x ? fa[x] : fa[x] = findx(fa[x]);}

inline int getrand(int P) {
	return rand() % P + 1;
}

int main() {
	srand(time(NULL));
	freopen("in.txt", "w", stdout);
	
	n = 10; k = getrand(n);
	cout << n << " " << k << endl;
	
	for(register int i = 1; i <= n; i++) fa[i] = i;
	
	for(register int i = 1; i < n; i++) {
		int x = getrand(n), y = getrand(n);
		while(findx(x) == findx(y))
			x = getrand(n), y = getrand(n);
		fa[findx(x)] = findx(y);
		cout << x << " " << y << " " << getrand(100) << endl;
	}
	return 0;
}
