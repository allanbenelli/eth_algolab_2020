#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef IK::Point_2 P;
typedef vector<P> Pts;
typedef vector<int> Covered; // for segments
typedef vector<Covered> Trs;
typedef Covered::const_iterator CCI;

bool contains(const Pts& t, const P& point){
    return (!CGAL::right_turn(t[0],t[1], point)&&!CGAL::right_turn(t[2],t[3], point)&&!CGAL::right_turn(t[4],t[5], point));
}

void testrun(){
    int m, n; cin >> m >> n;
    Pts path; path.reserve(m);
    for(int i = 0; i < m; ++i){
        P point; cin >> point;
        path.push_back(point);
    }
    vector<vector<int>> triangles(n);
    for(int i = 0; i < n; ++i){
        Pts t;
        for(int j = 0; j < 6; ++j){
            P tr; cin >> tr;
            t.push_back(tr);
        }
        for(int j = 0; j < 6; j+=2){
            if(CGAL::right_turn(t[j], t[j+1], t[(j+2)%6])){
                swap(t[j], t[j+1]);
            }
        }
        bool previous = contains(t, path[0]);
        for(int j = 1; j < m; ++j){
            if(contains(t, path[j])){
                if(previous){
                    triangles[i].push_back(j-1);
                } else previous = true;
            } else {
                previous = false;
            }
        }
    }
    vector<int> covered(m-1, 0);
    int uncovered = m-1;
    int best_nr = n;
    int l = 0, r = 0;
    while(l < n){
        while(uncovered && r < n){ // ensure covering property
            for(auto it = triangles[r].begin(); it!= triangles[r].end(); ++it){
                covered[*it]++;
                if(covered[*it]==1) uncovered--;
            }
            r++;
        }
        if(uncovered != 0) break; // coverty property broken
        do{ // can we remove triangle?
            for(auto it = triangles[l].begin(); it!= triangles[l].end(); ++it){
                covered[*it]--;
                if(covered[*it]==0) uncovered++;
            }
        } while( ++l != r && uncovered == 0);
        best_nr = min(best_nr, r-l+1);
    }
    cout << best_nr << "\n";
}

int main(){
    int t; cin >> t;
    for (int i = 0; i < t ; i++){
        testrun();
    }
}