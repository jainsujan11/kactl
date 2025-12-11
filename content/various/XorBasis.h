/**
 * Author: ProofByAC
 * Description: XorBasis.h
 */

class XorBasis {
public:
    int LOG;                                           
    vector<ll> base;
    int rk;

    XorBasis(int logBits = 20) {
        LOG = logBits + 1; // <= 2^LOG
        base.resize(LOG, 0);
        rk = 0;
    }

    bool exists(ll x) {
        for(int b = LOG - 1; b >= 0 && x; --b) {
            if(((x >> b) & 1) == 0) 
                continue;
            if(!base[b]) 
                return false;
            x ^= base[b];
        }
        return true;
    }

    void insert(ll x) {
        for(int b = LOG - 1; b >= 0 && x; --b) {
            if(((x >> b) & 1) == 0) 
                continue;
            if (!base[b]) {
                base[b] = x;
                ++rk;
            }
            x ^= base[b];
        }
    }

    ll maxXor(ll start = 0) {
        ll res = start;
        for(int b = LOG - 1; b >= 0; --b) {
            if(!base[b]) 
                continue;
            ll cand = res ^ base[b];
            if(cand > res) 
                res = cand;
        }
        return res;
    }
};