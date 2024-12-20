/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once
class MaxSparseTable
{
public:
    int n;
    vector<vector<int>> st;
    vector<int> log;
    MaxSparseTable(vector<int> &a)
    {
        n = a.size();
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++)
            log[i] = log[i / 2] + 1;
        st.assign(n, vector<int>(log[n] + 1));
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];
        for (int j = 1; j <= log[n]; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r)
    {
        int j = log[r - l + 1];
        return max(st[l][j], st[r - (1 << j) + 1][j]);
    }
};