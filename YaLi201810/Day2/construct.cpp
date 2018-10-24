// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int n, c, maxv, st[maxn][20];
deque<int> q;

LL ans, f[maxn], ss[maxn], s[maxn], h[maxn], t;

inline int read() {
    char ch = getchar(); int u = 0, f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) {u = u * 10 + ch - 48;  ch = getchar();} return u * f;
}

inline LL getS(LL x) {return x * x;}

inline void SetST(int n) {
    for(register int i = 1; i <= n; i++) st[i][0] = h[i];

    for(register int j = 1; j <= 20; j++)
        for(register int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
}

inline LL query(int x, int y) {
    int k = log2(y - x + 1);
    return max(st[x][k], st[y - (1 << k) + 1][k]);
}

inline LL calc(LL t, LL len, LL b) {return len * getS(t) - t * b;}

inline void trans(int i, int j) {
    LL SS = ss[i - 1] - ss[j], S = s[i - 1] - s[j], mx = 0, res = 0, len = 0;

    if(i == n + 1 && j == 0) {
        t = S / n; mx = query(1, n); res = SS; len = n;

        f[i] = min(f[i], res + calc(max(t + 1, mx), len, 2 * S));
        f[i] = min(f[i], res + calc(max(t, mx), len, 2 * S));
        f[i] = min(f[i], res + calc(max(t - 1, mx), len, 2 * S));
    }
    else if(i == n + 1 && j == n) f[i] = min(f[i], f[j]);
    else if(j == 0 && h[i] >= query(1, i - 1)) {
        t = double(c + 2 * S) / (2 * (i - j - 1));
        mx = h[i]; res = SS + h[i] * c; len = i - j - 1;

        t = max(t, query(j + 1, i - 1) + 1);

        f[i] = min(f[i], res + calc(min(t + 1, mx), len, 2 * S + c));
        f[i] = min(f[i], res + calc(min(t, mx), len, 2 * S + c));
        f[i] = min(f[i], res + calc(min(t - 1, mx), len, 2 * S + c));
    }
    else if(i == n + 1 && h[j] >= query(j + 1, n)) {
        t = double(c + 2 * S) / (2 * (i - j - 1));
        mx = h[j]; res = f[j] + SS + h[j] * c; len = i - j - 1;

        t = max(t, query(j + 1, i - 1) + 1);

        f[i] = min(f[i], res + calc(min(t + 1, mx), len, 2 * S + c));
        f[i] = min(f[i], res + calc(min(t, mx), len, 2 * S + c));
        f[i] = min(f[i], res + calc(min(t - 1, mx), len, 2 * S + c));
    }

    if(i == n + 1 || j == 0) return;

    if(j + 1 == i) f[i] = min(f[i], f[j] + c * abs(h[i] - h[j]));
    else if(h[j] >= query(j + 1, i - 1) && query(j + 1, i - 1) <= h[i]) {
        t = double(c + S) / (i - j - 1);
        mx = min(h[i], h[j]); res = f[j] + SS + (h[i] + h[j]) * c; len = i - j - 1;

        t = max(t, query(j + 1, i - 1) + 1);

        f[i] = min(f[i], res + calc(min(t + 1, mx), len, 2 * (S + c)));
        f[i] = min(f[i], res + calc(min(t, mx), len, 2 * (S + c)));
        f[i] = min(f[i], res + calc(min(t - 1, mx), len, 2 * (S + c)));
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("construct.in", "r", stdin);
    freopen("construct.out", "w", stdout);
#endif

    n = read(); c = read();

    for(register int i = 1; i <= n; i++) {
        h[i] = read(); s[i] = s[i - 1] + h[i];
        ss[i] = ss[i - 1] + getS(h[i]);
        f[i] = 1ll << 60;
    } SetST(n); f[n + 1] = 1ll << 60;

    f[1] = 0; h[0] = h[n + 1] = 1ll << 60; h[n + 1]--;

    q.push_back(0); q.push_back(1);

    for(register int i = 2; i <= n + 1; i++) {
        while(h[i] >= h[q.back()]) {
            trans(i, q.back());
            q.pop_back();
        }
        trans(i, q.back());
        if(q.back()) trans(i, 0);
        q.push_back(i);
    }

    cout << min(f[n + 1], f[n]);
    return 0;
}
/*
5 15
2 5 4 10 6
*/

