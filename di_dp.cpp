ll dp[20][200][2][5] ;
int vis[20][200][2][5] , fc = 0 ;
 
vector<int> convert( ll n){
	vector<int>ans;
	while(n>0){
		ans.pk(n%10);
		n/=10;
	}
	reverse(ans.begin() , ans.end());
	return ans ;
}
 
ll solve(int ind , int sum , bool f , int msk , vector<int>&digit){
	
	if( msk >= 4 ) return 0 ;
 	if(ind>=digit.size()) return 1 ;

	ll &ret = dp[ind][sum][f][msk];
	if(vis[ind][sum][f][msk]==fc) return ret ;
	ret =0 ;
	vis[ind][sum][f][msk]=  fc ;
	if(f){
		for(int i=0 ; i<=9 ; i++){
			int new_msk = msk + ( i >=1 ) ;
			ret += solve(ind+1 , sum+i , f , new_msk , digit ) ;
		}
	}else{
		for(int i=0; i<=digit[ind] ; i++ ){
			bool new_f = (i!=digit[ind]) ;
			int new_msk = msk + ( i >=1 ) ;
			ret += solve(ind+1 , sum+i , new_f , new_msk , digit ) ;
		}
	}
	
	return ret ;
	
}