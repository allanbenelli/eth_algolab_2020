#include <iostream>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run(){
    IT x, y; int n; cin >> x >> y >> n;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    const int X = 0;
    const int Y = 1;
    const int T = 2;
    for(int i = 0; i < n; ++i){
        IT a, b, c, v; cin >> a >> b >> c >> v;
        const int sign = a*x+b*y+c > 0 ? 1 : -1;
        IT det = sqrt(a*a + b*b);
        lp.set_a(X, i, -sign*a); lp.set_a(Y, i, -sign*b); lp.set_a(T, i, det*v); 
        lp.set_b(i, sign*c);
    }
    lp.set_l(T, true, 0);
    lp.set_c(T, -1);
    Solution s = CGAL::solve_linear_program(lp, ET());
    cout << floor(CGAL::to_double(-s.objective_value())) << "\n";

}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) run();
}