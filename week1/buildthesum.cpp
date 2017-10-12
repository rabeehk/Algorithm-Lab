#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int T;  cin >> T;
	for(int tt=0; tt <T; ++tt){
		int n; cin>>n;
		double sum = 0;
		for(int i=0; i <n; ++i){
			double a; cin>>a;
			sum += a;
		}
		cout.precision(6); cout << sum << endl;
	}
	return 0;
}
