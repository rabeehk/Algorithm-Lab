//============================================================================
// Name        : manman.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;

double floor_to_double(const K::FT & x){
	double a = floor(CGAL::to_double(x));
	while(a > x) a-=1;
	while(a+1 <= x) a+=1;
	return a;
}

int main() {
	ios_base::sync_with_stdio(false);
	int n; cin>>n;
	while(n!=0){
		long a,b,c,d; cin>>a>>b>>c>>d;
		K::Ray_2 ray(P(a,b), P(c,d));
		bool flag = false;
		vector<P> ps;
		for(int i=0; i <n; ++i){
			long r,s,t,u; cin>>r>>s>>t>>u;
			K::Segment_2 S(P(r,s), P(t, u));
			if(CGAL::do_intersect(ray, S)){
				CGAL::Object o = CGAL::intersection(ray, S);
				if(const P *in = CGAL::object_cast<P>(&o)){
					P p = *in;
					ps.push_back(p);
				}
				else if(const K::Segment_2 *in=CGAL::object_cast<K::Segment_2>(&o)){
					ps.push_back(in->source());
					//P p1= in->target();
					ps.push_back(in->target()); //p1);
				}

				flag= true;
			}
		}

		if(!flag)
			cout << "no\n";
		else{
			int bestind;
			K::FT mind = numeric_limits<double>::max();
			//cerr << mind << endl;
			P start = P(a,b);
			for(int i=0; i <ps.size(); ++i){
				K::FT d = CGAL::squared_distance(start, ps[i]);
				if(d < mind){
					mind = d;
					bestind = i;
				}
			}
			//cout bestind coordinates
			cout << (long)floor_to_double(ps[bestind].x()) << " "
			     << (long)floor_to_double(ps[bestind].y()) << "\n";
		}
		cin >> n;
	}
	return 0;
}

