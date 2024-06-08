#include <bits/stdc++.h>

#ifdef __APPLE__
    #include "./debug.h"
#else
    #define debug(...) 42
#endif

#define ll long long
#define int long long

using namespace std;

const int  N =  2e5 + 17  , INF = 1e16 ;


int mul( int a , int b ,int MOD ){
    return ( a*1ll*b )%MOD ;
}

int add( int a , int b  ,int MOD ){
    a+=b; if( a >= MOD ) a-=MOD ;  return a ;
}

int sub( int a , int b ,int MOD ){
    a-=b ; if( a < 0 ) a+=MOD ;	 return a ;
}


int logPw( int n  , int count , int MOD  ){
    int ret = 1 ;
    while( count ){
        if( count & 1 ) ret = mul( n , ret , MOD ) ;
        n = mul( n , n , MOD ) ;
        count>>=1 ;
    }
    return ret ;
}

int modinv(int x , int MOD) {
    return logPw(x , MOD-2  , MOD) ;
}

int Div(int x , int y , int MOD) {
    return mul( x , modinv(y , MOD) , MOD ) ;
}

int pw[2][ N ] , inv[2][N] ;

void preprocess(  ){

    int mod = 1e9 + 7 , base = 31 ;
    pw[ 0 ][ 0 ] = 1 ;
    inv[ 0 ][ 0 ] = modinv( pw[0][0] , mod ) ;
    for( int i = 1 ; i< N ; i++ )
        pw[ 0 ][ i ] = mul( pw[ 0 ][i-1] , base , mod ) , inv[ 0 ][ i ] = modinv( pw[ 0 ][i] , mod ) ;

    mod = 1e9 + 9 , base = 43 ;
    pw[ 1 ][ 0 ] = 1 ;
    inv[ 1 ][ 0 ] = modinv( pw[1][0] , mod ) ;
    for( int i = 1 ; i< N ; i++ )
        pw[ 1 ][ i ] = mul( pw[ 1 ][i-1] , base , mod ) , inv[ 1 ][ i ] = modinv( pw[ 1 ][i] , mod ) ;
}


struct item{
    int mod1 = 1e9 + 7 , mod2 = 1e9 + 9 ;

    pair< int , int > fr , rev ;
    int sz ;
    item( ){ sz = 0 , fr = { 0 , 0 } , rev = { 0 , 0 }; }
    item( char v ){ sz = 1 , fr = { v, v } , rev = { v , v } ;  } 
    
    item merge( item left , item right ){
       
        item ret ;
        ret.sz = left.sz + right.sz ;

        // this is double hash XD
        ret.fr.first = add(mul( left.fr.first , pw[0][right.sz] , mod1 ) , right.fr.first , mod1)  ;
        ret.fr.second = add( mul( left.fr.second , pw[1][right.sz] , mod2 ) , right.fr.second , mod2 ) ;


        // what about the rev
        ret.rev.first = add(mul( right.rev.first , pw[0][left.sz] , mod1 ) , left.rev.first , mod1)  ;
        ret.rev.second = add(mul( right.rev.second , pw[1][left.sz] , mod2 ) , left.rev.second , mod2)  ;

        return ret ;
    }
};

struct sugtree{

private: 	
    void build(  vector<char>&a , int ind , int l  , int r  ){
        if( l == r ){
            tree[ind] = item( a[l] ) ;
            return ;
        }
        int m = (l+r)/2 ;
        build( a , ind*2 , l , m   ) ; 
        build( a , ind*2+1 , m+1 , r  ) ;
        
        tree[ind] = item().merge( tree[ind*2], tree[ind*2+1] ) ;
    }
    
    
    item query(int ind , int left , int right , int l , int r  ){
        if( left > r || right < l ) return item() ;
        if( left >=l && right<=r  ) return tree[ind] ;
        int m = (left+right)/2;
        item op1 = query( ind*2 , left , m , l ,r   ) , 
            op2 = query( ind*2+1 ,m+1 , right , l ,r  ) ;
        return item().merge(op1 , op2) ;
    }
    
    void update( int ind , int left , int right , int tar , ll val  ){
         if( left == right ){
            tree[ind] = item( val ) ;
            return ;
         }
         int m = (left+right)/2 ;
         if( tar <= m ) update( ind*2 , left , m , tar , val   );
         else update( ind*2+1 , m+1 , right , tar , val  );
            
         tree[ind] = item().merge( tree[ind*2] , tree[ind*2+1] ) ;
    }
    

    int find_first_index( int ind , int l , int r , ll val, const function<bool( item a , ll com )> &f) {
        
        if( l == r )
            return l ;
        
        int mid = (l+r)/2;		
        if(  f( tree[ ind*2 ] , val ) )
            return find_first_index(  ind*2 ,   l ,  mid ,  val , f ) ;
        else
            return find_first_index(  ind*2+1 ,  mid+1 , r ,  val , f ) ;
    }

    int find_first( int ind , int left , int right , int l , int r , ll val , const function<bool( item a , ll com )> &f ){
        if( left >=l && right<=r  ){
            if( !f( tree[ind] , val ) ) {
                return -1 ;
            }
            return find_first_index( ind , left , right , val , f ) ;
        }
        int mid = ( left + right ) / 2 ;
        int res = -1 ;
        if(  l <= mid )
            res = find_first( ind*2 , left , mid , l , r, val , f );
        
        if( res == -1 && r > mid )
            res = find_first( ind*2+1 , mid+1 , right , l , r , val , f  ) ;
        
        return res ;
    }


    int find_last_index( int ind , int l , int r, ll val , const function<bool( item a , ll com )> &f  ){
        if( l == r )
            return l ;

        int mid = ( l + r ) / 2 ;
        if( f( tree[ ind*2 + 1 ] , val ) )
            return find_last_index( ind*2+1 , mid+1 , r ,  val , f ) ;
        else
            return find_last_index( ind*2 , l , mid , val , f ) ;
    }

    int find_last( int ind , int left , int right , int l , int r , ll val , const function<bool( item a , ll com )> &f ){
        if( left >=l && right<=r  ){
            if( !f( tree[ind] , val ) ) {
                return -1 ;
            }
            return find_last_index( ind , left , right , val , f ) ;
        }
        int mid = ( left + right ) / 2 ;
        int res = -1 ;
        if(  r > mid )
            res = find_last( ind*2+1 ,  mid+1 , right , l , r, val , f );
        
        if( res == -1 && l <= mid )
            res = find_last( ind*2 , left , mid , l , r , val , f  ) ;
        
        return res ;
    }

public:
   vector< item >tree ;
   int n ; 
   // 0 - index 

   void init( vector<char>&a ){
        n = a.size();
        tree.resize( a.size()*4 ); 
        for( int i = 0 ; i<tree.size() ; i++ ) tree[i] = item() ;
        build( a , 1 , 0 , n-1 ) ;
    }
    
    void update( int tar , ll val ){
        return update( 1 , 0 , n-1 , tar , val ) ;
    }
      
    item query( int l , int r   ){
        return query( 1 , 0 , n-1 , l , r  ) ;
    }

    int find_first( int l , int r , ll val , const function<bool( item a , ll com )> &f ){
        return find_first( 1 , 0 , n - 1 , l , r , val , f )  ;
    }	

    int find_last( int l , int r , ll val , const function<bool( item a , ll com )> &f ){
        return find_last( 1 , 0 , n-1 , l ,    r , val , f ) ;
    } 
    
}sug;

void Solve( int tc ){

    vector< char > test = { 'a' , 'a'  , 'b' , 'a' , 'a' } ;

    sug.init( test ) ;

    while( 1 ){
        int l , r ; 
        cin >> l >> r ; l-- , r-- ;

        auto get = sug.query( l , r ) ;
        
        debug( get.fr );
        debug( get.rev );

        if( get.fr == get.rev )
            cout << "YES\n";
        else
            cout << "NO\n" ;
            
    }

}

int32_t main(){

    preprocess() ;
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(0); cin.tie(0);
#endif

    int t = 1 , tc =1  ;
    cin>>t;
    while( t-- ) Solve( tc++ ) ;
}
