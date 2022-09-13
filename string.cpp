int paild( string &s ){
	int l = 0 , r = s.size()-1 ;
	while( l < r ){
		if( s[l] != s[r] ) return 1 ;
 
		l++ ;
	 	r-- ;
	 }
  
	return 0 ;
}