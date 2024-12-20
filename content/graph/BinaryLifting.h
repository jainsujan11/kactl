/**
 * Author: AlooParatha
 * Description: BinaryLifting.h
 */
class Binary_lift{
    public:
        int n,l,timer;
        vector<vector<int>> adj, up, min_v;
        vector<int> depth, tin, tout;
        Binary_lift(int n){
            this->n = n;
            this->l = log2(n)+1;
            adj.resize(n);
            up.resize(n, vector<int>(l, -1));
            min_v.resize(n, vector<int>(l, inf));
            depth.resize(n);tin.resize(n);tout.resize(n);
            timer = 0;
        }
        // skip if path min not required
        void set_min_v(vi& a){
            fr(i,0,n) min_v[i][0] = a[i];
        }
        void add_edge(int u, int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        void dfs(int u, int p, vi& a, int d=0){
            up[u][0] = p;
            depth[u] = d;  
            tin[u] = timer++;
            for(int i=1;i<l;i++){
                if(up[u][i-1] != -1){
                    up[u][i] = up[up[u][i-1]][i-1];
                    // skip if path min not required
                    min_v[u][i] = min(min_v[u][i-1], min_v[up[u][i-1]][i-1]);
                }
            }
            for(int v: adj[u]){
                if(v != p) dfs(v, u,a,d+1);
            }
            tout[u] = timer;
        }
        int lift(int u, int k){
            for(int i=l-1;i>=0;i--){
                if(k >= (1<<i)){
                    u = up[u][i];
                    k -= (1<<i);
                }
            }
            return u;
        }
        int lca(int u, int v){
            if(depth[u] < depth[v]) swap(u,v);
            u = lift(u, depth[u]-depth[v]);
            if(u == v) return u;
            for(int i=l-1;i>=0;i--){
                if(depth[u]<(1<<i)) continue;
                if(up[u][i] != up[v][i]){
                    u = up[u][i];
                    v = up[v][i];
                }
            }
            return up[u][0];
        }
        int get_kth_node_on_path(int u, int v, int k){
            int lca = this->lca(u,v);
            int dist = this->depth[u] + this->depth[v] - 2*this->depth[lca];
            if(k > dist) return -1;
            if(k == 0) return u;
            if(k == dist) return v;
            if(this->depth[u] - this->depth[lca] >= k)
                return this->lift(u, k);
            return this->lift(v, dist-k);
        }
        int get_min_on_path(int u, int v){
            int lca = this->lca(u,v);
            int ans = inf;
            for(int i=l-1;i>=0;i--){
                if(this->depth[u] - (1<<i) >= this->depth[lca]){
                    ans = min(ans, this->min_v[u][i]);
                    u = this->up[u][i];
                }
            }
            for(int i=l-1;i>=0;i--){
                if(this->depth[v] - (1<<i) >= this->depth[lca]){
                    ans = min(ans, this->min_v[v][i]);
                    v = this->up[v][i];
                }
            }
            ans = min(ans, this->min_v[u][0]);
            ans = min(ans, this->min_v[v][0]);
            return ans;
        }
        int first_node_less_equal_k_on_path(int u, int v, int k, vi& a){
            if(a[u] <= k) return u;
            int lca = this->lca(u,v);
            for(int i=l-1;i>=0;i--){
                if(this->depth[u] - (1<<i) >= this->depth[lca]){
                    if(this->min_v[u][i] <= k) continue;
                    u = this->up[u][i];
                }
            }
            int j = -1;
            if(u!=lca) return u;
            if(a[u] <= k) return u;
            for(int i=l-1;i>=0;i--){
                if(this->depth[v] - (1<<i) >= this->depth[lca]){
                    int height = this->depth[v] - this->depth[lca] - (1<<i);
                    int node = this->lift(v, height);
                    j=i;
                    if(this->min_v[node][i] <= k) v = node;
                    else lca = up[v][i];
                    break;
                }
            }
            for(int i=j;i>0;i--){
                if(this->depth[v] - (1<<i) >= this->depth[lca]){
                    int node = this->up[v][i-1];
                    if(this->min_v[node][i-1] <= k) v = node;
                    else lca = node;
                }
            }
            return v;
        }
        int get_dist(int u, int v){
            return this->depth[u] + this->depth[v] - 2*this->depth[this->lca(u,v)];
        }
};