struct item{
	ll val ;
	item( ){ val = INF ; }
	item( ll v ){ val = v ; } 
	item merge( item a , item b ){
		item ret ;
		ret.val =  min( a.val , b.val );
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

   void init( vector<ll>&a ){
		n = a.size();
		tree.resize( a.size()*4 ); 
		for( int i = 0 ; i<tree.size() ; i++ ) tree[i] = item() ;
        build( a , 1 , 0 , n-1 ) ;
	}
	
    // 0 - index 
 	void update( int tar , ll val ){
	 	return update( 1 , 0 , n-1 , tar , val ) ;
	}
     
    
    item query( int l , int r   ){
	 	return query( 1 , 0 , n-1 , l , r  ) ;
	 }	 
	
}sug;
