struct Compress{
    
    vector< ll > comp ;
    set< ll >se; 

    ll toOrginal( ll idCom ){ 
       return comp[ idCom ] ; 
    }


    void compress(  vector<ll>&a ){
        for( int i = 0 ; i<a.size() ; i++ ){
            se.insert( a[i] ) ;
        } 
        
        for( auto u : se ) comp.push_back( u ) ;

        for( int i = 0 ; i<a.size() ; i++ ){
            a[i] =  lower_bound( comp.begin() , comp.end() , a[i] ) - comp.begin()  ;
        }   
    }

}compo;

// set ;
struct cmp{
    bool operator()( const pair< ll ,ll > &a ,const pair< ll ,ll > &b ) const {
        if( a.first == b.first )
            return a.second < b.second ;
        return a.first > b.second ;
    }
};
