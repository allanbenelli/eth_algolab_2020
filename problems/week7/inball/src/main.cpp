#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void run(int n, int d){
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    for(int i = 0; i < n; ++i){
        int sum = 0;
        for(int j = 0; j < d; ++j){
            int a; cin >> a;
            lp.set_a(j, i, a);
            sum += a*a;
        }
        int norm = sqrt(sum);
        lp.set_a(d, i, norm);
        int b; cin >> b;
        lp.set_b(i, b);
    }
    lp.set_c(d, -1);
    lp.set_l(d, true, 0);

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) cout << "none\n";
    else if(s.is_unbounded()) cout << "inf\n";
    else cout << floor(CGAL::to_double(-s.objective_value())) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int n, d; cin >> n >> d;
    while(n!=0){
        run(n,d);
        cin >> n >> d;
    }
}