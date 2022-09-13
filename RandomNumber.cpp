auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
unsigned long long Rand(ll mod) { return mt()%mod ; }
unsigned long long Rand() { return mt() ; }
