#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define cerr if(false) cout
int table[1010][1010];
int solve(vector<int> (&cs), int start, int end){
	if(table[start][end] != -1)
		return  table[start][end];

	if(start == end) // only one left
		return table[start][end] = cs[start];

	if(start+1==end) //only two return max
		return table[start][end]=max(cs[start], cs[end]);

	
	int s1 = cs[start] + min(solve(cs, start+2, end), solve(cs,start+1, end-1));
	int s2 = cs[end] + min(solve(cs, start+1, end-1), solve(cs,start, end-2));
	return table[start][end]=max(s1, s2);

}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				table[i][j]=-1;
		vector<int>cs(n);
		for(int i=0; i <n; ++i) {cin>>cs[i];}
		cout << solve(cs, 0, n-1) << "\n";
	}
	return 0;
}

