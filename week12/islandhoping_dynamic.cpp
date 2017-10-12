#include<iostream>
#include<vector>
#include<limits>
#include <fstream>

using namespace std;

vector<pair<int,int> > table(1020);

//return back cost, update nodes online
pair<int,int> solve(vector<int>ds, int start, int r, int k){
	if(table[start].first != -1){
		return table[start];
	}

	if(start == k){
		return make_pair(0, 0);
	}


	pair<int,int> best = make_pair(numeric_limits<int>::max(),numeric_limits<int>::max());

	for(int i=1; i<=r; ++i){
		int node = 0; 
		if((i+start) <= k){
			int cost = ds[i+start];
			if(i+start < k) node++;
			pair<int,int> res = solve(ds, i+start, r, k);
			cost+= res.first; node += res.second;
			if(make_pair(cost, node) < best){best = make_pair(cost, node);} //compare :)
		}
	}
	return table[start] = best;
}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int k,r,e; cin>>k>>r>>e;
		for(int i=0; i <= k; ++i) // = error :)
			table[i].first = -1;

		vector<int> ds; ds.push_back(0);
		for(int i=0; i <(k-1); ++i){
			int a; cin>>a; ds.push_back(a);
		}
		ds.push_back(0);

		int start =0;
		pair<long,int> res = solve(ds, start, r, k);
		int remain = e-res.first;
		if(remain <= 0){cout << "safe\n"; continue;}
		cout << res.second << " " << remain << endl;
	}
	return 0;
}

