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

ll all_div( ll num ){
	ll ans = 0 ;

	for(ll i =2 ; i*i<=num ; i++){
		if( num%i == 0 ){
			ans++;
			if( num/i != i )
				ans++ ;
		}
	}

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

//number of coprimes of in the range ( 1 , n )
int phi_1_to_n(int n) {
    int phi[n + 1];
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi[n];
    
}

void primeFactors(int n)
{
    int c=2;
    while(n>1)
    {
        if(n%c==0){
        cout<<c<<" ";
        n/=c;
        }
        else c++;
    }
}

const int N = 1e6 + 1;
int sp[N];

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (sp[i])continue;
    for (int j = i; j < N; j += i) {
      sp[j] = i;
    }
  }
}

vector<pair<int, int>> primes;
vector<int> factors;

void solve(int i, int cur) {
  if (i == primes.size()) {
    factors.emplace_back(cur);
    return;
  }
  for (int j = 0; j <= primes[i].second; ++j) {
    solve(i + 1, cur);
    cur *= primes[i].first;
  }
}

void get(int x) {
  primes.clear();
  factors.clear();
  while (x > 1) {
    int p = sp[x], c = 0;
    while (!(x % p))x /= p, ++c;
    primes.emplace_back(p, c);
  }
  solve(0, 1);
}
