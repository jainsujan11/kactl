/**
 * Author: ProofByAC
 * Description: Segment tree implementation for range minimum query with count
 */
#pragma once
class Segtree {
    vector<ll> seg;
    ll n;
    ll merge(ll left, ll right) {
        return max(left, right); 
    }
public:
    Segtree(ll n1, ll arr[]) {
        n = n1;
        seg.resize(4 * n + 1);
        build(0, 0, n - 1, arr);
    }
    void build(ll ind, ll low, ll high, ll arr[]) {    
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }
        ll mid = (low + high) >> 1;
        build((ind << 1) + 1, low, mid, arr);
        build((ind << 1) + 2, mid + 1, high, arr);
        seg[ind] = merge(seg[(ind << 1) + 1], seg[(ind << 1) + 2]);
    }
    void update(ll ind, ll low, ll high, ll pos, ll val) {
        if (low == high) {
            seg[ind] = val;
            return;
        }
        ll mid = (low + high) >> 1;
        if (pos <= mid) update((ind << 1) + 1, low, mid, pos, val);
        else update((ind << 1) + 2, mid + 1, high, pos, val);
        seg[ind] = merge(seg[(ind << 1) + 1], seg[(ind << 1) + 2]);
    }
    ll query(ll ind, ll low, ll high, ll l, ll r) {                    
        if (high < l || low > r) return 0;
        if (low >= l && high <= r) return seg[ind];
        ll mid = (low + high) >> 1;
        ll left = query((ind << 1) + 1, low, mid, l, r);
        ll right = query((ind << 1) + 2, mid + 1, high, l, r);
        return merge(left, right);
    }
    ll get_first(ll ind, ll low, ll high, ll l, ll r, ll x) {
        if(low > r || high < l) return -1;
        if(seg[ind] <= x) return -1;
        if (low == high) return low;
        ll mid = low + (high - low) / 2;
        ll left = get_first((ind << 1) + 1, low, mid, l, r, x);
        if(left != -1) return left;
        ll right = get_first((ind << 1) + 2, mid + 1, high, l, r, x);
        return right;
    }
    ll get_last(ll ind, ll low, ll high, ll l, ll r, ll x) {
        if(low > r || high < l) return -1;
        if(seg[ind] <= x) return -1;
        if (low == high) return low;
        ll mid = low + (high - low) / 2;
        ll right = get_last((ind << 1) + 2, mid + 1, high, l, r, x);
        if(right != -1) return right;
        ll left = get_last((ind << 1) + 1, low, mid, l, r, x);
        return left;
    }
    void update(ll pos, ll val) { update(0, 0, n - 1, pos, val); }
    ll query(ll l, ll r) { return query(0, 0, n - 1, l, r); }
    ll get_first(ll l, ll r, ll x) { return get_first(0, 0, n - 1, l, r, x); }
    ll get_last(ll l, ll r, ll x) { return get_last(0, 0, n - 1, l, r, x); }
};