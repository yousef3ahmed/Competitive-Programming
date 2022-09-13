ll Mul( ll a , ll b ){
    a%=MOD ;
    b%=MOD;
	return ( a*b )%MOD ;
}

ll Add( ll a , ll b ){
	a+=b;
	if( a >= MOD ) a-=MOD ;
	return a ;
}

ll Sub( ll a , ll b ){
	a-=b ;
	if( a < 0 ) a+=MOD ;	
	return a ;
}



struct Matrix {
    vector<vector<ll>> matrix;
    int rows = 0, cols = 0;
 
    Matrix (int _rows, int _cols) {
        rows = _rows;
        cols = _cols;
        matrix = vector<vector<ll>>(rows, vector<ll>(cols));
    }

 
    void identityMatrix() {
        for (int i = 0; i < rows; ++i)
            matrix[i][i] = 1;
    }
 
    Matrix mul (Matrix other) {
        Matrix ret(rows, other.cols);
        if (cols != other.rows) return ret;
 
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    ret.matrix[i][j] = Add(  ret.matrix[i][j]    ,  Mul( matrix[i][k]  , other.matrix[k][j] ) ) ;
        return ret;
    }
};
 
Matrix matrixPower(Matrix mat, ll p) {
    Matrix ret(mat.rows, mat.cols);
    ret.identityMatrix();
    while (p) {
        if (p & 1) ret = ret.mul( mat );
        mat = mat.mul( mat );
        p >>= 1;
    }
    return ret;
}