#include <iostream>
#include <iomanip>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Min_circle_2_traits_2<IK> IK_Traits;
typedef CGAL::Min_circle_2<IK_Traits> IK_Min_circle;
typedef IK::Point_2 IK_P;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> K_Traits;
typedef CGAL::Min_circle_2<K_Traits> K_Min_circle;
typedef K::Point_2 K_P;

double ceil_to_double(const K::FT& x){ // given in tutorial
    double a = ceil(CGAL::to_double(x));
    while (a - 1 >= x) a -= 1;
    while (a  < x) a += 1;
    return a;
}
void testcase(int n){
    vector<IK_P> points(n);
    for(int i = 0; i < n; i++){
        long x, y;
        cin >> x >> y;
        points[i] = IK_P(x,y);
    }
    IK_Min_circle mc(points.begin(), points.end(), true);

    //time
    vector<K_P> new_points;
    new_points.reserve(mc.number_of_support_points());
    for(auto it = mc.support_points_begin(); it!=mc.support_points_end(); ++it ){
        long x = it->x(); long y = it->y();
        new_points.push_back(K_P(x,y));
    }

    K_Min_circle new_mc(new_points.begin(), new_points.end(), true);
    K_Traits::Circle c = new_mc.circle();
    
    K::FT radius = CGAL::sqrt(c.squared_radius());

    cout << ceil_to_double(radius) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);

    int n; cin >> n;
    while(n>0){
        testcase(n);
        cin >> n;
    }    
}