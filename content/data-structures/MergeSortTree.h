/**
 * Author: ProofByAC
 * Description: MergeSortTree.h
 */

ll a[N];

class Segtree {
    vector<vector<ll>> seg;

    public:
    Segtree(ll n) {
        seg.resize(4 * n + 1);
    }

    void build(ll ind, ll low, ll high) {
        if (low == high) {
            seg[ind].push_back(a[low]);
            return;
        }
        ll mid = (low + high) >> 1;
        build((ind << 1) + 1, low, mid);
        build((ind << 1) + 2, mid + 1, high);
        
        merge(seg[(ind << 1) + 1].begin(), seg[(ind << 1) + 1].end(),
              seg[(ind << 1) + 2].begin(), seg[(ind << 1) + 2].end(),
              back_inserter(seg[ind]));
    }

    ll query(ll ind, ll low, ll high, ll l, ll r, ll x) {
        if (r < low || l > high)
            return 0;
        if (l <= low && r >= high) {
            ll val = upper_bound(seg[ind].begin(), seg[ind].end(), x) - seg[ind].begin();
            return seg[ind].size() - val;
        }
        ll mid = (low + high) >> 1;
        ll left = query((ind << 1) + 1, low, mid, l, r, x);
        ll right = query((ind << 1) + 2, mid + 1, high, l, r, x);
        return left + right;
    }
};