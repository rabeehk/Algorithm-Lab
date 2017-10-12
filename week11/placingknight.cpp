#include<iostream>
using namespace std;
#include<boost/graph/max_cardinality_matching.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<vector>
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		vector<vector<int> > table(n);
		int size = 0;
		for(int i=0; i <n; ++i)
			for(int j=0; j<n; ++j){
					int a; cin>>a;
					if(a == 1) size ++;
					table[i].push_back(a);
			}
		Graph g(n);
		int dx[8]={-1,-1,1,1,-2,-2,2,2};
		int dy[8]={-2,2,-2,2,-1,1,-1,1};
		for(int i=0; i <n; ++i)
			for(int j=0; j<n; ++j){
				if(table[i][j] != 0){
					for(int k=0; k<8; ++k){
						int nx= i+dx[k];
						int ny = j+dy[k];
						if(nx >=0 && nx< n && ny>=0 && ny < n &&
							table[nx][ny] == 1)
							add_edge(i*(n)+j, nx*n+ny, g);
					}
				}
			}

		vector<int> mate(n*n);
		edmonds_maximum_cardinality_matching(g, &mate[0]);
		int s = matching_size(g, &mate[0]);
		cout << size - s << endl;


	}
	return 0;
}

