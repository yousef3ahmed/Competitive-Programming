ll mul( ll a , ll b ,ll MOD ){
	return ( a*b )%MOD ;
}
 
ll add( ll a , ll b  ,ll MOD ){
	a+=b; if( a >= MOD ) a-=MOD ;  return a ;
}
 
ll sub( ll a , ll b ,ll MOD ){
	a-=b ; if( a < 0 ) a+=MOD ;	 return a ;
}
 
 
ll logPw( ll n  , ll count , ll MOD  ){
	ll ret = 1 ;
	while( count ){
		if( count & 1 ) ret = mul( n , ret , MOD ) ;
		n = mul( n , n , MOD ) ;
		count>>=1 ;
	}	
	return ret ;
}
 
ll modinv(ll x , ll MOD) {
	return logPw(x , MOD-2  , MOD) ;
}
 
ll Div(ll x , ll y , ll MOD) {
	return mul( x , modinv(y , MOD) , MOD ) ;
}
 
ll pw[2][ N ] , inv[2][ N ] ; 
void init(  ){
	
	ll mod = 1e9 + 7 , base = 31 ;
	pw[ 0 ][ 0 ] = 1 ;
	inv[ 0 ][ 0 ] = modinv( pw[0][0] , mod ) ; 
	for( int i = 1 ; i< N ; i++ ) pw[ 0 ][ i ] = mul( pw[ 0 ][i-1] , base , mod ) , inv[ 0 ][ i ] = modinv( pw[ 0 ][i] , mod ) ;
 
	mod = 1e9 + 9 , base = 43 ;
 
	pw[ 1 ][ 0 ] = 1 ;
	inv[ 1 ][ 0 ] = modinv( pw[1][0] , mod ) ; 
	for( int i = 1 ; i< N ; i++ ) pw[ 1 ][ i ] = mul( pw[ 1 ][i-1] , base , mod ) , inv[ 1 ][ i ] = modinv( pw[ 1 ][i] , mod ) ;
}
 
 
struct MASH{
 
	ll  mod , base ;
	vector< ll >hs ;
	int n , id ;
 
	int get( char c ){
		if( c == '$' ) return 29; 
		int ind = (int)( c - 'a' ) ;
		ind++ ;
		return ind ;
	}
 
 
	void addBack( char c ){
		int sz = hs.size() ;	
		if( sz )
			 hs.push_back( add( hs[ sz - 1 ] , mul( pw[ id ][ sz  ] , get( c ) , mod ) , mod ) )  ;
		else
			hs.push_back( get( c ) ) ;
	}
 
 
	void build( string &s ){
		for( int i = 0 ; i<n ; i++ ) addBack( s[i] ) ;
	}
 
	ll range( int l , int r ){
		if( l == 0 ) return hs[ r ] ;
		return mul( sub( hs[r] , hs[l-1] , mod ) , inv[ id ][ l ] , mod ) ;
	}
 
	void init( string &cpy , int ID , ll MOD , ll BASE ){
		mod = MOD ;
		base = BASE ;
		id = ID ;
		n = cpy.size(); 
		hs.clear() ;
		build( cpy ) ;
	}
 
	int size(){
		return hs.size() ;
	}
 
};
 
struct fire  {
 
	MASH Me[2] ;
 
	void init( string &s ){
		Me[0].init( s , 0 ,  1e9+7 , 31 ) ;
		Me[1].init( s , 1 ,  1e9+9 , 43 ) ;
	}
 
	void push_back( char c ){
		Me[0].addBack( c ) ;
		Me[1].addBack( c ) ;
	}
	// 0 base
	pair< ll , ll > range( int l , int r ){
		return{ Me[0].range( l , r ) , Me[1].range( l , r ) } ;
	}
 
	int size(  ){
		return  Me[0].size() ;
	}
 
}hs[ 2 ];
 