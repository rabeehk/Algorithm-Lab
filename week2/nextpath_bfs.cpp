// removing the edges of shortest path one by one
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		
		int n,m; cin>>n>>m;
		int s,t; cin>>s>>t; 
		s--; t--;
		vector<vector<int> > nb(n);
		for(int i=0; i<m; ++i){
			int a,b; cin>>a>>b;
	                a--; b--;
			nb[a].push_back(b);
		}
		queue<pair<int, int> > q;
		vector<int>visit(n, 0);
		q.push(make_pair(s, 0));
		bool done = false;
		int len;
		while(!q.empty()){
			pair<int, int> cur = q.front(); q.pop();
			// you should increase the visit here, and not once 
			// pushed as you want to add all its neighbours for the
			// second time as well.
			visit[cur.first]++;
			//cout << "node " << cur.first << " " << " hop " << cur.second << " " << " times " << visit[cur.first] << endl;
			if(cur.first == t && visit[cur.first] == 2){
				len = cur.second;
				done = true; break;
			}
			if(visit[cur.first] >= 3) continue;

			for(int i=0; i<nb[cur.first].size(); ++i){
				int neighb = nb[cur.first][i];
				if(visit[neighb] < 2){		
					int hop = cur.second+1;
					q.push(make_pair(neighb, hop));
				}
			}		
		}	
		if(done)
			cout << len << endl;
		else
			cout << "no\n";
	}
	return 0;
}

