#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		vector<int>ms(n);
		for(int i=0; i<n; ++i){
			cin >> ms[i];
		}
		
		vector<pair<int,int> > rs;
		for(int i=0; i<n; ++i)
			for(int j=0; j<ms[i]; ++j){
				long p; cin>>p;
				rs.push_back(make_pair(p,i));
			}

		sort(rs.begin(), rs.end());
		long mincost = numeric_limits<long>::max();
		vector<int>visit(n, 0);
		int sum =0;
		int a=0;
		for(int b=0; b<rs.size(); ++b){
			if(!visit[rs[b].second])
				sum++;
			visit[rs[b].second]++;
		
			while(sum == n){
				long cost = rs[b].first - rs[a].first+1;
				mincost = min(mincost, cost);
				visit[rs[a].second]--;
				if(visit[rs[a].second] == 0)
					sum--;
				a++;
			}
		}

		cout << mincost << endl;
	}
	return 0;
}
