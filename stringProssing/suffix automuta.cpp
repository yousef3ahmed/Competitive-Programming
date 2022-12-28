struct suffix_automaton {
	struct state {
		int len, link = 0, cnt = 0;
		bool terminal = false;
		bool is_clone = false;
		map<char, int> next;
		state(int len = 0) :
				len(len) {
		}
		bool have_next(char ch) {
			return next.find(ch) != next.end();
		}
		void clone(const state &other, int nlen) {
			len = nlen;
			next = other.next;
			link = other.link;
			is_clone = true;
		}
	};
	vector<state> st;
	int last = 0;
	suffix_automaton() {
		st.push_back(state());
		st[0].link = -1;
	}
	suffix_automaton(const string &s) :
			suffix_automaton() {
		for (char ch : s)
			extend(ch);
		mark_terminals();
	}
	void mark_terminals() {
		for (int cur = last; cur >= 0; cur = st[cur].link)
			st[cur].terminal = true;
	}
	void extend(char c) {
		int cur = st.size();
		st.push_back(state(st[last].len + 1));
		st[cur].cnt = 1;
		int p = last;
		last = cur;
		while (p != -1 && !st[p].have_next(c)) {
			st[p].next[c] = cur;
			p = st[p].link;
		}
		if (p == -1)
			return;
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len) {
			st[cur].link = q;
			return;
		}
		int clone = st.size();
		st.push_back(state());
		st[clone].clone(st[q], st[p].len + 1);
		while (p != -1 && st[p].next[c] == q) {
			st[p].next[c] = clone;
			p = st[p].link;
		}
		st[q].link = st[cur].link = clone;
	}

	void calc_number_of_occurrences() {
		vector<pair<int, int>> v;
		for (int i = 1; i < st.size(); i++)
			v.push_back( { st[i].len, i });
		sort(v.begin() , v.end() );
		for (int j = v.size() - 1; j >= 0; j--) {
			int cur = v[j].second;
			st[st[cur].link].cnt += st[cur].cnt;
		}
	}

  int find( string &s ){
    int cur = 0 ;
    for( auto ch : s ){
      if( st[ cur ].have_next( ch ) ){
        cur = st[cur].next[ch];
      }
      else  
        return 0 ;
    }
    return 1 ;
  }

 
  int count( string &s ){
    int cur = 0 ; 
    for( auto ch : s ){
      if( st[ cur ].have_next( ch ) ){
        cur = st[cur].next[ch];
      }
      else  
        return 0 ;
    }

    return st[ cur ].cnt ;
  }

};