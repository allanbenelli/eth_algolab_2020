#include <iostream>
#include <vector>
#include <climits>
#include <queue>

// CGAL includes
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 Point;


void precompute(Triangulation &t){
    std::priority_queue<std::pair<K::FT, Triangulation::Face_handle>> queue;
    for(auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it){
        if(t.is_infinite(it)){
            it->info() = INT64_MAX;
            queue.push(std::make_pair(INT64_MAX, it));
        } else {
            Point v = t.dual(it);
            K::FT dist = CGAL::squared_distance(v, it->vertex(0)->point());
            it->info() = dist;
            queue.push(std::make_pair(dist, it));
        }
    }
    while (!queue.empty()){
        Triangulation::Face_handle curr_f = queue.top().second;
        K::FT escape_val = queue.top().first;
        queue.pop();
        if(escape_val < curr_f->info()) continue; // already handled
        for(int i = 0; i < 3; i++){
            Triangulation::Face_handle neighbor = curr_f->neighbor(i);
            K::FT new_dist = t.segment(curr_f, i).squared_length();
            K::FT new_val = std::min(curr_f->info(), new_dist);
            if(neighbor->info() < new_val){
                queue.push(std::make_pair(new_val, neighbor));
                neighbor->info() = new_val;
            }
        }
    }
    
}

void run(){
    int n, m; long r; std::cin >> n >> m >> r;
    std::vector<Point> trees(n);
    for(int i = 0; i < n; ++i){
        long x, y; std::cin >> x >> y;
        trees[i] = Point(x,y);
    }
    Triangulation t;
    t.insert(trees.begin(), trees.end());
    precompute(t);

    for(int i = 0; i < m; ++i){
        long x, y, s_in; std::cin >> x >> y >> s_in;
        Point pos(x,y);
        K::FT s = s_in+r;
        Point nearest = t.nearest_vertex(pos)->point();
        if(CGAL::squared_distance(pos, nearest)< s*s) {std::cout << "n"; continue;}
        Triangulation::Face_handle f = t.locate(pos);
        if (f->info() < CGAL::square(2 * s)){
            std::cout << "n";
        } else{
            std::cout << "y";

        }
    }
    std::cout << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) run();
}