#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_2<K>   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K>    Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Face_handle                                  Face;


void compute3(Delaunay &t){
    priority_queue<pair<K::FT, Face>> q;
    for(auto it = t.all_faces_begin(); it != t.all_faces_end(); it++){
        K::FT dist = INT64_MAX;
        if(!t.is_infinite(it)){
            K::Point_2 v = t.dual(it);
            dist = CGAL::squared_distance(v, it->vertex(0)->point());
        }
        it->info() = dist;
        q.push({dist, it});
    }
    while(!q.empty()){
        K::FT curr_d = q.top().first;
        Face curr_f = q.top().second;
        q.pop();
        if(curr_d < curr_f->info()) continue;
        for(int i = 0; i < 3; i++){
            Face ng = curr_f->neighbor(i);
            K::FT new_d = t.segment(curr_f, i).squared_length();
            new_d = min(new_d, curr_f->info());
            if(new_d > ng->info()){
                ng->info() = new_d;
                q.push({new_d, ng});
            }
        }
    }
}


void compute2(Delaunay &t){
    priority_queue<pair<K::FT, Face>> q;
    for(auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it){
        K::FT dist = INT64_MAX;
        if(!t.is_infinite(it)){
            K::Point_2 v = t.dual(it);
            dist = CGAL::squared_distance(v, it->vertex(0)->point());
        }
        it->info() = dist;
        q.push({dist, it});
    }
    while(!q.empty()){
        K::FT curr_d = q.top().first;
        Face curr_f = q.top().second;
        q.pop();
        if(curr_d < curr_f->info()) continue;
        for(int i = 0; i < 3; i++){
            Face ng = curr_f->neighbor(i);
            K::FT new_distance = t.segment(curr_f, i).squared_length();
            new_distance = min(new_distance, curr_f->info());
            if(new_distance > ng->info()){
                ng->info() = new_distance;
                q.push({new_distance, ng});
            }
        }
    }
}


void compute(Delaunay &t){
    priority_queue<pair<K::FT, Face>> q;
    for(Face it = t.all_faces_begin(); it != t.all_faces_end(); ++it){
        K::FT dist = INT64_MAX;
        if(!t.is_infinite(it)){
            K::Point_2 v = t.dual(it);
            dist = CGAL::squared_distance(it->vertex(0)->point(), v);
        }
        it->info() = dist;
        q.push({dist, it});
    }
    while(!q.empty()){
        /* wenn dein escapevalue kleiner ist als min meines und der distanz der kante, dann kannst du bei mir raus
            man schaut nicht moving an, sondern, man maximiert nach dem grössten escapevalue vom face
            wenn man gefangen ist in einem face, dann ist der escapevalue gleich dem anfang
            WENN man ausweg suchen muss, dann muss bei nicht infiniten die info initial bei -1 sien
            die distance in der queue = 0
        
        */
        K::FT curr_esc = q.top().first;
        Face curr_face = q.top().second;
        q.pop();
        if(curr_esc < curr_face->info()) continue; //already found a bigger escape val
        for(int i = 0; i < 3; i++){
            Face ng = curr_face->neighbor(i);
            K::FT new_esc = t.segment(curr_face, i).squared_length();
            new_esc = min(new_esc, curr_face->info()); //wähle minimum von mir und der kante
            if(ng->info()<new_esc){
                ng->info()= new_esc;
                q.push({new_esc, ng});
            }
        }

    }
}

void run(){
    int n, m; long r; cin >> n >> m >> r;
    vector<K::Point_2> trees; trees.reserve(n);
    for(int i = 0; i < n; ++i){
        long x, y; cin >> x >> y;
        trees.push_back(K::Point_2(x,y));
    }
    Delaunay t;
    t.insert(trees.begin(), trees.end());
    compute3(t);
    for(int i = 0; i < m; ++i){
        long x, y, s_in; cin >> x >> y >> s_in;
        K::FT s = s_in+r;
        K::Point_2 pos(x,y);
        K::Point_2 nearest_v = t.nearest_vertex(pos)->point();
        if(CGAL::squared_distance(pos, nearest_v) < s*s){
            cout << "n"; continue;
        }
        Face fa = t.locate(pos);
        if(fa->info()< CGAL::square(2*s)){
            cout << "n";
        } else{
            cout << "y";
        }        
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}