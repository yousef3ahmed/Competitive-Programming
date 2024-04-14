#include <bits/stdc++.h>

// #define int int64_t

using namespace std;

const int long long  N =  2e5 + 17  , MOD = 1e9 + 7  , INF = 1e16 ;

void Solve( int tc ){
    int long long  k ; cin>>k ;

    string a ;
    cin>>a;

    int long long n = a.size() ;

    vector< int long long > prf( n ) ;
    prf[0] = a[0] - '0' ;

    for( int i = 1 ; i<n ; i++ )
        prf[i] = prf[i-1] + ( a[i] - '0' ) ;

    auto rang = [&](  int l , int r ){
        if( l == 0 )
            return prf[r] ;

        return prf[r] - prf[l-1] ;
    };

    auto bsl = [&]( int idx ){
        int long long l = 0 , r = idx - 1 , ans = -1 ;

        while( l <= r ){
             int mid = ( l + r  )/2ll ;
            
             if( rang( mid , idx ) == 1 )
                ans = mid , r = mid - 1ll ;
            else
                l = mid + 1ll ;
        }


        if( ans == -1 ) 
            return 0ll ;

        ans = idx - ans  ;
        return ans ;
    };

    auto bsr = [&]( int idx ){
        int long long l = idx + 1 , r = n - 1 , ans = -1 ;

        while( l <= r ){
             int mid = ( l + r  )/2ll ;
             if( rang( idx , mid ) == 1 )
                l = mid + 1 , ans = mid ;
            else
                r = mid - 1 ;
        }


        if( ans == -1 ) 
            return 0ll ;

        ans = ans - idx ;
        return ans ;
    };


    vector< int > ones ;

    for( int i = 0 ; i<n ; i++ )
        if( a[i] == '1' )
            ones.push_back( i ) ;
        

    if( k == 0 ){

        int long long ans = 0 ;
        
        int nxt = 0 ;
        while( nxt < n ){
            while( nxt < n && a[nxt] == '1' )
                nxt++;
            
            int sz = 0 ;
            while( nxt < n && a[nxt] == '0' )
                nxt++ , sz++ ;
            
            ans += (sz*1ll*(sz+1ll))/2ll ;
        }



        return cout<<ans , void() ;
    }


    int long long ans = 0 ;
    for( int l = 0, r = k-1 ; r < ones.size() ; l++ , r++ ){
        ans++ ;
        int long long solvel = 0 , solver = 0 ;

        if( ones[l] != 0 )
            solvel = bsl( ones[l] ) ;
       
        if( ones[r] != n - 1 )
            solver = bsr( ones[r] ) ;

        ans += solvel ;
        ans += solver ;

        ans += solvel*1ll*solver ;
    }

    cout<<ans;
}

int32_t main(){

#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0); cin.tie(0);
#endif

    int t = 1 , tc =1  ;
    // cin>>t;
    while( t-- ) Solve( tc++ ) ;
}