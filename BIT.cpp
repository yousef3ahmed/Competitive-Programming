struct BIT{
	// 0 based ;
	vector< ll > tree ;
	BIT(){}
	
	void init( int n ){
		int sz = 0 ;
		while( ( 1 << sz ) <= n ) sz++;
		tree.assign( 1<<sz , 0 ) ;
	}

	void update( int pos , ll val ){
		for( ++pos ; pos <= tree.size() ; pos+=( pos & (-pos) ) ) tree[ pos - 1 ] += val ;
	}

	ll get( int pos ){
		ll ret = 0 ;
		for( ++pos ; pos ; pos-=( pos&(-pos) )  ) ret+=tree[ pos-1 ] ;
		return ret ;
	}


	ll range( int str , int end ){
		return get( end  ) - get( str - 1 ) ;
	}


	int lower_bound( int val ){
		int st = 0  ;
		for( int sz = tree.size() >> 1 ; sz ; sz>>=1 ){
			if( tree[ st + sz  - 1] < val ){
				val-=tree[ ( st+=sz )  - 1] ;
			}
		}

		return st;
	}
};

struct Myset{

	BIT bit;
	Myset(){}
	
	void init( int n ){
		bit.init(n) ;
		bit.update( 0  , -1 ) ;
	}

	void insert( int val ){
		bit.update( val , 1 ) ;
	}

	void erase( int val  ){
		bit.update( val , -1 ) ;
	}

	ll count( int val ){
		return bit.range( val-1 , val ) ;
	}

	int size(  ){
		return bit.get( bit.tree.size()-1 )+1 ;
	}

	int operator[](int idx) {
       return bit.lower_bound( idx ) ;
    }

	int at( int idx ){
		return bit.lower_bound( idx ) ;
	}

	// return ind ;
	int lower_bound( ll val ){
		int l = 0 , r = this->size()-1  , ans = -1 ;
		while( l<=r ){
			int mid = ( l+r )/2 ;
			if( this->at( mid ) < val ){
				ans = mid ;
				l = mid + 1 ;
			}else{
				r = mid-1 ;
			}
		}
		return ans ;
	}

	ll CntLes( ll val ){
		ll cnt = lower_bound( val ) ;
		if( cnt == -1 ) return 0 ;
		return cnt + 1 ;
	}

	ll CntLesOrEqual( ll val ){
		ll cnt = lower_bound( val ) ;
		if( cnt == -1 ) cnt = 0 ;
		return cnt + this->count( val ) ;
	}

}myset;
