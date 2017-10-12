#include<iostream>
#include<boost/graph/max_cardinality_matching.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<vector>

using namespace std;
using namespace boost;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main(){
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
	 int w,h; cin>>w>>h;
	 
	 int sum =0 ;
	 vector<vector<int> > table(h);
	 for(int i=0; i <h; ++i){
	  for(int j=0; j<w; ++j){
	      int a; cin>>a;
	      table[i].push_back(a);
	      if(a == 1){sum++;}
	  }
	 }
	 
	 
	 Graph g(h*w);
	 int dx[4]={0, 0, 1, -1};
	 int dy[4]={1, -1, 0, 0};
	 for(int i=0; i<h; ++i)
	   for(int j=0; j<w; ++j){
	    if(table[i][j] == 1){
		for(int k=0; k < 4; ++k){
		    int nx = i+dx[k];
		    int ny = j+dy[k];
		    if(nx <=(h-1) && nx >=0 && ny <=(w-1) && ny >=0 && table[nx][ny] == 1){
			add_edge(i*w+j, nx*w+ny, g);
		    }
		}
	    }
	   }
	   
	   vector<int> mate(h*w);
	   edmonds_maximum_cardinality_matching(g, &mate[0]);
	   
	  int size = matching_size(g, &mate[0]);
	  if(size*2 == sum)
	    cout <<"yes\n";
	  else 
	    cout <<"no\n";  
	  
	}
	return 0;
}
