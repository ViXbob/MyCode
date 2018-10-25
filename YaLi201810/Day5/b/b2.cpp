#include <bits/stdc++.h>
#define mid (l + r >> 1)

using namespace std;

typedef long long LL;

const int maxn = 2e5 + 5;
const int LOG = 85;
const int inf = 1e9 + 7;

int n, m, k, A, a[maxn], B, b[maxn], vis[maxn], p[maxn][3], C[3], Id[maxn], tmp[maxn];

LL ans, v[maxn];

double newv[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline bool cmp(int x, int y) {newv[x] < newv[y];}

struct node {
	int id;
	bool operator < (const node &t) const {
		int x = id, y = t.id;
		if(!C[1] && !C[2]) return v[x] < v[y];
		if(!vis[x] && !vis[y]) return v[x] < v[y];
		if(!vis[x] || !vis[y]) return vis[x] ? true : false;
		if(C[1] > 0 && C[2] > 0) {
			LL Px = 1 + (vis[x] < 2), Py = 1 + (vis[y] < 2);
			return v[x] * Px < v[y] * Py;
		}
		else {
			LL X = v[x], Y = v[y];
			if(vis[x] == 1 && C[p[x][1]] <= 0) X = inf;
			if(vis[y] == 1 && C[p[y][1]] <= 0) Y = inf;
			return X < Y;
		}
	}
};

priority_queue<node> q;

int main() {
	freopen("b.in", "r", stdin);
	//freopen("my.out", "w", stdout);
	
	n = read(); m = read(); k = read();
	
	for(register int i = 1; i <= n; i++) v[i] = read(), Id[i] = i;	
	
	A = read();
	for(register int i = 1; i <= A; i++) {
		a[i] = read(), vis[a[i]]++;
		p[a[i]][vis[a[i]]] = 1;
	}
	
	B = read();
	for(register int i = 1; i <= B; i++) {
		b[i] = read(), vis[b[i]]++;
		p[b[i]][vis[b[i]]] = 2;
	}
	
	C[1] = k; C[2] = k;
	
	/*for(register int i = 1; i <= n; i++) {
		q.push((node){i});
		//cout << q.top().id << endl;
	}*/
	
	int tot = n;
	
	if(A < k || B < k) {cout << -1; return 0;}
	
	while(m--) {
		node t = (node){Id[1]};
		for(register int i = 2; i <= tot; i++) 
			t = min(t, (node){Id[i]});
		int id = t.id;
		ans += v[id];
		for(register int i = 1; i <= vis[id]; i++)
			C[p[id][i]]--;
		int z = 0;
		for(register int i = 1; i <= tot; i++)
			if(Id[i] != id) tmp[++z] = Id[i];
		tot = z;
		for(register int i = 1; i <= tot; i++) Id[i] = tmp[i];
	}
	
	if(C[1] > 0 || C[2] > 0) {cout << -1; return 0;}

	cout << ans;
	return 0;
}
