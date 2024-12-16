/**
 * Author: AlooParatha
 * Description: Seg_tree.h
 */

struct node{
    int mini;int ct;
    node(int m=1e9,int c=0){
        mini = m;
        ct = c;
    }
};
struct SegTree{
    const int range = 1e5;
    int arr[range];
    node segment[4*range];
    node merge(node& a,node& b)
    {
        if(a.mini==b.mini)
        {
            node c(a.mini,a.ct+b.ct);
            return c;
        }
        else if(a.mini<b.mini) return a;
        else return b;
    }
    // tree is 1-indexed // arr is global
    void build(int idx,int low,int high) // call(build(1,0,n-1))
    {
        if(low==high)
        {
            segment[idx] = node(arr[low],1);
            return;
        }
        int mid = low + (high - low)/2;
        build(2*idx,low,mid);
        build(2*idx+1,mid+1,high);
        segment[idx] = merge(segment[2*idx],segment[2*idx+1]);
    }
    node query(int idx,int low,int high,int l,int r) // call query(1,0,n-1,l,r)
    {
        if(l<=low&&high<=r) return segment[idx]; 
        if (high<l||low>r) return node(); 
        int mid = low + (high-low)/2;
        node left = query(2*idx,low,mid,l,r);
        node right = query(2*idx+1,mid+1,high,l,r);
        return merge(left,right);
    }
    void pointUpdate(int idx,int low,int high,int pos_in_arr,int val)
    {
        if(pos_in_arr<low||pos_in_arr>high) return;
        if(low==high)
        {
            segment[idx]=node(val,1);
            arr[low] = val;
            return;
        }
        int mid = low + (high - low)/2;
        pointUpdate(2*idx,low,mid,pos_in_arr,val);
        pointUpdate(2*idx+1,mid+1,high,pos_in_arr,val);
        segment[idx] = merge(segment[2*idx],segment[2*idx+1]);
    }
};