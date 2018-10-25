#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 30;

int n, k, st, tot;

double ans = 0;

char s[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

namespace Map {
	const int maxlen = 24;
	
	map<int, double> f[maxn];
	double f0[1 << maxlen + 1];
	
	inline void init() {
		for(register int i = 0; i < (1 << maxlen + 1); i++) f0[i] = -1;
	}
	
	inline bool count(int S, int len) {
		if(len <= maxlen) return f0[1 << len | S] != -1;
		else return f[len].count(S);
	}
	
	inline double &find(int S, int len) {
		if(len <= maxlen) return f0[1 << len | S];
		else return f[len][S];
	}
}

inline int getdel(int S, int pos) {
	return (S & (1 << pos - 1) - 1) | ((S >> pos) << pos - 1);
}

inline double dfs(int S, int len) {
	if(len <= n - k) return 0;
	if(Map :: count(S, len)) return Map :: find(S, len);
	
	double &rnt = Map :: find(S, len); rnt = 0;
	
	for(register int i = 1, j = len; i <= j; i++, j--)
		if(i < j) 
			rnt += max(dfs(getdel(S, i), len - 1) + (S >> i - 1 & 1), dfs(getdel(S, j), len - 1) + (S >> j - 1 & 1)) * 2;
		else rnt += dfs(getdel(S, i), len - 1) + (S >> i - 1 & 1);
	
	return rnt /= len;
}

int main() {
	freopen("v.in", "r", stdin);
	freopen("v.out", "w", stdout);
	
	n = read(); k = read();
	scanf("%s", s + 1);
	
	for(register int i = 1; i <= n; i++)
		st |= ((s[i] == 'W') << i - 1);
	
	Map :: init();
	
	printf("%.10lf", dfs(st, n));
	return 0;
}
