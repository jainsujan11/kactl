/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Flow algorithm. Use add and not Eadd.
 * Status: stress-tested
 */
const int N = 1000;
template < int N, int Ne > struct flows { 
 using F = int; // flow type
 F inf = 1e9;
 int n, s, t; // Remember to assign n, s and t !
 int ehd[N], cur[N], ev[Ne << 1], enx[Ne << 1], eid = 1;
 void clear() {
 eid = 1, memset(ehd, 0, sizeof(ehd));
 }
 F ew[Ne << 1], dis[N];
 void Eadd(int u, int v, F w) {
 ++eid, enx[eid] = ehd[u], ew[eid] = w, ev[eid] = v, ehd[u] = eid;
 }
 void add(int u, int v, F w) {
 Eadd(u, v, w), Eadd(v, u, 0);
 }
 bool bfs() {
 queue < int > q;
 fr(i, 1, n+1) dis[i] = inf, cur[i] = ehd[i]; 
 q.push(s), dis[s] = 0;
 while(!q.empty()) {
  int u = q.front();
  q.pop();
  for(int i = ehd[u]; i; i = enx[i]) if(ew[i] && dis[ev[i]] == inf) {
  dis[ev[i]] = dis[u] + 1, q.push(ev[i]);
  }
 }
 return dis[t] < inf;
 }
 F dfs(int x, F now) {
 if(!now || x == t) return now;
 F res = 0, f;
 for(int i = cur[x]; i; i = enx[i]) {
  cur[x] = i;
  if(ew[i] && dis[ev[i]] == dis[x] + 1) {
  f = dfs(ev[i], min(now, ew[i])), ew[i] -= f, now -= f, ew[i ^ 1] += f, res += f;
  if(!now) break;
  }
 }
 return res;
 }
 F max_flow() {
 F res = 0;
 while(bfs())
  {
   res += dfs(s, inf);
  }
 return res;
 }
} ;