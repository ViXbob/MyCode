#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e3 + 5;
const int inf = 0x3f3f3f3f3f3f3f3f;
const int P = 1e9 + 7;

int T, MaxP, W, AP[maxn], BP[maxn], AS[maxn], BS[maxn];

deque<int> q;

LL f[maxn][maxn], ans = -inf;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

inline void Pushit(int id, int a, int b) {
	if(id < 0 || id > MaxP) return;
	while(!q.empty() && f[a][q.back()] + q.back() * b <= f[a][id] + id * b) q.pop_back();
	q.push_back(id);
}

inline void Gpop(int Lim) {
	while(!q.empty() && q.front() > Lim) q.pop_front();
}

inline void Lpop(int Lim) {
	while(!q.empty() && q.front() < Lim) q.pop_front();
}

int main() {
	T = read(); MaxP = read(); W = read();
	
	for(register int i = 1; i <= T; i++) {
		AP[i] = read(); BP[i] = read();
		AS[i] = read(); BS[i] = read();
	}
	
	memset(f, ~0x3f, sizeof(f));
	
	f[0][0] = 0;
	
	for(register int i = 1; i <= T; i++) {
		for(register int j = 0; j <= MaxP; j++) {
			f[i][j] = f[i - 1][j];
			if(j <= AS[i]) chkmax(f[i][j], f[0][0] - AP[i] * j);
		}
		if(i - W - 1 < 0) continue;
		int P = i - W - 1;
		
		while(!q.empty()) q.pop_back();
		for(register int j = MaxP; j >= MaxP - AS[i]; j--) Pushit(j, P, AP[i]);
		
		for(register int j = MaxP; j >= 0; j--) {
			chkmax(f[i][j], f[P][q.front()] + AP[i] * q.front() - AP[i] * j);
			Gpop(j - 1); Pushit(j - 1 - AS[i], P, AP[i]);
		}
		
		while(!q.empty()) q.pop_back();
		for(register int j = 0; j <= BS[i]; j++) Pushit(j, P, BP[i]);
		
		for(register int j = 0; j <= MaxP; j++) {
			chkmax(f[i][j], f[P][q.front()] + BP[i] * q.front() - BP[i] * j);
			Lpop(j + 1); Pushit(j + 1 + BS[i], P, BP[i]);
		}
	}
	
	for(register int i = 0; i <= MaxP; i++) chkmax(ans, f[T][i]);
	
	cout << ans;
	return 0;
}
