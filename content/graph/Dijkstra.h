/**
 * Author: AlooParatha
 * Description: Dijkstra.h
 */
const int mx = 1e5+10;
const int INF = 1e9+10;
// taking input for graph(connection,wt)
vector<pair<int,int>> g[mx];
vector<int> d(mx,INF),par(mx); // array for storing d 
void dijkstra(int source)
{
 vector<int> vis(mx,0); // visited array
 set<pair<int,int>> st;
 st.insert({0,source});
 d[source] = 0;
 while (st.size()>0)
 {
  auto node = *st.begin();
  int v = node.second;
  int dist = node.first;
  st.erase(st.begin());
  if(vis[v]) continue;
  vis[v]=1;
  for (auto child : g[v])
  {
   int child_v = child.first;
   int wt = child.second;
   if(d[v]+wt<d[child_v])
   {
    d[child_v] = d[v] + wt;
    st.insert({d[child_v],child_v});
   }}}}