typedef int typ;

 // AVL tree ;
struct node{
	typ val;
	node *left ;
	node *right ;
	int height ;
	int frq ;
	int sz ; 
	node(  ):val( 0 ) ,left(NULL) ,right(NULL) ,height(0) , frq(0) , sz(0) {}
	node( int v ):val(v) ,left(NULL) ,right(NULL) ,height(1) , frq(1) , sz(1) {}
};



struct AVL{

	node *root = NULL ;
	void init(){
		Clear( root ) ;
		root = NULL ;
	}

	void Clear( node* &nd ){
		if( nd == NULL ) return ;
		Clear( nd->left ) ;
		Clear( nd->right ) ;
		delete nd ;
	}

	int deep( node* cur ){
		if( cur == NULL ) return 0 ;
		return cur->height ;
	}

	int acc( node *cur ){
		if( cur == NULL || cur == nullptr ) return 0 ;
		return  cur->sz  ;
	}

	node* newNode( typ key ){
		node* nd = new node(key) ;
		return (nd) ;
	}

	void updeep( node* &y ){
		y->height = max( deep(y->left) , deep(y->right) )+1 ;
	}

	void upsize( node* &y ){
		y->sz = y->frq + acc( y->left ) + acc( y->right ) ;
	}

	node* Rrotate( node *y ){
		node* x = y->left ;
		node* t2 = x->right ;

		x->right = y ;
		y->left = t2 ;
		
		updeep( y ) ;
		updeep( x ) ;
		upsize(y) ;
		upsize(x) ;

		return x ; 
	}

	node* Lrotate( node *x ){
		
		node *y = x->right;
		node *t2 = y->left;
	
		// Perform rotation
		y->left = x;
		x->right = t2;
		updeep(x) ;
		updeep(y) ;
		upsize(x) ;
		upsize(y) ;
	
		return y ;
	}

	int Balance( node* nd ){
		if( nd == NULL ) return 0; 
		return deep( nd->left ) - deep( nd->right ) ;
	}

	node* insert( node* nd , int key ){

		if( nd == NULL ) return ( newNode( key ) ) ;
		if( key < nd->val )
			nd->left = insert( nd->left , key ) ;
		else if( key > nd->val )
			nd->right = insert( nd->right , key ) ;
		else 
			return  ++nd->sz , ++nd->frq , nd ;

		updeep(nd) ;
		upsize(nd) ;
		int ck = Balance( nd ) ;

		// 4 case ;
		if( ck > 1 && key < nd->left->val )
			return Rrotate( nd ) ;
		
		if( ck < -1 && key > nd->right->val )
			return Lrotate( nd ) ;
		
		if( ck > 1 && key > nd->left->val  ){
			nd->left = Lrotate( nd->left ) ;
			return Rrotate( nd ) ;
		}

		if( ck < -1 && key < nd->right->val ){
			nd->right = Rrotate( nd->right ) ;
			return Lrotate( nd ) ;
		}

		return nd ;

	}

	int Count(node *root,typ v){
		if(root == NULL)
			return 0;
		
		if(v < root->val)
			return Count(root->left,v);
		if(v > root->val)
			return Count(root->right,v);
		return root->frq;
	}

	int lower_bound( node* root , typ v ){
		if( root == NULL ) return 0;

		if( v < root->val )
			return lower_bound( root->left , v ) ;
		
		int lefsz = 0 ;
		if( root->left != NULL ) lefsz = root->left->sz ;

		if( v == root->val ) return lefsz  ;

		return lefsz + lower_bound( root->right , v ) + root->frq ;
	}

	void print(node *rt,int dpth=0){
		if(rt == NULL)
			return;
		print(rt->left,dpth+1);
		printf("%s( %2d,%2d,%2d ) \n",string(dpth*5,' ').c_str(),rt->val,rt->frq,rt->sz);
		print(rt->right,dpth+1);
	}

	void insert( typ key ){
		this->root = insert( root , key ) ;
	}

	int Count( typ v ){
		return Count( root , v ) ;
	}
	 
	int lower_bound( typ v  ){ // 0 - based;
		return lower_bound( root  , v );
	}

	int upper_bound( typ v ){ // 0 based
		return lower_bound( root  , v+1 ) ;
	}

	int size(  ){
		return root->sz ;
	}

	

}avl;
