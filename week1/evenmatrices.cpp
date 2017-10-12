#include<iostream>
#include<vector>
using namespace std;

int compute(vector<int> &arr, int n){
	int sum =0;
	int count = 0;
	int pree = 1, preo = 0;
	for(int i=0; i <n; ++i){
		sum += arr[i];
		if(sum % 2 == 0){
			count += pree;
			pree++;
		}
		else{
			count += preo; preo++;
		}
	}
	return count;
}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;

		vector<vector<int> > t(n);
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				int a; cin>>a;
				t[i].push_back(a);
			}
		}

		int count =0;
		//fix two columns
		for(int i=0; i<n; ++i){
			vector<int>sum(n, 0);
			for(int j=i; j<n; ++j){
				//iterate over a row
				for(int k=0; k<n; ++k){
					sum[k]+=t[k][j];
				}
				// now this sum is complete
				count += compute(sum,n);
			}
		}
		cout << count << "\n";
	}
	return 0;
}

