struct LCA{
	
	vector< int > tin , tout , d ;
	vector< vector< int > >up ;
	int time = 0 ;

	void dfs( int node , int par  , int deep , vector< vector<int> >&adj ){
		
		d[node] = deep ;
		tin[ node ] = time++; 
		up[ node ][ 0 ] = par ;

		for( int i=1 ; i<30 ; i++ ){
			up[ node ][i] = up[ up[node][i-1] ][i-1] ;
		}

		for(auto u : adj[node]){
			if( u == par ) continue ;
			dfs( u , node  , deep+1 , adj ) ;
		}

		tout[node] = time++ ;
	}
	
	
	int is_ancestor( int u , int v ){
		return (tin[u] <= tin[v] && tout[u] >= tout[v]) ;
	}
	

	int lca(  int u , int v ){
		if( is_ancestor( u , v ) ) return u ;
		if( is_ancestor( v , u ) ) return v ;

		for(int i=29  ; i>=0 ; i--){
			if( !is_ancestor( up[u][i] , v ) )
				u = up[u][i] ;

		}

		return up[u][0] ;
	}
	
	ll dist( int u , int v ){
		return d[u] + d[v] - 2*d[ lca( u , v ) ] ;
	}
	
	
	void preprocess( int n , vector<vector<int>>&adj ){
		tin.resize( n+1 ) ;
		tout.resize( n+1 ) ;
		d.resize( n+1 ) ;
		time = 0 ;
		up.resize( n+1 , vector<int>(30) ) ;
		dfs( 0 , 0 , 0 , adj ) ;
	}

};


// find k-Anc or min or mx ( from root to node ) ;

ll dp[20][ N ]  , cost[N] , Mincost[20][N] , n ;
vector< int >adj[ N ];

void dfs( int nd , int pr ){
	dp[0][nd] = pr ;
	Mincost[0][nd] = cost[nd];

	for( auto u : adj[nd] ){
		if( u == pr ) 
			continue;
		dfs( u , nd ) ;
	}
}


int kth_anc( int nd , int k ){	
	for( int i = 0 ; i < 20 ; i++ ){
		if( k & ( 1 << i ) )
			nd = dp[i][nd] ;
	}
	return nd ;
}

ll Mn( int u  ){
	
	ll ans = INF ;
	for( int i = 0 ; i<20  ; i++ )
		ans = min( ans , Mincost[i][u] ) ;

	return ans; 
}

void goLca(  ){
	
	dfs( 0 , 0 , 0 ) ;
	
	for( int i = 1 ; i < 20 ; i++ ){
		for( int u = 0 ; u < n ; u++ ){
			
			dp[ i ][ u ] = dp[ i - 1 ][ dp[ i - 1 ][u] ] ;
			
			Mincost[i][u] = min( Mincost[i][u] ,
								 Mincost[ i - 1 ][  dp[ i - 1 ][u] ] ) ;
		}
	}
}

void init( ){ for( int i = 0 ; i<n ; i++ ) adj[i].clear() ; }
