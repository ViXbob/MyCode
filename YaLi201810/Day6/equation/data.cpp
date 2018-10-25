#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 5;
const int maxw = 1e3;
const int inf = 1e5;

int n, m, fa[maxn];

inline int findx(int x) {return x == fa[x] ? fa[x] : fa[x] = findx(fa[x]);}

inline void merge(int x, int y) {fa[findx(x)] = findx(y);}

inline int getrand(int P) {
	return (rand() << 15 | rand()) % P + 1;
}

int main() {
	//freopen("data.in", "r", stdin);
	freopen("data.in", "w", stdout);
	
	srand(time(NULL));
	
	n = 100000; m = 500000;
	
	cout << n << " " << m << endl;
	
	for(register int i = 1; i <= n; i++) fa[i] = i;
	
	for(register int i = 2; i <= n; i++) {
		int f = getrand(i - 1), w = getrand(maxw);
		while(findx(f) == findx(i)) f = getrand(i - 1);
		//cout << f << " " << w << endl;
		printf("%d %d\n", f, w);
	}
	
	for(register int i = 1; i <= m; i++) {
		int opt = getrand(2);
		//cout << opt << " ";
		printf("%d ", opt);
		if(opt == 1) printf("%d %d %d\n", getrand(n), getrand(n), getrand(inf));
		else printf("%d %d\n", getrand(n), getrand(maxw));
	}
	return 0;
}
