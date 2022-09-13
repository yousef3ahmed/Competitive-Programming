int low[N] , dfs[N] ,   ndfs =  1 ; 
vector<ll>adj[N] ;
int point[N] ;
int root = 0 ;
 
 //  articulation point (or cut vertex) if removing it (and edges through it) disconnects the graph.
 
 
void tarjan( int node , int par ){
	
	low[node] = dfs[node] =  ndfs++ ;
	
	for(auto i : adj[node]){
		if( low[ i ] == -1  ){
			tarjan( i , node ) ;
			low[node] = min( low[node] , low[i] ) ;
			
			if( low[i] >= dfs[node] ){
				
				if( dfs[node]==1 && root==0 ){
					root = 1 ;
				}else{
					point[node] = 1 ;
				}
			}
			
		}else if( par != i  ){
			low[node] = min( low[node] , dfs[i] ) ;
		}
			
	}	
	
	
}
 
void init(){
	memset( low , -1 , sizeof(low) ) ;
	memset( point , 0 , sizeof( point ) );
	ndfs = 1 ;
}

