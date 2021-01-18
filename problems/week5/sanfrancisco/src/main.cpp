#include <iostream>
#include <vector>

using namespace std;

typedef vector<long> VI;
typedef vector<VI> VVI;

long calc_max(VVI &memo, const vector<vector<pair<int,int>>> & holes, int pos, int moves){
    if(moves == 0) return 0; // no moves left
    if(memo[pos][moves] != -1) return memo[pos][moves]; // already calculated
    if(holes[pos].size() == 0) return calc_max(memo, holes, 0, moves); //leaf, go back to start (no move)
    long best = 0;
    for(auto c : holes[pos]){
        best = max(best, calc_max(memo, holes, c.first, moves - 1)+ c.second);
    }
    memo[pos][moves] = best;
    return best;
}

void testcase(){
    int n, m, k; long x; cin >> n >> m >> x >> k;
    vector<vector<pair<int,int>>> holes(n);
    for(int i = 0; i < m; i++){
        int u, v, p; cin >> u >> v >> p;
        holes[u].push_back(make_pair(v, p));
    }
    VVI memo(n, VI(k+1, -1));
    long max_score = calc_max(memo, holes, 0, k);
    if(max_score < x) {cout << "Impossible" << "\n";}
    else{
        int l = 1;
        int r = k;
        while(l != r){
            int m = (l+r)/2;
            if(calc_max(memo, holes, 0, m) < x){ // can wee reach it with m moves?
                l = m + 1; // we need more moves
            } else r = m; // we don't need that much moves
        }
        cout << l << "\n";
    }
    
}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){testcase();}
}