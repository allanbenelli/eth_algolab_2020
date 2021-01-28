#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <tuple>
#include <algorithm>

typedef std::size_t                                            Index;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

using namespace std;

int question_2(const EdgeV &edges, const long s, const int k, const int n){
    vector<int> component_size(n,1);
      // setup and initialize union-find data structure
    boost::disjoint_sets_with_storage<> uf(n);
    Index n_components = n;
    // ... and process edges in order of increasing length
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
        // determine components of endpoints
        Index c1 = uf.find_set(std::get<0>(*e));
        Index c2 = uf.find_set(std::get<1>(*e));
        if (get<2>(*e) >= s) break; // early termination
        if (c1 != c2) {
            // this edge connects two different components => part of the emst
            uf.link(c1, c2);
            Index parent = uf.find_set(c1);
            component_size[parent] = component_size[c1] + component_size[c2];
            (parent == c1 ) ? component_size[c2] = 0 : component_size[c1] = 0;
            if (--n_components == 1) break;
        }
    }
    sort(component_size.begin(), component_size.end(), greater<int>());
    int largest_idx = 0, smallest_idx = n_components-1, confirmed_families = 0;
    while(largest_idx<=smallest_idx){
        if(component_size[largest_idx]>=k){
            confirmed_families++;
            largest_idx++;
        } else{
            component_size[largest_idx] += component_size[smallest_idx--];
        }
    } return confirmed_families;
}

void run(){
    int n, k, f; long s; cin >> n >> k >> f >> s;
    vector<pair<K::Point_2, Index>> tents; tents.reserve(n);
    for(int i = 0; i < n; ++i){
        int x, y; cin >> x >> y;
        tents.push_back(make_pair(K::Point_2(x,y), i));
    }
    Triangulation t;
    t.insert(tents.begin(), tents.end());
    EdgeV edges;
    edges.reserve(3*n); // there can be no more in a planar graph
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    std::sort(edges.begin(), edges.end(),
            [](const Edge& e1, const Edge& e2) -> bool {
            return std::get<2>(e1) < std::get<2>(e2);
                });

    int answer2 = question_2(edges, s, k, n);

    int left = 0, right = edges.size()-1;
    long answer1 = 0;
    while(left <= right){
        int idx = left + (right-left)/2;
        long sq_len = get<2>(edges[idx]);
        if(question_2(edges, sq_len, k, n) >= f){
            left = idx + 1;
            answer1 = sq_len;
        } else{
            right = idx -1;
        }
    }
    cout << answer1 << " " << answer2 << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}