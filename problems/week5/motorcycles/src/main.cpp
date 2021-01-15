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
typedef tuple<R, int, K::FT> ray_int_slope;


bool sort_bikers_start(const ray_int_slope &i, const ray_int_slope &j){
    return get<0>(i).source().y() > get<0>(j).source().y();
}

bool sort_bikers_index(const ray_int_slope &i, const ray_int_slope &j){
    return get<1>(i) < get<1>(j);
}

void testcase(){
    int n; cin >> n;
    vector<ray_int_slope> bikers; bikers.reserve(n);
    for(int i = 0; i < n; ++i){
        long y0, x1, y1; cin >> y0 >> x1 >> y1;
        R ray(P(0,y0), P(x1, y1));
        K::FT slope = (K::FT(y1-y0)) / K::FT(x1);
        bikers.push_back(make_tuple(ray, i, slope));
        
    }
    sort(bikers.begin(), bikers.end(), sort_bikers_start);
    vector<ray_int_slope> sunshine;
    ray_int_slope best_slope = bikers[0];
    sunshine.push_back(best_slope);
    for(int i = 1; i < n; ++i){
        if(get<2>(bikers[i])<=get<2>(best_slope)){
            sunshine.push_back(bikers[i]);
            best_slope = bikers[i]; 
            continue; // we have no problem with this slope,
        }
        if(CGAL::abs(get<2>(bikers[i]))<=CGAL::abs(get<2>(best_slope))){ // check how much of the previous are faulty and then remove them
            int check = sunshine.size();
            while(check && CGAL::do_intersect(get<0>(bikers[i]), get<0>(sunshine[check-1])) && CGAL::abs(get<2>(bikers[i])) <= CGAL::abs(get<2>(sunshine[check-1]))) check--;
            sunshine.erase(sunshine.begin()+check, sunshine.end());
            if(check == 0 || get<2>(bikers[i]) <= get<2>(sunshine[check-1])){
                best_slope = bikers[i];
                sunshine.push_back(best_slope);
            }
        }
    }
    sort(sunshine.begin(), sunshine.end(), sort_bikers_index);
    for(ray_int_slope res:sunshine){
        cout << get<1>(res) << " ";
    }
    cout <<"\n";
        
}
int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) testcase();      
}