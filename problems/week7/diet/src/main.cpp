#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;



int main(){
    ios_base::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    while (n != 0 && m != 0)
    {
        Program lp (CGAL::SMALLER, true, 0, false, 0);
        for(int i = 0; i < n; ++i){
            int min_i, max_i; cin >> min_i >> max_i;
            lp.set_b(i, -min_i);
            lp.set_b(n+i, max_i);
        }
        for(int i = 0; i < m; ++i){
            int c; cin >> c;
            for(int j = 0; j < n; ++j){
                int n_j; cin >> n_j;
                lp.set_a(i, j, -n_j);
                lp.set_a(i, n+j, n_j);
            }
            lp.set_c(i, c);
        }
        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()) cout << "No such diet.\n";
        else cout << floor(CGAL::to_double(s.objective_value())) << "\n";
        cin >> n >> m;
    }
    
}