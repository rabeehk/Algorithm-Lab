#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/boyer_myrvold_planar_test.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;


int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		Graph g(n+1); //one more for toilet
		for(int i=0; i<m; ++i){
			int a,b; cin>>a>>b;
			add_edge(a,b,g);
		}
		for(int i=0; i<n; ++i)
			add_edge(i, n, g);

		if(boyer_myrvold_planarity_test(g))
			cout << "yes\n";
		else
			cout << "no\n";
	}
	return 0;
}

