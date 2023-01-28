struct SegTree{
    int tree[1<<19],sz,INIT=0;
    void init(int n){
        sz=1;
        while(sz<n)sz*=2;
        memset(tree,0,2*sz*sizeof(tree[0]));
    }
    int op(int a,int b){
        return max(a,b);
    }
    void update(int l,int r,int p,int idx,int val){
        if(l==r){
            tree[p]=val;
            return;
        }
        int md=(l+r)>>1;
        if(md>=idx)update(l,md,p*2+1,idx,val);
        else update(md+1,r,p*2+2,idx,val);
        tree[p]=op(tree[p*2+1],tree[p*2+2]);
    }
    void update(int idx,int val){
        update(0,sz-1,0,idx,val);
    }
    int query(int l,int r,int p,int l_q,int r_q){
        if(l>r_q||r<l_q)return INIT;
        if(l>=l_q&&r<=r_q)return tree[p];
        int md=(l+r)>>1;
        int ch1=query(l,md,p*2+1,l_q,r_q);
        int ch2=query(md+1,r,p*2+2,l_q,r_q);
        return op(ch1,ch2);
    }
    int query(int l,int r){
        return query(0,sz-1,0,l,r);
    }
}tree;
