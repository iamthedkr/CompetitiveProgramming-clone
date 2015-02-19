#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int ui;
typedef unsigned long long ull;

#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)
#define Fit(i,v) For(__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++i)
#define Fitd(i,v) For(__typeof((v).rbegin()) i = (v).rbegin(); i != (v).rend(); ++i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#define ms(a,x) memset(a, x, sizeof(a))

template<class F, class T> T convert(F a, int p = -1) { stringstream ss; if (p >= 0) ss << fixed << setprecision(p); ss << a; T r; ss >> r; return r; }
template<class T> T gcd(T a, T b) { T r; while (b != 0) { r = a % b; a = b; b = r; } return a; }
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
template<class T> T sqr(T x) { return x * x; }
template<class T> T cube(T x) { return x * x * x; }
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return s == 0 ? 0 : cntbit(s >> 1) + (s & 1); }
const int bfsz = 1 << 16; char bf[bfsz + 5]; int rsz = 0;int ptr = 0;
char gc() { if (rsz <= 0) { ptr = 0; rsz = (int) fread(bf, 1, bfsz, stdin); if (rsz <= 0) return EOF; } --rsz; return bf[ptr++]; }
void ga(char &c) { c = EOF; while (!isalpha(c)) c = gc(); }
int gs(char s[]) { int l = 0; char c = gc(); while (isspace(c)) c = gc(); while (c != EOF && !isspace(c)) { s[l++] = c; c = gc(); } s[l] = '\0'; return l; }
template<class T> bool gi(T &v) {
    v = 0; char c = gc(); while (c != EOF && c != '-' && !isdigit(c)) c = gc(); if (c == EOF) return false; bool neg = c == '-'; if (neg) c = gc();
    while (isdigit(c)) { v = v * 10 + c - '0'; c = gc(); } if (neg) v = -v; return true;
}

typedef pair<int, int> II;

const ld PI = acos(-1.0);
const ld eps = 1e-9;

const int inf = (int)1e9 + 5;
const ll linf = (ll)1e17 + 5;
int dr[4] = {-1, 0, +1, 0};
int dc[4] = {0, -1, 0, +1};
const ll mod = 1000000007;

#define maxn 305

bool a[maxn];

int n, m, k;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//    freopen("in.txt", "r", stdin);
    cin >> n >> m >> k;
    int u;
    ms(a, 0);
    Rep(run, k){
        cin >> u;
        a[u] = 1;
    }

    if(k == n || m > (n) * (n - 1) / 2 - k + 1){
        cout << -1;
        return 0;
    }

    For(run, 1, n) if(!a[run]){
        int t1, t2;
        For(i, 1, n) if(i != run && a[i]){
            For(j, 1, n) if(j != run && j != i && a[j]){
                t1 = i;
                t2 = j;
                break;
            }
            break;
        }

        cout << t1 << " " << run << endl;
        cout << t2 << " " << run << endl;
        m -= 2;
        For(i, 1, n) For(j, i + 1, n){
            if(m == 0) break;
            if(i == t1 && j == t2) continue;
            if(i == t2 && j == t1) continue;
            if(i == t1 && j == run) continue;
            if(i == run && j == t1) continue;
            if(i == t2 && j == run) continue;
            if(i == run && j == t2) continue;
            if(i == t2 && a[j]) continue;
            if(j == t2 && a[i]) continue;
            cout << i << " " << j << endl;
            m--;
        }
        break;
    }

    return 0;
}