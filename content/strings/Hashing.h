/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once
//dp[i]=31^i
//dp2[i]=1/31^i
int dp[200005],dp2[200005], dp3[200005], dp4[200005];
// bin_pow
void calc()
{
    dp[0]=1,dp2[0]=1,dp3[0]=1,dp4[0]=1;
    int t=bp(31,mod-2), t1=bp(97,mod-2);
    fr(i,1,200005) dp[i]=dp[i-1]*31%mod,dp2[i]=dp2[i-1]*t%mod,dp3[i]=dp3[i-1]*97%mod,dp4[i]=dp4[i-1]*t1%mod;
}
class String_
{
    public:
    string s;
    int n;
    vector<pii> hash, rev_hash;
    String_(string s)
    {
        this->s=s;
        n=s.size();
        hash.resize(n+1);
        rev_hash.resize(n+1);
        hash[0]={0,0};
        fr(i,1,n+1) hash[i]={(hash[i-1].ff+((s[i-1]-97) + 1)*dp[i]%mod)%mod, (hash[i-1].ss+((s[i-1]-97) + 1)*dp3[i]%mod)%mod};
        rev_hash[0]={0,0};
        fr(i,1,n+1) rev_hash[i]={(rev_hash[i-1].ff+((s[n-i]-97) + 1)*dp[i]%mod)%mod, (rev_hash[i-1].ss+((s[n-i]-97) + 1)*dp3[i]%mod)%mod};
    }
    pii get_hash(int l, int r)
    {
        return {(hash[r+1].ff-hash[l].ff+mod)%mod*dp2[l]%mod, (hash[r+1].ss-hash[l].ss+mod)%mod*dp4[l]%mod};
    }
    pii get_rev_hash(int l, int r)
    {
        return {(rev_hash[r+1].ff-rev_hash[l].ff+mod)%mod*dp2[l]%mod, (rev_hash[r+1].ss-rev_hash[l].ss+mod)%mod*dp4[l]%mod};
    }
};