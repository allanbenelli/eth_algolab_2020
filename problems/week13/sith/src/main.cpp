#include <iostream>
#include <vector>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;

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
    boost::disjoint_sets_with_storage<> uf(n);
    Triangulation t;
    int best = 0;
    for(int i = n-1; i>=0&&i>=best; i--){
        cluster_size[i] = 1;
        auto v = t.insert(pts[i]);
        v->info()= i;
        Triangulation::Vertex_circulator c = t.incident_vertices(v);
        if(c!=0){
            do{
                if(!t.is_infinite(c)){
                    int neighb = c->info();
                    K::FT dist = CGAL::squared_distance(v->point(), c->point());
                    if (dist <= r * r){
                        int set_1 = uf.find_set(i);
                        int set_2 = uf.find_set(neighb);
                        if(set_1!=set_2){
                            uf.link(set_1, set_2);
                            cluster_size[uf.find_set(i)] = cluster_size[set_2] + cluster_size[set_1];
                        }
                    }
                }
            }while(++c != t.incident_vertices(v));

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