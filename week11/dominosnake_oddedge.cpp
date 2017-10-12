//method 2: BFS with odd edges 
/*
Solution. Create a new digraph G' with two vertices v and v' for each vertex v in G. For each edge v->w in G, include two edges: v->w' and w->v'. Now, any path from s to v' in G' corresponds to an odd-length path from s to v in G. Run either BFS or DFS to determine the vertices reachable from s. 
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<boost/graph/adjacency_list.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main()
{
 int T; cin>>T;
 for(int tt=0; tt<T; ++tt){
   int w,h; cin>>w>>h;
   int q,r,s,t; cin>>q>>r>>s>>t;
   q--; r--;s--;t--;
   
   vector<vector<int> > table(h);
   for(int i=0; i <h; ++i)
     for(int j=0; j <w; ++j){
      int a; cin>>a;
      table[i].push_back(a);       
     }
     
     if(table[r][q] == 0 || table[t][s] == 0){cout <<"no\n"; continue;}
     
     
     Graph g(h*w*2);
     vector<vector<int> > nb(2*h*w);
    int dx[]={-1,1,0,0};
    int dy[]={0,0,1,-1};
   for(int i=0; i <h; ++i)
     for(int j=0; j <w; ++j){
       if(table[i][j] == 0) continue;
       for(int k=0; k <4; ++k){
	int ni = i + dx[k];
	int nj = j + dy[k];
	if(ni >=0 && ni <=(h-1) && nj>=0 && nj<=(w-1)&&
	  table[ni][nj] ==1){
	  nb[i*w+j].push_back(ni*w+nj+w*h);
	nb[i*w+j+w*h].push_back(ni*w+nj);	
	nb[ni*w+nj+w*h].push_back(i*w+j);
	nb[ni*w+nj].push_back(i*w+j+w*h);
	}
       }
     }
     
     
     
     queue<int>qu;
     int start = q*w+r;
     int end = s*w+t+w*h;
     qu.push(start);
     vector<bool>visit(2*h*w, false);
     visit[start]=true;
     
     bool found = false;
     while(!qu.empty()){
      int cu = qu.front(); qu.pop();
      if(cu == end){
	found = true; break;
      }
      for(int i=0; i <nb[cu].size(); ++i){
	int n = nb[cu][i];
	if(!visit[n]){
	 visit[n]=true;
	 qu.push(n);
	}
      }
     }
         
     if(!found)
       cout <<"no\n"; 
     else
       cout<<"yes\n";
 }
 return 0;  
  
}
