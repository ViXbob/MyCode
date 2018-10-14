#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 6e3 + 5;
const int P = 1e9 + 7;

int f[maxn][2], n, ans;
pair<int, int> t[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
inline int dec(int x, int y) {x -= y; return x < 0 ? x + P : x;}

int main() {
#ifndef ONLINE_JUDGE
	freopen("refract.in", "r", stdin);
	freopen("refract.out", "w", stdout);
#endif
	n = read();
	
	for(register int i = 1; i <= n; i++)
		t[i].first = read(), t[i].second = read();
		
	sort(t + 1, t + 1 + n);
	
	for(register int i = 1; i <= n; i++) {
		f[i][0] = f[i][1] = 1;
		
		for(register int j = i - 1; j >= 1; j--) {
			if(t[j].second > t[i].second) f[j][1] = pls(f[j][1], f[i][0]);
			else f[i][0] = pls(f[i][0], f[j][1]);
		}
	}
	
	for(register int i = 1; i <= n; i++) ans = pls(ans, pls(f[i][0], f[i][1]));
	
	cout << dec(ans, n);
	return 0;
}
