vector< ll > all_div( ll num ){
	vector< ll > ans ;

	for(ll i =2 ; i*i<=num ; i++){
		if( num%i == 0 ){
			ans.pk( i ) ;
			if( num/i != i )
				ans.pk( num / i ) ;
		}
	}
	if( num > 1 ) ans.pk( num ) ;
	sort( ans.begin() , ans.end() ) ;
	return ans ;
}


vector<int> prime;
void sieve(int n) {
    prime.assign(n, 1);
    prime[1] = false;
    for (ll i = 2; i <= n; i++)
        if (prime[i])
            for (ll j = i * i; j <= n; j += i)
                prime[j] = false;
}



// to count numder of element between two number in array sort  log(n);
int cnt(ll l , ll u , vector<ll>&copy){
	return  upper_bound(copy.begin() , copy.end() , u) - lower_bound(copy.begin() , copy.end() , l) ;
}