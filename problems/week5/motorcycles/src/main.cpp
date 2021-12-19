#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;

struct bikerT{
    R ray;
    int i;
    K::FT slope;
};

bool sortByInt(bikerT &b1, bikerT &b2){
    return b1.i < b2.i;
}

bool sortDescByY(bikerT &b1, bikerT &b2){
    return b1.ray.source().y() > b2.ray.source().y();
}


void testcase(){
    int n; cin >> n;
    vector<bikerT> bikers; bikers.reserve(n);
    for(int i = 0; i < n; ++i){
        long y0, x1, y1; cin >> y0 >> x1 >> y1;
        bikerT biker({R(P(0,y0), P(x1,y1)), i, K::FT(y1-y0)/ K::FT(x1)});
        bikers.push_back(biker);
    }

    sort(bikers.begin(), bikers.end(), sortDescByY);

    vector<bikerT> sunSet; sunSet.push_back(bikers[0]);
    K::FT best_slope = bikers[0].slope;
    for(int i = 1; i < n; ++i){
        if(bikers[i].slope <= best_slope){
            sunSet.push_back(bikers[i]);
            best_slope = bikers[i].slope;
            continue;
        }
        if(CGAL::abs(bikers[i].slope) <= CGAL::abs(best_slope)){
            int check = sunSet.size();
            while(check && CGAL::do_intersect(bikers[i].ray, sunSet[check-1].ray) && CGAL::abs(bikers[i].slope) <= CGAL::abs(best_slope)) check--;
            sunSet.erase(sunSet.begin()+check, sunSet.end());
            if (check == 0 || bikers[i].slope <= sunSet[check-1].slope){
                sunSet.push_back(bikers[i]);
                best_slope = bikers[i].slope;
            }
        }
    }
    sort(sunSet.begin(), sunSet.end(), sortByInt);
    for(auto t: sunSet){
        cout << t.i << " ";
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) testcase();      
}