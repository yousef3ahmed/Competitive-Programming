struct DSU{
	vector< ll > sz , root ;
	int forests = 0 ;
	DSU(){}	
	void init( int n ){
		sz.resize( n+1 ) ;
		root.resize( n+1 ) ;
		for(int i=0 ; i<n+1 ; i++) sz[i] = 1 , root[i] = i ;
		forests = n ;
	}
	
	int find_set( ll node ){
		if( root[node] == node ) return node ;
		return root[node] = find_set( root[node] ) ;
	}

	int union_sets(int a, int b) {
		a = find_set(a);
		b = find_set(b);
		if (a != b) {

			if (sz[a] < sz[b])
				swap(a, b);
		
			root[b] = a;
			sz[a]+=sz[b];

			return 1 ;
		}

		return 0 ;
	}

	ll MST( vector< pair<  ll , pair< int , int > > >&adj ){
		sort( adj.begin() , adj.end() ) ;
		ll ans = 0 ;
		for(int i=0 ; i<adj.size() ; i++){
			if( union_sets( adj[i].second.first , adj[i].second.second ) ){
				ans+=adj[i].first;
			}
		}

		return ans ;
	}

};