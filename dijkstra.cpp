void dijkstra(int source, vector<ll> &dist, vector< vector< pair<int, int> > > &adj) {
	
	int n  = dist.size() ;
	for (int i = 0 ; i < n ; i++)
		dist[i] = INF ;
    priority_queue<pair<ll, int>> pq;
    
	pq.push({0, source});
    dist[source] = 0;
    
	while (!pq.empty()) {
        int node = pq.top().second;
		ll cost = -pq.top().first ;
        pq.pop();
		
		if( dist[ node ] != cost ) continue;

        for (auto child: adj[node]) {
            if (dist[node] + child.second < dist[child.first]) {
                dist[child.first] = dist[node] + child.second;
                pq.push({-dist[child.first], child.first});
            }
        }
 
    }
}