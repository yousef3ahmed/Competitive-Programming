struct LCA{
	
	vector< int > tin , tout , d ;
	vector< vector< int > >up ;
	int time = 0 ;


	// this Traverse the tree  and do any thing you want when Traverse  ;
	// kill nodes ^_^ ;

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
