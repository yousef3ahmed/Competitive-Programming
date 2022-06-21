
vector<ll>a;
int n ;
struct sugtree{
	
	vector< ll >tree , lazy;
	 
	void init( int x){
		n =  x;
		tree.resize( n*5 ); 
	}
	
	ll merge( ll  a , ll b ){
		return a+b ;
	}
		
 	void build( int ind = 1 , int l = 0 , int r = n - 1 ){
	    if( l == r ){
	 		tree[ind] = a[l] ;
	        return ;
	    }
	    int m = (l+r)/2 ;
	    build( ind*2 , l , m ) ;
	    build(ind*2+1 , m+1 , r ) ;
	    tree[ind] = merge( tree[ind*2], tree[ind*2+1] ) ;
 	}
	
	
	void push( int ind ){
		return void();
	}

	
	 ll query(int ind , int left , int right , int l , int r ){
		push( ind ) ;
		if( left > r || right < l ) return 0 ;
		if( left >=l && right<=r  ) return tree[ind] ;
		push( ind ) ;
		int m = (left+right)/2;
		ll op1 = query( ind*2 , left , m , l ,r  ) ;
		ll op2 = query( ind*2+1 ,m+1 , right , l ,r  ) ;
		return merge(op1 , op2) ;
	
	}
	
	void update( int ind , int left , int right , int tar , ll val  ){
	 	push( ind ) ;
		 if( left == right ){
		    tree[ind] = val ;
		    return ;
		 }
		 push( ind ) ;
		 int m = (left+right)/2 ;
		 if( tar <= m )
		 	update( ind*2 , left , m , tar , val  );
		 else
		    update( ind*2+1 , m+1 , right , tar , val );
		    
		 tree[ind] = merge( tree[ind*2] , tree[ind*2+1] ) ;
	 
	 }
	
	 void update( int tar , ll val ){
	 	return update( 1 , 0 , n-1 , tar-1 , val ) ;
	 }
	 
	 ll query( int l , int r ){
	 	return query( 1 , 0 , n-1 , l-1 , r-1 ) ;
	 }
	 
	
};

sugtree sug ;
// to get new index ;
int BS( int ind ){
	int l = 1 , r = n , ans = -1 ;
	while( l<=r ){
		int m = ( l+r )/2;
		
		ll cur = sug.query( 1 , m ) ;
		 
		if( cur >= ind ){
			ans = m ;
			r = m-1; 
		}else{
			l = m+1 ;
		}
	}
	
	return ans ;
}

