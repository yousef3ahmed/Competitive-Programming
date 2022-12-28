struct LIST{
	
	
	list< ll >ls ;
	list< ll >::iterator it   ;
	int pos ;

	void init(  ){
		ls.clear() ;
		it = ls.begin() ;
		pos = 0 ;
	}
	
	/*
		0 - base ;
		insert in this position;
		after insert int org vales to right --> ;
		now it = new val ;
	*/

	void update( int idx ){
		int add =  idx - pos ;
		while( add > 0 ) add-- , it++ , pos++ ;
		while( add < 0 ) add++ , it-- , pos-- ;
	}

	void insert( int idx , ll x ){
		idx = min( idx , (int)ls.size() );
		idx = max( 0 , idx ) ;

		update( idx ) ;
		ls.insert( it , x ) ;
		it-- ;
	}

	/*
		0 - base ;
		erase this position ;
		after erase it = tar + 1 go --> ;
		or it = tar - 1 if tar == end ; 
	*/
	void erase( int idx ){
		
		if( idx >= ls.size() ) return ;
		update( idx ) ;		

		list< ll >::iterator tmp ;
		if( ls.size() > 1 ){
			if( it == ls.begin() )
				tmp = it , tmp++; 
			else 
				tmp = it , tmp-- , pos-- ;
		}

		ls.erase( it );

		if( ls.size() == 0 ){
			it = ls.begin();
			pos = 0 ; 
		}else{
			it = tmp ;
		}

	}


	ll operator[](int idx) {
		update( idx ) ;
		return *it ;
    }

	ll front( ) {
		return ls.front() ;
	}

	ll back( ){
		return ls.back() ; 
	}

	int size(){ return ls.size(); } 

}ls;

