#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Min_circle_2_traits_2<IK>  IK_Traits;
typedef CGAL::Min_circle_2<IK_Traits>      IK_Min_circle;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt   EK;
typedef CGAL::Min_circle_2_traits_2<EK>  EK_Traits;
typedef CGAL::Min_circle_2<EK_Traits>      EK_Min_circle;

double ceil_to_double(const EK::FT& x){
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

void testcase(int n){
    vector<IK::Point_2> citizens;
    for(int i = 0; i < n; ++i){
        long x,y; cin >> x >> y;
        citizens.push_back(IK::Point_2(x,y));
    }
    IK_Min_circle mc(citizens.begin(), citizens.end(), true);
    //IK_Traits::Circle c = mc.circle();
    vector<EK::Point_2> supp_p;
    supp_p.reserve(mc.number_of_support_points());
    for(auto it = mc.support_points_begin(); it != mc.support_points_end(); ++it){
        supp_p.push_back(EK::Point_2(it->x(), it->y()));
    }
    EK_Min_circle new_mc(supp_p.begin(), supp_p.end(), true);
    EK_Traits::Circle c = new_mc.circle();
    cout << ceil_to_double(CGAL::sqrt(c.squared_radius())) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int n; cin >> n;
    while(n>0){
        testcase(n);
        cin >> n;
    }    
}