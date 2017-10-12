//method 1: BFS - end and start different colors 
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

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
     
     if((q+r)%2 == (s+t)%2){
       cout <<"no\n"; 
       continue;
     }
     if(table[r][q] == 0 || table[t][s] == 0){cout <<"no\n"; continue;}
     
     vector<vector<int> > nb(h*w);
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
	    nb[i*w+j].push_back(ni*w+nj);	  
	}
       }
     }
     
     
     queue<int>qu;
     int start = q*w+r;
     int end = s*w+t;
     qu.push(start);
     vector<bool>visit(h*w, false);
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
