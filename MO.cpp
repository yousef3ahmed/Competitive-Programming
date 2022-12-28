const ll  N =  1e6 + 16 , MOD = 1e9+7 , INF = 1e18 , blk = 287 ;
 
 
struct item{
	int l , r , ind ;
	item(){}
	item( int l_ , int r_ , int ind_ ): l( l_ ) , r( r_ ) , ind( ind_ ){ }
};
 
bool com( item a , item b ){
	if( a.l/blk != b.l/blk )
		return a.l < b.l ;
	return a.r < b.r ;
}
 

// hints ;
// pass vc 1 base ;
// l and r query 1 base
// pass query 0 base ;

struct MOo {
	
	// 1 base for error
	ll curl=1 , curr=1  , ans=1  ;
	int frq[ N ] ;
	vector<item>query;
	vector<ll>a , as ;
	
	void init( vector< item >&qu , vector< ll >&vc ){	
 
		query = qu ;
		a = vc ;
		sort( query.begin() , query.end() , com ) ;
		as.resize( query.size() ) ;
		for( int i = 0 ; i <= a.size() + 7 ; i++ ) frq[ i ] = 0 ; 
		ans = 1 ;
		curl=1 , curr=1;
		for( int  i = 0 ; i < query.size() ; i++ ) Mo( i ) ;
	}
 
	vector< ll > Answer(  ){  return as ; }
 
	void update(  ){  while( frq[ ans ] ) ans++ ; }
 
	void add(ll val){
	
		frq[ val ] = 1 ;
		update( ) ;
	}
 
	void rem( ll val ){
		
		frq[ val ] = 0 ; 
		if( val < ans ){
			ans = val ;
		}
		
	}
 
	void Mo( int i ){
	
		int l = query[i].l , r = query[i].r ;
		
		while( curl > l ) add( a[--curl] );
		while( curr < r+1 ) add( a[curr++] );
 
		while( curl < l ) rem( a[curl++] ) ;
		while( curr > r+1 ) rem(  a[--curr] );
		
		as[query[i].ind] = ans;
	}
 
}mo;
 