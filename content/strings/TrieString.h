/**
 * Author: ProofByAC
 * Description: TrieString.h
 */
struct TrieString{
    
    struct node
    {
        struct node *child[26];
        bool endchar;
    };
     
    node* root = new node();
     
    void insert(string key)
    {
        node* cur = root;     
        for (int i = 0; i < key.length(); i++)
        {            
            if (!cur->child[key[i] - 'a'])
                cur->child[key[i] - 'a'] = new node();     
            cur = cur->child[key[i] - 'a'];
        }
        cur->endchar = true;
    }
    
    bool search(string key)
    {
        node* cur = root;     
        for (int i = 0; i < key.length(); i++)
        {            
            if (!cur->child[key[i] - 'a'])
                return false;     
            cur = cur->child[key[i] - 'a'];
        }
        return (cur->endchar);
    }  
    ll lcp(string key)
      {
          node* cur = root;
          ll ct = 0;
          for(int i = 0; i < key.length(); i++)
          {
            if(!cur->child[key[i] - 'a']){
              return ct;
            }
            cur = cur->child[key[i] - 'a'];
            ct++;
          }
          return ct;        
      }
};