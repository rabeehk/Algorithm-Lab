#include<iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, directedS,
no_property, property<edge_weight_t, int> > Graph;



#include <fstream>



int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int k,r,e; cin >> k >> r >> e;
		vector<int> ds;
		Graph g(k+1);

		ds.push_back(0);
		for(int i=0; i <(k-1); ++i){
			int a; cin>>a; ds.push_back(a);
		}
		ds.push_back(0);

		//build graph
		for(int i=0; i <k; ++i){
			for(int s=1; s <=r; ++s){
				if(i+s <= k){
				add_edge(i, i+s, ds[i+s], g);
				}
			}
		}

		vector<int>d(k+1);
		vector<int>p(k+1);
		dijkstra_shortest_paths(g, 0,
		predecessor_map(&p[0]).distance_map(&d[0]));

		int remain = e - d[k];
		if(remain <=0 )
			{cout << "safe\n"; continue;}
		int cur = p[k];
		int node = 0;
		while(cur != 0){
			node++;
			cur = p[cur];
		}

		cout << node << " " << remain << endl;

	}
	return 0;
}

