#include <iostream>
#include <vector>
#include <array>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

typedef vector<vector<int>> VVI;
typedef vector<vector<CGAL::Gmpz>> VVGMPZ;
typedef vector<VVGMPZ> VVVI;

void run(){
    int h, t; cin >> h >> t;
    const int total = h+t;
    VVI cells(total, vector<int>(3));
    for(int i = 0; i < total; ++i){
          cin >> cells[i][0]; 
          cin >> cells[i][1]; 
          cin >> cells[i][2]; 
    }
    vector<vector<vector<CGAL::Gmpz>>> powers(total, vector<vector<CGAL::Gmpz>>(31, vector<CGAL::Gmpz>(3)));
    int sol = -1;
    CGAL::Quadratic_program_options options;
    options.set_pricing_strategy(CGAL::QP_BLAND);
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    lp.set_l(0, true, 0);
    lp.set_c(0, -1);
    for(int deg = 0; deg <= 30; deg++){
        for(int i = 0; i < total; ++i){
            const int sign = i < h ? 1 : -1;
            const int x = cells[i][0];
            const int y = cells[i][1];
            const int z = cells[i][2];
            if(deg == 0){
                powers[i][deg][0] = 1;
                powers[i][deg][1] = 1;
                powers[i][deg][2] = 1;
            } else {
                powers[i][deg][0] = powers[i][deg-1][0] * x;
                powers[i][deg][1] = powers[i][deg-1][1] * y;
                powers[i][deg][2] = powers[i][deg-1][2] * z;
            }
            lp.set_a(0, i, 1);
            int param = 1;
            for(int a = 0; a <= deg; a++){
                for(int b = 0; b <= deg - a; b++){
                    for(int c = 0; c <= deg - b -a; c++){
                        lp.set_a(param++, i, sign*powers[i][a][0]*powers[i][b][1]*powers[i][c][2]);
                    }
                }
            }
        }
        Solution s = CGAL::solve_linear_program(lp, ET(), options);
        if(s.is_unbounded()){
            sol = deg;
            break;
        }
    }
    if(sol == -1) cout << "Impossible!\n"; 
    else cout << sol << "\n";


}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) run();   
}