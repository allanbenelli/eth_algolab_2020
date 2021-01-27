#include <iostream>
#include <vector>
#include <algorithm>
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

long round_to_long(const CGAL::Quotient<ET> & x){
  double y = std::ceil(CGAL::to_double(x));
  while(y < x) y++;
  while(y-1 >= x) y--;
  return (long) y;
}

void run(){
    int n, m; long S; std::cin >> n >> m >> S;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    IT x_sum = 0, y_sum = 0;
    const int b = 0;
    const int c_s = 1;
    const int c_w = 2;
    const int d = 3;
    std::vector<std::pair<int,int>> noble; noble.reserve(n);
    std::vector<std::pair<int,int>> common; common.reserve(m);

    int row= 0;
    for(int i = 0; i < n; ++i){
        int x,y; std::cin >> x >> y;
        //use a != 0 and take x to the other side
        lp.set_b(row, -x);
        lp.set_a(b, row, -y);
        lp.set_a(c_s, row, -1);
        x_sum -= x; y_sum +=y;
        row++;
        // perpendicular canals -> <(a_w, b_w), (a_s,b_s)> = 0 with a_s = -1
            // Using a_s = -1 we obtain: -a_w + b_w*b_s = 0
    // Thus: a_w = 1 and b_w = 1/b_s.
    // Inserting those results back into the line equation we obtain: x + 1/b_s*y + c = 0, which translates to c' - b_s*x = y with c' = -b_s*c
    // To minimize the length of the longest water pipe we minimize the distance d such that all houses are containined
    // in the interval defined by c' - b_s*x - d ≤ y and c' - b_s*x + d ≥ y
    // copied from Sebastien Foucher
        lp.set_a(b, row,x);
        lp.set_a(c_w, row, 1);
        lp.set_a(d, row, -1);
        lp.set_b(row,-y);
        row++;

        lp.set_a(b, row, -x);
        lp.set_a(c_w, row, -1);
        lp.set_a(d, row, -1);
        lp.set_b(row, y);
        row++;


    }
    for(int i = 0; i < m; ++i){
        int x,y; std::cin >> x >> y;
        lp.set_b(row, x);
        lp.set_a(b, row, y);
        lp.set_a(c_s, row, 1);
        common.push_back({x,y});
        x_sum += x; y_sum -=y;

        row++;
        
        lp.set_a(b, row,x);
        lp.set_a(c_w, row, 1);
        lp.set_a(d, row, -1);
        lp.set_b(row,-y);
        row++;

        lp.set_a(b, row, -x);
        lp.set_a(c_w, row, -1);
        lp.set_a(d, row, -1);
        lp.set_b(row, y);
        row++;
    }
    lp.set_c(d,1);

    lp.set_l(d, true, 0);

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()){
        std::cout << "Yuck!\n";
    } else {
        if(S == -1){
            std::cout << round_to_long(s.objective_value()) << "\n";
        }
        else{
            lp.set_a(b, row, y_sum); lp.set_a(c_s, row, n-m); lp.set_b(row, S-x_sum);
            s = CGAL::solve_linear_program(lp, ET());
            if(s.is_infeasible())
            std::cout << "Bankrupt!\n";
            else std::cout << round_to_long(s.objective_value()) << "\n";
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) run();
}