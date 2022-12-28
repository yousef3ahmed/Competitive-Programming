struct Trie{
	
	int nxt[N][2] , cnt[N] , nNodes , root ;
	
	int creatNode(){
		memset( nxt[ nNodes ] , -1 , sizeof( nxt[ nNodes ] ) ) ;
		return nNodes++ ;
	}
	void init(  ){
		nNodes = 0 ;
		memset( cnt , 0 , sizeof( cnt ) ) ;
		root  = creatNode() ;
	}

	void add( ll x ){
		int cur = root ;
		for( ll bit  = 31 ; ~bit  ; bit-- ){
			int in = ( ( ( 1ll<<bit ) & x ) ? 1 : 0  ) ;
			int &child = nxt[ cur ][ in ];
			if( child == -1 ) child = creatNode() ;
			cnt[ cur = child ]++ ;
		}
	}

	void erase( ll x ){
		int cur = root  ;
		for( ll bit = 31 ; ~bit ; bit-- ){
			int in = ( ( ( 1ll<<bit ) & x ) ? 1 : 0  ) ;
			int &child = nxt[ cur ][ in ] ;
			cnt[ cur = child ]-- ;
		}
	}

	int find( ll x ){
		int cur = root ;
		for( ll bit = 31 ; ~bit ; bit-- ){
			int in = ( ( ( 1ll<<bit ) & x ) ? 1 : 0  ) ;
			int &child = nxt[ cur ][ in ] ;
			if( child == -1 || !cnt[ child ] ) return 0 ;
			cur = child ;
		}

		return cnt[ cur ];
	}

}trie;