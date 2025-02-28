/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Coordinate Comp
 * Usage: 
 * Time: About 5x as fast as cin/scanf.
 * Status: tested on SPOJ INTEST, unit tested
 */
#pragma once
struct Coordinate_Compression
{
    map<ll,ll> compVal;
    vi rev;
    int ct=0;
    // these two func are main for CC
    // add and build
    void add(ll x)
    {
        compVal[x];
    }
    void build()
    {
        ct=0;
        for(auto &pr : compVal)
        {
            pr.sc=ct++;
            rev.pb(pr.fr);
        }
    }
    inline ll getComp(ll x) {return compVal[x];}
    inline ll getOrig(ll x) {return rev[x];}
    ll getPrev(ll x)
    {
        auto it = compVal.upper_bound(x);
        // auto it = upper_bound(rev.begin(),rev.end(),x);
        it--;
        return it->second;
    }
    ll getNext(ll x)
    {
        auto it = compVal.lower_bound(x);
        // auto it = upper_bound(rev.begin(),rev.end(),x);
        it--;
        return it->second;
    }
};

void rand()
{
	const int INF = 0xFFFFFFFFFFFFFFFLL;
	const int SEED=chrono::steady_clock::now().time_since_epoch().count();
	mt19937_64 rng(SEED);
	inline int rnd(int l=0,int r=INF)
	{return uniform_int_distribution<int>(l,r)(rng);}
}