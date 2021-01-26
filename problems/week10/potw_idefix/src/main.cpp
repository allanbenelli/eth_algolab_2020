#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

typedef std::tuple<K::FT,Index,Index> Edge;
typedef std::vector<Edge> EdgeV;
typedef K::Point_2 P;

using namespace std;

void run(){
    int n, m, k; long s; cin >> n >> m >> s >> k;
    vector<pair<K::Point_2,Index>> trees; trees.reserve(n);
    for(int i = 0; i < n; ++i){
        P tree; cin >> tree;
        trees.emplace_back(tree, i);
    }
    Delaunay t;
    t.insert(trees.begin(), trees.end());

    EdgeV edges;
    edges.reserve(3*n+m); // there can be no more in a planar graph
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(t.segment(e).squared_length(), i1, i2);
    }

    for(int i = 0; i < m; ++i){
        P bone; cin >> bone;
        auto neareast_v = t.nearest_vertex(bone);
        edges.emplace_back(4*CGAL::squared_distance(bone, neareast_v->point()), neareast_v->info(), -1);
    }
    std::sort(edges.begin(), edges.end());

    int maxK = 0;
    K::FT minRadius = -1;
    vector<int> bones_in_set(n,0);
    // setup and initialize union-find data structure
    boost::disjoint_sets_with_storage<> uf(n);
    // ... and process edges in order of increasing length
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
        K::FT dist = get<0>(*e);
        int v1 = get<1>(*e);
        int v2 = get<2>(*e);
        if(v2 == -1){ // bone
        bones_in_set[uf.find_set(v1)]++;
        } else{
            // determine components of endpoints
            Index c1 = uf.find_set(v1);
            Index c2 = uf.find_set(v2);
            if (c1 != c2) {
                int total_bones = bones_in_set[c1] + bones_in_set[c2];
                // this edge connects two different components => part of the emst
                uf.link(c1, c2);
                bones_in_set[uf.find_set(v1)] = total_bones;
            }
        }
        if(dist <= s){
            maxK = max(maxK, bones_in_set[uf.find_set(v1)]);
        }
        if(minRadius == -1 && bones_in_set[uf.find_set(v1)] >= k){
            minRadius = dist;
        }
    }
    cout << setprecision(0) << fixed << maxK << " " << minRadius << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}