int low[N] , dfs[N] , instack[N]  , id[N]  , ndfs =  1; 
vector<ll>adj[N] ;
vector< vector<ll> > coms ;
stack<int>stk; 
 
// find SSC

void tarjan( int node ){

	low[node] = dfs[node] =  ndfs++ ;
	instack[ node ] = 1 ;
	stk.push(node) ;
	
	for(auto i : adj[node]){
		if( low[ i ] == -1  ){
			tarjan( i ) ;
			low[node] = min( low[node] , low[i] ) ;
		}else if( instack[ i ] ){
			low[node] = min( low[node] , dfs[i] ) ;
		}
			
	}
	
	
	if( dfs[node] == low[node] ){
		coms.emplace_back();
		int sz = coms.size() - 1 , x = -1 ;
		
		while( x != node ){
			x = stk.top() ; stk.pop() ; instack[x] = 0 ;
			coms[sz].pk( x ) ;
			id[x] = sz+1 ;
		}	
		
	} 
	
}
 
void init(){
	memset( low , -1 , sizeof(low) ) ;
	ndfs = 1 ;
	
}
