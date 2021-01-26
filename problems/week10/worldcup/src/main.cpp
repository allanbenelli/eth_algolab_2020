#include <iostream>
#include <vector>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;

// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;

using namespace std;

double floor_to_double(const SolT& x){
  double a = std::floor(CGAL::to_double(x));
    while (a+1 <= x) a += 1;
  while (a > x) a -= 1;
  return a;
}

void run(){
    int n, m, c; cin >> n >> m >> c;
    Program lp (CGAL::SMALLER, true, 0, false, 0);
    vector<P> pos_w; pos_w.reserve(n);
    vector<P> pos_s; pos_s.reserve(m);

    for(int i = 0; i < n; ++i){
        long x, y, s, a; cin >> x >> y >> s >> a;
        pos_w.push_back(P(x,y));
        lp.set_b(i, s);
        for(int j = 0; j < m; ++j){
            lp.set_a(i*m+j, i, 1); //limit supply
            lp.set_a(i*m+j, n+j, a); // limit alcohol
            lp.set_a(i*m+j, n+m+j, 1); //equals liter
        }
    }
    for(int j = 0; j < m; ++j){
        long x, y, d, u; cin >> x >> y >> d >> u;
        pos_s.push_back(P(x,y));

        lp.set_b(n+j, 100.0*u); // limit alcohol
        lp.set_b(n+m+j, d);
        lp.set_r(n+m+j, CGAL::EQUAL);
    }
    vector<vector<double>> rev(n, vector<double>(m,0));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> rev[i][j];
        }
    }
    Triangulation t;
    t.insert(pos_w.begin(), pos_w.end());
    t.insert(pos_s.begin(), pos_s.end());

    for(int i = 0; i < c; ++i){
        long x, y, r; cin >> x >> y >> r;
        P pnt(x,y);
        long sqr_r = r*r;
        
        auto v = t.nearest_vertex(pnt);
        if(CGAL::squared_distance(v->point(), pnt) >= sqr_r) continue;

        for(int j = 0; j < n; ++j){
            bool w_in = CGAL::squared_distance(pos_w[j],pnt)<=sqr_r;
            for(int k = 0; k < m; ++k){
                bool s_in = CGAL::squared_distance(pos_s[k],pnt)<=sqr_r;
                if(w_in != s_in){
                    rev[j][k] -= 0.01;
                }
            }
        }
    }   

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; j++){
            lp.set_c(i*m+j, -rev[i][j]); // minimize it
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) cout << "RIOT!\n";
    else{
        cout << floor_to_double(-s.objective_value()) << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int t; cin >> t;
    while(t--) run();
}