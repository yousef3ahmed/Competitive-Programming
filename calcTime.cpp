int32_t main() {
#ifdef __APPLE__
	auto _clock_start = chrono::high_resolution_clock::now();
#endif

#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0); cin.tie(0);
#endif

    int t = 1 , tc =1  ;
    // cin>>t;
    while( t-- ) Solve( tc++ ) ;
#ifdef __APPLE__
	cerr << "Executed in " << chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now()
			- _clock_start).count() << "ms." << endl;
#endif
	return 0;
}
