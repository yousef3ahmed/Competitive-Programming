struct point{
	int x , y; 
	point(){}
	point( int xx , int yy ){
		x = xx ;
		y = yy ;
	}

	
};

 
// without / 2 ;
ll findArea(point a, point b, point c) 
{ 
	ll mx = max( abs(a.x-b.x)*abs( a.y - c.y ) , abs( c.x - a.x )*abs( b.y - a.y )  ) ;
	ll mn = min( abs(a.x-b.x)*abs( a.y - c.y ) , abs( c.x - a.x )*abs( b.y - a.y ) ) ;
	return  mx - mn ;
}
 


float findArea(float a, float b, float c) 
{ 
    // Length of sides must be positive 
    // and sum of any two sides 
    // must be smaller than third side. 
    if (a < 0 || b < 0 || c < 0 || 
       (a + b <= c) || a + c <= b || 
                       b + c <= a) 
    { 
        cout << "Not a valid triangle"; 
        exit(0); 
    } 
    float s = (a + b + c) / 2; 
    return sqrt(s * (s - a) * 
                    (s - b) * (s - c)); 
} 


ll myceil( ll bg , ll sm ){
	bg+=(sm-1);
	return( bg/sm ) ;
}

cout <<fixed << setprecision(0) << ans << '\n';
