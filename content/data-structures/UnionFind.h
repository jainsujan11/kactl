/**
 * Author: AlooParatha
 * Description: UnionFind.h
 */
#pragma once
struct DSU
{
	vi par,size;
    DSU(int n) : par(n), size(n, 1) { iota(par.begin(), par.end(), 0); }
	int find(int x){return x == par[x] ? x : par[x] = find(par[x]);}
	void merge(int x, int y)
    {
        int nx = find(x); 
        int ny = find(y); 
        if(nx!=ny)
        { 
            if(size[nx]<size[ny]) swap(nx,ny);
            par[ny] = nx;
            size[nx]+=size[ny];
		}
    }
};
