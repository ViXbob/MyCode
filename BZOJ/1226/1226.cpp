#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

template <typename T> bool chkmax(T &a, T b) {return a < b ? a = b, 1 : 0;}
template <typename T> bool chkmin(T &a, T b) {return a > b ? a = b, 1 : 0;}

const int maxn = 1e3 + 5;
const int maxS = (1 << 8) + 5;
const int del = 8;
const int inf = 0x3f3f3f3f;

int T, a[maxn], b[maxn], n, f[maxn][maxS][16], ans;

inline int read() {
    char ch = getchar(); int u = 0, f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline int w(int x, int y) {return x <= 0 ? 0 : a[x] ^ a[y];}

int main() {
    T = read();
    
    while(T--) {
        n = read();
        memset(f, 0x3f, sizeof(f));
        
        for(register int i = 1; i <= n; i++)
            a[i] = read(), b[i] = min(read(), n - i);
    
        f[1][0][del - 1] = 0;
        for(register int i = 1; i <= n; i++) {
            for(register int S = 0; S < (1 << 8); S++) 
                for(register int k = -8; k <= 7; k++) if(f[i][S][k + del] < inf) {
                    int now = f[i][S][k + del];
                    if(S & 1) {int &t = f[i + 1][S >> 1][k - 1 + del]; t = min(t, now); continue;}
                    int Lim = 7;
                    for(register int j = 0; j <= Lim; j++) if(((1 << j) & S) == 0) {
                        int &t = f[i][S | (1 << j)][j + del];
                        t = min(t, now + w(i + k, i + j));
                        Lim = min(Lim, j + b[i + j]);
                    }
                }
        }
        
        ans = inf;
        for(register int k = -8; k <= -1; k++) 
            ans = min(ans, f[n + 1][0][k + del]);
        cout << ans << endl;
    }
    
    return 0;
}
