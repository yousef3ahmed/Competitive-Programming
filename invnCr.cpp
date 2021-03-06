
ll mul( ll a , ll b ){
	return ( a*b )%MOD ;
}

ll add( ll a , ll b ){
	a+=b;
	if( a >= MOD ) a-=MOD ;
	return a ;
}

ll sub( ll a , ll b ){
	a-=b ;
	if( a < 0 ) a+=MOD ;	
	return a ;
}


ll pw( ll n  , ll count  ){
	ll ret = 1 ;
	while( count ){
		if( count & 1 ) ret = mul( n , ret ) ;
		n = mul( n , n ) ;
		count>>=1 ;
	}
	
	return ret ;
}

ll modinv(ll x) {
	return pw(x , MOD-2) ;
}
 
int Div(int x , int y) {
	return mul( x , modinv(y) ) ;
}

struct combination{

	vector<ll>fac , inv ;
	combination( int n ){
		fac.resize( n+1 ) ;
		inv.resize( n+1 ) ;
		fac[0] = 1 ;
		inv[0] = 1 ;
		
		for(int i=1 ; i<=n ; i++){
			fac[i] = mul( fac[i-1] , i ) ;
			inv[i] = modinv( fac[i] ) ;
		}
	
	}

	ll nCr( ll n , ll r ){
		if( r < 0 || n < r ) return 0 ;	
		return mul( mul( fac[n] , inv[r] ) , inv[n-r] ) ; 	
	}

	ll nPr( ll n , ll r ){
		if( r<0 || n<r ) return 0 ;
		return mul( fac[n] , inv[n-r] ) ;
	}

};

ll nCr(int n, int r) {
 
    long long p = 1, k = 1;
 
    if (n - r < r)
        r = n - r;
 
    if (r != 0) {
        while (r) {
            p *= n;
            k *= r;

            long long m = __gcd(p, k);
 
            p /= m;
            k /= m;
 
            n--;
            r--;
        }
    } else
        p = 1;
	
	return p ;
}
 

ll dp[ N ][ N ] ;
ll nCr(int n, int k) {
	
    if (dp[n][k] != -1)    
        return dp[n][k];
 
    if (k == 0) 
        return dp[n][k] = 1;
     
    if (k == n) 
        return dp[n][k] = 1;

    return dp[n][k] = nCr( n - 1, k - 1) + nCr(n - 1, k );
}
 

ll nCr( ll n ,  ll r ){
 
	if( n < r || r<=0  ) return 0LL ;
	if( r == 1 ) return n;
	if( r == n ) return 1LL ;
	
	return ( 1LL*(n*nCr( n-1 , r-1 ) )/r); 
}

