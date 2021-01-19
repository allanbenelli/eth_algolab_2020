#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int n; cin >> n;
    while(n!=0){
        vector<P> locs; locs.reserve(n);
        for(int i = 0; i < n; ++i){
            P loc; cin >> loc;
            locs.push_back(loc);
        }
        Triangulation t;
        t.insert(locs.begin(), locs.end());
        int m; cin >> m;
        for(int i = 0; i<m; ++i){
            P pos; cin >> pos;
            P v = t.nearest_vertex(pos)->point();
            cout << CGAL::squared_distance(pos, v) << "\n";
        }
        cin >> n;
    }
}