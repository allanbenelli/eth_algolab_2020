#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <map>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 P;

// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}
using namespace std;

void run(){
    int n; long r ; cin >> n >> r;
    vector<P> pts; pts.reserve(n);
    for(int i = 0; i < n; ++i){
        P pt; cin >> pt;
        pts.push_back(pt);
    }
    map<int,int> cluster;
    Delaunay t;
    boost::disjoint_sets_with_storage<> uf(n);
    int best = 0;
    for(int i = n-1; i >= 0 && i > best; i--){
        cluster[i] = 1;
        auto v = t.insert(pts[i]);
        v->info() = i;
        Delaunay::Vertex_circulator c = t.incident_vertices(v);
        if(c!=0){
            do{
                if(!t.is_infinite(c)){
                    int ng = c->info();
                    if(CGAL::squared_distance(c->point(), v->point()) <= r*r){
                        Index c1 = uf.find_set(i);
                        Index c2 = uf.find_set(ng);
                        if(c1!=c2){
                            uf.link(c1,c2);
                            cluster[uf.find_set(c1)] = cluster[c1] + cluster[c2];
                        }
                    }
                }
            } while(++c != t.incident_vertices(v));
        }
        best = max(best, min(i, cluster[uf.find_set(i)]));
    }
    cout << best << "\n";
    

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}