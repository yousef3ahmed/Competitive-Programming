struct FenwickTree{
private:
    // Matrix to store the ;
	// query 1-index ;
	// pass vector 0-index ;

    vector<vector<ll>> ft;

public:
    // Function to get least significant bit; 
    int LSB(int x){
        return x & (-x);
    }

    ll query(int x, int y){
        ll sum = 0;
        for(int x_ = x; x_ > 0; x_ = x_ - LSB(x_)){
            for(int y_ = y; y_ > 0; y_ = y_ - LSB(y_)){
                sum = sum + ft[x_][y_];
            }
        }
        return sum;
    }

    ll query(int x1, int y1, int x2, int y2){
        return (query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1));
    }

    void update(int x, int y, ll value){
        for(int x_ = x; x_ < ft.size(); x_ = x_ + LSB(x_)){
            for(int y_ = y; y_ < ft[0].size(); y_ = y_ + LSB(y_)){
                ft[x_][y_] += value;
            }
        }
    }

    void init( vector< vector<ll> > &matrix){
        int n = matrix.size();
        int m = matrix[0].size();

        ft.assign(m + 1, vector<ll> (n + 1, 0));

        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j)
                update(i + 1, j + 1, matrix[i][j]);
        }
    }
}bit;