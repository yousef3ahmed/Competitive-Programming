extern struct node* empty ;
typedef ll typ;
mt19937 eng{ std::random_device{}() } ;
uniform_int_distribution< ll > uid ( 0 , (int)1e9 ) ;

struct node{
	typ val ;
	ll priority , sz , frq ;
	node* ch[2] ,  *par ;
	node():ch( { this , this } ) , par( this ) , frq(0) , sz(0) , priority(INT_MIN){	}
	node( typ val ):ch( { empty , empty } ) , par( empty ) , frq(1) , sz(1) , priority( uid(eng) ) , val(val){	}
};

node* empty = new node() ;
enum dir{ le , rt } ;

void push_up( node* cur ){
	cur->sz = cur->frq + cur->ch[le]->sz + cur->ch[rt]->sz ;
}

void link( node* pr , node* child , dir D ){

	if( child != empty ){
		child->par = pr ;
	}
	
	if( pr != empty ){
		pr->ch[D] = child ;
		push_up(pr);
	}
}

// 1 --> right ;
// 0--> left ;
dir get_Dir( node* par , node* child ){
	return (dir) (par->ch[rt] == child) ;
}


void rotate( node* &p , dir d ){
	node *pp = p->par , *q = p->ch[!d]  ;
	link( p , q->ch[d] , (dir)!d ) ; 
	link( q , p , (dir)d ) ;
	link( pp , q , get_Dir( pp , p ) ) ;
	p = q ;
}


void balance( node* &cur ){
	if( cur->ch[rt]->priority > cur->priority ){
		rotate( cur , le ) ;
	}

	if( cur->ch[le]->priority > cur->priority ){
		rotate( cur , rt ) ;
	}
}

void insert( node* &cur , typ v ){
	if( cur == empty ){
		cur = new node(v) ;
	}
	else if( cur->val == v ){
		cur->frq++ ;
		cur->sz++ ;
	}else if( v < cur->val ){
		insert( cur->ch[le] , v ) ;
	}else{
		insert( cur->ch[rt] , v ) ;
	}

	push_up( cur ) ;
	balance( cur ) ;
}


void kill( node* &cur ){
	for( int i = 0 ; i<2;  i++ ){
		if( cur->ch[i] == empty ){
			auto tmp = cur ;
			rotate( cur , (dir)i  );
			delete tmp  ;
			link( cur , empty , (dir)i ) ;
			return ;
		}
			
	}

	if( cur->ch[le]->priority > cur->ch[rt]->priority )
		rotate( cur , rt ) , kill( cur->ch[rt] ) ;
	else
		rotate( cur , le ) , kill( cur->ch[le] ) ;
}


void del( node* &cur , typ v ){
	if( cur == empty ) return ;
	
	if( cur->val == v ){
		if( !--cur->frq )
			kill( cur ) ;
			
	}else if( cur->val > v )
		del( cur->ch[le] , v ) ;
	else	
		del( cur->ch[rt] , v ) ;

	push_up( cur ) ;
}


void print( node *root  , int deep = 0 ){
		if( root == empty ) return ;
		print( root->ch[le]  , deep+1) ;
		for( int i=0 ; i<3*deep ; i++ ) cout<<" ";
		cout<<root->val<<"\n";
		print( root->ch[rt]  , deep+1) ;
}	

int at( node* root , int ind ){
	
	if( root == empty ) return INT_MIN ;

	if( root->ch[le]->sz > ind ){
		return at( root->ch[le] , ind );
	}

	int tmp = root->ch[le]->sz + root->frq ; 
	if( ind >= tmp ){
		return at( root->ch[rt] , ind - tmp ) ;
	}

	return root->val ;
}
