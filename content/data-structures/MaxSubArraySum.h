/**
 * Author: ProofByAC
 * Description: MaxSubArraySum.h
 */

ll a[N];

struct Node {
    ll sum, pref, suff, best;
    Node(ll v = -INF) {
        if(v == -INF) { sum = pref = suff = best = -INF; }
        else { sum = v; pref = suff = best = v; }
    }
};

Node mergeNode(Node &L, Node &R) {
    if(L.sum == -INF) return R;
    if(R.sum == -INF) return L;
    Node res;
    res.sum  = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.best = max({L.best, R.best, L.suff + R.pref});
    return res;
}

struct SegmentTree {
    int n;
    vector<Node> st;
    SegmentTree(ll n1) {
        n = n1;
        st.assign(4 * n + 1, Node());
        build(0, 0, n - 1);
    }

    void build(int ind, int l, int r) {
        if(l == r) {
            st[ind] = Node(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build((ind << 1) + 1, l, m);
        build((ind << 1) + 2, m + 1, r);
        st[ind] = mergeNode(st[(ind << 1) + 1], st[(ind << 1) + 2]);
    }

    void update(int idx, ll val) { 
        update(0, 0, n - 1, idx, val); 
    }

    void update(int ind, int l, int r, int idx, ll val) {
        if(l == r) {
            st[ind] = Node(val);
            return;
        }
        int m = (l + r) >> 1;
        if(idx <= m) update((ind << 1) + 1, l, m, idx, val);
        else update((ind << 1) + 2, m + 1, r, idx, val);
        st[ind ]  = mergeNode(st[(ind << 1) + 1], st[(ind << 1) + 2]);
    }

    Node query1(int L, int R) { 
        return query(0, 0, n - 1, L, R); 
    }

    Node query(int ind, int l, int r, int L, int R) {
        if(R < l || r < L) return Node(-INF); 
        if(L <= l && r <= R) return st[ind];
        int m = (l + r) >> 1;
        Node left = query((ind << 1) + 1, l, m, L, R);
        Node right = query((ind << 1) + 2, m + 1, r, L, R);
        return mergeNode(left, right);
    }
    ll query(int L, int R) {
        Node ans = query1(L, R);
        return ans.best;
    }
};