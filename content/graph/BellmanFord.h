/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once
int bellmanford(int n,int m,int src,int dest,vector<vector<int>> &edges){
    vector<int> dist(n+1,1e9);
    dist[src] = 0;
    for (int i = 1; i < n; i++)
    {for (int j = 0; j < m; j++){
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
            if(dist[u]!=1e9&&(dist[u]+wt)<dist[v])
            {
                dist[v] = (dist[u]+wt);
            }}}
    bool flag = 0;
    for (int j = 0; j < m; j++)
    {
        int u = edges[j][0];
        int v = edges[j][1];
        int wt = edges[j][2];
        if(dist[u]!=1e9&&(dist[u]+wt)<dist[v]) flag=1;
    }
    if(flag==0) return dist[dest];
    else return -1;
}
