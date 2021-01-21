#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef K::Point_2 P;

using namespace std;

void run(int n){
    int l, b, r, t; cin >> l >> b >> r >> t;
    vector<P> locs; locs.reserve(n);
    for(int i = 0; i < n; ++i){
        P pos; cin >> pos;
        locs.push_back(pos); // point of bacteria
    }
    Triangulation trang(locs.begin(), locs.end());
    vector<double> dist; dist.reserve(n);
    for(auto v = trang.finite_vertices_begin(); v!=trang.finite_vertices_end(); ++v){
        const int x = v->point().x();
        const int y = v->point().y();
        auto c = v->incident_vertices();
        double closest_squared = numeric_limits<double>::max();
        if(c!=0){
            do{
                if(!trang.is_infinite(c)){
                double dist_this = CGAL::squared_distance(c->point(), v->point());
                closest_squared = min(closest_squared, dist_this);
                }
            } while (++c != v->incident_vertices());
        }

        double boundary_distance = min({abs(l-x),abs(r-x),abs(b-y), abs(t-y)});
        dist.push_back(min(boundary_distance-0.5, (sqrt(max(closest_squared,1.0))-1)/2));
    }

    sort(dist.begin(), dist.end());
    cout << ceil(sqrt(dist[0])) << " " << ceil(sqrt(dist[n/2])) << " " << ceil(sqrt(dist[n-1])) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    //cout << fixed << setprecision(0);
    int n; cin >> n;
    while(n!=0){
        run(n);
        cin >> n; 
    }
}