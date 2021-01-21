#include <iostream>
#include <vector>
#include <climits>
#include <queue>

// CGAL includes
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

void compute(Triangulation &t){
    std::priority_queue<std::pair<K::FT, Triangulation::Face_handle>> queue;
    for (auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it){
        if (t.is_infinite(it)){
            it->info() = INT64_MAX;
            queue.push({INT64_MAX, it});
        } else {
            it->info() = -1;
            queue.push({0, it});
        }
    }
    while (!queue.empty()){
        Triangulation::Face_handle curr_f = queue.top().second;
        K::FT escape_val = queue.top().first;
        queue.pop();

        if (escape_val < curr_f->info())  continue; // already handled
        for (int i = 0; i < 3; i++){
            Triangulation::Face_handle nb = curr_f->neighbor(i);
            K::FT new_dist = t.segment(curr_f, i).squared_length();
            K::FT new_val = std::min(curr_f->info(), new_dist);
            if (nb->info() < new_val){
                queue.push({new_val, nb});
                nb->info() = new_val;
            }
        }
    }
}

void run(int n){
    std::vector<P> infected; infected.reserve(n);
    for (int i = 0; i < n; ++i){
        int x, y; std::cin >> x >> y;
        infected.push_back(P(x, y));
    }
    Triangulation t;
    t.insert(infected.begin(), infected.end());
    int m;std::cin >> m;
    compute(t);

    for (int i = 0; i < m; i++){
        P pos; std::cin >> pos;
        long d_in; std::cin >> d_in;
        K::FT d = d_in;

        P nearest = t.nearest_vertex(pos)->point();
        if (CGAL::squared_distance(pos, nearest) < d){ //early exit
            std::cout << "n"; continue;
        }
        Triangulation::Face_handle fh = t.locate(pos);
        if (4 * d <= fh->info()) std::cout << "y";
        else std::cout << "n";
    }
    std::cout << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    while (n!=0){
        run(n); std::cin >> n;
    }
}