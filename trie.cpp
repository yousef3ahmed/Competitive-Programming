struct trie{
	trie*  child[30] ;
	int leaf ;
	trie(){
		memset( child , 0 , sizeof(child) );
		leaf = 0 ;
	}
	
	void insert( string &s , int nx ){
		if( nx == s.size() ){
			leaf = 1 ;
		} else {
			
			int cur = (s[nx] - 'a') ; 
			
			if( child[ cur ] == 0 )
				child[ cur ] = new trie() ;
				
			child[ cur ]->insert( s , nx+1 ) ;
		}
	}
	
	int check( string &s , int nx ){
		if( nx == s.size() ){
			return leaf ;
		}
		
		int cur = ( s[nx] - 'a' ) ;
		if( child[ cur ] == 0 ) return 0;
		
		return child[ cur ]->check(s ,nx+1);	
	}
	
	int chk_pri( string &s , int nx ){
		if( nx == s.size() ) return 1 ;
		
		int cur = ( s[nx] - 'a' ) ;
		if( child[ cur ] == 0 ) return 0;
		
		return child[ cur ]->chk_pri(s ,nx+1);	
		
	}
	
};
