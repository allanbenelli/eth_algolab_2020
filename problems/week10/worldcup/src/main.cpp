#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;
typedef CGAL::Quotient<CGAL::Gmpq> SolT;

using namespace std;

double floor_to_double(const SolT& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void run(){
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    int n, m, c; cin >> n >> m >> c;
    vector<P> wpos; wpos.reserve(n);
    vector<P> spos; spos.reserve(m);
    for(int i = 0; i < n; i++){
        long x,y,s,a; cin >> x >> y >> s >> a;
        wpos.push_back(P(x,y));
        lp.set_b(i, s);
        for(int j = 0; j < m; j++){
            lp.set_a(i*m+j, i, 1);
            lp.set_a(i*m+j, n+j, a);
            lp.set_a(i*m+j, n+m+j, 1);
        }
    }
    for(int i = 0; i < m; i++){
        long x,y,d,u; cin >> x >> y >> d >> u;
        spos.push_back(P(x,y));
        lp.set_b(n+i, 100.0*u);
        lp.set_b(n+m+i, d);
        lp.set_r(n+m+i, CGAL::EQUAL);
    }
    vector<vector<double>> rev(n, vector<double>(m,0));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> rev[i][j];
        }
    }
    Triangulation t;
    t.insert(wpos.begin(), wpos.end());
    t.insert(spos.begin(), spos.end());
    for(int i = 0; i < c; ++i){
        long x,y,r; cin >> x >> y >> r;
        P pnt(x,y);
        long sqr_r = r*r;
        
        auto v = t.nearest_vertex(pnt);
        if(CGAL::squared_distance(v->point(), pnt) >= sqr_r) continue;
        for(int j = 0; j < n; ++j){
            bool w_in = CGAL::squared_distance(wpos[j], pnt) <= sqr_r;
            for(int k = 0; k < m; ++k){
                bool s_in = CGAL::squared_distance(spos[k], pnt) <= sqr_r;
                if(w_in!=s_in) rev[j][k] -= 0.01;
            }
        }
    }

    for(int i = 0; i <n; ++i){
        for(int j = 0; j<m; ++j){
            lp.set_c(i*m+j, -rev[i][j]);
        }
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()){
        cout << "RIOT!\n";
    } else {
        //cout << floor_to_double(-s.objective_value()) << "\n";
        for(auto it = s.variable_values_begin(); it != s.variable_values_end(); it++){
            cout << CGAL::to_double(*it) << " ";
        }
        cout  << s << endl;
    }

}

int main(){
    ios_base::sync_with_stdio(false);
        cout << fixed << setprecision(0);
    int t; cin >> t;
    while(t--) run();
}