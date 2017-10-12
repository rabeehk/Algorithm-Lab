#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/max_cardinality_matching.hpp>
#include<vector>
#include<queue>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int ng,ns,l; cin>>ng>>ns>>l;
		Graph g(ng+ns);
		for(int i=0; i<l; ++i){
			int u,v; cin>>u>>v; 
			add_edge(u,v+ng,g);
		}

		// min vertex cover for bipartite graphs
		//1) run max cardinality matching
		vector<int>mate(ng+ns);
		edmonds_maximum_cardinality_matching(g, &mate[0]);
		//2) add all unmatched vertices on left to explore and
		// make them visited
		queue<int> q;
		vector<bool> visited((ng+ns), false);
		for(int i=0; i<ng; ++i){
			if(mate[i]==-1){
				q.push(i);
				visited[i]=true;
			}
		}
		//3) start exploring, from left to right along the edges which
		// are not matched, and from right to left along the matched edges
		while(!q.empty()){
			int cur = q.front(); q.pop();
			OutEdgeIt ebeg, eend;
			// left to right along the edges which are not matched
			if(cur < ng){
				for(tie(ebeg, eend)=out_edges(cur, g);ebeg!=eend; ++ebeg){
						int t = target(*ebeg, g);
						if(t != mate[cur] && ! visited[t]){
							q.push(t); visited[t]=true;
						}
				}
			}
			// right to left along the matched edges
			else{
				if(mate[cur]!=-1 && !visited[mate[cur]]){
					q.push(mate[cur]); visited[mate[cur]] = true;
				}
			}
		}
		// choose all unvisited vertices on left and all visited
		// vertices on right
		vector<int> gsol, // left
					ssol; //right
		for(int i=0; i<ng; ++i)
			if(!visited[i])
				gsol.push_back(i);
		for(int i=ng; i<ng+ns; ++i)
			if(visited[i])
				ssol.push_back(i-ng);

		cout << gsol.size() << " " << ssol.size() << endl;
		for(int i=0; i<gsol.size(); ++i)
			cout << gsol[i] << " ";
		for(int i=0; i<ssol.size(); ++i)
					cout << ssol[i] << " ";
		cout << "\n";
	}
	return 0;
}

