#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

struct cmp{
	bool operator()(pair<int,int>a, pair<int,int> b){
		if(a.first < b.first) return true;
		else if((a.first == b.first) && (a.second > b.second))
			return true;
		else
			return false;
	}
}cmp;

bool subset(pair<int,int>a, pair<int,int>b){
	if(b.first >= a.first && b.second <= a.second)
		return true;
	else
		return false;
}

#define cerr if(false) cout 
int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		vector<pair<int,int> > rs;
		for(int i=0; i<n; ++i){
			int p,q; cin>>p>>q;
			if(p!=0 && q != 0)
				rs.push_back(make_pair(p,q));
		}
		sort(rs.begin(), rs.end(), cmp);

		for(int i=0; i<n; ++i)
			cerr << rs[i].first << " " << rs[i].second << endl;

		 n = rs.size(); // remove (0,0) pairs
		pair<int,int> last = make_pair(-1,-1);
		vector<bool> alive(n, true);
		// range of covered humans
		int start, end;
		bool gap = false;
		start = end = rs[0].first;
		if(start > 1){cout <<"0\n"; continue;}
		for(int i=0; i <n; ++i){
			// if the same
			if((i>0&&rs[i-1]==rs[i])|| (i < (n-1)&&rs[i]==rs[i+1]))
				alive[i]=false;

			// if it is not covered by the last one, it is now alive
			if(subset(last, rs[i]))
				alive[i] = false;
			else
				last = rs[i];

			if((rs[i].first-1 <= end) ){
				if(rs[i].second > end)
					end = rs[i].second;
			}
			else{
				gap = true;
				break;
			}
		}
		if(gap)
			{cout << "0\n"; continue;}

		int count=0;
		for(int i=0; i<n; ++i)
			if(alive[i])count++;
		if(end == m)
			cout << count << "\n";
		else
			cout<<"0\n";
	}
	return 0;
}

