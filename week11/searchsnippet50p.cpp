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
		vector<vector<long> > ps(n);
		for(int i=0; i<n; ++i)
			for(int j=0; j<ms[i]; ++j){
				long p; cin>>p;
				ps[i].push_back(p);
			}

		sort(ps[0].begin(), ps[0].end());
		sort(ps[1].begin(), ps[1].end());

		long minr = numeric_limits<long>::max();
		int i=0, j=0;
		while(i < ms[0] && j < ms[1]){
			long diff = fabs(ps[0][i]-ps[1][j])+1;
			minr= min(minr, diff);
			if(ps[0][i] > ps[1][j])
				j++;
			else
				i++;
		}
		cout << minr << endl;
	}
	return 0;
}
