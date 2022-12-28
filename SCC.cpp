
vector< ll >adj[N] , radj[N] ;
int vis[ N ] , vid , stk[N] , sksz , n , comid[ N ] , npc ;
void init( int num ){ memset( vis , 0 ,  num * sizeof( vis[0] ) ); vid = 1; sksz = 0; npc = 0; }

void dfs1( int u ){
	vis[ u ] = vid ;

	for( auto v : adj[u] ){
		if( vis[v] == vid ) 
			continue;
		dfs1( v ) ;
	}

	stk[ sksz++ ] = u ;
}

void dfs2( int u , int id ) {
	vis[u] = vid ;
	comid[ u ] = id ; 

	for( auto v : radj[u] ){
		if( vis[v] == vid ) 
			continue;

		dfs2( v , id ) ;
	}
}

void go( ){
	
	vid++ ;	
	for( int i = 0 ; i<n ; i++ ){
		if( vis[ i ] == vid ) continue;
		dfs1( i ) ;
	}

	vid++ ;
	for( int i = n-1 ; ~i ; i-- ){
		if( vis[ stk[i] ] == vid ) continue;
		dfs2( stk[i] , npc++ ) ;
	}
}
