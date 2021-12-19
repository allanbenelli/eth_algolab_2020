#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

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
    int n, m, k; long s; cin >> n >> m >> s >> k;
    typedef pair<K::Point_2, Index> IPoint;
    vector<IPoint> points; points.reserve(n);
    for(int i = 0; i < n; ++i){
        int x,y; cin >> x >> y;
        points.push_back({K::Point_2(x,y), i});
    }
    Delaunay t;
    t.insert(points.begin(), points.end());

    // extract edges and sort by (squared) length
    // This step takes O(n log n) time (for the sorting).
    EdgeV edges;
    edges.reserve(3*n+m); // there can be no more in a planar graph
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    for(int i = 0; i < m; ++i){
        K::Point_2 bone; cin >> bone;
        auto nearest_v = t.nearest_vertex(bone);
        edges.push_back({nearest_v->info(), -1, 4*CGAL::squared_distance(nearest_v->point(), bone)});
    }
    std::sort(edges.begin(), edges.end(),
            [](const Edge& e1, const Edge& e2) -> bool {
            return std::get<2>(e1) < std::get<2>(e2);
                });

    boost::disjoint_sets_with_storage<> uf(n);
    Index n_components = n;
    vector<int> components(n,0);
    K::FT minRadius = -1;
    int maxK = 0;
    // ... and process edges in order of increasing length
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
        int v1 = get<0>(*e);
        int v2 = get<1>(*e);
        K::FT dist = get<2>(*e);
        if(v2 == -1){
            components[uf.find_set(v1)]++;
        }else{
            // determine components of endpoints
            Index c1 = uf.find_set(v1);
            Index c2 = uf.find_set(v2);
            if (c1 != c2) {
                int total_bones = components[c1]+components[c2];
                // this edge connects two different components => part of the emst
                uf.link(c1, c2);
                Index parent = uf.find_set(c1);
                components[parent] = components[c1]+components[c2];
                parent == c1 ? components[c2] = 0 : components[c1] = 0; 
                //components[uf.find_set(c1)] = total_bones;
            }

        }
        if(dist <= s){
            maxK = max(maxK, components[uf.find_set(v1)]);
        }
        if(minRadius == -1 && components[uf.find_set(v1)] >= k){
            minRadius = dist;
        }
    }
    cout << fixed << setprecision(0) << maxK << " " << minRadius << "\n";

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}