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

void preprocess(  ){
	
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
 
	int mod = 1e9 + 7 , base = 31 , n ;
	vector< int >hs[2];
  vector< int > arr ;

	void build( ){

    mod = 1e9 + 7 , base = 31;
    hs[0][0] = arr[0] ;
		for( int i = 1 ; i<n ; i++ ){
      hs[0][i] = add( hs[0][i-1] , mul( pw[ 0 ][ i  ] , arr[i] , mod ) , mod ) ;
    }

    mod = 1e9 + 9 , base = 43;
    hs[1][0] = arr[0] ;
		for( int i = 1 ; i<n ; i++ ){
      hs[1][i] = add( hs[1][i-1] , mul( pw[1][i] , arr[i] , mod ) , mod ) ;
    }

	}
 
	pair< int , int > range( int l , int r ){
		if( l == 0 ) return { hs[0][r] , hs[1][r] } ;

    pair< int , int >ret ;

    mod = 1e9 + 7 , base = 31;
    ret.first = mul( sub( hs[0][r] , hs[0][l-1] , mod ) , inv[0][ l ] , mod );

    mod = 1e9 + 9 , base = 43;
    ret.second = mul( sub( hs[1][r] , hs[1][l-1] , mod ) , inv[1][ l ] , mod );

		return ret ;
	}
 
	void init( vector< int >&a ){
		n = a.size(); 
    arr = a ;
		hs[0].clear() ;
    hs[0].resize( n );
    hs[1].clear() ;
    hs[1].resize( n );
		build( );
	}
 
}hs;
