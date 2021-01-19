#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::pair<int,bool> vertex_info; //int component, bool which color 
typedef CGAL::Triangulation_vertex_base_with_info_2<vertex_info,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> dfs_tds;
typedef CGAL::Delaunay_triangulation_2<K, dfs_tds> Triangulation;
typedef K::Point_2 pnt;

bool sanity_check(std::vector<pnt> & v0, K::FT const & r){
    Triangulation t0(v0.begin(), v0.end());
    //sanity check, no 2 radio stations with same color are too close to each other
    for(auto e = t0.finite_edges_begin(); e != t0.finite_edges_end(); ++e){
        if(t0.segment(*e).squared_length() <= r) return false;
    }
    return true;
}

bool coloring_mst_possible(Triangulation & t, K::FT const & r){
    //initializing
    for(auto v = t.finite_vertices_begin(); v!=t.finite_vertices_end(); ++v){
        v->info() = {0,false};
    }
    int comp = 0;
    std::vector<pnt> v0, v1;
    // sanity check at the end that no two radio stations with the same color are too close to each other!
    for(auto v  = t.finite_vertices_begin(); v!=t.finite_vertices_end(); ++v){
        if(v->info().first == 0){
            v->info().first = ++comp;
            // DFS 
            std::vector<Triangulation::Vertex_handle> stack(1,v);
            while (!stack.empty()){
                Triangulation::Vertex_handle cur = stack.back(); //DFS: get latest element
                stack.pop_back(); //remove last element
                Triangulation::Vertex_circulator c = t.incident_vertices(cur); // get neighbors from current vertex
                do {
                    if(!t.is_infinite(c) && CGAL::squared_distance(cur->point(), c->point()) <= r){ // ignor if edge longer than r
                        if(cur->info()==c->info()) return false; // same color neighbor, 2-coloring fails
                        if(c->info().first == 0){ // in no component if it's still 0
                            stack.push_back(c);
                            c->info() = {comp, !cur->info().second}; // give inc component ctr and opposite boolean
                        }
                    }
                } while (++c != t.incident_vertices(cur)); // while not at beginning again
            }
        }
        // seperate by color // try this as it is slow

        if(v->info().second) v0.push_back(v->point());
        else v1.push_back(v->point());
    }
    return sanity_check(v0, r) && sanity_check(v1, r);; // everything good
}

bool check_stations(Triangulation & t, pnt & start, pnt & end, K::FT const & r){
    auto station_start = t.nearest_vertex(start);
    auto station_end = t.nearest_vertex(end);
    /*
    Checks to make:
    1. station start and station end in the same component
    2. distance from Holmes to Start Station smaller than r
    3. distance from End Station to watson smaller than r
    */
    if (station_start->info().first == station_end->info().first &&
        CGAL::squared_distance(start, station_start->point()) <= r &&
        CGAL::squared_distance(end, station_end->point()) <= r){ 
        return true;
    } else{
        return false;
    }
}

void testcase(){
    std::size_t n,m;  K::FT r;
    std::cin >> n >> m >> r;

    r *= r; // we check squared_distance with CGAL
    std::vector<pnt> stations(n);
    for (std::size_t i = 0; i < n; i++){
        std::cin >> stations[i];
    }
    // delaunay trangulation
    Triangulation trang(stations.begin(), stations.end());
    // two color possible?
    bool possible = coloring_mst_possible(trang, r);

    //check for each point
    for (std::size_t i = 0; i < m; i++){
        pnt start, end;
        std::cin >> start >> end;

        if(!possible) std::cout << "n"; //finished here 
        else{
            if(CGAL::squared_distance(start, end) <=r) {
                std::cout << "y"; continue;
            }
            if(check_stations(trang, start, end, r)) std::cout << "y";
            else std::cout << "n";
        }
    }
    std::cout << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::size_t t; std::cin >> t;
    for(std::size_t i = 0; i < t; i++){
        testcase();
    }
}