#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e3 + 5;

int n, m, a, b, c, d, mp[maxn][maxn], sum[maxn][maxn], Sa[maxn][maxn], Sc[maxn][maxn];
int ans = 0;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

struct Deque {
	deque<int> q; int id;
	
	inline void push(int x) {
		while(!q.empty() && Sa[id][x] <= Sa[id][q.back()])
			q.pop_back();
		q.push_back(x);
	}
	
	inline void pop(int Lim) {
		while(!q.empty() && q.front() <= Lim)
			q.pop_front();
	}
	
	inline void clear() {while(!q.empty()) q.pop_back();}
	inline int Front() {return q.front();}
	inline int Back() {return q.back();}
	inline int Wget() {return Sa[id][q.front()];}
	
} Q[maxn], zQ;

inline int Martix(int x0, int y0, int x, int y) {
	return sum[x][y] - sum[x][y0 - 1] - sum[x0 - 1][y] + sum[x0 - 1][y0 - 1];
}

inline void pushit(int x) {
	while(!zQ.q.empty() && Q[x].Wget() <= Q[zQ.Back()].Wget())
		zQ.q.pop_back();
	zQ.q.push_back(x);
}

inline void getans(int id) {
	zQ.clear();
	
	for(register int i = 2; i + c - 1 < a; i++) pushit(i);
	
	ans = max(ans, Sc[1][id] - Q[zQ.Front()].Wget());
	for(register int i = 1; i + a - 1 < n; i++) {
		zQ.pop(i + 1); pushit(i + a - c);
		ans = max(ans, Sc[i + 1][id] - Q[zQ.Front()].Wget());
	}
}

int main() {
	n = read(); m = read(); a = read(); b = read(); c = read(); d = read();
	
	for(register int i = 1; i <= n; i++)
		for(register int j = 1; j <= m; j++) {
			mp[i][j] = read();
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mp[i][j];
		}

	for(register int i = 1; i + c - 1 <= n; i++) {
		Q[i].id = i;
		for(register int j = 1; j + d - 1 <= m; j++)
			Sa[i][j] = Martix(i, j, i + c - 1, j + d - 1);
	}
	
	for(register int i = 1; i + a - 1 <= n; i++)
		for(register int j = 1; j + b - 1 <= m; j++)
			Sc[i][j] = Martix(i, j, i + a - 1, j + b - 1);
	
	for(register int j = 2; j + d - 1 < b; j++)
		for(register int i = 2; i + c - 1 < n; i++) Q[i].push(j);
	getans(1);
	
	for(register int j = 1; j + b - 1 < m; j++) {
		for(register int i = 1; i + c - 1 < n; i++) {
			Q[i + 1].pop(j + 1); Q[i + 1].push(j + b - d);
		} getans(j + 1);
	}
	
	cout << ans;
	return 0;
}
