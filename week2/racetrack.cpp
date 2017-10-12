#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct cell{
  double x,y,vx,vy, hop;
  
};
struct obs{
  double minx, maxx, miny, maxy;
};

bool available(int x, int y,
	       vector<obs> (&obss), int p){
  for(int i=0; i<p ; ++i){
    if( x>= obss[i].minx && x <= obss[i].maxx &&
      y >= obss[i].miny && y<= obss[i].maxy)
      return false;
  }
  return true;
	       }
	       
	       int main(){
		 int T; cin>>T;
		 for(int tt=0; tt<T; ++tt){
		   int X, Y; cin>>X>>Y;
		   cell start, end;
		   cin >> start.x >> start.y >> end.x >> end.y;
		   int p; cin>>p;
		   vector<obs>obss(p);
		   for(int i=0; i <p; ++i){
		     cin>>obss[i].minx >>obss[i].miny>>obss[i].maxx >>
		     obss[i].maxy;
		   }
		   
		   queue<cell> q;
		   q.push(start);
		   vector<vector<vector<vector<bool> > > > visit(X);
		   for(int i=0; i <X; ++i){
		     visit[i].resize(Y);
		     for(int j=0; j<Y; ++j){
		       visit[i][j].resize(7);
		       for(int k=0; k<7; ++k){
			 visit[i][j][k].resize(7);
			 for(int a=0; a<7; ++a)
			   visit[i][j][k][a]=false;
		       }
		     }
		     
		   }
		   
		   bool done = false; int len;
		   start.hop=start.vx=start.vy=0;
		   while(!q.empty()){
		     cell cur = q.front(); q.pop();
		     if(cur.x == end.x && cur.y ==end.y){
		       done=true; len = cur.hop; break;}
		       for(int i=-1; i<=1; ++i)
			 for(int j=-1; j<=1; ++j){
			   int vx=cur.vx+i, vy=cur.vy+j;
			   if(vx<=3 && vy <=3 && vx>=-3 && vy >= -3){
			     int nx = cur.x+vx, ny = cur.y+vy;
			     if(nx >=0 && nx <X && ny>=0 && ny<Y){
			       if(visit[nx][ny][vx+3][vy+3]) continue;
			       if(!available(nx, ny, obss, p)) continue;
			       cell n; n.x=nx;n.y=ny;
			       n.vx=vx; n.vy=vy; n.hop=cur.hop+1;
			       q.push(n);
			       visit[nx][ny][vx+3][vy+3]=true;///
			     }
			   }
			 }
		   }
		   if(done)
		     cout << "Optimal solution takes " << len <<" hops.\n";
		   else
		     cout << "No solution.\n";
		     
		 }
		 return 0;
	       }
	       
