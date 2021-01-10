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
    int m, n;
    cin >> m >> n;
    Pts path;
    path.reserve(m);
    for(int i = 0; i < m; i++){
        P point;
        cin >> point;
        path.push_back(point);
    }
    Trs triangles(n); // for saving which triangle covers which path segment
    for(int i = 0; i < n; i++){
        Pts t;
        for(int j = 0; j < 6; j++){
            P po; cin >> po;
            t.push_back(po);
        }
        for(int j = 0; j<6; j+=2){
            if(CGAL::right_turn(t[j], t[j+1], t[(j+2)%6])){ // check that they are right
                swap(t[j], t[j+1]);
            }
        }
        //check which segments are covered by triangle

        bool previous = contains(t, path[0]); // first point
        for(int j = 1; j < m; j++){
            if(contains(t, path[j])){
                if(previous){
                    triangles[i].push_back(j-1); // covers segment i -> i+1
                } else {
                    previous = true;
                }
            } else {
                previous = false;
            } 
        }
    }
    Covered covered(m-1, 0); // which leg is covered #times
    int uncovered = m-1; // nr of uncovered elements
    int best_nr = n; // how many map parts do we need?
    int ind_b = 0, ind_e = 0;
    while(ind_b < n){
        // ensure covering
        while(uncovered && ind_e < n){
            for(CCI j = triangles[ind_e].begin(); j!= triangles[ind_e].end(); j++){
                covered[*j]++;
                if(covered[*j] == 1) uncovered--; //first time covered, we can removce it fom uncovered counter
            }
            ind_e++;
        }
        if(uncovered != 0) break; // covering property broken, stop
        // can we remove triangle b ?
        do{
            for(CCI j = triangles[ind_b].begin(); j != triangles[ind_b].end(); j++){
                covered[*j]--;
                if(covered[*j] == 0) uncovered++; // uncovered property broken
            }
        } while (++ind_b != ind_e && uncovered == 0);
        best_nr = min(best_nr, ind_e - ind_b + 1);
    }
    cout << best_nr << "\n";
}

int main(){
    int t; cin >> t;
    for (int i = 0; i < t ; i++){
        testrun();
    }
}