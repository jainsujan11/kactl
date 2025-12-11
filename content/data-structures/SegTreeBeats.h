/**
 * Author: ProofByAC
 * Credits : https://judge.yosupo.jp/submission/279090
 * Description: SegTreeBeats.h
 */

const ll inf = 1e18;
const ll MXN = 3e5 + 1;

ll a[MXN], mx[MXN<<2], smx[MXN<<2], mn[MXN<<2], smn[MXN<<2], sum[MXN<<2], lz[MXN<<2];
int n, mxc[MXN<<2], mnc[MXN<<2];

inline void pull(int id) {
    if(mx[lc]>mx[rc]) {
        mx[id] = mx[lc]; mxc[id] = mxc[lc];
        smx[id] = max(smx[lc], mx[rc]);
    }
    else if(mx[lc]<mx[rc]) {
        mx[id] = mx[rc]; mxc[id] = mxc[rc];
        smx[id] = max(mx[lc], smx[rc]);
    }
    else {
        mx[id] = mx[lc]; mxc[id] = mxc[lc]+mxc[rc];
        smx[id] = max(smx[lc], smx[rc]);
    }

    if(mn[lc]<mn[rc]) {
        mn[id] = mn[lc]; mnc[id] = mnc[lc];
        smn[id] = min(smn[lc], mn[rc]);
    }
    else if(mn[lc]>mn[rc]) {
        mn[id] = mn[rc]; mnc[id] = mnc[rc];
        smn[id] = min(mn[lc], smn[rc]);
    }
    else {
        mn[id] = mn[lc]; mnc[id] = mnc[lc] + mnc[rc];
        smn[id] = min(smn[lc], smn[rc]);
    }

    sum[id] = sum[lc] + sum[rc];
}
void build(int l=0, int r=n, int id=1) {
    if(r-l == 1) {
        mx[id] = mn[id] = sum[id] = a[l];
        mxc[id] = mnc[id] = 1;
        smx[id] = -inf;
        smn[id] = inf;
        return;
    }
    build(l, mid, lc);
    build(mid, r, rc);
    pull(id);
}
inline void apply_chmin(ll x, int id) {
    if(x>=mx[id]) return;
    sum[id] += (x-mx[id])*mxc[id];
    if(mx[id]==mn[id]) mx[id] = mn[id] = x;
    else if(mx[id]==smn[id]) mx[id] = smn[id] = x;
    else mx[id] = x;
}
inline void apply_chmax(ll x, int id) {
    if(x<=mn[id]) return;
    sum[id] += (x-mn[id])*mnc[id];
    if(mn[id]==mx[id]) mn[id] = mx[id] = x;
    else if(mn[id]==smx[id]) mn[id] = smx[id] = x;
    else mn[id] = x;
}
inline void apply_add(ll x, int l, int r, int id) {
    mx[id] += x; smx[id] += x;
    mn[id] += x; smn[id] += x;
    sum[id] += (r-l)*x;
    lz[id] += x;
}
inline void push(int l, int r, int id) {
    if(r-l==1) return;
    if(lz[id]) {
        apply_add(lz[id], l, mid, lc);
        apply_add(lz[id], mid, r, rc);
        lz[id] = 0;
    }
    if(mx[id]<mx[lc]) apply_chmin(mx[id], lc);
    if(mx[id]<mx[rc]) apply_chmin(mx[id], rc);
    if(mn[id]>mn[lc]) apply_chmax(mn[id], lc);
    if(mn[id]>mn[rc]) apply_chmax(mn[id], rc);
}
void chmin(int s, int e, ll x, int l=0, int r=n, int id=1) {
    if(s>=r || l>=e || mx[id]<=x) return;
    if(s<=l && r<=e && smx[id]<x) {
        apply_chmin(x, id);
        return;
    }
    push(l, r, id);
    chmin(s, e, x, l, mid, lc);
    chmin(s, e, x, mid, r, rc);
    pull(id);
}
void chmax(int s, int e, ll x, int l=0, int r=n, int id=1) {
    if(s>=r || l>=e || mn[id]>=x) return;
    if(s<=l && r<=e && smn[id]>x) {
        apply_chmax(x, id);
        return;
    }
    push(l, r, id);
    chmax(s, e, x, l, mid, lc);
    chmax(s, e, x, mid, r, rc);
    pull(id);
}
void add(int s, int e, ll x, int l=0, int r=n, int id=1) {
    if(s>=r || l>=e) return;
    if(s<=l && r<=e) {
        apply_add(x, l, r, id);
        return;
    }
    push(l, r, id);
    add(s, e, x, l, mid, lc);
    add(s, e, x, mid, r, rc);
    pull(id);
}
ll get_sum(int s, int e, int l=0, int r=n, int id=1) {
    if(s>=r || l>=e) return 0;
    if(s<=l && r<=e) return sum[id];
    push(l, r, id);
    return get_sum(s, e, l, mid, lc) + get_sum(s, e, mid, r, rc);
}
