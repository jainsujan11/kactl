/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

class DSU {
  private:
	vector<int> p, sz;
	// stores previous unites
	vector<pair<int &, int>> history;

  public:
	DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

	int get(int x) { return x == p[x] ? x : get(p[x]); }

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return; }
		if (sz[a] < sz[b]) { swap(a, b); }

		// save this unite operation
		history.push_back({sz[a], sz[a]});
		history.push_back({p[b], p[b]});

		p[b] = a;
		sz[a] += sz[b];
	}

	int snapshot() { return history.size(); }

	void rollback(int until) {
		while (snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};