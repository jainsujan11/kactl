/**
 * Author: AlooParatha
 * Description: ProofByAC.h
 */

struct TrieBits{
    struct node
    {
        struct node *child[2];
        int cnt = 0;
    };
     
    node* root = new node();
     
    void insert(int num)
    {
        node* cur = root;    
        for (int i = 30; i >= 0; i--)
        {           
            int isset = ((num & (1ll<<i))>0);
            if (!cur->child[isset])
                cur->child[isset] = new node();    
            cur = cur->child[isset];
            cur->cnt++;
        }       
    } 
 
    ll query(int num,int num2){        
        node* cur = root;
        ll ans = 0; int eq = 0;
        for(int i = 30; i >= 0; i--)
        {
            int isset = ((num & (1<<i))>0);
            int isset2 = ((num2 & (1<<i))>0);
            if(!isset2){
                  if(cur->child[(isset^1)])
                      ans += 1ll*(cur->child[isset^1])->cnt;
                  if(cur->child[isset]){
                      cur = cur->child[isset];
                      eq = cur->cnt;
                  }
                  else{
                      eq = 0;
                      break;
                  }                      
            }
            else{                  
                  if(cur->child[isset^1]){
                      cur = cur->child[isset^1];
                      eq = cur->cnt;
                  }
                  else{
                      eq = 0;
                      break;
                  }                     
            }
        }
        return ans + 1ll*eq;
    }
    ll mx(ll x) {
        node* cur = root;
        ll ans = 0;
        for (int i = 30; i >= 0; i--) {
            int isset = ((x & (1 << i)) > 0);
            if (cur->child[isset ^ 1]) {
                ans |= (1 << i);
                cur = cur->child[isset ^ 1];
            } else {
                cur = cur->child[isset];
            }
        }
        return ans;
    }
    ll mn(ll x) {
        node* cur = root;
        ll ans = 0;
        for (int i = 30; i >= 0; i--) {
            int isset = ((x & (1 << i)) > 0);
            if (cur->child[isset]) {
                cur = cur->child[isset];
            } else {
                ans |= (1 << i);
                cur = cur->child[isset ^ 1];
            }
        }
        return ans;
    }
};