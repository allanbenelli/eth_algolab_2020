#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_2<K>   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K>    Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 P;
typedef Delaunay::Face_handle Face;

using namespace std;

void compute(Delaunay &t){
    priority_queue<pair<K::FT, Face>> q;
    for(Face it = t.all_faces_begin(); it != t.all_faces_end(); ++it){
        it->info() = INT64_MAX;
        K::FT dist = INT64_MAX;
        if(!t.is_infinite(it)){
            dist = 0;
            it->info() = -1;
        }
        q.push({dist, it});
    }
    while(!q.empty()){
        K::FT curr_d = q.top().first;
        Face curr_f = q.top().second;
        q.pop();
        if(curr_d < curr_f->info()) continue;
        for(int i = 0; i < 3; ++i){
            Face ng = curr_f->neighbor(i);
            K::FT new_d = t.segment(curr_f, i).squared_length();
            new_d =  min(new_d, curr_f->info());
            if(ng->info()<new_d){
                ng->info() = new_d;
                q.push({new_d, ng});
            }
        }
    }
}

void run(int n){
    vector<P> infected; infected.reserve(n);
    for(int i = 0; i < n; ++i){
        int x, y; cin >> x >> y;
        infected.push_back(P(x,y));
    }
    Delaunay t;
    t.insert(infected.begin(), infected.end());
    compute(t);
    int m; cin >> m;
    for(int i = 0; i<m; ++i){
        int x,y; long d; cin >> x >> y >> d;
        K::FT D = d;
        P pos(x,y);
        P neareast_v = t.nearest_vertex(pos)->point();
        if(CGAL::squared_distance(pos, neareast_v) < D){
            cout << "n"; continue;
        }
        Face nearest_f = t.locate(pos);
        if(nearest_f->info() < 4*D){
            cout << "n";
        } else cout << "y";
    } 
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t!=0){
        run(t);
        cin >> t;
    }
}
