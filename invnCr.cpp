
void check( int &a , int &b ){
    if( b < 0 ) b+=MOD ;
    if( a < 0 ) a+=MOD ;
    if( b > MOD ) b-=MOD ;
    if( a > MOD ) a-=MOD ;
}

ll mul( ll a , ll b ){
  	check( a , b );
	return ( a*b )%MOD ;
}

ll add( ll a , ll b ){
  	check( a , b );
	a+=b;
	if( a >= MOD ) a-=MOD ;
	return a ;
}

ll sub( ll a , ll b ){
	check( a , b );
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


// very importion infortions
// stars and bars
// (n+k-1) choose (k) if you can assgin 0 object to one
// ( n - 1 ) choose ( k - 1 ) if at least one ;


int andOperator(int a, int b) {
 
    // ShiftCount variables counts till which bit every value will convert to 0
      int shiftcount = 0;
    //Iterate through every bit of a and b simultaneously
      //If a == b then we know that beyond that the and value will remain constant
      while(a != b and a > 0) {
          shiftcount++;
          a = a >> 1;
          b = b >> 1;
    }
      return int64_t(a << shiftcount);
}
 


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


//  catalan ( ( )( ) ...
ll catalan = comp.nCr(2 * n , n) - comp.nCr(2 * n , n + 1);



// A Derangement is a permutation of n elements, such that no element appears in its original position
ll dp[N] ;
ll countDer(ll n)
{
  // Base cases
  if (n == 1) return 0;
  if (n == 2) return 1;
 
  ll &ret = dp[ n ] ;
  if( ~ret ) return ret ;
 
  // countDer(n) = (n-1)[countDer(n-1) + der(n-2)]
  return  ret =  mul( (n - 1) , add( countDer(n - 1)  ,  countDer(n - 2) )  )  ;
}
