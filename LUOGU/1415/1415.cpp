#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 5e3 + 5;

int f[maxn], n, lcp[maxn][maxn], L, lead[maxn][maxn], g[maxn];

char s[maxn], id[maxn], o[maxn], a[maxn];

inline int cmp(int i, int j, int x, int y) {
	while(s[i] == '0' && i <= j) i++;
	while(s[x] == '0' && x <= y) x++;
	int L0 = j - i + 1, L1 = y - x + 1;
	if(L0 == 0 && L1 == 0) return -1;
	else if(L0 > L1) return 1;
	else if(L0 < L1) return 0;
	else {
		while(s[i] == s[x] && i <= j && x <= y) i++, x++;
		if(i > j && x > y) return -1;
		else return s[i] > s[x];
	}
}

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
	while(~scanf("%s", s + 1)) {
		//scanf("%s", s + 1);
		n = strlen(s + 1);

		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		L = 0; f[1] = 1;

		for(register int i = 2; i <= n; i++)
			for(register int j = i - 1; j >= 0; j--)
				if(j == 0 || cmp(j + 1, i, f[j], j) == 1) {
					f[i] = j + 1; break;
				}

		int cnt = 0;
		for(register int i = f[n] - 1; i && s[i] == '0'; i--) g[i] = n, cnt++;
		g[f[n]] = n;
		for(register int i = f[n] - 1 - cnt; i >= 1; i--)
			for(register int j = f[n] - 1; j >= i; j--)
				if(i == j || cmp(i, j, j + 1, g[j + 1]) == 0) {
					g[i] = j; break;
				}

		//for(register int i = 1; i <= n && !L; i++) if(f[n][i]) L = i;

		//cout << (id + 1) << endl;
		//cout << n - f[n] + 1 << endl;

		int now = 1;
		while(now <= n) {
			for(register int i = now; i <= g[now]; i++) putchar(s[i]);
			if(g[now] != n) putchar(',');
			now = g[now] + 1;
		} cout << endl;
	}
	return 0;
}

