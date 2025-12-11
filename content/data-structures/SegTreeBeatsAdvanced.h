/**
 * Author: ProofByAC
 * Description: SegTreeBeatsAdvanced.h
 */

ll a[N];

struct Node {
    //s = sum, m1 = max, m2 = second max, n1 = min, n2 = second min
    //mc = max count, nc = min count, lz = lazy value
    ll s, m1, m2, mc, n1, n2, nc, lz;
} seg[N * 4];

void merge(int idx) {
    seg[idx].s = seg[idx << 1].s + seg[idx << 1 | 1].s;

    // max
    if (seg[idx << 1].m1 == seg[idx << 1 | 1].m1) {
        seg[idx].m1 = seg[idx << 1].m1;
        seg[idx].m2 = max(seg[idx << 1].m2, seg[idx << 1 | 1].m2);
        seg[idx].mc = seg[idx << 1].mc + seg[idx << 1 | 1].mc;
    } else {
        if (seg[idx << 1].m1 > seg[idx << 1 | 1].m1) {
            seg[idx].m1 = seg[idx << 1].m1;
            seg[idx].m2 = max(seg[idx << 1].m2, seg[idx << 1 | 1].m1);
            seg[idx].mc = seg[idx << 1].mc;
        } else {
            seg[idx].m1 = seg[idx << 1 | 1].m1;
            seg[idx].m2 = max(seg[idx << 1].m1, seg[idx << 1 | 1].m2);
            seg[idx].mc = seg[idx << 1 | 1].mc;
        }
    }

    // min
    if (seg[idx << 1].n1 == seg[idx << 1 | 1].n1) {
        seg[idx].n1 = seg[idx << 1].n1;
        seg[idx].n2 = min(seg[idx << 1].n2, seg[idx << 1 | 1].n2);
        seg[idx].nc = seg[idx << 1].nc + seg[idx << 1 | 1].nc;
    } else {
        if (seg[idx << 1].n1 < seg[idx << 1 | 1].n1) {
            seg[idx].n1 = seg[idx << 1].n1;
            seg[idx].n2 = min(seg[idx << 1].n2, seg[idx << 1 | 1].n1);
            seg[idx].nc = seg[idx << 1].nc;
        } else {
            seg[idx].n1 = seg[idx << 1 | 1].n1;
            seg[idx].n2 = min(seg[idx << 1].n1, seg[idx << 1 | 1].n2);
            seg[idx].nc = seg[idx << 1 | 1].nc;
        }
    }
}

void add(int idx, int l, int r, ll val) {
    if (val == 0) return;
    seg[idx].s += (r - l + 1) * val;
    seg[idx].m1 += val;
    if (seg[idx].m2 != -INF) seg[idx].m2 += val;
    seg[idx].n1 += val;
    if (seg[idx].n2 != INF) seg[idx].n2 += val;
    seg[idx].lz += val;
}

void applyMax(int idx, ll val, bool single) {
    if (val >= seg[idx].m1) return;
    seg[idx].s -= seg[idx].m1 * seg[idx].mc;
    seg[idx].m1 = val;
    seg[idx].s += seg[idx].m1 * seg[idx].mc;
    if (single) {
        seg[idx].n1 = seg[idx].m1;
    } else {
        if (val <= seg[idx].n1) {
            seg[idx].n1 = val;
        } else if (val < seg[idx].n2) {
            seg[idx].n2 = val;
        }
    }
}

void applyMin(int idx, ll val, bool single) {
    if (val <= seg[idx].n1) return;
    seg[idx].s -= seg[idx].n1 * seg[idx].nc;
    seg[idx].n1 = val;
    seg[idx].s += seg[idx].n1 * seg[idx].nc;
    if (single) {
        seg[idx].m1 = seg[idx].n1;
    } else {
        if (val >= seg[idx].m1) {
            seg[idx].m1 = val;
        } else if (val > seg[idx].m2) {
            seg[idx].m2 = val;
        }
    }
}

void push(int idx, int l, int r) {
    if (l == r) return;

    //sum
    int m = (l + r) >> 1;
    add(idx << 1, l, m, seg[idx].lz);
    add(idx << 1 | 1, m + 1, r, seg[idx].lz);
    seg[idx].lz = 0;

    //max
    applyMax(idx << 1, seg[idx].m1, l == m);
    applyMax(idx << 1 | 1, seg[idx].m1, m + 1 == r);

    //min
    applyMin(idx << 1, seg[idx].n1, l == m);
    applyMin(idx << 1 | 1, seg[idx].n1, m + 1 == r);
}

void build(int idx = 1, int l = 0, int r = N - 1) {
    seg[idx].lz = 0;
    if (l == r) {
        seg[idx].s = seg[idx].m1 = seg[idx].n1 = a[l];
        seg[idx].mc = seg[idx].nc = 1;
        seg[idx].m2 = -INF;
        seg[idx].n2 = INF;
        return;
    }
    int m = (l + r) >> 1;
    build(idx << 1, l, m);
    build(idx << 1 | 1, m + 1, r);
    merge(idx);
}

void updAdd(int s, int e, ll val, int idx, int l, int r) {
    if (e < l || r < s) return;
    if (s <= l && r <= e) {
        add(idx, l, r, val);
        return;
    }
    push(idx, l, r);
    int m = (l + r) >> 1;
    updAdd(s, e, val, idx << 1, l, m);
    updAdd(s, e, val, idx << 1 | 1, m + 1, r);
    merge(idx);
}

void updChMin(int s, int e, ll val, int idx, int l, int r) {
    if (e < l || r < s || val >= seg[idx].m1) return;
    if (s <= l && r <= e && val > seg[idx].m2) {
        applyMax(idx, val, l == r);
        return;
    }
    push(idx, l, r);
    int m = (l + r) >> 1;
    updChMin(s, e, val, idx << 1, l, m);
    updChMin(s, e, val, idx << 1 | 1, m + 1, r);
    merge(idx);
}

void updChMax(int s, int e, ll val, int idx = 1, int l = 0, int r = N - 1) {
    if (e < l || r < s || val <= seg[idx].n1) return;
    if (s <= l && r <= e && val < seg[idx].n2) {
        applyMin(idx, val, l == r);
        return;
    }
    push(idx, l, r);
    int m = (l + r) >> 1;
    updChMax(s, e, val, idx << 1, l, m);
    updChMax(s, e, val, idx << 1 | 1, m + 1, r);
    merge(idx);
}

ll query(int s, int e, int idx, int l, int r) {
    if (e < l || r < s) return 0;
    if (s <= l && r <= e) return seg[idx].s;
    push(idx, l, r);
    int m = (l + r) >> 1;
    return query(s, e, idx << 1, l, m) + query(s, e, idx << 1 | 1, m + 1, r);
}
