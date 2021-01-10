#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef IK::Point_2 P;
typedef IK::Segment_2 S;
typedef IK::Ray_2 R;

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    long x, y, a, b;
    long r, s, t, u;
    while(true){
        int n; cin >> n;
        if(n==0) break;
        bool intersection= false;
        cin >> x >> y >> a >> b;
        R ray(P(x,y), P(a,b));
        for(int i = 0; i< n ; i++){
            cin >> r >> s >> t >> u;
            if(!intersection){
                S seg(P(r,s), P(t,u));
                if(CGAL::do_intersect(ray,seg)) intersection = true;
            }
        }
        cout << (intersection ? "yes" : "no") << "\n";
    }
}