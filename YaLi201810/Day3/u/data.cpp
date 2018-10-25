#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 1e3 + 5;

int n, q;

LL ans = 0;

int main() {
	freopen("data.in", "w", stdout);
	
	n = 300; q = 30000;
	
	cout << n << " " << q << endl;
	
	while(q--) {
		int x = rand() % n + 1, y = rand() % n + 1, L = rand() % n + 1, s = rand();
		//cout << x << " " << y << " " << L << " " << s << endl;
		printf("%d %d %d %d\n", x, y, L, s);
	}
	return 0;
}
