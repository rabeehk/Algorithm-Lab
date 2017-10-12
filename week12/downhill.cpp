/*
 observation 1: we cannot use Delaunay triangulation, because then there will be 
 edges which are not in the original graph, as if you have 4 nodes, it will make traingles 
 and connect the ones which should not get connected 
 */
#include<iostream>
#include<vector>
#include<set>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>


using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;


void processneighbours(int node, vector<vector<int> > (&nb), 
		      set<int> (&degree)[3], vector<bool> (&processed)){
  
  //check all neighbours 
  for(int i=0; i <nb[node].size(); ++i){
    int ind = nb[node][i];
    if(processed[ind]) continue;
    bool in_deg1 = degree[1].find(ind) != degree[1].end();
    if(in_deg1){
      degree[1].erase(ind);
    }
    else{ // it is degree 2
      degree[2].erase(ind);
      for(int j=0; j<nb[ind].size(); ++j){
	int ind1 = nb[ind][j];
	if(processed[ind1]) continue;
	bool in_deg1 = degree[1].find(ind1) != degree[1].end();
	if(in_deg1){
	  degree[1].erase(ind1);
	  degree[0].insert(ind1);
	}
	else{ // in degree 2
	  degree[2].erase(ind1);
	  degree[1].insert(ind1);	
	}		     
      }
    } 
 }
}
//#define cerr if(false) cout

int main(){
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
	 int n,r; cin>>n>>r;
	  vector<P>pts;
	  for(int i=0; i<n; ++i){
	   int x,y; cin>>x>>y;
	   pts.push_back(P(x,y));
	  }
	  
	  vector<vector<int> > nb(n);
	  vector<int> deg(n, 0);
	  for(int i=0; i <n; ++i)
	    for(int j=i+1; j<n; ++j){
	      double d = CGAL::to_double(CGAL::squared_distance(pts[i], pts[j]));
	      if(d < r){
		nb[i].push_back(j);
		nb[j].push_back(i);
		deg[i]++;deg[j]++;
	      }
	    }
	 
	    set<int> degree[3]; // degree 0 , 1 , 2
	    for(int i=0; i <n; ++i){
	     if(deg[i] == 0){
	       degree[0].insert(i); }
	     else if(deg[i]==1){
	       degree[1].insert(i);}
	     else{
	       degree[2].insert(i);}	      
	    }
	    
	    int count = 0;
	    set<int>::iterator it;
	    vector<bool> processed(n, false);
	    
	    //as we should always update use this method
	    while(degree[0].size() != 0 ||
		 degree[1].size()!=0 ||
		 degree[2].size()!=0){

	       count += degree[0].size(); degree[0].clear();
	    
	      // degree 1
	      if(degree[1].size() >  0){
		int node = *degree[1].begin();
		count++;
		// remove it
		degree[1].erase(node);
		processed[node]=true;
		processneighbours(node, nb, degree, processed);
		continue;
	      }
	      
	     if(degree[2].size() >  0){
		int node = *degree[2].begin();
		count++;
		degree[2].erase(node);
		processed[node]=true;
		processneighbours(node, nb, degree,processed); 
		continue;
	      }
	    }

	    cout << count << endl;
	}
	return 0;

}

// how to iterate over a set
/*for(it = degree[0].begin(); it != degree[0].end(); ++it){
  cerr<<*it << " "; 
}*/
