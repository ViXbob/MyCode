#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long LL;
 
template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}
 
const int maxn = 1e2 + 5;
const int P = 9999973;
 
int n, m, f[maxn][maxn][maxn], ans;
 
inline int read() {
    char ch = getchar(); int u = 0, f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}
 
inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
inline int mul(int x, int y) {LL rnt = 1ll * x * y; return (int)(rnt >= P ? rnt % P : rnt);}
inline int mul(int x, int y, int z) {return mul(x, mul(y, z));}
 
inline int ksm(int x, int k) {
    int cnt = 1;
    while(k) {
        if(k & 1) cnt = mul(cnt, x);
        x = mul(x, x); k >>= 1;
    } return cnt;
}
 
inline int C(int n) {return n * (n - 1) / 2;}
 
int main() {
    n = read(); m = read();
 
    f[0][0][0] = 1;
     
    for(register int i = 1; i <= n; i++)
        for(register int j = 0; j <= m; j++)
            for(register int k = 0; j + k <= m; k++) {
                f[i][j][k] = pls(f[i][j][k], f[i - 1][j][k]);
                if(j >= 1)
                    f[i][j][k] = pls(f[i][j][k], mul(f[i - 1][j - 1][k], m - j - k + 1));
                if(k >= 1 && j + 1 <= m) 
                    f[i][j][k] = pls(f[i][j][k], mul(f[i - 1][j + 1][k - 1], j + 1));
                if(k >= 1 && j >= 1)
                    f[i][j][k] = pls(f[i][j][k], mul(f[i - 1][j][k - 1], m - j - k + 1, j));
                if(j >= 2)
                    f[i][j][k] = pls(f[i][j][k], mul(f[i - 1][j - 2][k], C(m - j + 2 - k)));
                if(k >= 2 && j + 2 <= m)
                    f[i][j][k] = pls(f[i][j][k], mul(f[i - 1][j + 2][k - 2], C(j + 2)));
            }
     
    for(register int i = 0; i <= m; i++)
        for(register int j = 0; i + j <= m; j++)
            ans = pls(ans, f[n][i][j]);
     
    cout << ans;
    return 0;
}

