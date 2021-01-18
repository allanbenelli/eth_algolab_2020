#include <iostream>
// example: how to solve a simple explicit LP
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

typedef CGAL::Quotient<ET> SolT;

using namespace std;


double floor_to_double(const SolT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

double ceil_to_double(const SolT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  if(abs(a) == 0) a = 0;
  return a;
}




void run1(int a, int b){
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    const int X = 0; 
    const int Y = 1;
    lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);  //  x + y  <= 4
    lp.set_a(X, 1,  4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);  //  4x + 2y  <= ab
    lp.set_a(X, 2,  -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);  // - x + y  <= 1

    lp.set_c(Y, -b); lp.set_c(X, a); 

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) cout <<"no\n";
    else if(s.is_unbounded()) cout <<"unbounded\n";
    else cout << floor_to_double(-s.objective_value()) << "\n";
}
void run2(int a, int b){
    Program lp (CGAL::LARGER, false, 0, true, 0); 
    const int X = 0; 
    const int Y = 1;
    const int Z = 2;
    lp.set_a(X, 0,  1); lp.set_a(Y, 0, 1); lp.set_b(0, -4);  //  x + y  >= -4
    lp.set_a(X, 1,  4); lp.set_a(Y, 1, 2); lp.set_a(Z,1,1); lp.set_b(1, -a*b);  //  4x + 2y + z >= -ab
    lp.set_a(X, 2,  -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);  // - x + y  >= -1

    lp.set_c(X, a); lp.set_c(Y, b); lp.set_c(Z, 1);

    Solution s = CGAL::solve_quadratic_program(lp, ET());
    if(s.is_infeasible()) cout <<"no\n";
    else if(s.is_unbounded()) cout <<"unbounded\n";
    else cout << ceil_to_double(s.objective_value()) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    while(true){
        int p, a, b;
        cin >> p;
        if(p == 0) break;
        cin >> a >> b;
        if(p == 1){
            run1(a,b);
        } else {
            run2(a,b);
        }
    }
}