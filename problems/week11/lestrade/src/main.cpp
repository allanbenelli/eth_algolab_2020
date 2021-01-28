#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
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

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;


struct gangInfo{
    int u, v, w;
};


void run(){
    int feeHolmes, where, who, how; cin >> feeHolmes >> where >> who >> how;
    int a, g; cin >> a >> g;
    vector<pair<K::Point_2, int>> g_loc(g);
    vector<gangInfo> g_info(g);
    for(int i = 0; i < g; ++i){
        int x, y, u, v, w; cin >> x >> y >> u >> v >> w;
        g_loc[i] = make_pair(K::Point_2(x,y), i);
        g_info[i] = {u,v,w};
    }
    Delaunay t;
    t.insert(g_loc.begin(), g_loc.end());

    vector<int> gang_cost(g, 1025);
    for(int i = 0; i < a; ++i){
        int x, y, z; cin >> x >> y >> z;
        K::Point_2 pos(x,y);
        int neareast = t.nearest_vertex(pos)->info();
        gang_cost[neareast] = min(z, gang_cost[neareast]);
    }

    Program lp(CGAL::LARGER, true, 0, true, 24);

    int agent = 0;
    for(int i = 0; i < g; ++i){
        if(gang_cost[i] > 1024) continue;

        lp.set_a(agent, 0, g_info[i].u);
        lp.set_a(agent, 1, g_info[i].v);
        lp.set_a(agent, 2, g_info[i].w);

        lp.set_c(agent, gang_cost[i]);
        agent++;
    }
    lp.set_b(0, where);
    lp.set_b(1, who);
    lp.set_b(2, how);

    Solution sol = CGAL::solve_linear_program(lp, ET());

    if(sol.is_infeasible() || sol.objective_value() > feeHolmes){
        cout << "H\n";
    } else cout << "L\n";

    
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) run();
}