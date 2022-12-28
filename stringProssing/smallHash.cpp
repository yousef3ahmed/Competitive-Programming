ll pw[ 12 ]  ;

void init( ){
    pw[0] = 1 ;
    for( int i = 1 ; i<12 ; i++ ) pw[i] = ( pw[i-1] * 27ll ) ;
}


ll addhash( int pos , char a , ll oldHash ){
    ll ret = oldHash + ( ( ( a - 'a' ) + 1ll ) * pw[pos] ) ;
    return ret ;
}

ll delethash( int pos , char a , ll oldHash ){
    ll ret = oldHash - ( ( ( a - 'a' ) + 1ll ) * pw[pos] ) ;
    return ret ;
}

ll createHash( string &a ){
    ll ret = 0 ;
    int n = a.size() ;
    for( int i = 0 ; i<n ; i++ ) ret += ( ( ( a[i] - 'a' ) + 1ll ) * pw[i] ) ;
    return ret ;
}

pair< ll , ll > createHash( string &a  ){
    pair< ll , ll > ret = { 0 , 0 } ;
    int n = a.size() ;
    ll modd = 1e9 + 7 ;
    for( int i = 0 ; i<n ; i++ ) ret.first = add( ret.first , mul( pw[ 0 ][ i ] , ( a[i] - 'a' )+1ll , modd ) , modd ) ;
    
    modd = 1e9 + 9 ;
    for( int i = 0 ; i<n ; i++ ) ret.second = add( ret.second , mul( pw[ 1 ][ i ] , ( a[i] - 'a' )+1ll , modd ) , modd ) ;
    
    return ret ;
}