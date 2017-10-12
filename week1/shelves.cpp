/* bn+am <= l */
#include<iostream>
#include<cmath>
#include<limits>
using namespace std;

int main()
{
	int T; cin>>T;
	for(int tt=0;tt<T; ++tt){
		long l,m,n; cin>>l>>m>>n;
		double sqrtl = sqrt(l);
		int o_a, o_b, o_r = numeric_limits<int>::max();
		if(n > sqrtl){
			for(int b=sqrt(l); b >= 0; --b){
					if(l-b*n <0) continue;
					int a = (l-b*n)/m;
					int r = l-a*m-b*n;
					if(r < o_r){
						o_a = a;
						o_b=b;
						o_r=r;
					}
			}
		}
		else{
			for(int a=0; a<sqrtl; ++a){
				if(l-a*m<0) continue;
				int b = (l-a*m)/n;
				int r = l-a*m-b*n;
				if(r < o_r){
					o_a=a;
					o_b=b;
					o_r=r;
				}
			}
		}
		cout << o_a << " " << o_b << " " << o_r << endl;
	}
	return 0;
}

