#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/boyer_myrvold_planar_test.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
int main(){
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		vector<vector<int> > nb(n);
		for(int i=0; i<n; ++i)
			for(int j=0; j<(n-1); ++j){
				int a; cin>>a;
				nb[i].push_back(a);
			}

		Graph g(n);
		int t =0;
		for(int i=0; i <(n-1); ++i){
			for(int j=0; j<n; ++j)
				add_edge(j, nb[j][i], g);
			if(!boyer_myrvold_planarity_test(g)){
				break;}
			t++;
		}
		cout << t << endl;
	}
	return 0;
}

