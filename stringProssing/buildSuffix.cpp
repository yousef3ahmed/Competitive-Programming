struct SuffixArray {
	

	vector< int > p , c ;
	string s ;

	void radix_sort( vector< array< int , 3 > > &a ) {
		int n = a.size() ;
		
		{
			vector< int > cnt( n , 0 ) ;
			for( auto u : a ) cnt[ u[1] ]++ ;

			vector< array< int , 3 > > a_new( n ) ;
			vector< int >pos( n ) ;

			pos[ 0 ] = 0 ;
			for( int i = 1 ; i<n ; i++ )
				pos[ i ] = pos[ i - 1 ] + cnt[ i - 1 ] ;
			
			for( auto x : a )
				a_new[ pos[  x[1] ]++ ] = x ;

			a = a_new ;
		}

		
		{
			vector< int > cnt( n , 0 ) ;
			for( auto u : a ) cnt[ u[0] ]++ ;

			vector< array< int , 3 > > a_new( n ) ;
			vector< int >pos( n ) ;

			pos[ 0 ] = 0 ;
			for( int i = 1 ; i<n ; i++ )
				pos[ i ] = pos[ i - 1 ] + cnt[ i - 1 ] ;
			
			for( auto x : a )
				a_new[ pos[  x[0] ]++ ] = x ;

			a = a_new ;
		}
		

	}


	void build( ){
		
		// k = 0 ;
		s+="$";
		int n = s.size() ;
		vector< pair< char , int > >a( n ) ;
		
		for( int i = 0 ; i < n ; i++ ) a[i] = { s[i] , i } ;
		sort( a.begin() , a.end() ) ;

		for( int i = 0 ; i < n ; i++ ) p[i] = a[i].second ;

		c[ p[0] ] = 0 ;
		for( int i = 1 ; i < n ; i++ ) {
			if( a[ i ].first == a[ i-1 ].first ) c[ p[i] ] = c[ p[i-1] ]  ;
			else c[ p[i] ] = c[ p[i-1] ] +  1 ;
		}

		int k = 0 ;
		while( ( 1 << k ) < n ) {
			
			vector< array< int , 3 > > a( n ) ;
			
			for( int i = 0 ; i<n ; i++ ) {
				array< int , 3 > in ;
				in[ 0 ] = c[ i ] ;
				in[ 1 ] = c[ ( i + ( 1 << k )%n )%n  ] ;
				in[ 2 ] = i ;

				a[ i ] = in ;
			}

			radix_sort( a ) ;
			for( int i = 0 ; i < n ; i++ ) p[i] = a[i][2] ;

			c[ p[0] ] = 0 ;
			for( int i = 1 ; i < n ; i++ ) {
				if( a[ i ][0] == a[ i-1 ][0] && a[ i-1 ][1] == a[i][1] ) c[ p[i] ] = c[ p[i-1] ]  ;
				else c[ p[i] ] = c[ p[i-1] ] + 1 ;
			}

			k++ ;
		}
	}

	int can( int mid , string &pat  ){
	
		int j = 0 , i = p[mid] ;

		for(  ; i < s.size() && j < pat.size() ; i++ , j++ ) {
			if( s[i] > pat[ j ] )
				return 1 ;
			
			if( s[i] < pat[ j ] )
				return 2 ;
		}

		if( i == s.size() - 1 && j != pat.size() ) return 2 ;

		return 10 ;
	}

	int lower( int st , int en , string &pat ){
		int l = st , r = en  ;
		while( l <= r ){
			int mid = ( l + r ) / 2 ;

			int cc = can( mid , pat ) ;
			if( cc == 10 ) return 1 ;

			if( cc == 1 )
				r = mid - 1 ;
			else
				l = mid + 1 ; 
		}

		return 0 ;
	}

	int find( string &pat ) {
		return lower( 0 , s.size() - 1 , pat ) ;
	}	

	void init( string &str ){
		s = str ;
		p.resize( s.size() + 1 ) ;
		c.resize( s.size() + 1 ) ;
		build() ;
	}

} suff ;
