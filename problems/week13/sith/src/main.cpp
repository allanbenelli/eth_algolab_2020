#include <iostream>
#include <vector>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>


using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                              P;
typedef Triangulation::Vertex_circulator                        V_Circulator;


void testcase(){
    int n; long r;
    cin >> n >> r;
    vector<P> pts; pts.reserve(n);

    for(int i = 0; i < n; ++i){
        P point;
        cin >> point;
        pts.push_back(point);
    }
    map<int, int> cluster_size;
    Triangulation t;
    boost::disjoint_sets_with_storage<> uf(n);
    int best = 0;
    for(int i = n-1; i>=0 && i > best; i--){
        cluster_size[i] = 1;
        auto v = t.insert(pts[i]);
        v->info() = i;
        V_Circulator c = t.incident_vertices(v);
        if(c!=0){
            do{
                if(!t.is_infinite(c)){
                    int neighbor = c->info();
                    if(CGAL::squared_distance(pts[i], pts[neighbor])<= r*r){
                        //union
                        int c1 = uf.find_set(i);
                        int c2 = uf.find_set(neighbor);
                        if(c1 != c2){
                            uf.link(c1, c2);
                            cluster_size[uf.find_set(i)] = cluster_size[c1] + cluster_size[c2];
                        }
                    }

                }
            } while (++c != t.incident_vertices(v));

        }
        best = max(best, min(i, cluster_size[uf.find_set(i)]));
    }
    
    cout << best << "\n";
    

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}