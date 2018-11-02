#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long LL;
 
const int maxn = 15;
const int P = 1e8;
 
int n, m, f[maxn][1 << maxn], G[maxn][maxn], U, p[1 << maxn], ans, ban[maxn];
 
inline int read() {
    char ch = getchar(); int u = 0, f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}
 
inline int pls(int x, int y) {x += y; return x >= P ? x - P : x;}
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("explosion.in", "r", stdin);
    freopen("explosion.out", "w", stdout);
#endif
    n = read(); m = read();
 
    for(register int i = 1; i <= n; i++)
        for(register int j = 1; j <= m; j++)
            G[i][j] = read(), ban[i] |= ((G[i][j] ^ 1) << j - 1);
 
    U = 1 << m;
 
    for(register int i = 0; i < U; i++) {
        p[i] = 1;
        for(register int j = m - 1; j >= 0; j--)
            if((i & (1 << j)) && (i & (1 << j + 1))) p[i] = 0;
    }
 
    f[0][0] = 1;
    for(register int i = 1; i <= n; i++)
        for(register int S = 0; S < U; S++) {
            int now = ~S & (U - 1);
            for(register int S2 = now; S2; S2 = (S2 - 1) & now)
                if(!(S2 & ban[i]))
                    f[i][S2] = pls(f[i][S2], f[i - 1][S] * p[S2]);
            f[i][0] = pls(f[i][0], f[i - 1][S] * p[0]);
        }
 
    for(register int i = 0; i < U; i++) ans = pls(ans, f[n][i]);
 
    cout << ans;
    return 0;
}
/*
9 9
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1
*/
