struct prefix2D{
  
  vector<vector<int>> f;
  
  void init( vector< vector<int> > &matrix ){

    int n = matrix.size() ;
    int m = matrix[0].size() ;

    f.assign(n + 1, vector<int> (m + 1, 0));

    for( int i = 1; i<=n ; i++ ){
      for( int j = 1 ; j<=m ; j++ ){
        f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1] + matrix[i-1][j-1] ; 
      }
    }
  }


  // query 1-index 
	// pass vector 0-index ;
  int query( int x1, int y1 , int x2 , int y2 ){
    return f[x2][y2] - f[x2][y1-1] - f[x1-1][y2] + f[x1-1][y1-1];
  }

}prf2D;
