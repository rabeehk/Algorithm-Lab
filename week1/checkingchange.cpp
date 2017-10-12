#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
using namespace std;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int maxm = 10001; //overflows with max
		vector<int>table(10010, maxm);
		vector<bool>visit(10010, false);

		table[0]=0;
		int c,m; cin>>c>>m;
		vector<int> cs(c);
		for(int i=0; i<c; ++i){
			cin >> cs[i];
		}
		for(int i=0; i<m; ++i){
			int value; cin >> value;
			for(int i=1; i<= value; ++i){
				if(visit[i]) continue;
				for(int j=0; j<c; ++j){
					if(cs[j] <= i)
						if( (table[i-cs[j]]+1) < table[i])
							table[i]=table[i-cs[j]]+1;
				}
				visit[i]=true;
			}
			if(table[value] == maxm)
				cout << "not possible\n";
			else
				cout << table[value] << "\n";
		}
	}
	return 0;
}

