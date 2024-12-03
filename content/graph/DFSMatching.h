struct bipartite {
    int n, m;
    vector<vector<int>> g;
    vector<bool> paired;
    vector<int> match;

    bipartite(int n, int m): n(n), m(m), g(n), paired(n), match(m, -1) {}
    
    void add(int a, int b) {
        g[a].push_back(b);
    }

    vector<size_t> ptr;
    bool kuhn(int v) {
        for(size_t &i = ptr[v]; i < g[v].size(); i++) {
            int &u = match[g[v][i]];
            if(u == -1 || (dist[u] == dist[v] + 1 && kuhn(u))) {
                u = v;
                paired[v] = true;
                return true;
            }
            
        }
        return false;
    }

    vector<int> dist;
    bool bfs() {
        dist.assign(n, n);
        int que[n];
        int st = 0, fi = 0;
        for(int v = 0; v < n; v++) {
            if(!paired[v]) {
                dist[v] = 0;
                que[fi++] = v;
            }
        }
        bool rep = false;
        while(st < fi) {
            int v = que[st++];
            for(auto e: g[v]) {
                int u = match[e];
                rep |= u == -1;
                if(u != -1 && dist[v] + 1 < dist[u]) {
                    dist[u] = dist[v] + 1;
                    que[fi++] = u;
                }
            }
        }
        return rep;
    }
    
    auto matching() {
        while(bfs()) {
            ptr.assign(n, 0);
            for(int v = 0; v < n; v++) {
                if(!paired[v]) {
                    kuhn(v);
                }
            }
        }
        vector<pair<int, int>> ans;
        for(int u = 0; u < m; u++) {
            if(match[u] != -1) {
                ans.emplace_back(match[u], u);
            }
        }
        return ans;
    }
};
