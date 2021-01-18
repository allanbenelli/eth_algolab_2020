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
        Program lp(CGAL::SMALLER, true, 0, false, 0);

        for(int i = 0; i < n; ++i){
            // n nutrients
            int n_min, n_max; cin >> n_min >> n_max;
            lp.set_b(i, n_max);
            lp.set_b(i+n, -n_min);
        }

        for(int j = 0; j < m; ++j){
            // j = food, #foods = m
            int cost; cin >> cost;
            lp.set_c(j, cost);
            for(int i = 0; i < n; ++i){
                // amount of nutrient per food
                int food_n; cin >> food_n;
                lp.set_a(j, i, food_n);
                lp.set_a(j, i+n, -food_n);
            }
        }

        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()) cout << "No such diet.\n";
        else cout << floor(CGAL::to_double(s.objective_value())) << "\n";
        cin >> n >> m;
    }
    
}