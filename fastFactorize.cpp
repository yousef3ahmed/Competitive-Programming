int SPF[N];
 
 
void preprocess() {
 
    for(int i=1; i<N; i++)
        SPF[i] = i;
 
    for(int i=2; i<N; i++) {
        if(SPF[i] == i) {
            for(int j=i; j<N; j+=i)
                SPF[j] = min(SPF[j], i);
        }
    }
}
 
 
vector< int > factorize ( int n ){
  vector< int > ans ;
  
  while( n > 1 ){
    ans.push_back( SPF[n] ) ;
    n/=SPF[n] ;
  } 
  return ans;
}
 