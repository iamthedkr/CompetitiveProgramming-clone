#include "debug.h"

#include "bits/stdc++.h"
using namespace std;

/*
// sub 1 {{{
int k = -1;
std::vector<int> a;

void init(int n, std::vector<int> _a) {
    assert((int) _a.size() == n);
    a = _a;
    k = max_element(a.begin(), a.end()) - a.begin();
}

int max_towers(int l, int r, int d) {
    if (k < l || r < k) return 1;
    if (a[l] <= a[k] - d && a[r] <= a[k] - d) return 2;
    return 1;
}
// }}}

// sub 2 {{{
std::vector<int> a;

void init(int n, std::vector<int> _a) {
    assert((int) _a.size() == n);
    a = _a;
}

int max_towers(int l, int r, int d) {
    std::vector<int> f(a.size());
    for (int i = l; i <= r; ++i) {
        f[i] = 1;

        int max_tower = -1;
        for (int j = i - 1; j >= l; --j) {
            if (a[i] <= max_tower - d
                    && a[j] <= max_tower - d) {
                f[i] = std::max(f[i], f[j] + 1);
            }
            max_tower = std::max(max_tower, a[j]);
        }
    }
    return *max_element(f.begin(), f.end());
}
// }}}

// SegTree, copied from AtCoder library {{{
// AtCoder doc: https://atcoder.github.io/ac-library/master/document_en/segtree.html
//
// Notes:
// - Index of elements from 0 -> n-1
// - Range queries are [l, r-1]
//
// Tested:
// - (binary search) https://atcoder.jp/contests/practice2/tasks/practice2_j
// - https://oj.vnoi.info/problem/gss
// - https://oj.vnoi.info/problem/nklineup
// - (max_right & min_left for delete position queries) https://oj.vnoi.info/problem/segtree_itstr
// - https://judge.yosupo.jp/problem/point_add_range_sum
// - https://judge.yosupo.jp/problem/point_set_range_composite
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

template<
    class T,  // data type for nodes
    T (*op) (T, T),  // operator to combine 2 nodes
    T (*e)() // identity element
>
struct SegTree {
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<T> (n, e())) {}
    explicit SegTree(const vector<T>& v) : _n((int) v.size()) {
        log = ceil_pow2(_n);
        size = 1<<log;
        d = vector<T> (2*size, e());

        for (int i = 0; i < _n; i++) d[size+i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    // 0 <= p < n
    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // 0 <= p < n
    T get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    // Get product in range [l, r-1]
    // 0 <= l <= r <= n
    // For empty segment (l == r) -> return e()
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        T sml = e(), smr = e();
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    T all_prod() const {
        return d[1];
    }

    // Binary search on SegTree to find largest r:
    //    f(op(a[l] .. a[r-1])) = true   (assuming empty array is always true)
    //    f(op(a[l] .. a[r])) = false    (assuming op(..., a[n]), which is out of bound, is always false)
    template <bool (*f)(T)> int max_right(int l) const {
        return max_right(l, [](T x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        T sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // Binary search on SegTree to find smallest l:
    //    f(op(a[l] .. a[r-1])) = true      (assuming empty array is always true)
    //    f(op(a[l-1] .. a[r-1])) = false   (assuming op(a[-1], ..), which is out of bound, is always false)
    template <bool (*f)(T)> int min_left(int r) const {
        return min_left(r, [](T x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        T sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    vector<T> d;

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }
};
// }}}

// sub 3 {{{
std::vector<int> a, vals;

void init(int n, std::vector<int> _a) {
    assert((int) _a.size() == n);

    // compress
    vals = _a;
    vals.push_back(2000111000);
    std::sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    for (int i = 0; i < n; ++i) {
        a.push_back(std::lower_bound(vals.begin(), vals.end(), _a[i]) - vals.begin());
    }
}

struct MaxSegTreeOp {
    static int op(int x, int y) {
        return max(x, y);
    }
    static int e() {
        return 0;
    }
};

int max_towers(int l, int r, int d) {
    SegTree<int, MaxSegTreeOp::op, MaxSegTreeOp::e> f(vals.size()), g(vals.size());

    int res = 0;
    for (int i = l; i <= r; ++i) {
        // i: chosen tower
        int min_h = std::lower_bound(vals.begin(), vals.end(), vals[a[i]] + d) - vals.begin();
        int cur_f = 1 + g.prod(min_h, vals.size());
        res = std::max(res, cur_f);
        f.set(a[i], std::max(f.get(a[i]), cur_f));

        // i: not chosen
        int max_h = std::upper_bound(vals.begin(), vals.end(), vals[a[i]] - d) - vals.begin();
        int cur_g = f.prod(0, max_h);
        g.set(a[i], std::max(g.get(a[i]), cur_g));
    }
    return res;
}
// }}}
*/

// sub 4 {{{
std::vector<int> a;
std::vector<int> tops;

void init(int n, std::vector<int> _a) {
    assert((int) _a.size() == n);
    a = _a;

    tops.push_back(-1);
    for (int i = 1; i < n - 1; ++i) {
        if (a[i] > a[i-1] && a[i] > a[i+1]) tops.push_back(i);
    }
    tops.push_back(n + 1);
}

int max_towers(int l, int r, int d) {
    assert(d == 1);
    int first = std::upper_bound(tops.begin(), tops.end(), l) - tops.begin();
    int last = std::lower_bound(tops.begin(), tops.end(), r) - tops.begin();
    
    if (first <= last) return 1 + last - first;
    return 1;
}
// }}}

int main() {
    int n, q; std::cin >> n >> q;
    std::vector<int> a(n);
    for (int& val : a) std::cin >> val;
    init(n, a);
    for (int i = 0; i < q; ++i) {
        int l, r, d; std::cin >> l >> r >> d;
        std::cout << max_towers(l, r, d) << '\n';
    }
    return 0;
}
