#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef IK::Point_2 P;
typedef IK::Segment_2 S;
typedef IK::Ray_2 R;

using namespace std;

void run(int n){
    vector<S> seg(n); R ray;
    cin >> ray;
    for(int i = 0; i < n; ++i){
        cin >> seg[i];
    }
    bool inter = false;
    for(int i = 0; i <n; ++i){
        if(CGAL::do_intersect(ray, seg[i])){
            inter = true;
            break;
        }
    }
    if(inter) cout << "yes\n"; 
    else cout << "no\n";
}

int main(){
    ios::sync_with_stdio(false);
    int t; 
    while(cin >> t && t) run(t);
}