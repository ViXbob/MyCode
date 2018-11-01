#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e5 + 5;

string str;

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline pair<int, int> GetBracket(string s, char l, char r) {
	int n = s.size(); int cnt = 0, L = 0, num = 0;
	for(register int i = 0; i < n; i++) {
		if(s[i] == l) {
			cnt++;
			if(cnt == 1) L = i;
		}
		if(s[i] == r) {
			if(cnt == 1) {
				int R = i + 1;
				while(R < n && isdigit(s[R])) num = num * 10 + s[R] - '0', R++;
				return make_pair(i - L + 1, num);
			} else cnt--;
		}
	}
}

inline int getlen(int x) {
	int rnt = 0;
	while(x) rnt++, x /= 10;
	return rnt;
}

string Extract(string &s) {
	int n = s.size(), cnt = 0, judge = 0, l = 0, pos = 0, len;
	string rnt, tmp, z;
	pair<int, int> T0, T1;
	for(register int i = 0; i < n; ) {
		if(s[i] == '[') {
			T0 = GetBracket(s.substr(i), '[', ']');
			int num = T0.second, now = i;
			i += T0.first + getlen(T0.second);
			tmp = s.substr(now + 1, T0.first - 2);
			tmp = Extract(tmp);
			l = i; pos = 1;
			for(; l < n && s[l] == '{'; ) {
				T1 = GetBracket(s.substr(l), '{', '}');
				while(pos <= T1.second) rnt += tmp, pos++;
				z = s.substr(l + 1, T1.first - 2);
				rnt += Extract(z);
				l += T1.first + getlen(T1.second);
			}
			while(pos <= T0.second) rnt += tmp, pos++;
			i = l;
		} else rnt += s[i], i++;
	} return rnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("extract.in", "r", stdin);
	freopen("extract.out", "w", stdout);
#endif
	cin >> str;

	//cout << str.substr(1, 3);

	cout << Extract(str);
	return 0;
}
/*
asdfg[[a]8{b}4{Edt}4asdfg]3zh
*/

