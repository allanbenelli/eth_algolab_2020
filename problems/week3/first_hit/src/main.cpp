#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <limits>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel IK;
typedef IK::Point_2 P;
typedef IK::Segment_2 S;
typedef IK::Ray_2 R;
typedef result_of<IK::Intersect_2(R, S)>::type IT;

double floor_to_double(const IK::FT& x){ // given in tutorial
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a + 1 <= x) a += 1;
    return a;
}


void cut_ray(IK::Segment_2& s, const IT& o) {
    if (const IK::Point_2* p = boost::get<IK::Point_2>(&*o))
        s = IK::Segment_2(s.source(), *p);
    else if (const IK::Segment_2* t = boost::get<IK::Segment_2>(&*o))
        // select endpoint of *t closer to s.source()
        if (CGAL::collinear_are_ordered_along_line(s.source(), t->source(), t->target()))
            s = IK::Segment_2(s.source(), t->source());
        else
            s = IK::Segment_2(s.source(), t->target());
    else
        throw std::runtime_error("Strange␣segment␣intersection.");
}

void shorten_segment(S& cutted_ray, const IT& cutting_point){
    if(const P* op = boost::get<P>(&*cutting_point)){
        cutted_ray = S(cutted_ray.source(), *op);
    } else if(const S* seg = boost::get<S>(&*cutting_point)){
        //check if they are overlapping and decide which one to choose
        if(CGAL::collinear_are_ordered_along_line(cutted_ray.source(), seg->source(), seg->target())){
            cutted_ray = S(cutted_ray.source(), seg->source());
        }else{
            cutted_ray = S(cutted_ray.source(), seg->target());
        }
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    int n;
    long x, y, a, b, r, s, t, u;
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin >> n;
    while(n!=0){
        cin >> x >> y >> a >> b;
        R ray(P(x,y), P(a,b));
        vector<S> segments;
        segments.reserve(n);
        for(int i = 0; i < n; i++){
            cin >> r >> s >> t >> u;
            S seg(P(r,s), P(t,u));
            segments.push_back(seg);
        }
        random_shuffle(segments.begin(), segments.end());
        S cutted_ray(ray.source(), ray.point(1)); // initialize

        int i = 0;
        for(;i < n; i++){ // search first intersection
            if(CGAL::do_intersect(segments[i], ray)){ // take all the ray
                cut_ray(cutted_ray, CGAL::intersection(segments[i], ray));
                break;
            }
        }
        if(i == n) {
            cout << "no" << "\n";
        } else {
            while(++i < n){
                if(CGAL::do_intersect(segments[i], cutted_ray)){ // take cutted one
                    cut_ray(cutted_ray, CGAL::intersection(segments[i], ray)); // intersection with ray function
                }
            }
            cout << floor_to_double(cutted_ray.target().x()) << " " << floor_to_double(cutted_ray.target().y()) << "\n";        
        }
        cin >> n;
    }
}
