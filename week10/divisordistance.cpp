#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

/*just to have it*/
//create prime numbers up to n
vector<int> primes;
void generate_prime(int n){
	vector<bool> sieve(n, true);
	sieve[1] = false;
	for(int i=2; i<n; ++i){
		if(sieve[i]){
			for(int j=2*i; j<n; j+=i){
					sieve[j]=false;
			}
		}
	}

	primes.clear();
	for(int i=2; i<n; ++i){
		if(sieve[i]){
			primes.push_back(i);
		}
	}

	cerr<< "primes numbers\n";
	for(int i=0; i<primes.size(); ++i)
		cerr << primes[i] << " ";
	cerr<<endl;
}

#define num 10000000
int table[num]; //parent

int parent(int a){
	if(table[a-1] != -1)
		return table[a-1];

	for(int d=2; d<=sqrt(a); ++d)
		if(a%d ==0)
			return table[a-1]=a/d;

	return table[a-1]=1;
}

int main()
{
	int T; cin>>T;
	for(int i=0; i<num; ++i )
		table[i] = -1;
	for(int tt=0; tt<T; ++tt){
		int n,c; cin>>n>>c;
		for(int i=0; i<c; ++i){
			int a,b; cin>>a>>b;

			int count=0;
			while(a != b){
				if(a > b)
					a = parent(a);
				else
					b = parent(b);
				count++;
			}
			cout << count << "\n";
		}
	}
	return 0;
}

