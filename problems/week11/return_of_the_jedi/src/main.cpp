#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;

struct edge {
    int u, v, c, i;
    bool in_mst;
};
bool mySort(const edge & e1, const edge & e2){
    return e1.c < e2.c;
}

int get_cost(int n, int skipped, vector<edge> &edges){
    boost::disjoint_sets_with_storage<> uf(n);
    int cost_sum = 0;
    for (auto &e: edges){
        if (e.i == skipped) continue;

        int component1 = uf.find_set(e.u);
        int component2 = uf.find_set(e.v);
        if(component1 != component2){
            if (skipped == -1) e.in_mst = true;
            uf.link(component1, component2);
            cost_sum += e.c;
            if(--n == 1) break;
        }
    }
    return cost_sum;
}

void run(){
    int n, i; cin >> n >> i;
    vector<edge> edges;
    int index = 0;
    for(int u = 0; u < n-1; ++u){
        for(int v = u+1; v <n; ++v){
            int c; cin >> c;
            edges.push_back({u,v,c,index++,false});
        }
    }
    sort(edges.begin(), edges.end(), mySort);
    get_cost(n, -1, edges);

    int min_non_mst_cost = INT_MAX;
    for(auto &e : edges){
        if (e.in_mst){
            int cost = get_cost(n, e.i, edges);
            min_non_mst_cost = min(min_non_mst_cost, cost);
        }
    }
    cout << min_non_mst_cost << endl;

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--){
        run();
    }
    
}
