#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
using namespace std;


int table[100100][2];

//solve for each block
int solve(vector<int> (&s), vector<int> (&ps), int end, int k, bool block)
{
	if(end <= -1) // finished
		return 0;

	if(table[end][block] != -1)
			return table[end][block];

	// consider the last block
	int nextend = (end/k)*k-1;

	int w=0, c=0;
	for(int i=end; i> nextend; --i){ //n is divisable by k so we are always in a blocked position
		int s_i = s[i];
		if(block) s_i = !s_i;
		if(s_i != ps[i%k])
			w++;
		else
			c++;
	}

	int s1 = w + solve(s, ps, nextend, k, block);
	int s2 = c + 1 + solve(s, ps, nextend, k, !block);
	return table[end][block] = min(s1, s2);

}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n, k, x; cin>>n>>k>>x;
		vector<int>s(n);
		for(int i=0; i<n; ++i){cin>>s[i];}

		for(int i=0; i <n; ++i){table[i][0] = table[i][1] =-1;}
		//compute pattern
		vector<int> ps(k);
		for(int i=1; i <=k; ++i){
			ps[k-i] = !!(x & ( 1 << (i-1) ));
		}

		cout << solve(s, ps, n-1, k, 0) << endl;
	}
	return 0;
}

