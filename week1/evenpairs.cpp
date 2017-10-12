#include<iostream>
using namespace std;

int main()
{
	int n; cin >>n;
	int sum =0;
	int count  = 0;
	int pree = 1; // pre even
	int preo = 0; // pre odd
	for(int i=0; i <n; ++i){
		int a; cin >> a;
		sum += a;
		if(sum %2 ==0){
			count += pree;
			pree++;
		}
		else
		{
			count += preo;
			preo++;
		}
	}
	cout << count  << "\n";
	return 0;
}

