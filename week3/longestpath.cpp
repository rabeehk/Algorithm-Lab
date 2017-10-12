#include<iostream>
#include<vector>
#include<limits>
using namespace std;

int len;
int table[100010];

int longest(vector<vector<int> > &nb, int a, int from){

	if(table[a] != -1)
		return table[a];
	
	if(nb[a].size() == 1 && nb[a][0] == from){
		//len = max(len,2);
		return 1;
	}

	int h1=0,h2=0;
	for(int i=0; i<nb[a].size(); ++i){
		int node = nb[a][i];
		if(node == from) continue;
		int h = longest(nb, node, a);
		if(h > h1){  h2=h1; h1=h;}
		else if(h > h2){h2=h;}
	}
	len = max(len, h1+h2+1);
	return table[a]=h1+1;
}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		len = numeric_limits<int>::min();
		for(int i=0; i <n; ++i)
			table[i]=-1;

		vector<vector<int> >nb(n);
		for(int i=0; i<(n-1); ++i){
			int a,b; cin>>a>>b;
			nb[a].push_back(b);nb[b].push_back(a);
		}
		if(n == 1)
			{cout << 1 << endl; continue;}
		longest(nb, 0, -1);
		cout << len << endl;

	}
	return 0;
}

