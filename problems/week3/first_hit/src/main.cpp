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
typedef result_of<IK::Intersect_2(R,S)>::type IT;

double floor_to_double(const IK::FT& x){ // given in tutorial
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a + 1 <= x) a += 1;
    return a;
}

void shortenSeg(IK::Segment_2& s, const IT& o){
    if(const P* op = boost::get<P>(&*o)){
        s = S(s.source(), *op);
    } else if (const S* os = boost::get<S>(&*o)){
        if( CGAL::collinear_are_ordered_along_line(s.source(), os->source(), os->target())){
            s = S(s.source(), os->source());
        } else {
            s = S(s.source(), os->target());
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
        for(; i < n; ++i){
            if(CGAL::do_intersect(ray, segments[i])){
                shortenSeg(cutted_ray, CGAL::intersection(ray, segments[i]));
                break;
            }
        }
        if(i == n) cout << "no\n";
        else{
            while(++i < n){
                if(CGAL::do_intersect(cutted_ray, segments[i])){
                    shortenSeg(cutted_ray, CGAL::intersection(ray,segments[i]));
                }
            }
            cout << floor_to_double(cutted_ray.target().x()) << " " << floor_to_double(cutted_ray.target().y()) << "\n";
        }
        cin >> n;
    }
}
