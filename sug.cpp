struct item{
	ll val ;
	item( ){ val = -INF ; }
	item( ll v ){ val = v ; } 
	item merge( item a , item b ){
		item ret ;
		ret.val =  max( a.val , b.val );
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
	

	int find_first_index( int ind , int l , int r , ll val, const function<bool( item a , ll com )> &f) {
		
		if( l == r )
			return l ;
		
		int mid = (l+r)/2;		
		if(  f( tree[ ind*2 ] , val ) )
			return find_first_index(  ind*2 ,   l ,  mid ,  val , f ) ;
		else
			return find_first_index(  ind*2+1 ,  mid+1 , r ,  val , f ) ;
 	}

	int find_first( int ind , int left , int right , int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		if( left >=l && right<=r  ){
			if( !f( tree[ind] , val ) ) {
				return -1 ;
			}
			return find_first_index( ind , left , right , val , f ) ;
		}
		int mid = ( left + right ) / 2 ;
		int res = -1 ;
		if(  l <= mid )
			res = find_first( ind*2 , left , mid , l , r, val , f );
		
		if( res == -1 && r > mid )
			res = find_first( ind*2+1 , mid+1 , right , l , r , val , f  ) ;
		
		return res ;
	}


	int find_last_index( int ind , int l , int r, ll val , const function<bool( item a , ll com )> &f  ){
		if( l == r )
			return l ;

		int mid = ( l + r ) / 2 ;
		if( f( tree[ ind*2 + 1 ] , val ) )
			return find_last_index( ind*2+1 , mid+1 , r ,  val , f ) ;
		else
			return find_last_index( ind*2 , l , mid , val , f ) ;
	}

	int find_last( int ind , int left , int right , int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		if( left >=l && right<=r  ){
			if( !f( tree[ind] , val ) ) {
				return -1 ;
			}
			return find_last_index( ind , left , right , val , f ) ;
		}
		int mid = ( left + right ) / 2 ;
		int res = -1 ;
		if(  r > mid )
			res = find_last( ind*2+1 ,  mid+1 , right , l , r, val , f );
		
		if( res == -1 && l <= mid )
			res = find_last( ind*2 , left , mid , l , r , val , f  ) ;
		
		return res ;
	}

public:
   vector< item >tree ;
   int n ; 
   // 0 - index 

   void init( vector<ll>&a ){
		n = a.size();
		tree.resize( a.size()*4 ); 
		for( int i = 0 ; i<tree.size() ; i++ ) tree[i] = item() ;
        build( a , 1 , 0 , n-1 ) ;
	}
	
 	void update( int tar , ll val ){
	 	return update( 1 , 0 , n-1 , tar , val ) ;
	}
      
    item query( int l , int r   ){
	 	return query( 1 , 0 , n-1 , l , r  ) ;
	}

	int find_first( int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		return find_first( 1 , 0 , n - 1 , l , r , val , f )  ;
	}	

	int find_last( int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		return find_last( 1 , 0 , n-1 , l ,    r , val , f ) ;
	} 
	
}sug;
