/**
 * Author: Benjamin Qi, chilli
 * Date: 2020-04-04
 * License: CC0
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Description: Given a weighted bipartite graph, matches every node on
 * the left with a node on the right such that no
 * nodes are in two matchings and the sum of the edge weights is minimal. Takes
 * cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j] and
 * returns (min cost, match), where L[i] is matched with
 * R[match[i]]. Negate costs for max cost. Requires $N \le M$.
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, stress-tested
 */
#pragma once
typedef long double ld;
vector<int> hungarian(const vector<vector<ld>>& A, int n) {
    // Labels for workers (u) and jobs (v)
    vector<ld> u(n + 1, 0.0), v(n + 1, 0.0);
    
    // p[j] - the worker assigned to job j
    vector<int> p(n + 1, 0);
    
    // way[j] - the previous job in the augmenting path for job j
    vector<int> way(n + 1, 0);
    
    for(int i = 1; i <= n; ++i){
        p[0] = i;
        int j0 = 0;
        // minv[j] - minimum reduced cost for job j
        vector<ld> minv(n + 1, inf);
        // used[j] - whether job j is used in the current augmenting path
        vector<bool> used(n + 1, false);
        
        int j1;
        while(true){
            used[j0] = true;
            int i0 = p[j0];
            ld delta = inf;
            j1 = 0;
            
            // Iterate over all jobs to find the minimum delta
            for(int j = 1; j <= n; ++j){
                if(!used[j]){
                    ld cur = A[i0 - 1][j - 1] - u[i0] - v[j];
                    if(cur < minv[j]){
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if(minv[j] < delta){
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            
            // Update labels
            for(int j = 0; j <= n; ++j){
                if(used[j]){
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else{
                    minv[j] -= delta;
                }
            }
            
            j0 = j1;
            if(p[j0] == 0)
                break;
        }
        
        // Augmenting path: update the matching
        do{
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while(j0 != 0);
    }
    
    // Construct the result: ans[i] = j means worker i is assigned to job j
    vector<int> ans(n, -1);
    for(int j = 1; j <= n; ++j){
        if(p[j] != 0){
            ans[p[j] - 1] = j - 1;
        }
    }
    
    return ans;
}