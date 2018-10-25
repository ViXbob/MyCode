#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 5;

int n, m, k[maxn], b[maxn];

LL S, a[maxn];

inline bool cmp(LL x, LL y) {return x > y;}

inline bool check(int mid) {
	LL tot = 0;
	for(register int i = 1; i <= n; i++) a[i] = 1ll * mid * k[i] + b[i];
	
	//sort(a + 1, a + 1 + n, cmp);
	
	nth_element(a + 1, a + m, a + 1 + n, cmp);
	
	for(register int i = 1; i <= m; i++)
		if(a[i] > 0 && (tot += a[i]) >= S) return true;
	
	return tot >= S;
}

inline int biniry(int l, int r) {
	int mid = (l + r) / 2, ans = 0;
	while(l <= r) {
		mid = (l + r) / 2;
		if(check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	} return ans;
}

inline LL read() {
	char ch = getchar(); LL u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("merchant.in", "r", stdin);
	freopen("merchant.out", "w", stdout);
#endif

	n = read(); m = read(); S = read();
	
	for(register int i = 1; i <= n; i++) k[i] = read(), b[i] = read();
	
	//if(check(0)) {puts("0"); return 0;}
	
	printf("%d", biniry(0, (int)1e9));
	return 0;
}
