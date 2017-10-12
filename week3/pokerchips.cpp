#include<iostream>
#include <vector>
#include <cmath>
#include <map>
#include <limits>
using namespace std;

map<vector<int>, int> table;
int solve(vector<vector<int> > cs, vector<int> ms, int n){
	if(table.count(ms))
		return table[ms];

	int maxs = numeric_limits<int>::min();
	for(int i=1; i<(1 <<n); ++i){
		int c = -1;
		int num =0;
		int k;
		vector<int> nms;
		nms = ms;
		for(k=0; k<n; ++k){
			if(i &(1<<k)){
				if(ms[k] == 0)
					break;
				if(c == -1){
					c = cs[k][ms[k]-1];
					nms[k]--;
				}
				else if (c !=cs[k][ms[k]-1] )
					break;
				else
					nms[k]--;
				num++;
			}
		}
		if(k == n){
		int score = num >= 2 ? pow(2, num-2) : 0;
		score += solve(cs, nms, n);
		maxs = max(maxs, score);
		}
	}
	return table[ms] = maxs;
}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		table.clear();
		int n; cin>>n;
		vector<int>ms(n);
		for(int i=0; i<n; ++i){
			cin >> ms[i];
		}
		vector<vector<int> > cs(n);
		for(int i=0; i<n; ++i){
			for(int j=0; j<ms[i]; ++j){
				int a; cin>>a;
				cs[i].push_back(a);
			}
		}
		vector<int> zerostate(n,0);
		table[zerostate]=0;
		cout << solve(cs, ms, n) << endl;

	}
	return 0;
}

