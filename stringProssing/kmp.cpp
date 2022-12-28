char pat[N] , str[N] ;
int f[N] ;

int go( int l , char c ){
	
	while( l && c != pat[l] ) l = f[l-1];	
	return	l += ( c == pat[ l ] ) ;
}

void compute(  ){
	
	if( !pat[0] ) return ;	
	f[0] = 0 ;
	for( int i = 1; pat[i] ; i++ ){
		f[i] = go( f[i-1] , pat[i] ) ;
	}
}

vector< int > match(  ){
	compute() ;
	int l = 0 ;
	vector< int > ans;

	for( int i = 0 ; str[i] ; i++ ){
		l = go( l , str[i] ) ;
		if( !pat[l] ) ans.push_back( i - l + 1 ) ;
	}

	return ans ;
}


// scanf("%s"  , pat) ;
// scanf("%s" , s) ;

// how many pat in string ;

///////////////////////////////////////////////////////////////////////////////////////

struct KMP{
 
	string pat ;
	int f[N] ;
 
	int go( int l , char c ){
		
		while( l && c != pat[l]  ) l = f[l-1];	
		return	l += ( c == pat[ l ] ) ;
	}
 
	void init( string &s ){
		
		if( s.size() == 0 ) return ;	
		
		f[0] = 0 ;
		pat = s ;
		pat+='$' ;
 
		for( int i = 1; i < pat.size() ; i++ )
			f[i] = go( f[i-1] , pat[i] ) ;
	
	}
 
	int match( string &s ){
		
		if( pat.size() == 0 ) return 0 ;
 
		int l = 0 , mx = 0 ;
		for( int i = 0 ; i < s.size() ; i++ ){
			l = go( l , s[i] ) ;
 
			if( pat[ l ] == '$'  ) return l ;
		}
 
		return l ;
	}
 
} kmp[ 3 ];