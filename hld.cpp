#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define int long long
 
 
const int  N =  2e5 + 17  , MOD = 998244353  , INF = 1e16 ;
 
vector<int> parent, depth, heavy, head, pos;
int cur_pos;
const int LOG=19;
int up[N][LOG];
 
struct item{
	ll val ;
	item( ){ val = 0 ; }
	item( ll v ){ val = v ; } 
	item merge( item a , item b ){
		item ret ;
		ret.val = max( a.val  , b.val ) ;
		return ret ;
	}
};
 
struct sugtree{
 
private: 	
 	void build(  vector<ll>&a , int ind , int l  , int r  ){
	    if( l == r ){
	 		tree[ind] = item( a[l] ) ;
	        return ;
	    }
	    int m = (l+r)/2 ;
	    build( a , ind*2 , l , m   ) ; build( a , ind*2+1 , m+1 , r  ) ;
	    tree[ind] = item().merge( tree[ind*2], tree[ind*2+1] ) ;
 	}
	
	
	item query(int ind , int left , int right , int l , int r  ){
		if( left > r || right < l ) return item() ;
		if( left >=l && right<=r  ) return tree[ind] ;
		int m = (left+right)/2;
		item op1 = query( ind*2 , left , m , l ,r   ) , op2 = query( ind*2+1 ,m+1 , right , l ,r  ) ;
		return item().merge(op1 , op2) ;
	
	}
    
    void update( int ind , int left , int right , int tar , ll val  ){
		 if( left == right ){
		    tree[ind] = item( val ) ;
		    return ;
		 }
		 int m = (left+right)/2 ;
		 if( tar <= m ) update( ind*2 , left , m , tar , val   );
		 else update( ind*2+1 , m+1 , right , tar , val  );
		    
		 tree[ind] = item().merge( tree[ind*2] , tree[ind*2+1] ) ;
	}
	
public:
   vector< item >tree ;
   int n ; 
   // 0 - index
 
  void init( int nn  ){
		n = nn;
		tree.resize( n*4 ); 
    vector< int >a( n , 0 ) ;
		for( int i = 0 ; i<tree.size() ; i++ ) tree[i] = item() ;
    build( a , 1 , 0 , n-1 ) ;
	}
	
 	void update( int tar , ll val ){
	 	return update( 1 , 0 , n-1 , tar , val ) ;
	}
      
    item query( int l , int r   ){
	 	return query( 1 , 0 , n-1 , l , r  ) ;
	}
	
}seg;
 
 
int dfs(int v, vector<vector<int>> const& adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            depth[c] = depth[v] + 1;
            up[c][0]=v;
            for(int i=1;i<LOG;i++){
                up[c][i]=up[ up[c][i-1] ][i-1];
            }
            parent[c] = v;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    return size;
}
 
int get_lca(int u,int v) {
    
    if(depth[u]<depth[v]) swap(u,v);
    int k=depth[u]-depth[v];
 
    for(int i=LOG-1;i>=0;i--)
    {
        if(k & (1<<i)){
            u=up[u][i];
        }
    }
    if(u==v) return u;
 
    for(int i=LOG-1;i>=0;i--)
    {
        if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }
    return up[u][0];
}
 
void decompose(int v, int h, vector<vector<int>> const& adj) {
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c, adj);
    }
}
 
// 0-base;
// in query pass any two nodes 

int queryPath(int u, int v) {
    int queryRes = 0;  // be careful from u = v for isValueOnEdge
    for (; head[u] != head[v]; v = parent[head[v]]) {
      if (depth[head[u]] > depth[head[v]])
        swap(u, v);

      queryRes = max( queryRes , seg.query( pos[head[v]], pos[v]).val ) ;
    }
    if (depth[u] > depth[v])
      swap(u, v);
    
    queryRes  = max(  queryRes , seg.query( pos[u] , pos[v]).val ) ;
    
    return queryRes;  // u = LCA node
  }

// update pass only node and new val
void update( int node , int val  , vector< int >&vals ){
    vals[node] = val;
    seg.update(pos[node],vals[node]);
}
 
void init(vector<vector<int>> const& adj ,  vector< int >&val  ) {
    
    int n = adj.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 0;
    
    for(int i=0 ; i < n ; i++){
      for(int j=0;j<19;j++){
          up[i][j]=0;
      }
    }
 
    dfs(0, adj);
    decompose(0, 0, adj);
    seg.init( n ) ;
    for(int i=0 ; i < n ;i++){
      seg.update(pos[i],val[i]);
    }
}
 
 
void Solve( int tc ){ 
    int n,q; cin>>n>>q;
    
    vector<vector<int>>adj(n);
    vector< int >val( n ) ;
 
    for(int i=0;i<n;i++) cin>>val[i];
    
    for(int i=0;i<n-1;i++){
        int x,y; cin>>x>>y;
        x-- , y-- ;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
 
    init(adj , val);
    while(q--){
        int x,a,b;
        cin>>x>>a>>b;
        if(x==1){
            a-- ;
            update( a , b , val ) ;
        }
        else{
          a-- , b-- ;
          cout<<queryPath( a , b )<<"\n";
        }
    }
} 
 
 
int32_t main() {
 
//   freopen( "input.txt" , "r", stdin);
 
  #ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0); cin.tie(0);
  #endif
 
  int t = 1 , tc =1 , n  ;
  // cin>>t;
  while( t-- ) Solve( tc++ ) ;
}