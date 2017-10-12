#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<boost/graph/max_cardinality_matching.hpp>
#include<boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

#define cerr if(false) cout 
int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,c,f; cin>>n>>c>>f;
		cout << n << endl;
		Graph g(n);
		vector<set<string> > chs(n);
		for(int i=0; i <n; ++i){
			for(int j=0; j<c; ++j){
				string a; cin>>a;
				chs[i].insert(a);
			}
		}

		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j){
				set<string> res;
				set_intersection(chs[i].begin(), chs[i].end(),
						chs[j].begin(), chs[j].end(),
						inserter(res, res.begin()));

				cerr << res.size() << endl;
				if(res.size() > f)
					add_edge(i, j, g);
			}

		vector<int> mate(n);
		edmonds_maximum_cardinality_matching(g, &mate[0]);
		int match = matching_size(g, &mate[0]);
		cerr << "match " << match << endl;
		if(match*2 == n)
			cout << "not optimal\n";
		else
			cout << "optimal\n";
	}
	return 0;
}

