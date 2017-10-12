#include<iostream>
#include<vector>
#include<algorithm>
#include <limits>
using namespace std;

//you should also consider all the baot can have the p inside the range you choose 
int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin >>n;
		vector<pair<int,int> > lp;
		for(int i=0; i <n; ++i){
			int l,p; cin >> l >> p;
			lp.push_back(make_pair(p, l));
		}
		sort(lp.begin(), lp.end());
		int best;
		int end = numeric_limits<int>::min();
		best = -1;
		int count =0;
		for(int i=0; i <n; ++i){
			if(i <= best) continue;
			int last = max(end+lp[i].second, lp[i].first);
			if(end > lp[i].first) continue; // to the next
			//check for betters
			for(int j=i+1; j<n ;++j){
				
				int pos = max(end+lp[j].second, lp[j].first);
				if(pos < last){
					best = j; // best all have starting point before the one chosen
					last = pos;
				}
				if(lp[j].first > last) // it cannot be any better in this choice
					break;
			}
			end = last;
			count ++;
		}
		cout << count << endl;

	}
	return 0;
}

