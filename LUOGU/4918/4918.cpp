#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int n, m, k, w[maxn], wa, wb, a, b;
int cnt, head[maxn], f[maxn][55], in[maxn];
queue<int> q;

struct Graph {int to, nt;} e[maxn << 1];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline void ini(int x, int y) {e[++cnt] = {y, head[x]}; head[x] = cnt;}

inline void PreSolve() {
	for(register int i = 2; i <= m; i++)
		if(!in[i]) q.push(i);
		
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(register int i = head[u]; i; i = e[i].nt) {
			int v = e[i].to;
			in[v]--; if(!in[v]) q.push(v);
		}
	}
}

inline void Topsort() {
	while(!q.empty()) q.pop();

	memset(f, ~0x3f, sizeof(f));

	f[1][0] = w[1];
	q.push(1); int ans = -inf;

	while(!q.empty()) {
		int u = q.front(); q.pop();

		for(register int i = head[u]; i; i = e[i].nt) {
			int v = e[i].to;
			
			if(f[u][0] != -(inf + 1)) {
				if(a != 1) chkmax(f[v][a - 1], f[u][0] - wa);
				else chkmax(f[v][a - 1], f[u][0] - wa + w[v]);
				
				if(b != 1) chkmax(f[v][b - 1], f[u][0] - wb);
				else chkmax(f[v][a - 1], f[u][0] - wb + w[v]);
			}
			
			if(f[u][1] != -(inf + 1)) chkmax(f[v][0], f[u][1] + w[v]);
			for(register int P = b; P > 1; P--)
				if(f[u][P] != -(inf + 1)) chkmax(f[v][P - 1], f[u][P]);
			
			in[v]--; if(!in[v]) q.push(v);
		}
	}

	for(register int i = 1; i <= m; i++) chkmax(ans, f[i][0]);

	cout << ans;
}

int main() {
	n = read(); m = read(); k = read();

	a = read(); b = read(); wa = read(); wb = read();

	for(register int i = 1; i <= n; i++) {
		int pos = read();
		w[pos] += read();
	}

	for(register int i = 1; i <= k; i++) {
		int x = read(), y = read();
		ini(x, y); in[y]++;
	}

	PreSolve();
	Topsort();
	
	return 0;
}

