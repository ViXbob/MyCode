#include <bits/stdc++.h>
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 2e5 + 5;
const int LOG = 50;

int m;

LL maxr, opt[maxn], l[maxn], r[maxn];

inline LL read() {
	char ch = getchar(); LL u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline LL getrand(LL P) {
	LL p1 = rand() << 15 | rand();
	LL p2 = rand() << 15 | rand();
	return (p1 << 30 | p2) % P;
}

int main() {
	freopen("data.in", "w", stdout);
	
	m = 100000;
	
	cout << m << endl;
	
	maxr = (LL)1e18;
	
	for(register int i = 1; i <= m; i++) {
		LL opt = rand() % 3 + 1, l = getrand(maxr / 3) + 1, r = l + getrand(maxr / 2) + 1;
		/*if(rand() % 5 == 2) {
			cout << 3 << " " << "1 " << " " << maxr << endl; continue;
		}*/
		cout << opt << " " << l << " " << r << endl;
	}
	return 0;
}
