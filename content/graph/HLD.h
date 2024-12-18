/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. fr(i, 0, n) b[pos[i]] = a[i];
 */

class HLD{
public:
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    vector<vector<int>> adj;
 
    int dfs(int v) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size;
    }
 
    void decompose(int v, int h) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c);
        }
    }
 
    void build()
    {
        dfs(0);
        decompose(0, 0);
    }
 
    HLD(int n) {
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        adj = vector<vector<int>>(n);
        cur_pos = 0;
    }
 
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    vi query(int a, int b, int x, SegmentTree& st) {
        vi res;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            vi cur_heavy_path_max = st.query(pos[head[b]], pos[b], x);
            for(auto i: cur_heavy_path_max) res.pb(i);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        vi last_heavy_path_max = st.query(pos[a], pos[b], x);
        for(auto i: last_heavy_path_max) res.pb(i);
        return res;
    }
};