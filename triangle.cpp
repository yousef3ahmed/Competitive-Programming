struct point{
	int x , y; 
	point(){}
	point( int xx , int yy ){
		x = xx ;
		y = yy ;
	}
};


double distance(ll x1, ll y1, ll x2, ll y2) {
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

int checkTriangle(ll x1, ll y1, ll x2,
                  ll y2, ll x3, ll y3) {

    // Calculation the area of
    // triangle. We have skipped
    // multiplication with 0.5
    // to avoid floating point
    // computations
    ll a = x1 * (y2 - y3)
           + x2 * (y3 - y1)
           + x3 * (y1 - y2);

    // Condition to check if
    // area is not equal to 0
    if (a == 0)
        return 0ll ;
    else
        return 1ll ;
}
 
// without / 2 ;
ll findArea(point a, point b, point c) {
    ll x1 = a.x;
    ll y1 = a.y;
    ll x2 = b.x;
    ll y2 = b.y;
    ll x3 = c.x;
    ll y3 = c.y;
    
	ll ret =   ( c.x - a.x )*( b.y - a.y ) - (a.x-b.x)*( a.y - c.y )   ;
    return  abs( ret ) ;
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

cout <<fixed << setprecision(8) << ans << '\n';

bool isPowerOfTwo (ll x) {
    return x && (!(x&(x-1)));
}


double ternarySearch(  ){
	double l = 0 , r = 1000000.0 ;
	
	for( int i = 0 ; i<200 ; i++ ){
		
		double mid1 = l + (r - l) / 3.0;
        double mid2 = r - (r - l) / 3.0;
 
		if( calc( mid1 ) < calc( mid2 ) ){
			r = mid2 ;
		}else{
			l = mid1 ;
		}
	}
 
	return  calc( ( l + r  ) / 2 ) ;
}

 