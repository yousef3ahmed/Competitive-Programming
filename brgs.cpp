int low[N] , dfs[N] ,   ndfs =  1 ; 
vector<ll>adj[N] ;
vector< pair< int , int > >brg ;
 
// A bridge is defined as an edge which, when removed, makes the graph disconnected

void tarjan( int node , int par ){
	
	low[node] = dfs[node] =  ndfs++ ;
	
	for(auto i : adj[node]){
		if( low[ i ] == -1  ){
			tarjan( i , node ) ;
			low[node] = min( low[node] , low[i] ) ;
			
			if( low[i] == dfs[i]  ) brg.push_back( { node , i  } ) ;   	
		}else if( par != i  ){
			low[node] = min( low[node] , dfs[i] ) ;
		}
			
	}	
}
 
void init(){
	memset( low , -1 , sizeof(low) ) ;
	ndfs = 1 ;
	
}
