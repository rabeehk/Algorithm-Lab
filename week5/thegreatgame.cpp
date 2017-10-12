#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
using namespace std;
 
int table[50010][2];
int dp(int pos, int goal, bool minimize,
        vector<vector<int> > (&nb)){
    if(table[pos][minimize] != -1)
        return table[pos][minimize];
 
    if(pos == goal)
        return 0;
 
    int finalcount;
    if(minimize)
        finalcount=numeric_limits<int>::max();
    else
        finalcount=numeric_limits<int>::min();
 
    for(int i=0; i<nb[pos].size(); ++i){
        int count = 0;
        int node = nb[pos][i];
        count +=(1+dp(node, goal, !minimize, nb));
        if(minimize)
            finalcount = min(finalcount, count);
        else
            finalcount = max(finalcount, count);
    }
 
    return table[pos][minimize] = finalcount;
    return 0;
}
 
int main()
{	
    ios_base::sync_with_stdio(false);
    int T; cin>>T;
    for(int tt=0; tt<T; ++tt){
        int n,m; cin>>n>>m;
        for(int i=0; i<n; ++i)
            table[i][0]=table[i][1]=-1;
        int r,b; cin>>r>>b; r--; b--;
        vector<vector<int> > nb(n);
        for(int i=0; i<m; ++i){
            int u,v; cin>>u>>v; u--; v--;
            nb[u].push_back(v);
        }
 
        int cr = dp(r, n-1, 1, nb);
        int cb = dp(b, n-1, 1, nb);
 
        if((cr == cb && cr %2 == 1) || (cr < cb))
            cout <<"0\n";
        else
            cout << "1\n";
    }
    return 0;
}
