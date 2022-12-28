
typedef int TN;
extern struct Node *empty;
enum DIR{L,R};
 
struct Node {
	TN val;
	int freq,sz,hi;
	Node *chld[2];
	
	Node() : val(0), freq(0), sz(0), hi(0), chld({this,this}) {}
	Node(TN v,Node *lt = empty,Node *rt = empty){
		val = v;
		sz = freq = 1;
		hi = 1;
		chld[L] = lt;
		chld[R] = rt;
	}
	
	void Push_Up(){
		sz = freq;
		hi = 0;
		for(int i=0;i<2;++i){
			sz += chld[i]->sz;
			hi = max(hi,chld[i]->hi);
		}
		++hi;
	}
	
	int Balance_Factor(){
		return chld[R]->hi - chld[L]->hi;
	}
};
Node *empty = new Node();
 
struct AVL {
	Node *root;
	AVL() : root(empty) {}
	void init(){
		Clear(root);
		root = empty;
	}
	void Clear(Node *&root){
		if(root == nullptr || root == empty)
			return;
		Clear(root->chld[L]);
		Clear(root->chld[R]);
		delete root;
	}
	
/*
 
     p
    / \
   q   c  dir=1
  / \
 a   b
 
      q
     / \
    a   p
       / \
      b  c
*/
	
	void SetChild(Node *&par,Node *ch,int dir){
		par->chld[dir] = ch;
		par->Push_Up();
	}
	void Rotate(Node *&p,int dir){
		Node *q = p->chld[!dir];
		SetChild(p, q->chld[dir], !dir);
		SetChild(q, p, dir);
		p = q;
	}
	
	void Balance(Node *&root){
		int curBF = root->Balance_Factor();
		if(curBF == 2){ // Left
			if(root->chld[R]->Balance_Factor() == -1)
				Rotate(root->chld[R], R);
			Rotate(root,L);
		}
		
		if(curBF == -2){ // Right
			if(root->chld[L]->Balance_Factor() == 1)
				Rotate(root->chld[L], L);
			Rotate(root,R);
		}
	}
	
	Node *MinMaxNode(Node *root,int dir){
		if(root == empty)
			return root;
		while(root->chld[dir] != empty)
			root = root->chld[dir];
		return root;
	}
	
	void Insert(Node *&root,TN v){
		if(root == empty){
			root = new Node(v);
			return;
		}
		
		if(v == root->val){
			root->freq++;
			root->sz++;
			return;
		}
		if(v > root->val)
			Insert(root->chld[R],v);
		else
			Insert(root->chld[L],v);
		
		Balance(root);
		root->Push_Up();
	}
	
	void Erase(Node *&root,TN v){
		if(root == empty)
			return;
		
		if(v == root->val){
			if(root->freq > 1){
				root->freq--;
				root->sz--;
				return;
			}
			if(root->chld[L] == empty){
				Node *temp = root->chld[R];
				delete root;
				root = temp;
				return;
			}
			if(root->chld[R] == empty){
				Node *temp = root->chld[L];
				delete root;
				root = temp;
				return;
			}
			int curbf = root->Balance_Factor();
			Rotate(root,(curbf <= 0));
 
		}
		if(v > root->val)
			Erase(root->chld[R],v);
		else
			Erase(root->chld[L],v);
		
		Balance(root);
		root->Push_Up();
	}
	
	int Count(Node *root,TN v){
		if(root == empty)
			return 0;
		
		if(v < root->val)
			return Count(root->chld[L],v);
		if(v > root->val)
			return Count(root->chld[R],v);
		return root->freq;
	}
	
	int Lower_Bound(Node *root,TN v){
		if(root == empty)
			return 0;
		if(v < root->val)
			return Lower_Bound(root->chld[L],v);
		
		int lefsz = root->chld[L]->sz;
		if(v == root->val)
			return lefsz;
		return lefsz + root->freq + Lower_Bound(root->chld[R],v);	
	}
	
	TN GetByIndex(Node *root,int idx){
		if(root->sz <= idx) // Ivalid Case
			return -1;
		
		int lefsz = root->chld[L]->sz;
		if(idx < lefsz)
			return GetByIndex(root->chld[L],idx);
		lefsz += root->freq;
		if(idx >= lefsz)
			return GetByIndex(root->chld[R],idx - lefsz);
		return root->val;
	}
	
	void print(Node *rt,int dpth=0){
	    if(rt == empty)
	        return;
	    print(rt->chld[L],dpth+1);
	  	printf("%s%2d,%2d,%2d\n",string(dpth*5,' ').c_str(),rt->val,rt->sz,rt->hi);
	    print(rt->chld[R],dpth+1);
	}
	
	/* Using Function */
	
	void Insert(TN v){
		Insert(root,v);
	}
	
	void Erase(TN v){
		Erase(root,v);
	}
	
	int Count(TN v){
		return Count(root,v);
	}
	
	TN operator [] (int idx){ // Zero-Based
		if(idx >= 0 && idx < Size())
			return GetByIndex(root,idx);
		puts("Invalid");
		return -1;
	}
	
	int Lower_Bound(TN v){ // Zero-Based
		return Lower_Bound(root,v);
	}
	
	int Upper_Bound(TN v){ // Zero-Based
		return Lower_Bound(root,v + 1);
	}
	
	int Size(){
		return root->sz;
	}
	
	TN Min(){
		if(!Size())
			puts("Empty Tree\n");
		return MinMaxNode(root, L)->val;
	}
	
	TN Max(){
		if(!Size())
			cout<<"Empty Tree\n";
		return MinMaxNode(root, R)->val;
	}
	
} avl;