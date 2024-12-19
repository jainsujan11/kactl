/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once
class mo_algorithm
{
public:
 int n, q, block_size;
 vector<int> a;
 vector<pair<int, pii>> queries;
 vector<int> answers;
 int answer, val;
 mo_algorithm(int n, int q, vector<int> a, vector<pair<int, int>> queries)
 {
  this->n = n;
  this->q = q;
  this->a = a;
  for (int i = 0; i < q; i++)
   this->queries.push_back({queries[i].first, {queries[i].second, i}});
  block_size = sqrt(n);
  answers.resize(q);
  val = 0;
 }
 inline void add(int x) {val--;} // Try your best to keep this O(1) since n*root(n)*log(n) is too slow
 inline void remove(int x) {val--;}
 void process()
 {
  sort(queries.begin(), queries.end(), [this](pair<int, pii> x, pair<int, pii> y) {
   int block_x = x.first / block_size;
   int block_y = y.first / block_size;
   if (block_x != block_y)
    return block_x < block_y;
   return x.second.first < y.second.first;
  });
  int l = 0, r = -1;
  for (auto z : queries)
  {
   int x = z.first, y = z.second.first;
   while (r < y)
    add(a[++r]);
   while (r > y)
    remove(a[r--]);
   while (l < x)
    remove(a[l++]);
   while (l > x)
    add(a[--l]);
   answers[z.second.second] = (val == 0);
  }
 }
};