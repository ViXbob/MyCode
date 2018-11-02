#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 2e3 + 15;
const int P = 1e9 + 7;

int S[maxn], C[maxn][maxn], a, k;

LL n;

inline LL read() {
    char ch = getchar(); LL u = 0, f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int mul(int x, int y, int z) {return mul(x, mul(y, z));}
inline int dec(int x, int y) {x -= y; return x < 0 ? x + P : x;}

inline int ksm(LL x, LL k) {
    int cnt = 1; x = x % P;
    while(k) {
        if(k & 1) cnt = mul(cnt, x);
        x = mul(x, x); k >>= 1;
    } return cnt;
}

inline int inv(int x) {return ksm(x, P - 2);}

int main() {
    n = read(); a = read(); k = read();
    
    
    
    C[1][1] = 1;
    for(register int i = 2; i <= k + 5; i++)
        for(register int j = 1; j <= i; j++)
            C[i][j] = pls(C[i - 1][j], C[i - 1][j - 1]);
    
    //cout << C[10 + 1][3 + 1];
    
    //cout << S[0] << endl;
    
    if(a == 1) {
    	S[0] = n % P;
    	for(register int i = 1; i <= k; i++) {
    		int res = 0;
    		S[i] = dec(ksm(n + 1, i + 1), 1);
    		for(register int j = 0; j < i; j++)
    			res = pls(res, mul(C[i + 2][j + 1], S[j]));
    		S[i] = dec(S[i], res);
    		S[i] = mul(S[i], inv(i + 1));
    	}
    }
    else if(a > 1) {
    	S[0] = mul(a, dec(ksm(a, n), 1), inv(a - 1));
		for(register int i = 1; i <= k; i++) {
		    int res = 0;
		    S[i] = mul(ksm(n, i), ksm(a, n + 1));
		    for(register int j = 0; j < i; j++) 
		        if((i - j) & 1) res = dec(res, mul(S[j], C[i + 1][j + 1]));
		        else res = pls(res, mul(S[j], C[i + 1][j + 1]));
		    if(res > 0) S[i] = pls(S[i], res);
		    else S[i] = dec(S[i], res);
		    S[i] = mul(S[i], inv(a - 1));
		}
    }
    
    cout << S[k];
    return 0;
}
