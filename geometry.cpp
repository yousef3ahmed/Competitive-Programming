// point == vector ;

struct point{
	ll x , y ;
};

double dis( point a , point b ){
	
	ll vax = a.x - b.x ;
	ll vay = a.y - b.y ;
	
	return sqrt( vax*vax + vay*vay ) ;
}

//Compute the dot product AB · BC
ll bot( point a , point b , point c ){
	point ab;
	ab.x = b.x - a.x ;
	ab.y = b.y - a.y ;
	
	point bc;
	bc.x = c.x -  b.x ;
	bc.y = c.y -  b.y ;
	
	return( ( 1LL* ab.x * bc.x ) +  ( 1LL * ab.y * bc.y )  ) ;
}


//Compute the cross product AB x AC
ll cross( point a , point b  ,point c ){
	point ab , ac ;
	ab.x = b.x - a.x ;
	ab.y = b.y - a.y ;
	
	ac.x = c.x - a.x ;
	ac.y = c.y - c.x ;
	
	return ( ( 1LL*ab.x*ac.y ) - ( 1LL*ab.y*ac.x ) );
}
