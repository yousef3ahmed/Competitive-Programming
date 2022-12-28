struct item{
	ll val , lazy ;
	item( ){
		val = 0 ;
		lazy = 0 ;
	}

	item( ll v ){
		val = v ;
		lazy = 0 ;
	} 

	item merge( item a , item b ){
		item ret ;
		ret.val =   a.val + b.val  ;
		return ret ;
	}
};


struct sugtree{

private:

	vector< item >tree ;
   	int n ; 

 	void build(  vector<ll>&a , int ind  , int l  , int r    ){
	    if( l == r ){
	 		tree[ind] = item( a[l] ) ;
	        return ;
	    }
	    int m = (l+r)/2 ;
	    build( a , ind*2 , l , m   ) ;
	    build( a , ind*2+1 , m+1 , r  ) ;
	    tree[ind] = item().merge( tree[ind*2], tree[ind*2+1] ) ;
 	}
	
	
	void push( int ind , int l , int r ){
		
		if( tree[ ind ].lazy == 0 ) return ;	
		
		int all = ( r - l )+1 ;
		ll one = tree[ind].lazy/( all ) ;
		int mid = ( r+l )/2  ;

		int left = ( mid - l )+1  , right = ( r - mid ) ;

		tree[ind*2].lazy+=( one * left );
		tree[ind*2+1].lazy+=( one * right ) ;
		tree[ind*2].val+=( one * left ) ;
		tree[ ind*2+1 ].val+=( one * right ) ;

		tree[ ind ].lazy = 0 ;
	}

	
	item query(int ind , int left , int right , int l , int r  ){
		
		if( left > r || right < l ) return item() ;
		push( ind , left , right ) ;
		if( left >=l && right<=r  ) return tree[ind] ;
		int m = (left+right)/2;
		item op1 = query( ind*2 , left , m , l ,r   ) ;
		item op2 = query( ind*2+1 ,m+1 , right , l ,r  ) ;
		return item().merge(op1 , op2) ;
			
	}
	
	void update( int ind , int left , int right , int l , int r , ll val  ){
		if( left > r || right < l ) return ;

		if( left >=l && right<=r  ){
			 push( ind , left , right ) ;
			int all = ( right - left )+1 ;
			tree[ind].lazy+=( all*val );
			tree[ind].val+=( all*val ) ;
			return ;
		}

		push( ind , left , right ) ;
		int m = (left+right)/2 ;
		update( ind*2 , left , m , l , r , val   );
		update( ind*2+1 , m+1 , right , l , r, val  );
		    
		 tree[ind] = item().merge( tree[ind*2] , tree[ind*2+1] ) ;
	}

	int find_first_index( int ind , int l , int r , ll val, const function<bool( item a , ll com )> &f) {
		
		if( l == r )
			return l ;
		
		push( ind , l , r ) ;
		int mid = (l+r)/2;		
		if(  f( tree[ ind*2 ] , val ) )
			return find_first_index(  ind*2 ,   l ,  mid ,  val , f ) ;
		else
			return find_first_index(  ind*2+1 ,  mid+1 , r ,  val , f ) ;
 	}

	int find_first( int ind , int left , int right , int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		if( left >=l && right<=r  ){
			push( ind , left , right ) ;
			if( !f( tree[ind] , val ) ) {
				return -1 ;
			}
			return find_first_index( ind , left , right , val , f ) ;
		}
		
		push( ind , left , right ) ;
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

		push( ind , l , r ) ;
		int mid = ( l + r ) / 2 ;
		if( f( tree[ ind*2 + 1 ] , val ) )
			return find_last_index( ind*2+1 , mid+1 , r ,  val , f ) ;
		else
			return find_last_index( ind*2 , l , mid , val , f ) ;
	}

	int find_last( int ind , int left , int right , int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		if( left >=l && right<=r  ){
			push( ind , left , right ) ;
			if( !f( tree[ind] , val ) ) {
				return -1 ;
			}
			return find_last_index( ind , left , right , val , f ) ;
		}

		push( ind , left , right ) ;
		int mid = ( left + right ) / 2 ;
		int res = -1 ;
		if(  r > mid )
			res = find_last( ind*2+1 ,  mid+1 , right , l , r, val , f );
		
		if( res == -1 && l <= mid )
			res = find_last( ind*2 , left , mid , l , r , val , f  ) ;
		
		return res ;
	}


public:

	// 0-base 
	void init( vector< ll >&a  ){
		n =  a.size();
		tree.resize( n*9 );
		build( a , 1 , 0 , n-1 ) ;
	}
	
	void update( int l , int r , ll val ){
	 	return update( 1 , 0 , n-1 , l , r , val ) ;
	}

 	item query( int l , int r   ){
	 	return query( 1 , 0 , n-1 , l , r ) ;
	}
	
	int find_first( int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		return find_first( 1 , 0 , n - 1 , l , r , val , f )  ;
	}	

	int find_last( int l , int r , ll val , const function<bool( item a , ll com )> &f ){
		return find_last( 1 , 0 , n-1 , l , r , val , f ) ;
	} 


}sug;