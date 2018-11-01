#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 3e2 + 15;
const int inf = 0x3f3f3f3f;
const int P = 1e9 + 7;

int n;

struct BIGInt{
	const LL Base = 1e8;
    LL num[125];
    inline void reset() {
		while(num[0])num[num[0]] = 0, num[0]--;
		num[1] = 1; num[0] = 1;
	}
    inline void setoo() {num[120] = 1; num[0] = 120;}
    inline void print() {
    	printf("%lld", num[num[0]]);
        for (register int i = num[0] - 1; i >= 1; i--)
            printf("%08lld", num[i]);
        putchar('\n');
    }
    BIGInt operator + (const BIGInt &t) const {
		BIGInt x = (*this);
		int len = max(t.num[0], x.num[0]);
		for(register int i = len; i >= 1; i--)
			x.num[i] += t.num[i];
		for(register int i = 1; i <= len; i++){
			x.num[i + 1] += x.num[i] / Base;
			x.num[i] %= Base;
		}
		x.num[0] = len + 1;
        while(!x.num[x.num[0]] && x.num[0]) x.num[0]--;
        return x;
	}
    BIGInt operator * (const int &t) const {
        BIGInt x = (*this);
        x.num[0] = x.num[0] + 6;
        for (register int i = 1; i <= x.num[0]; i++)
            x.num[i] = x.num[i] * t;
        for (register int i = 1; i <= x.num[0]; i++)
            x.num[i + 1] += x.num[i] / Base, x.num[i] %= Base;
        while(!x.num[x.num[0]] && x.num[0]) x.num[0]--;
        return x;
    }
    BIGInt operator * (const BIGInt &t) const {
    	BIGInt c;
    	memset(c.num, 0, sizeof(c.num));
    	for(register int i = 1; i <= num[0]; i++)
    		for(register int j = 1; j <= t.num[0]; j++)
    			c.num[i + j - 1] += num[i] * t.num[j];
    	c.num[0] = num[0] + t.num[0] + 5;
    	for(register int i = 1; i <= c.num[0]; i++)
    		c.num[i + 1] += c.num[i] / Base, c.num[i] %= Base;
    	while(!c.num[c.num[0]] && c.num[0]) c.num[0]--;
    	return c;
    }
    BIGInt operator / (const int &t) const {
        BIGInt x = (*this); LL tmp = 0;
        for (register int i = x.num[0]; i >= 1; i--){
            tmp = tmp * Base + x.num[i];
            x.num[i] = tmp / t;
            tmp %= t;
        }
        while(!x.num[x.num[0]] && x.num[0]) x.num[0]--;
        return x;
    }
    BIGInt operator = (const BIGInt &t) {
    	memcpy(num, t.num, sizeof(t.num));
    }
    
    void equal(const BIGInt &t) {
    	memcpy(num, t.num, sizeof(t.num));
    }
} C[maxn][maxn], ans, tmp, f[maxn], fac[maxn];

inline int read() {
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : (x < 0 ? x + P : x);}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}

int main() {
#ifndef ONLINE_JUDGE
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	n = read();

	C[1][1].reset(); f[0].reset(); fac[0].reset();

	for(register int i = 2; i <= n + 5; i++)
		for(register int j = 1; j <= i; j++)
			C[i][j].equal(C[i - 1][j] + C[i - 1][j - 1]);

	for(register int i = 1; i <= n + 5; i++)
		fac[i].equal(fac[i - 1] * i);
		//fac[i] = fac[i - 1] * i;

	//(fac[4] * fac[4]).print();

	//C[5][2].print();

	//(C[5][3] * fac[2]).print(); cout << endl;

	for(register int i = 1; i <= n; i++) {
		f[i].equal(f[i - 1]);
		for(register int j = 2; j <= i; j++) {
			tmp.equal(f[i - j]);
			tmp.equal(tmp * C[i][j]);
			//tmp.equal(tmp * j);
			tmp.equal(tmp * fac[j]);
			
			// Com(i - 1, j - 1) * j! / 2
			
			//tmp.equal(tmp * j);
			tmp.equal(tmp / 2);
			f[i].equal(f[i] + tmp);
			//if(i == n)
				//f[i].print();
		}
		
		for(register int j = 4; j <= i; j++) {
			if(j % 3 == 0) continue;
			tmp.equal(f[i - j]);
			tmp.equal(tmp * C[i][j]);
			tmp.equal(tmp * fac[j - 1]);
			
			// Com(i - 1, j - 1) * (j - 1)! / 2
			
			tmp.equal(tmp / 2);
			f[i].equal(f[i] + tmp);
		}
	}

	//one.reset();

	f[n].print();
	return 0;
}

