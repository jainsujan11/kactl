/**
 * Author: Aloo Paratha
 * Description: IntervalContainer.h
 */
#pragma once

struct non_overlapping_segment{
    set<pair<int,int>> seg;
    non_overlapping_segment()
    {
        seg.clear();
    }
    int insert(int lo, int hi)
    {
        auto it = seg.upper_bound({lo,0});
        int added = 0;
        if(it != seg.begin())
        {
            --it;
            if((*it).ss >= lo)
            {
                added -= (*it).ss - (*it).ff + 1;
                lo = (*it).ff;
                hi = max(hi,(*it).ss);
                seg.erase(it);
            }
        }
        while(true)
        {
            auto it = seg.lower_bound({lo,0});
            if(it == seg.end()) break;
            if((*it).ff > hi) break;
            hi = max(hi,(*it).ss);
            added -= (*it).ss - (*it).ff + 1;
            seg.erase(it);
        }
        added += hi - lo + 1;
        seg.insert({lo,hi});
        return added;
    }
};
