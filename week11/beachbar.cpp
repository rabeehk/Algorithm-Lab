//============================================================================
// Name        : beachbar.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<limits>
#include<vector>
#include<cmath>
#include <algorithm>
using namespace std;

int main() {
	int T;
	cin>>T;
	for(int tt=0; tt<T; ++tt){
			int minR = numeric_limits<int>::max();
			int maxc = numeric_limits<int>::min();
			vector<int>sol;
			int n; cin>>n;
			vector<int>ls(n);
			for(int i=0; i <n; ++i){
				cin >> ls[i];
			}
			sort(ls.begin(), ls.end());
			for(int i=0; i <n; ++i){

				int l = i;bool f = false; // last index
				while(ls[l]-ls[i] <= 200 && l<n){
					f = true; l++;
					}
				if(f)
					l--;
				int r;
				int range = ls[l]-ls[i];
				//cout <<"r: "  << ls[l] <<  " " << ls[i] << endl;
				int count = l-i+1;
				if(range % 2 == 0)
					r = ls[l]-(ls[l]+ls[i])/2;
				else
					r = ls[l]-floor((ls[l]+ls[i])/2.0);

				if(count > maxc ||(count==maxc && r < minR) ){
					sol.clear();
				}

				if(count > maxc ||(count==maxc && r < minR)||
					(count==maxc && r == minR)){
					minR = r; maxc = count;
					if(range%2==0){
						sol.push_back((ls[l]+ls[i])/2.0);
						//cout <<"sol"<< (ls[l]+ls[i])/2.0 << endl;
					}else{
						sol.push_back(floor((ls[l]+ls[i])/2.0));
						sol.push_back(ceil((ls[l]+ls[i])/2.0));
						//cout << "sol" << floor((ls[l]+ls[i])/2.0) << " " << ceil((ls[l]+ls[i])/2.0) << endl;
					}
				}
			}
			cout << maxc << " " << minR << endl;
			for(int i=0; i <sol.size(); ++i){
				if(i < sol.size()-1)
					cout << sol[i] << " " ;
				else cout << sol[i];
			}
			cout << endl;

	}
	return 0;
}

