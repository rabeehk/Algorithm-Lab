/*max size of matching in a tree(with DP)*/
#include<iostream>
#include<vector>
#include<limits>

using namespace std;
int table[1000000];

int maxsizematching(int s, int from, vector<vector<int> > (&nb)){
    if(table[s]!= -1)
        return table[s];

    if(nb[s].size() == 0)
        return table[s]=0;

    int maxs = numeric_limits<int>::min();
    int s1=0;
    for(int i=0; i<nb[s].size(); ++i){
	if(nb[s][i] == from) continue;
        s1+=maxsizematching(nb[s][i], s, nb);
    }
    maxs = max(s1, maxs);

    for(int i=0; i<nb[s].size(); ++i){
        int node = nb[s][i];
        if(node==from) continue;
        int s2=1; // choose this edge

        // add all the rest
        s2+=(s1-maxsizematching(node, s, nb));

        // for the chosen edge, add subtree size
        for(int j=0; j<nb[node].size(); ++j){
	    if(nb[node][j] == s) continue;
            s2+=maxsizematching(nb[node][j], node, nb);
        }
        maxs = max(s2, maxs);
    }

    return table[s]=maxs;
}

int main()
{
    int T; cin>>T;
    for(int i=0; i<1000000; ++i)
        table[i]=-1;
    for(int tt=0; tt<T; ++tt){
        int n,m; cin>>n>>m;
        vector<vector<int> > nb(n);
        for(int i=0; i<m; ++i){
            int a,b; cin>>a>>b; a--; b--;
            nb[a].push_back(b);
            nb[b].push_back(a);
        }
	
        cout << maxsizematching(0, -1, nb ) << endl;
    }
    return 0;
}

