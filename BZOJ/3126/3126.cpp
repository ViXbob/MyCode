#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int n, m, f[maxn], In[maxn], Out[maxn];

struct Deque {
	deque<int> q;

	inline void push(int x) {
		while(!q.empty() && f[x] >= f[q.back()]) 
			q.pop_back();
		q.push_back(x); 
	}
	
	inline void pop(int Lim) {
		while(!q.empty() && q.front() < Lim)
			q.pop_front();
	}
	
	inline int Front() {return q.front();}
} Q;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
	n = read(); m = read();
	
	for(register int i = 1; i <= n + 1; i++) In[i] = i - 1;
	for(register int i = 1; i <= m; i++) {
		int l = read(), r = read();
		In[r] = min(In[r], l - 1);
		Out[r + 1] = max(Out[r + 1], l);
	}
	
	for(register int i = n; i >= 1; i--) In[i] = min(In[i], In[i + 1]);
	for(register int i = 2; i <= n + 1; i++) Out[i] = max(Out[i], Out[i - 1]);
	
	for(register int i = 1; i <= n + 1; i++) {
		for(register int j = In[i - 1]; j <= In[i]; j++) Q.push(j);
		Q.pop(Out[i]);
		if(Q.q.empty()) f[i] = -inf;
		else f[i] = f[Q.Front()] + 1;
	}
	
	cout << (f[n + 1] >= 0 ? f[n + 1] : 0) - 1;
	
	return 0;
}
